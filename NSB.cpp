//
// Created by Christos on 5/4/2024.
//

#include <iostream>
#include <map>
#include <queue>
#include "NSB.h"


NSB::NSB(int elements, double beta_d) : numberOfElements(elements), beta_d(beta_d) {}

// Function to form the steering vector
ComplexMatrix NSB::calcWeightsNSB(std::vector<double> angles) {

    ComplexMatrix steeringMatrix(numberOfElements, angles.size());
    std::complex<double> z(0, 1);

    for (int row = 0; row < numberOfElements; ++row) {
        for (int col = 0; col < angles.size(); ++col) {

            double angleRadians = angles[col] * M_PI / 180;

            std::complex<double> exponent = std::exp((double) row * z * beta_d * std::cos(angleRadians));
            steeringMatrix(row, col) = exponent;  // Fill the matrix with computed values
        }
    }

    steeringMatrix = steeringMatrix.inverse().transpose();

    Weights weights = steeringMatrix.col(0);


    return weights.normalized();

}

RadiationPattern NSB::createRadiationPattern(Weights weights, double step) {

    double theta = 0;
    std::complex<double> z(0, 1);
    struct RadiationPattern radPattern;
    while (theta <= 180) {
        std::complex<double> signal(0.0, 0.0);
        for (int j = 0; j < numberOfElements; ++j) {
            double thetaRadians = theta * EIGEN_PI / 180;
            std::complex<double> exponent = std::exp((double) j * z * beta_d * std::cos(thetaRadians));
            signal += (weights[j] * exponent);

        }


        radPattern.data.emplace_back(theta, abs(signal));

        theta = theta + step;

    }


    radPattern.step = step;

    return radPattern;
}




