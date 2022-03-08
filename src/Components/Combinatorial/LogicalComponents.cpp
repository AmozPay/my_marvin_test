/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** basicComponents
*/

#include "../../../include/Core.hpp"
#include "../../../include/Combinatorial.hpp"
#include "../../../include/Sequential.hpp"
#include <cstddef>
#include <iostream>
#include <iomanip>

namespace nts {

    namespace components {

        Xor4030C::Xor4030C(std::string name, std::vector<AGate *>gates):
        AComponent(name, gates.size(), gates) // add the 2 electrical pins, though unused in this project
        {
            assign2In1Out4();
        }

        Tristate Xor4030C::compute(std::size_t pin)
        {
            if (pin >= this->_nbPins || !_pinLinks[pin])
                return FALSE;
                // throw ComponentException("Pin out of range");
            return _pinLinks[pin]->getVal();
        }

        IComponent *createXor4030C(std::string name)
        {
            std::vector<AGate *> gates = std::vector<AGate *>(4, nullptr);
            for (int i = 0; i < 4; i++)
                gates[i] = new gates::XorGate;

            return new Xor4030C(name, gates);
        }


        Nor4001C::Nor4001C(std::string name, std::vector<AGate *>gates):
        AComponent(name, gates.size(), gates)
        {
            assign2In1Out4();
        }


        Tristate Nor4001C::compute(std::size_t pin)
        {
            if (pin >= this->_nbPins)
                return FALSE;
                // throw ComponentException("Pin out of range");
            return _pinLinks[pin]->getVal();
        }

        IComponent *createNor4001C(std::string name)
        {
            std::vector<AGate *> gates = std::vector<AGate *>(4, nullptr);
            for (int i = 0; i < 4; i++)
                gates[i] = new gates::NorGate;

            return new Nor4001C(name, gates);
        }


        Nand4011C::Nand4011C(std::string name, std::vector<AGate *>gates):
        AComponent(name, gates.size(), gates)
        {
            assign2In1Out4();
        }


        Tristate Nand4011C::compute(std::size_t pin)
        {
            if (pin >= this->_nbPins)
                return FALSE;
                // throw ComponentException("Pin out of range");
            return _pinLinks[pin]->getVal();
        }

        IComponent *createNand4011C(std::string name)
        {
            std::vector<AGate *> gates = std::vector<AGate *>(4, nullptr);
            for (int i = 0; i < 4; i++)
                gates[i] = new gates::NandGate;

            return new Nand4011C(name, gates);
        }

        And4081C::And4081C(std::string name, std::vector<AGate *>gates):
        AComponent(name, gates.size(), gates) // add the 2 electrical pins, though unused in this project
        {
            assign2In1Out4();
        }


        Tristate And4081C::compute(std::size_t pin)
        {
            if (pin >= this->_nbPins || !_pinLinks[pin])
                return FALSE;
                // throw ComponentException("Pin out of range");
            return _pinLinks[pin]->getVal();
        }

        IComponent *createAnd4081C(std::string name)
        {
            std::vector<AGate *> gates = std::vector<AGate *>(4, nullptr);
            for (int i = 0; i < 4; i++)
                gates[i] = new gates::AndGate;

            return new And4081C(name, gates);
        }

        Or4071C::Or4071C(std::string name, std::vector<AGate *>gates):
        AComponent(name, gates.size(), gates) // add the 2 electrical pins, though unused in this project
        {
            assign2In1Out4();
        }


        Tristate Or4071C::compute(std::size_t pin)
        {
            if (pin >= this->_nbPins || !_pinLinks[pin])
                return FALSE;
                // throw ComponentException("Pin out of range");
            return _pinLinks[pin]->getVal();
        }

        IComponent *createOr4071C(std::string name)
        {
            std::vector<AGate *> gates = std::vector<AGate *>(4, nullptr);
            for (int i = 0; i < 4; i++)
                gates[i] = new gates::OrGate;

            return new Or4071C(name, gates);
        }


        Not4069C::Not4069C(std::string name, std::vector<AGate *>gates):
        AComponent(name, gates.size(), gates)
        {
            for (int i = 0; i < 6; i++) {
                assignPin(i, i / 2, i % 2);
            }
            for (int i = 0; i < 6; i++) {
                assignPin(i + 7, (i + 6) / 2, 1 - (i % 2));
            }
        }

        Tristate Not4069C::compute(std::size_t pin)
        {
            if (pin >= this->_nbPins || !_pinLinks[pin])
                // return FALSE;
                throw ComponentException("Pin out of range");
            return _pinLinks[pin]->getVal();
        }

        IComponent *createNot4069C(std::string name)
        {
            std::vector<AGate *> gates = std::vector<AGate *>(6, nullptr);
            for (int i = 0; i < 6; i++)
                gates[i] = new gates::NotGate;

            return new Not4069C(name, gates);
        }
    }
}