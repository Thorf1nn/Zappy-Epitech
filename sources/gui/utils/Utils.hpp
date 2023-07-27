#ifndef B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_UTILS_HPP
#define B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_UTILS_HPP

#include "raylib.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

namespace zappy {
    class Utils {
    public:
        static Vector3 addVector3(const Vector3& a, const Vector3& b);
        static in_addr_t inetAddr(const char* cp);
        static uint16_t htons(uint16_t hostshort);
        static bool strContains(const std::string& str, const std::string& toFind);
        static std::pair<std::string, std::string> split(const std::string& input, char delimiter, std::size_t numSplits);
        static std::pair<std::string, std::string> split(const std::string& input, char delimiter, std::size_t startPos, std::size_t endPos);
        static std::string getNumberAtIndex(const std::string& str, char delimiter, size_t index);
    };
} // zappy

#endif //B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_UTILS_HPP
