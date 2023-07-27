#include <criterion/criterion.h>
#include <iostream>
#include "Infos.hpp"

namespace zappy {
    Test(Infos, SetSizeMap) {
        Infos infos;
        infos.setSizeMap(10, 8);

        cr_assert_eq(infos.getSizeMap().first, 10);
        cr_assert_eq(infos.getSizeMap().second, 8);
    }

    Test(Infos, SetTeamName) {
        Infos infos;
        infos.setTeamName("Red");
        infos.setTeamName("Blue");

        cr_assert_eq(infos.getTeamsName().size(), 2);
        cr_assert_eq(infos.getTeamsName()[0], "Red");
        cr_assert_eq(infos.getTeamsName()[1], "Blue");
    }

    Test(Infos, GetTeamName) {
        Infos infos;
        infos.setTeamName("Red");
        infos.setTeamName("Blue");

        cr_assert_eq(infos.getTeamName("Red"), "Red");
        cr_assert_eq(infos.getTeamName("Blue"), "Blue");
        cr_assert_throw(infos.getTeamName("Green"), std::runtime_error);
    }
}
