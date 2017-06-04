#include "cl_kernel_manager.h"
#include <fstream>
#include <iostream>

CLKernelManager::CLKernelManager() {
    cl::Platform::get(&m_allPlatforms);
    if (m_allPlatforms.size() == 0) {
        std::cerr << "[ERROR]: no platforms found" << std::endl;
        exit(1);
    }

    m_platform = m_allPlatforms[2];
    m_platform.getDevices(CL_DEVICE_TYPE_CPU, &m_allDevices);
    if (m_allDevices.size() == 0) {
        std::cerr << "[ERROR]: no devices found" << std::endl;
        exit(1);
    }

    m_device = m_allDevices[0];
    m_context.reset(new cl::Context({m_device}));
    m_commandQueue.reset(new cl::CommandQueue(*m_context, m_device));
}

QSharedPointer<cl::Context> CLKernelManager::getContext() {
    return m_context;
}

QSharedPointer<cl::CommandQueue> CLKernelManager::getCommandQueue() {
    return m_commandQueue;
}

QSharedPointer<cl::Program> CLKernelManager::getProgram() {
    return m_program;
}

bool CLKernelManager::load(std::string fileName) {
    std::ifstream kernelSource;
    kernelSource.open(fileName, std::ios::in);
    if (!kernelSource.is_open()) {
        std::cerr << "[ERROR]: kernel source file is NOT open" << std::endl;
        return false;
    }

    cl::Program::Sources sources;
    std::string cl_source((std::istreambuf_iterator<char>(kernelSource)), std::istreambuf_iterator<char>());
    sources.push_back({cl_source.c_str(), cl_source.length()});

    kernelSource.close();

    m_program.reset(new cl::Program(*m_context, sources));
    if(m_program->build({m_device}) != CL_SUCCESS) {
        std::cerr << "[ERROR]: building: " << m_program->getBuildInfo<CL_PROGRAM_BUILD_LOG>(m_device) << std::endl;
        return false;
    }

    return true;
}
