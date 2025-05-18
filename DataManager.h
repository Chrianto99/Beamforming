//
// Created by Christos on 5/6/2024.
//

#ifndef BEAMFORMING_DATAMANAGER_H
#define BEAMFORMING_DATAMANAGER_H

#include <iostream>
#include <vector>
#include <map>
#include "NSB.h"

using VectorOfPairs = std::vector<std::pair<double, double>>;

class DataManager {


public:

    int numberOfElements;
    int numberOfUsers;

    DataManager(int elements,int users);

    std::vector<double> getData(RadiationPattern &radiationDiagram,std::vector<double> &inputAngles,double noisePower);


private:

    std::vector<double> calculateData(std::vector<double> &inputAngles, VectorOfPairs &MaxAndSideLobe, std::vector<double> &zeroes,
                       std::vector<double> &powerInUsersDirection, double noisePower);

    virtual std::vector<double> findZeroes(RadiationPattern &radiationPattern,VectorOfPairs &MaxAndSizeLobe);

    VectorOfPairs findMaxAndSideLobe(RadiationPattern &radiationPattern,std::vector<double> inputAngles);

    std::vector<double> findPowerInUsersDirection(RadiationPattern &radiationPattern, std::vector<double> &inputAngles);


    double calculateSINR(std::vector<double> &powerInUsersDirection, double &noisePower);




};


#endif //BEAMFORMING_DATAMANAGER_H
