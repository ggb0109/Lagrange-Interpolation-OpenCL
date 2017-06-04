#ifndef INTERPOLATIONWORKER_H
#define INTERPOLATIONWORKER_H

#include <interpolation_data.h>

template <class Interpolation>
class InterpolationWorker : public Interpolation {
public:
    void runInterpolation(InterpolationData &data) {
        this->interpolate(data);
    }
};

#endif // INTERPOLATIONWORKER_H
