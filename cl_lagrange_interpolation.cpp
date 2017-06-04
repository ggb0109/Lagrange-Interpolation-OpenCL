#include "cl_lagrange_interpolation.h"
#include <iostream>

bool CLLagrangeInterpolation::init(std::string path_to_kernelSource) {
    return m_clKernelManager->load(path_to_kernelSource);
}

InterpolationData CLLagrangeInterpolation::data() const {
    return m_data;
}

CLLagrangeInterpolation::CLLagrangeInterpolation() {
    m_clKernelManager.reset(new CLKernelManager);
    if (!init("cl_kernel.cl")) {
        std::cerr << "[ERROR] kernel is not loaded" << std::endl;
        exit(1);
    }
}

void CLLagrangeInterpolation::interpolate(InterpolationData &data) {
    m_data = data;
    int realXSize = m_data.realX.size();
    m_data.realY.resize(realXSize, 0);

    cl::Buffer buffer_dataX(*m_clKernelManager->getContext(), CL_MEM_WRITE_ONLY, sizeof(double)*m_data.dataSize);
    cl::Buffer buffer_dataY(*m_clKernelManager->getContext(), CL_MEM_WRITE_ONLY, sizeof(double)*m_data.dataSize);
    cl::Buffer buffer_size(*m_clKernelManager->getContext(), CL_MEM_WRITE_ONLY, sizeof(int));
    cl::Buffer buffer_realX(*m_clKernelManager->getContext(), CL_MEM_WRITE_ONLY, sizeof(double)*realXSize);
    cl::Buffer buffer_result(*m_clKernelManager->getContext(), CL_MEM_READ_ONLY, sizeof(double)*realXSize);

    m_clKernelManager->getCommandQueue()->enqueueWriteBuffer(buffer_dataX, CL_TRUE, 0, sizeof(double)*m_data.dataSize, &(m_data.dataX[0]));
    m_clKernelManager->getCommandQueue()->enqueueWriteBuffer(buffer_dataY, CL_TRUE, 0, sizeof(double)*m_data.dataSize, &(m_data.dataY[0]));
    m_clKernelManager->getCommandQueue()->enqueueWriteBuffer(buffer_size, CL_TRUE, 0, sizeof(int), &m_data.dataSize);
    m_clKernelManager->getCommandQueue()->enqueueWriteBuffer(buffer_realX, CL_TRUE, 0, sizeof(double)*realXSize, &(m_data.realX[0]));

    cl::Kernel interpolateKernel(*m_clKernelManager->getProgram(), "interpolate");
    interpolateKernel.setArg(0, buffer_dataX);
    interpolateKernel.setArg(1, buffer_dataY);
    interpolateKernel.setArg(2, buffer_size);
    interpolateKernel.setArg(3, buffer_realX);
    interpolateKernel.setArg(4, buffer_result);

    m_clKernelManager->getCommandQueue()->enqueueNDRangeKernel(interpolateKernel, cl::NullRange, cl::NDRange(realXSize), cl::NullRange);
    m_clKernelManager->getCommandQueue()->finish();
    m_clKernelManager->getCommandQueue()->enqueueReadBuffer(buffer_result, CL_TRUE, 0, sizeof(double)*realXSize, &(m_data.realY[0]));
}
