#include "lagrange_interpolation.h"

void LagrangeInterpolation::interpolate(InterpolationData &data) {
    m_data = data;
    for (int i = 0; i < (int)m_data.realX.size(); ++i) {
        m_data.realY.push_back(calc(m_data.realX[i]));
    }
}

double LagrangeInterpolation::calc(double x) {
    double result = 0, temp;
    for (int i = 0; i < m_data.dataSize; ++i) {
        temp = 1;
        for (int j = 0; j < m_data.dataSize; ++j) {
            if (i != j) {
                temp *= (x - m_data.dataX[j]) / (m_data.dataX[i] - m_data.dataX[j]);
            }
        }
        result += m_data.dataY[i] * temp;
    }
    return result;
}

InterpolationData LagrangeInterpolation::data() const {
    return m_data;
}
