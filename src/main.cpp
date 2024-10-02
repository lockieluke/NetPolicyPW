#include <iostream>
#include <filesystem>
#include <regex>
#include <argparse/argparse.hpp>
#include <nlohmann/json.hpp>
#include <fmt/color.h>

#include "constants.h"
#include "fs_utils.h"
#include "str_utils.h"
#include "base64.hpp"

using json = nlohmann::json;

int main(const int argc, char* argv[]) {
    argparse::ArgumentParser program(PROGRAM_NAME, PROGRAM_VERSION);

    program.add_argument("file")
           .required()
           .help("JSON file obtained from chrome://net-policy");

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return EXIT_FAILURE;
    }

    const auto file = program.get<std::string>("file");
    const auto path = std::filesystem::path(fs_utils::normalizePath(file));

    if (!exists(path)) {
        std::cerr << "File does not exist: " << path << std::endl;
        return EXIT_FAILURE;
    }

    if (is_regular_file(path) && path.has_extension() && path.extension() != ".json") {
        std::cerr << "File must be a JSON file" << std::endl;
        return EXIT_FAILURE;
    }

    const std::string content = fs_utils::readFile(path);
    std::vector<std::string> splitNetLog = str_utils::split(content, '\n');
    std::vector<std::string> policyNets = {};

    const std::vector<std::string> matchingPolicies = {
        "ya0NvbmZpZ3VyYXRpb2",
        "vcmtDb25maWd1cmF0aW",
        "rQ29uZmlndXJhdGlvbn",
        "Db25maWd1cmF0aW9ucw"
    };
    std::ranges::for_each(splitNetLog, [&policyNets, matchingPolicies](const std::string& line) {
        if (matchingPolicies.end() != std::find_if(matchingPolicies.begin(), matchingPolicies.end(),
                                                   [&line](const std::string& policy) {
                                                       return line.find(policy) != std::string::npos;
                                                   })) {
            policyNets.push_back(line);
        }
    });

    std::ranges::for_each(policyNets, [](const std::string& policyNet) {
        // Stripe out unnecessary properties
        std::string payload = base64::from_base64(str_utils::substring(
            policyNet, static_cast<int>(policyNet.find(R"("bytes":")")) + 9,
            static_cast<int>(policyNet.find(R"("},"phase")"))));

        // Stripe out raw bytes
        payload = str_utils::substring(payload, static_cast<int>(payload.find(R"("NetworkConfigurations":)")), static_cast<int>(payload.find("]\n}b"))) + "]";

        // Stripe out "NetworkConfigurations"
        const std::regex replacingRegex(R"(("NetworkConfigurations":|\n))");
        payload = std::regex_replace(payload, replacingRegex, "");

        // Stripe out new lines
        std::erase(payload, '\n');

        // Minify JSON
        const std::regex minifyRegex(R"(\s+)");
        payload = std::regex_replace(payload, minifyRegex, "");

        json j = json::parse(payload);
        std::ranges::for_each(j, [](const json& network) {
            const std::string guid = network["GUID"];

            const json& networkConfig = network["WiFi"];
            const std::string security = networkConfig["Security"];
            const std::string password = networkConfig["Passphrase"];
            const std::string ssid = networkConfig["SSID"];

            fmt::print(fmt::emphasis::bold, "SSID: ");
            fmt::print(fmt::fg(fmt::color::green), "{}\n", ssid);

            fmt::print(fmt::emphasis::bold, "Security: ");
            fmt::println("{}", security);

            fmt::print(fmt::emphasis::blink, "GUID: ");
            fmt::println("{}", guid);

            fmt::print(fmt::emphasis::blink, "Passphrase: ");
            fmt::print(fmt::emphasis::faint, "{}\n", password);
        });
    });

    return EXIT_SUCCESS;
}
