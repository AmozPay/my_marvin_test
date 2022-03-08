/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** main
*/

#include "Core.hpp"
#include "Combinatorial.hpp"
#include "Circuit.hpp"
#include "Cli.hpp"
int main(int ac, char **av)
{
    if (ac < 2) {
        std::cerr << "You must indicate a .nts file" << std::endl;
        return 84;
    }
    if (ac > 2) {
        std::cerr << "Only 1 arg required" << std::endl;
        return 84;
    }

    nts::Circuit circuit(av[1]);
    std::string s;
    try {
        circuit.parse();
    } catch (std::exception &e) {
        std::cerr << "Parsing Error:" << std::endl << e.what() << std::endl;
        return 84;
    }
    std::string line;
    circuit.simulate();
    std::cout << "> ";
    while (std::getline(std::cin, line)) {
        nts::cli::Action action;
        try {
            action = nts::cli::parseAction(line);
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
            std::cout << "> ";
            continue;
        }
        try {
            nts::cli::doAction(action, circuit);
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << "> ";
    }
    return 0;
}
