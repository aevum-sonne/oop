#include "Args/Args.h"
#include "VectorUtils/VectorUtils.h"

int main(int argc, const char * argv[])
{
    Args args;
    if (!args.ParseArgs(argc, argv))
    {
        return 1;
    }

    double minArg = GetMinElementInVector(args.vector);
    vector_t resultVector = MultVectorOnDouble(args.vector, minArg);
    // Print multiplied vector
    PrintVector(resultVector);
    // Print sorted result vector
    PrintVector(SortVector(resultVector));

    return 0;
}