#include "VectorUtils.h"
#include <iostream>
#include <cmath>

double GetMinElementInVector(vector_t& vector)
{
    return *std::min_element(vector.begin(), vector.end());
}

vector_t MultVectorOnDouble(vector_t& vector, double elem)
{
    for (size_t i = 0; i < vector.size(); i++)
    {
        vector[i] *= elem;
        vector[i] = std::round(vector[i] * 1000) / 1000.000;
    }

    return vector;
}

// Only for unit-tests
vector_t MultVectorOnMin(vector_t vectorToMultiplyOnMin)
{
    if (!vectorToMultiplyOnMin.empty())
    {
        double minElement = GetMinElementInVector(vectorToMultiplyOnMin);

        return MultVectorOnDouble(vectorToMultiplyOnMin, minElement);
    }

    return vectorToMultiplyOnMin;
}

void PrintVector(vector_t& vector)
{
    for (auto i = 0; i < vector.size(); i++)
    {
        std::cout << vector[i] << std::endl;
    }
}

vector_t SortVector(vector_t vector)
{
    std::sort(vector.begin(), vector.end());
    return vector;
}