//
// Created by Christos on 5/4/2024.
//

#ifndef BEAMFORMING_NSB_H
#define BEAMFORMING_NSB_H
#include "Eigen/Dense"

using ComplexMatrix = Eigen::Matrix<std::complex<double>, Eigen::Dynamic, Eigen::Dynamic>;
using Weights = Eigen::Matrix<std::complex<double>, 1 , Eigen::Dynamic>;

struct RadiationPattern {
    std::vector<std::pair<double,double>> data;
    double step;

};
class NSB {

public:

    int numberOfElements;
    double beta_d;

    NSB(int elements,double beta_d);

    ComplexMatrix calcWeightsNSB(std::vector<double> angles);

    struct RadiationPattern createRadiationPattern(Weights weights,double step);




private:

    void saveZeroesAndMax(double magnitude,double max,double min,std::vector<double> zeroes,std::vector<double> maxAndSideLobe);




};


#endif //BEAMFORMING_NSB_H
