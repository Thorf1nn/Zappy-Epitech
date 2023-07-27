#include "Utils.hpp"

namespace zappy {
    Vector3 Utils::addVector3(const Vector3& a, const Vector3& b) {
        return {a.x + b.x, a.y + b.y, a.z + b.z};
    }

    in_addr_t Utils::inetAddr(const char *cp) {
        return inet_addr(cp);
    }

    uint16_t Utils::htons(uint16_t hostshort) {
        return ::htons(hostshort);
    }

    bool Utils::strContains(const std::string& str, const std::string& toFind) {
        return str.find(toFind) != std::string::npos;
    }

    std::pair<std::string, std::string> Utils::split(const std::string& input, char delimiter, std::size_t numSplits) {
        std::string first;
        std::string second;

        std::size_t startPos = 0;
        for (std::size_t i = 0; i < numSplits; ++i) {
            std::size_t delimiterPos = input.find(delimiter, startPos);
            if (delimiterPos != std::string::npos) {
                first += input.substr(startPos, delimiterPos - startPos);
                startPos = delimiterPos + 1;
            } else {
                first += input.substr(startPos);
                break;
            }
        }

        second = input.substr(startPos);

        return {first, second};
    }

    std::pair<std::string, std::string> Utils::split(const std::string& input, char delimiter, std::size_t startPos, std::size_t endPos) {
        std::string first;
        std::string second;

        std::size_t delimiterPos = input.find(delimiter);
        if (delimiterPos != std::string::npos && delimiterPos >= startPos && delimiterPos <= endPos) {
            first = input.substr(startPos, delimiterPos - startPos);
            second = input.substr(delimiterPos + 1, endPos - delimiterPos);
        } else {
            first = input.substr(startPos, endPos - startPos + 1);
        }

        return {first, second};
    }

    std::string Utils::getNumberAtIndex(const std::string& str, char delimiter, size_t index) {
        std::vector<std::string> numbers;
        std::stringstream ss(str);
        std::string token;

        while (std::getline(ss, token, delimiter)) {
            numbers.push_back(token);
        }

        if (index < numbers.size()) {
            return numbers[index];
        }

        return "";
    }
} // zappy