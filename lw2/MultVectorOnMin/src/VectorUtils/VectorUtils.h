#pragma once

#include <vector>

using vector_t = std::vector<double>;
double GetMinElementInVector(vector_t& vector);
vector_t MultVectorOnDouble(vector_t& vector, double elem);
vector_t MultVectorOnMin(vector_t resultVector);
void PrintVector(vector_t& vector);
vector_t SortVector(vector_t vector);
