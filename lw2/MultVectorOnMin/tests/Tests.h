#pragma once
#define CATCH_CONFIG_MAIN

#include "../../catch/catch.hpp"
#include "../src/VectorUtils/VectorUtils.h"
#include "../src/Args/Args.h"
#include <string>

const std::string EXECUTABLE = "./MultVectorOnMin";
vector_t testVector, expectedVector, resultVector;
