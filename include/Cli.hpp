/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** Cli
*/

#ifndef CLI_HPP_
#define CLI_HPP_


#include "Circuit.hpp"

namespace nts {
    namespace cli {
        struct Action {
            std::string action;
            std::string arg;
        };

        Action parseAction(std::string line);
        void doAction(Action &action, nts::Circuit &circuit);

        class CliException: public std::exception {
            public:
                CliException(std::string msg): _msg(msg) {}
                const char *what() const noexcept override
                {
                    return _msg.data();
                }
            private:
                const std::string _msg;
        };
    }
}

#endif /* !CLI_HPP_ */
