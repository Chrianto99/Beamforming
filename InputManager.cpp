//
// Created by Christos on 5/4/2024.
//

#include "InputManager.h"
#include <iostream>

InputManager::InputManager(int users, int angles) : numberOfUsers(users), numberOfImaginaryAngles(angles) {}


std::vector<double> InputManager::generateInput(double start, double delta) {

    std::vector<double> inputAngles;

    for (int i = 0; i < numberOfUsers; ++i) {
        double angle = start + i * delta;
        inputAngles.push_back(angle);
    }

    return inputAngles;

}

void InputManager::defineAngleStep(int delta) {


    switch (delta) {

        case 8:
            angleStep = 5.9 ;
            start = 30;
            finish = 165;
            break;
        case 10:
            angleStep = 5 ;
            start = 30;
            finish = 160;
            break;
        case 12:
            angleStep = 4 ;
            start = 30;
            finish = 160;
            break;
        case 14:
            angleStep = 4.5 ;
            start = 30;
            finish = 160;
            break;
        case 16:
            angleStep =  4;
            start = 30;
            finish = 160;
            break;


    }
}


void InputManager::addImaginaryAngles(std::vector<double> &inputAngles, double delta) {

    defineAngleStep(delta);

    int counter = 0;// keeps track of number of imaginary angles
    double desiredAngle = inputAngles[0];

    // Sort input angles and find the index of the desired angle
    std::vector<double> inputAnglesSorted(numberOfUsers);
    std::copy_n(inputAngles.begin(), inputAngles.size(), inputAnglesSorted.begin());
    std::sort(inputAnglesSorted.begin(), inputAnglesSorted.end());
    auto idx = std::find(inputAnglesSorted.begin(), inputAnglesSorted.end(), desiredAngle);
    auto index = std::distance(inputAnglesSorted.begin(), idx);

    //Add imaginary nulls between users
    for (int i = 0; i < index - 1; ++i) {

         if (delta == 16 || delta == 14) {
            inputAngles.push_back(inputAnglesSorted[i] + delta / 4);
            ++counter;
        }

        inputAngles.push_back(inputAnglesSorted[i] + delta / 2);
        ++counter;
    }

    //Add imaginary nulls between users
    for (int i = index + 1; i < numberOfUsers - 1; ++i) {

        if (delta == 16 || delta == 14) {
            inputAngles.push_back(inputAnglesSorted[i] + delta / 4);
            ++counter;
        }
        inputAngles.push_back(inputAnglesSorted[i] + delta / 2);
        ++counter;
    }

    // Add the remaining angles
    if (inputAnglesSorted.back() + angleStep >= finish) {

        inputAngles.push_back(inputAnglesSorted.back() + start + angleStep - finish);
        ++counter;

    }
    else {
        inputAngles.push_back(inputAnglesSorted.back() + angleStep);
        ++counter;
    }
    while (counter < numberOfImaginaryAngles) {
        if (inputAngles.back() + angleStep >= finish) {

            inputAngles.push_back(inputAngles.back() + start + angleStep - finish);
            ++counter;
            continue;
        }

        inputAngles.push_back(inputAngles.back() + angleStep);
        ++counter;

    }




}





