#pragma once
#include <map>
#include <string>

using map_t = const std::map<std::string, char>;
void ReplaceEntity(std::string entity, char ch, std::string &decodedHtml);
std::string HtmlDecode(std::string const& html);

// Map of html entities
map_t EntityToCharMap = {
        {"&quot;", '"'},
        {"&apos;", '\''},
        {"&lt;", '<'},
        {"&gt;", '>'},
        {"&amp;", '&'},
};