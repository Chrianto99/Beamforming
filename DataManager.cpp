//
// Created by Christos on 5/6/2024.
//

#include <algorithm>
#include <cmath>
#include "DataManager.h"
//#include "GeneralUseFunctions.h"
#include "algorithm"
#include <limits>

DataManager::DataManager(int elements, int users) : numberOfElements(elements), numberOfUsers(users) {}

struct CompareSecond {
    bool operator()(const std::pair<double, double>& left, const std::pair<double, double>& right) const {
        return left.second < right.second;
    }
};

std::vector<double>
DataManager::getData(RadiationPattern &radiationDiagram, std::vector<double> &inputAngles, double noisePower) {

    std::vector<double> data;
    // find Max Angle and SideLobeLevel
    VectorOfPairs MaxAndSideLobe = findMaxAndSideLobe(radiationDiagram, inputAngles);

    // find the null angles
    std::vector<double> zeroes = findZeroes(radiationDiagram,MaxAndSideLobe);
    if (zeroes.size() == 0){
        for (int i = 0; i < 12; ++i) {
            data.push_back(180);
        }
        data.push_back(-250);
        data.push_back(-250);
        return data;
    }

    // find power in the intended directions
    std::vector<double> powerInUsersDirection = findPowerInUsersDirection(radiationDiagram, inputAngles);
    //Calculate errors , SINR  and sideLobeLevel
    data = calculateData(inputAngles, MaxAndSideLobe, zeroes, powerInUsersDirection, noisePower);

    data.push_back(10*std::log(radiationDiagram.data[10*inputAngles[0]].second/MaxAndSideLobe[1].second));

    return data;


}


std::vector<double>
DataManager::calculateData(std::vector<double> &inputAngles, VectorOfPairs &MaxAndSideLobe, std::vector<double> &zeroes,
                           std::vector<double> &powerInUsersDirection, double noisePower) {
    std::vector<double> data;
    for (int i = 0; i < numberOfUsers; ++i) {
        data.push_back(inputAngles[i]);
    }
    //calculateDesiredAngle error
    double desiredAngle = inputAngles[0];
    double errorMax = abs(MaxAndSideLobe[0].first - desiredAngle);
    if (errorMax < 0.1) errorMax = 0;
    data.push_back(errorMax);

    //calculate null errors
    std::vector<double> realAngles(numberOfUsers - 1);
    std::copy_n(inputAngles.begin() + 1, numberOfUsers - 1, realAngles.begin());

    for (int i = 0; i < realAngles.size() ; ++i) {
        std::vector<double> errors;
        for (int j = 0; j < zeroes.size() ; ++j) {


            errors.push_back(abs(zeroes[j] - realAngles[i]));
        }
        auto error = std::min_element(errors.begin(),errors.end());
        if (*error < 0.1){
            *error = 0;
        }
        data.push_back(*error);

    }


    //SINR
    double SINR = calculateSINR(powerInUsersDirection, noisePower);
    data.push_back(SINR);



    return data;


}

std::vector<double>
DataManager::findZeroes(RadiationPattern &radiationPattern,VectorOfPairs &MaxAndSizeLobe) {

    std::vector<double> zeroes;

    for (int i = 0; i < radiationPattern.data.size(); ++i) {
        if (MaxAndSizeLobe[0].second > 1000 * radiationPattern.data[i].second){
            zeroes.push_back(radiationPattern.data[i].first);

        }
    }

    return zeroes;


}

VectorOfPairs
DataManager::findMaxAndSideLobe(RadiationPattern &radiationPattern, std::vector<double> inputAngles) {

    VectorOfPairs maxAndSideLobe;
    auto max = std::max_element(radiationPattern.data.begin(),radiationPattern.data.end(),CompareSecond());
    maxAndSideLobe.push_back(*max);
    std::vector<double> searchPoints;
    double maxAgle = max->first;

    for (int i = 1/radiationPattern.step * maxAgle - 1; i > 0 ; --i) {

        if (radiationPattern.data[i - 1].second > radiationPattern.data[i].second){
            searchPoints.push_back(i);
            break;
        }

    }
    for (int i = 1/radiationPattern.step * maxAgle + 1; i < 180/radiationPattern.step ; ++i) {


        if (radiationPattern.data[i + 1].second > radiationPattern.data[i].second){
            searchPoints.push_back(i);
            break;
        }

    }

    auto max1 = std::max_element(radiationPattern.data.begin(),radiationPattern.data.begin() + searchPoints[0],CompareSecond());
    auto max2 = std::max_element(radiationPattern.data.begin() + searchPoints[1],radiationPattern.data.end(),CompareSecond());

    if (max1->second > max2->second) {
        maxAndSideLobe.push_back({max1->first,max1->second});
    }
    maxAndSideLobe.push_back({max2->first,max2->second});

    std::cout << maxAndSideLobe.size()<< " ";


    return maxAndSideLobe;
}

std::vector<double>
DataManager::findPowerInUsersDirection(RadiationPattern &radiationPattern, std::vector<double> &inputAngles) {
    std::vector<double> powerVector;
    for (int i = 0; i < numberOfUsers; ++i) {
        int index = inputAngles[i] / radiationPattern.step;
        powerVector.push_back(radiationPattern.data[index].second);
    }


    return powerVector;


}

double
DataManager::calculateSINR(std::vector<double> &powerInUsersDirection, double &noisePower) {

    double signalPower = powerInUsersDirection[0];

    double interference = 0;
    for (int i = 1; i < powerInUsersDirection.size(); ++i) {
        interference += powerInUsersDirection[i];

    }

    double SINR = 10 * log(signalPower / (interference + noisePower));

    return SINR;
}








