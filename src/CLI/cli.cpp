/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** cli
*/

#include "../../include/Cli.hpp"
#include "../../include/Circuit.hpp"
#include <regex>
#include <csignal>
#include <functional>

namespace nts {
    namespace cli
    {
        Action parseDoAction(std::smatch matches)
        {
            std::vector<std::string> validDoActions = {"exit", "display", "loop", "dump", "display", "simulate"};
            if (std::find(validDoActions.begin(), validDoActions.end(), matches[1]) != validDoActions.end()) {
                return Action {.action=matches[1], .arg=""};
            }
            throw CliException("Invalid input");
        }

        Action parseAction(std::string line)
        {
            std::regex do_rgx("^\\s*([^=\\s]+)\\s*$");
            std::regex assignment_rgx("^\\s*(\\S+)\\s*=\\s*(0|1|U)\\s*$");
            std::vector<std::regex> rgxs = { do_rgx, assignment_rgx };
            std::smatch matches;

            for (int i = 0; i < 2; i++) {
                if (std::regex_search(line, matches, rgxs[i])) {
                    if (i == 0) {
                        return parseDoAction(matches);
                    } else {
                        return Action {.action = matches[1].str(), .arg = matches[2].str()};
                    }
                }
            }
            throw CliException("Invalid input");
        }

        std::function<void()> stop_loop;
        void sighandler (int sig) {
            (void) sig;
            stop_loop();
        }

        void loop(Circuit &circuit)
        {
            bool looping = true;
            stop_loop = [&looping]() {
                looping = false;
            };
            signal(SIGINT, sighandler);
            while (looping) {
                circuit.simulate();
                circuit.display();
            }
            signal(SIGINT, SIG_DFL);
        }

        void doAction(Action &action, nts::Circuit &circuit)
        {
            const std::vector<std::string> actionTranslateTable = {"exit", "display", "simulate", "loop", "dump"};

            if (action.action == "exit")
                exit(0);
            if (action.action == "display") {
                circuit.display();
            } else if (action.action == "simulate") {
                circuit.simulate();
            } else if (action.action == "loop") {
                loop(circuit);
                (void) circuit;
            } else if (action.action == "dump") {
                circuit.dump();
            } else
                circuit.assignInput(action.action, action.arg);
            return;
        }
    }
}
