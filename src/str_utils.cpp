//
// Created by Sherlock LUK on 01/10/2024.
//

#include "str_utils.h"

namespace str_utils {
    std::vector<std::string> split(const std::string& s, const std::string& delimiter) {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        std::vector<std::string> res;

        while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
            std::string token = s.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back(token);
        }

        res.push_back(s.substr(pos_start));
        return res;
    }

    std::vector<std::string> split (const std::string &s, char delim) {
        std::vector<std::string> result;
        std::stringstream ss (s);
        std::string item;

        while (getline (ss, item, delim)) {
            result.push_back (item);
        }

        return result;
    }

    std::string substring(const std::string& s, int start, int end) {
        if (end == -1)
            return s.substr(start);

        return s.substr(start, end - start);
    }
} // str_utils
