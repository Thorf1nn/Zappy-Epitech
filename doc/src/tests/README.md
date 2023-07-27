---
sidebar: auto
---

# Tests Unitaires

## Python

```py
class Test(unittest.TestCase):
    def test_parse_arguments(self):
        p = Parsing()
        p.set_things(1234, "team", "localhost")
        self.assertEqual(p.get_port(), 1234)
        self.assertEqual(p.get_name(), 'team')
        self.assertEqual(p.get_machine(), 'localhost')

    def test_error_handling(self):
        p = Parsing()
        p.parser.parse_args(['-p', '1234'])

        with self.assertRaises(SystemExit) as cm:
            p.error_handing()
        self.assertEqual(cm.exception.code, 84)

if __name__ == '__main__':
    unittest.main()
```

- Tests unitaires de la connection au serveur

## C

```c

Test(get_args, all_work, .init = redirect_all_std)
{
    server_t *serv;
    char *data[] = {"./zappy_server", "-p", "8080",
                    "-x", "20", "-y", "20", "-f", "20"};
    char **args = data;
    int ret = 0;

    serv = malloc(sizeof(server_t));

    ret = get_args(serv, 7, args);
    cr_assert_eq(1, ret);
}

Test(get_args, classic_launch, .init = redirect_all_std)
{
    server_t *serv;
    char *data[] = {"./zappy_server"};
    char **args = data;
    int ret = 1;

    serv = malloc(sizeof(server_t));

    ret = get_args(serv, 1, args);
    cr_assert_eq(1, ret);
}

Test(get_args, bad_port, .init = redirect_all_std)
{
    server_t *serv;
    char *data[] = {"./zappy_server", "-p", "feur"};
    char **args = data;
    int ret = 0;

    serv = malloc(sizeof(server_t));

    ret = get_args(serv, 3, args);
    cr_assert_eq(0, ret);
}

Test(get_args, bad_x, .init = redirect_all_std)
{
    server_t *serv;
    char *data[] = {"./zappy_server", "-p", "8080", "-x", "31", "-y", "20"};
    char **args = data;
    int ret = 0;

    serv = malloc(sizeof(server_t));

    ret = get_args(serv, 7, args);
    cr_assert_eq(0, ret);
}
Test(get_args, bad_x2, .init = redirect_all_std)
{
    server_t *serv;
    char *data[] = {"./zappy_server", "-p", "8080", "-x", "9", "-y", "20"};
    char **args = data;
    int ret = 0;

    serv = malloc(sizeof(server_t));

    ret = get_args(serv, 7, args);
    cr_assert_eq(0, ret);
}

Test(get_args, bad_y, .init = redirect_all_std)
{
    server_t *serv;
    char *data[] = {"./zappy_server", "-p", "8080", "-x", "20", "-y", "31"};
    char **args = data;
    int ret = 0;

    serv = malloc(sizeof(server_t));

    ret = get_args(serv, 7, args);
    cr_assert_eq(0, ret);
}

Test(get_args, bad_y2, .init = redirect_all_std)
{
    server_t *serv;
    char *data[] = {"./zappy_server", "-p", "8080", "-x", "20", "-y", "9"};
    char **args = data;
    int ret = 0;

    serv = malloc(sizeof(server_t));

    ret = get_args(serv, 7, args);
    cr_assert_eq(0, ret);
}

Test(get_args, bad_freq, .init = redirect_all_std)
{
    server_t *serv;
    char *data[] = {"./zappy_server", "-p", "8080",
                    "-x", "20", "-y", "9", "-f", "1"};
    char **args = data;
    int ret = 0;

    serv = malloc(sizeof(server_t));

    ret = get_args(serv, 7, args);
    cr_assert_eq(0, ret);
}

Test(get_args, bad_freq2, .init = redirect_all_std)
{
    server_t *serv;
    char *data[] = {"./zappy_server", "-p", "8080",
                    "-x", "20", "-y", "9", "-f", "10001"};
    char **args = data;
    int ret = 0;

    serv = malloc(sizeof(server_t));

    ret = get_args(serv, 7, args);
    cr_assert_eq(0, ret);
}

```

- Tests des arguments au serveur

```c

Test(count_words, remove_str)
{
    const char *str = "Il a dit quoi j'ai dit feur";
    int new = count_words(str, " ");

    cr_assert_eq(7, new);
}

Test(strarr, separe_words)
{
    int i = 0;
    char *str = "Luca il n'a pas les cramptés";
    char **words = strarr(str, " ");

    while (words[i] != NULL) {
        i += 1;
    }
    cr_assert_eq(6, i);
    cr_assert_str_eq(words[0], "Luca");
    cr_assert_str_eq(words[1], "il");
    cr_assert_str_eq(words[2], "n'a");
    cr_assert_str_eq(words[3], "pas");
    cr_assert_str_eq(words[4], "les");
    cr_assert_str_eq(words[5], "cramptés");
}

Test(compare, compare_good_nb_words)
{
    int i = 0;
    char *str = "Luca il n'a pas les cramptés";
    bool comp = compare(str, 6);

    cr_assert_eq(comp, 1);
}

Test(compare, compare_bad_nb_words)
{
    int i = 0;
    char *str = "Luca il n'a pas les cramptés";
    bool comp = compare(str, 5);

    cr_assert_eq(comp, 0);
}
```

- Tests des fonctions de parsing

```c
void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(print_usage, check_message, .init = redirect_all_std)
{
    print_usage();

    cr_assert_eq(0, 0);
}

Test(print_usage_error, usage_error2, .init = redirect_all_std)
{
    int ret = print_usage_error("Feur", 84);

    cr_assert_eq(ret, 84);
}
```

- Tests des fonctions d'affichage



## C++

```cpp
namespace zappy {

    Test(Server, SendData) {
        Server server(4242, "127.0.0.1");
        server.create();
        server.connect();
        server.send("Hello, server!");
    }
}
```

- Tests de la classe Server

```cpp


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

```

- Tests de la classe Infos

```cpp
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
```

- Tests de la classe Parser

```cpp
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
```

- Tests de la classe Player

```cpp
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
```

- Tests de la classe Utils
