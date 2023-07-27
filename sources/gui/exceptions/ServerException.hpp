#ifndef B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_SERVEREXCEPTION_HPP
#define B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_SERVEREXCEPTION_HPP

#include <iostream>
#include <exception>

namespace zappy {
    class ServerException : public std::exception {
    public:
        ServerException(const std::string& message) : _message(message) {}

        const char *what() const noexcept override {
            return _message.c_str();
        }

    private:
        std::string _message;
    };

} // zappy
#endif //B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_SERVEREXCEPTION_HPP
