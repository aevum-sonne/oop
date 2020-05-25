#include <UrlParsingError/UrlParsingError.h>
#include <string>

UrlParsingError::UrlParsingError(const std::string& message)
        : invalid_argument(message)
{
}
