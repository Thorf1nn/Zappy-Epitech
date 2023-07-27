#include <criterion/criterion.h>
#include "Server.hpp"

namespace zappy {

    Test(Server, SendData) {
        Server server(4242, "127.0.0.1");
        server.create();
        server.connect();
        server.send("Hello, server!");
    }
}
