//
// Created by Sherlock LUK on 01/10/2024.
//

#ifndef FS_UTILS_H
#define FS_UTILS_H

#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace fs_utils {

    std::string normalizePath(const std::string& messyPath);
    std::string readFile(const std::string& file);
    std::string readFile(const std::filesystem::path& file);

} // fs_utils

#endif //FS_UTILS_H
