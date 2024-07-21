#include "string.hpp"

#include <algorithm>
#include <cctype>

namespace coral::string
{

void trim(std::string &string)
{
    string.erase(string.begin(),
                 std::find_if(string.begin(), string.end(), [](unsigned char ch)
                              { return !std::isspace(ch); }));

    string.erase(std::find_if(string.rbegin(), string.rend(),
                              [](unsigned char ch)
                              { return !std::isspace(ch); })
                     .base(),
                 string.end());
}

} // namespace coral::string
