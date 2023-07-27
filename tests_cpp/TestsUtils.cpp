#include <criterion/criterion.h>
#include "Utils.hpp"

namespace zappy {
    Test(Utils, InetAddr) {
        const char* cp = "127.0.0.1";
        in_addr_t result = zappy::Utils::inetAddr(cp);
        in_addr_t expected = inet_addr(cp);
        cr_assert_eq(result, expected);
    }

    Test(Utils, Htons) {
        uint16_t hostshort = 1234;
        uint16_t result = zappy::Utils::htons(hostshort);
        uint16_t expected = ::htons(hostshort);
        cr_assert_eq(result, expected);
    }

    Test(Utils, StrContains) {
        std::string str = "Hello, World!";
        std::string toFind = "World";
        bool result = zappy::Utils::strContains(str, toFind);
        cr_assert(result);
    }
}
