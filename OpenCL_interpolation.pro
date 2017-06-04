QT += core
QT -= gui

OPENCL_DIR = C:/Program Files (x86)/Intel/OpenCL SDK/6.3


CONFIG += c++11 console
CONFIG -= app_bundle

TARGET = OpenCL_interpolation

TEMPLATE = app

SOURCES += main.cpp \
    cl_kernel_manager.cpp \
    lagrange_interpolation.cpp \
    cl_lagrange_interpolation.cpp

INCLUDEPATH += "$${OPENCL_DIR}/include"
LIBS += -L"$${OPENCL_DIR}/lib/x64" -L"$${OPENCL_DIR}/lib/x86" -lOpenCL

DISTFILES += \
    cl_kernel.cl

HEADERS += \
    cl_kernel_manager.h \
    interpolation_worker.h \
    lagrange_interpolation.h \
    cl_lagrange_interpolation.h \
    interpolation_data.h
