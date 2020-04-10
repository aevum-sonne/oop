#include "Exception.h"
#include <iostream>

Exception::Exception(std::string errorMsg)
{
    errMsg = errorMsg;
}

const std::string Exception::GetError()
{
    return errMsg;
}