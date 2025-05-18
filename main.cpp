#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <map>
#include "NSB.h"
#include "InputManager.h"
#include "DataManager.h"


using ComplexMatrix = Eigen::Matrix<std::complex<double>, Eigen::Dynamic, Eigen::Dynamic>;
using Weights = Eigen::Matrix<std::complex<double>, 1, Eigen::Dynamic>;

int main() {

    int numberOfUsers = 6;
    int numberOfElements = 24;
    int numberOfImaginaryAngles = 18;
    double beta_d = M_PI;



    double step = 0.1;

    NSB *nsb = new NSB(numberOfElements, beta_d);
    InputManager *inputManager = new InputManager(numberOfUsers, numberOfImaginaryAngles);
    DataManager *dataManager = new DataManager(numberOfElements, numberOfUsers);

    double quality_factor = 0;

//    std::ofstream outputFile("C:/Users/Christos/Documents/MATLAB/Beamforming/radationPattern.txt");
    for (double SNR = -10; SNR <= 20; SNR += 10) {
        double noisePower = pow(10, 0.1 * (0 - SNR));
        for (double delta = 8; delta <= 16; delta += 2) {
            std::ofstream outputFile("data" + std::to_string((int)SNR) + "-" +
                                     std::to_string((int)delta) + ".txt");
            for (double start = 30; start < 180 - 5 * delta; ++start) {

                for (int i = 0; i < numberOfUsers; ++i) {



                    std::vector<double> inputAngles = inputManager->generateInput(start, delta);
                    if (i > 0) {
                        std::swap(inputAngles[0], inputAngles[i]);
                    }

                    inputManager->addImaginaryAngles(inputAngles, delta);


                    RadiationPattern radiationPattern;
                    Weights weights = nsb->calcWeightsNSB(inputAngles);
                    radiationPattern = nsb->createRadiationPattern(weights, step);


                    std::vector<double> data = dataManager->getData(radiationPattern, inputAngles, noisePower);
                    for (int j = 0; j < data.size(); ++j) {
                        std::cout << data[j] << " , ";
                        outputFile << data[j] << " ";

                    }
                    outputFile << std::endl;
                    std::cout << std::endl;
                    quality_factor += data.back();



                }

            }
            outputFile.close();
        }
    }


std::cout << "quality_factor:" << quality_factor;




}
