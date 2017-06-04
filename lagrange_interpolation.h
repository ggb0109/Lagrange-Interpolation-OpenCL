#ifndef LAGRANGEINTERPOLATION_H
#define LAGRANGEINTERPOLATION_H

#include "interpolation_data.h"

class LagrangeInterpolation {
public:
    void interpolate(InterpolationData &data);
    InterpolationData data() const;
private:
    double calc(double x);
    InterpolationData m_data;
};

#endif // LAGRANGEINTERPOLATION_H
