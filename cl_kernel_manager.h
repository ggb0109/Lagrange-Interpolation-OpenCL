#ifndef CL_KERNEL_MANAGER_H
#define CL_KERNEL_MANAGER_H

#include <CL/cl.hpp>
#include <QSharedPointer>

class CLKernelManager {
public:
    CLKernelManager();
    QSharedPointer<cl::Context> getContext();
    QSharedPointer<cl::CommandQueue> getCommandQueue();
    QSharedPointer<cl::Program> getProgram();
    bool load(std::string fileName);
private:
    cl::Platform m_platform;
    cl::Device m_device;
    QSharedPointer<cl::Context> m_context;
    QSharedPointer<cl::CommandQueue> m_commandQueue;
    QSharedPointer<cl::Program> m_program;
    std::vector<cl::Platform> m_allPlatforms;
    std::vector<cl::Device> m_allDevices;
};

#endif // CL_KERNEL_MANAGER_H
