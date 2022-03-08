/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** basicComponents
*/

#include <cstddef>
#include <algorithm>
#include <vector>


#include "../../../include/Core.hpp"
#include "../../../include/Combinatorial.hpp"

namespace nts {

    namespace components {
        Adder4008C::Adder4008C(std::string name, std::vector<AGate *>gates):
        AComponent(name, gates.size(), gates)
        {
            assignPin(14, 0, 0); //B4
            for (int i = 0; i <= 6; i++) {
                assignPin(i, 0, i + 1); // A4 to A1
            }
            assignPin(8, 0, 8); // C1
            for (size_t i = 9; i <= 13; i++) // S1 to C0
                assignPin(i, 0, i);
        }

        Adder4008C::~Adder4008C()
        {}

        Tristate Adder4008C::compute(std::size_t pin)
        {
            if (pin >= this->_nbPins)
                return FALSE;
                // throw ComponentException("Pin out of range");
            return _pinLinks[pin]->getVal();
        }

        IComponent *createAdder4008C(std::string name)

        {
            std::vector<AGate *> gates = std::vector<AGate *>(1, nullptr);
            gates[0] = new gates::AdderGate;

            return new Adder4008C(name, gates);
        }

    }

    namespace gates {
        AdderGate::AdderGate():
        AGate(9, 5)
        {}

        AdderGate::~AdderGate()
        {}

        Tristate halfAdder(Tristate n1, Tristate n2, Tristate carry)
        {
            auto a = n1 ^ n2;
            auto b = a ^ carry;
            (void)b;
            return n1 ^ n2 ^ carry;
        }

        Tristate halfAdder(Tristate n1, Tristate n2)
        {
            return n1 ^ n2;
        }

        Tristate fullAdder(Tristate n1, Tristate n2, Tristate carry)
        {
            return (n1 & n2) | (n1 & carry) | (n2 & carry);
        }

        Tristate fullAdder(Tristate n1, Tristate n2)
        {
            return n1 & n2;
        }

        void AdderGate::simulate()
        {
            // This function now computes each pin individually. This allows an input to be undefined, while computing other possible values
            std::vector<Tristate> nb1 = std::vector<Tristate>();
            std::vector<Tristate> nb2 = std::vector<Tristate>();
            std::vector<Tristate> tmp;
            Tristate carry;

            if (isTickSync())
                return;
            _tickCounter++;
            for (int i = 0; i < 8; i += 2) {
                nb1.push_back(_inPins[7 - i]->reduceInput());
                nb2.push_back(_inPins[7 - (i + 1)]->reduceInput());
            }
            carry = _inPins[8]->reduceInput();
            for (int i = 0; i < 4; i++) {
                auto a = halfAdder(nb1[i], nb2[i], carry);
                _outPins[i]->setVal(a);
                carry = fullAdder(nb1[i], nb2[i], carry);
            }
            _outPins[4]->setVal(carry);
        }
    }
}