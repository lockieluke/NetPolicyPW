//
// Created by Sherlock LUK on 01/10/2024.
//

#include "fs_utils.h"

namespace fs_utils {
    std::string normalizePath(const std::string& messyPath) {
        std::filesystem::path path(messyPath);
        std::filesystem::path canonicalPath = weakly_canonical(path);
        std::string npath = canonicalPath.make_preferred().string();
        return npath;
    }

    std::string readFile(const std::string& file) {
        std::filesystem::path path(file);
        if (!exists(path))
            throw std::runtime_error("File does not exist: " + file);

        return readFile(path);
    }

    std::string readFile(const std::filesystem::path& file) {
        std::ifstream input(file);
        std::stringstream buffer;

        buffer << input.rdbuf();

        return buffer.str();
    }

} // fs_utils