#ifndef CLLAGRANGEINTERPOLATION_H
#define CLLAGRANGEINTERPOLATION_H

#include <string>
#include "cl_kernel_manager.h"
#include "interpolation_data.h"

class CLLagrangeInterpolation {
public:
    CLLagrangeInterpolation();
    void interpolate(InterpolationData &data);
    InterpolationData data() const;
private:
    bool init(std::string path_to_kernelSource);
    QSharedPointer<CLKernelManager> m_clKernelManager;
    InterpolationData m_data;
};

#endif // CLLAGRANGEINTERPOLATION_H
