/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** Circuit
*/

#include "../../include/Circuit.hpp"
#include "../../include/Cli.hpp"
#include "Sequential.hpp"
#include <iostream>
#include <sstream>
#include <regex>

namespace nts {
    Circuit::Circuit(std::string filepath):
    _lineNb(0),
    _filename(filepath)
    {
        _availableComponents.insert({"4011", components::createNand4011C});
        _availableComponents.insert({"4001", components::createNor4001C});
        _availableComponents.insert({"4008", components::createAdder4008C});
        _availableComponents.insert({"4030", components::createXor4030C});
        _availableComponents.insert({"4071", components::createOr4071C});
        _availableComponents.insert({"4069", components::createNot4069C});
        _availableComponents.insert({"4081", components::createAnd4081C});
        _availableComponents.insert({"4512", components::createSelector4512Component});
        _availableComponents.insert({"clock", components::createClockComponent});
        _availableComponents.insert({"input", components::createInputComponent});
        _availableComponents.insert({"output", components::createOutputComponent});
        _availableComponents.insert({"true", components::createTrueComponent});
        _availableComponents.insert({"false", components::createFalseComponent});
        _availableComponents.insert({"4040", components::createCounter4040C});
        _availableComponents.insert({"4514", components::createDecoder4514C});
        _availableComponents.insert({"4801", components::createRam4801C});
        _availableComponents.insert({"4017", components::createJohnson4017});
        _availableComponents.insert({"4094", components::createShift4094C});
        _availableComponents.insert({"4013", components::createFlipFlop4013C});
        _availableComponents.insert({"2716", components::createRom2716C});
        _availableComponents.insert({"logger", components::createLoggerC});
    }

    Circuit::~Circuit()
    {
        if (_file.is_open())
            _file.close();
    }

    Circuit::Line Circuit::getLine()
    {
        std::string s = "";
        std::regex line("[^#\n]*");
        std::smatch m;


        while (_file.peek() != EOF) {
            _lineNb++;
            std::getline(_file, s);
            std::regex_search(s, m, line);
            s = s.substr(m.position(), m.length());
            if (s != "")
                break;
        }
        return Line(_lineNb, s);
    }

    void Circuit::parse()
    {
        _file.open(_filename);
        if (!_file.is_open()) {
            throw ParsingException(_filename, 0, "Could not open file.");
        }
        createComponents();
    }

    void Circuit::addComponent(Circuit::Line line)
    {
        std::vector<std::string> componentNames;
        for (auto it : _availableComponents) {
            componentNames.push_back(it.first);
        }
        //  = {"input", "clock", "output", "logger", "4001", "4004", "4008", "4011", "4081", "4013", "4017", "4030", "4040", "4069", "4071", "4512", "4514", "4040", "4801", "4094", "true", "false"};
        std::smatch matches;
        std::regex rgx("^\\s*(\\S+)\\s+(\\S+)\\s*$");
        std::string s = line.getStr();

        if (!std::regex_search(s, matches, rgx))
            throw ParsingException(_filename, line.getNb(), "Invalid syntax");
        std::vector<std::string>::iterator it = std::find(componentNames.begin(), componentNames.end(), matches[1]);
        if(it == componentNames.end())
            throw ParsingException(_filename, line.getNb(), std::string("Couln't find a component named ") + std::string(matches[1]));
        if (_components.find(matches[2]) != _components.end())
            throw ParsingException(_filename, line.getNb(), "Duplicate component name");
        _components.insert({matches[2], std::unique_ptr<IComponent>(_availableComponents[matches[1]](matches[2]))}) ;
    }

    void Circuit::createComponents()
    {
        Line line = getLine();
        std::string s = line.getStr();
        std::smatch matches;
        std::regex chipsets("^\\s*.chipsets:\\s*");
        std::regex links("^\\s*.links:\\s*");
        std::regex empty("^\\s*$");

        if (!std::regex_search(s, matches, chipsets))
            throw ParsingException(_filename, line.getNb(), "No '.chipsets' section found");
        do {
            line = getLine();
            s = line.getStr();
            if (std::regex_search(s, matches, links) || line.getStr() == "")
                break;
            addComponent(line);
        } while (true);
        if (_components.size() == 0) {
            throw ParsingException(_filename, line.getNb(), "No chipsets in the circuit");
        }
        if (!std::regex_search(s, matches, links))
            throw ParsingException(_filename, line.getNb(), "No '.links' section found");
        do {
            Line line = getLine();
            s = line.getStr();
            if (s == "")
                break;
            if (std::regex_search(s, matches, empty))
                continue;
            linkComponent(line);
        } while (true);
    }

    void Circuit::linkComponent(Circuit::Line line)
    {
        std::regex rgx("^\\s*(\\S+):([0-9]+)\\s+(\\S+):([0-9]+)\\s*$");
        std::smatch matches;
        std::string s = line.getStr();

        if (!std::regex_search(s, matches, rgx))
            throw ParsingException(_filename, line.getNb(), "Invalid syntax");
        if (_components.find(matches[1]) == _components.end())
            throw ParsingException(_filename, line.getNb(), std::string("Couln't find a component aliased to ") + std::string(matches[1]));
        if (_components.find(matches[3]) == _components.end())
            throw ParsingException(_filename, line.getNb(), std::string("Couln't find a component aliased to ") + std::string(matches[3]));
        if ((matches[2]).str()[0] == '0' || (matches[4]).str()[0] == '0') {
            throw ParsingException(_filename, line.getNb(), std::string("Pin assignments start at value 1"));
        }
        _components[matches[3]]->setLink(std::stoi(matches[4]) - 1, *(_components[matches[1]].get()), std::stoi(matches[2]) - 1);
    }

    void Circuit::simulate()
    {
        tickCounter++;
        for (auto it = _components.begin(); it != _components.end(); it++) {
            auto type = it->second.get()->getType();
            if (type == C_OUTPUT || type == C_DEVICE) {
                it->second.get()->simulate(1);
            }
        }
    }

    void Circuit::display() const
    {
        std::cout << "tick: " << tickCounter - 1 << std::endl;
        std::cout << "input(s):" << std::endl;
        for (auto it = _components.begin(); it != _components.end(); it++) {
            if (it->second.get()->getType() == C_INPUT) {
                it->second.get()->dump();
            }
        }
        std::cout << "output(s):" << std::endl;
        for (auto it = _components.begin(); it != _components.end(); it++) {
            if (it->second.get()->getType() == C_OUTPUT) {
                it->second.get()->dump();
            }
        }
    }

    void Circuit::dump() const
    {
        for (auto it = _components.begin(); it != _components.end(); it++) {
            it->second.get()->dump();
        }
    }

    void Circuit::assignInput(std::string target, std::string value)
    {
        Tristate val = stoTristate(value);
        if (_components.find(target) == _components.end())
            throw nts::cli::CliException("No component named" + target);
        if (_components[target].get()->getType() != nts::ComponentType::C_INPUT)
            throw nts::cli::CliException("Component " + target + "is not an input");
        dynamic_cast<nts::components::AInputC *>(_components[target].get())->setVal(val);
        _components[target].get()->simulate(1);
    }
}
