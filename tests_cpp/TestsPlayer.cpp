#include <criterion/criterion.h>
#include "Player.hpp"

namespace zappy {
    Test(Player, SetPosition) {
        Player player(1);
        player.setPosition(5, 10);

        cr_assert_eq(player.getPosition().first, 5);
        cr_assert_eq(player.getPosition().second, 10);
    }

    Test(Player, SetLevel) {
        Player player(1);
        player.setLevel(3);

        cr_assert_eq(player.getLevel(), 3);
    }

    Test(Player, SetOrientation) {
        Player player(1);
        player.setOrientation(2);

        cr_assert_eq(static_cast<int>(player.getOrientation()), 2);
    }

    Test(Player, GetId) {
        Player player(1);

        cr_assert_eq(player.getId(), 1);
    }
}
