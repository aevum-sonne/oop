#include <HttpUrl/HttpUrl.h>
#include <UrlParsingError/UrlParsingError.h>
#include <iostream>

int main()
{
    std::string url;

    while (getline(std::cin, url) && url != "q")
    {
        try
        {
            HttpUrl httpUrl(url);
            httpUrl.Print(std::cout);
        }
        catch (UrlParsingError& e)
        {
            std::cout << e.what();
        }
    }

    return 0;
}