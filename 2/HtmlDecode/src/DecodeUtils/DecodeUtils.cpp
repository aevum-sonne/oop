#include "DecodeUtils.h"

void ReplaceEntity(std::string entity, char ch, std::string& decodedHtml)
{
    size_t index = decodedHtml.find(entity);
    for (;;)
    {
        if (index == std::string::npos)
        {
            break;
        }

        decodedHtml.replace(index, entity.length(), std::string(1, ch));
        index = decodedHtml.find(entity, index + 1);    // index += length of char
    }
}

std::string HtmlDecode(std::string const& html)
{
    std::string decodedHtml = html;
    for (auto pair: EntityToCharMap)
    {
        ReplaceEntity(pair.first, pair.second, decodedHtml);
    }

    return decodedHtml;
};