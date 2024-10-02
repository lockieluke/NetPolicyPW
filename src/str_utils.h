//
// Created by Sherlock LUK on 01/10/2024.
//

#ifndef STR_UTILS_H
#define STR_UTILS_H

#include <vector>
#include <sstream>

namespace str_utils {

    std::vector<std::string> split(const std::string& s, const std::string& delimiter);
    std::vector<std::string> split(const std::string &s, char delim);
    std::string substring(const std::string& s, int start, int end);

} // str_utils

#endif //STR_UTILS_H
