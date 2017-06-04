#include <QCoreApplication>
#include <cl_lagrange_interpolation.h>
#include <lagrange_interpolation.h>
#include <interpolation_worker.h>
#include <iostream>
#include <chrono>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    InterpolationData data;
    data.dataX = {0, 3, 6, 9, 14};
    data.dataY = {0, 25, 100, 300, 200};
    data.realX = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    data.dataSize = data.dataX.size();

    InterpolationWorker<CLLagrangeInterpolation> cl_interpolator;

    auto start = std::chrono::steady_clock::now();
    cl_interpolator.runInterpolation(data);
    auto end = std::chrono::steady_clock::now();

    std::cout << "Lagrange Interpolation with OpenCL" << std::endl;
    for (int i = 0; i < cl_interpolator.data().realX.size(); ++i) {
        std::cout << cl_interpolator.data().realX[i] << "\t" << cl_interpolator.data().realY[i] << std::endl;
    }
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns" << std::endl;


    InterpolationWorker<LagrangeInterpolation> interpolator;
    interpolator.runInterpolation(data);

    std::cout << "Lagrange Interpolation without OpenCL" << std::endl;
    for (int i = 0; i < interpolator.data().realX.size(); ++i) {
        std::cout << interpolator.data().realX[i] << "\t" << interpolator.data().realY[i] << std::endl;
    }


    return a.exec();
}
