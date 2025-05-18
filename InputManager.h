//
// Created by Christos on 5/4/2024.
//

#ifndef BEAMFORMING_INPUTMANAGER_H
#define BEAMFORMING_INPUTMANAGER_H


#include <vector>
#include <valarray>

class InputManager {

public:


    int numberOfUsers;
    int numberOfImaginaryAngles;
    double angleStep,start,finish;

    InputManager(int users, int angles);

    std::vector<double> generateInput(double start, double delta);

    void addImaginaryAngles(std::vector<double> &inputAngles, double delta);

    void addImaginaryAnglesHigh(std::vector<double> &inputAngles, double delta);

    void defineAngleStep(int delta);


};


#endif //BEAMFORMING_INPUTMANAGER_H
