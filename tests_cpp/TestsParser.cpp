#include <criterion/criterion.h>
#include "Parser.hpp"

namespace zappy {
    Test(Parser, GetSizeMap) {
        Parser parser;
        std::string input = "msz 10 10\n";
        parser.getCommands(input);
        Infos infos = parser.getInfos();

        cr_assert_eq(infos.getSizeMap().first, 10);
        cr_assert_eq(infos.getSizeMap().second, 10);
    }
}
