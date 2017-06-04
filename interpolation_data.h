#ifndef INTERPOLATION_DATA_H
#define INTERPOLATION_DATA_H

#include <vector>

struct InterpolationData {
    int dataSize;
    std::vector<double> dataX;
    std::vector<double> dataY;
    std::vector<double> realX;
    std::vector<double> realY;
};

#endif // INTERPOLATION_DATA_H
