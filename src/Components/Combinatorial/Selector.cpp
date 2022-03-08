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
        Selector4512C::Selector4512C(std::string name, std::vector<AGate *>gates):
        AComponent(name, gates.size(), gates)
        {
            for (size_t i = 0; i < 7; i++)
                assignPin(i, 0, i);
            for (size_t i = 8; i < 13; i++)
                assignPin(i, 0, i - 1);
            assignPin(14, 0, 12); // output Z is before last input pin "OE"
            assignPin(13, 0, 13);
        }

        Selector4512C::~Selector4512C()
        {}

        Tristate Selector4512C::compute(std::size_t pin)
        {
            if (pin >= this->_nbPins)
                throw ComponentException("Pin out of range");
            return _pinLinks[pin]->getVal();
        }

        IComponent *createSelector4512Component(std::string name)
        {
            std::vector<AGate *> gates = std::vector<AGate *>(1, nullptr);
            gates[0] = new gates::Selector8Gate;

            return new Selector4512C(name, gates);
        }

    }

    namespace gates {
        Selector8Gate::Selector8Gate():
        AGate(13, 1)
        {}

        Selector8Gate::~Selector8Gate()
        {}

        void Selector8Gate::simulate()
        {

            if (isTickSync())
                return;
            _tickCounter++;
            std::vector<Tristate> selBus = std::vector<Tristate>();
            int sel;
            Tristate OE = _inPins[12]->reduceInput();
            Tristate inhibit = _inPins[8]->reduceInput();

            for (auto it: _inPins)
                it->reduceInput(); // simulate all
            if (OE != FALSE || inhibit == UNDEFINED) {
                _outPins[0]->setVal(UNDEFINED);
            } else if (inhibit == TRUE) {
                _outPins[0]->setVal(FALSE);
            } else {
                for (int i = 9; i <= 11; i++)
                    selBus.push_back(_inPins[i]->reduceInput());
                sel = binToDec(selBus);
                if (sel == -1) {
                    _outPins[0]->setVal(UNDEFINED);
                    return;
                }
                _outPins[0]->setVal(_inPins[sel]->reduceInput());
            }
        }
    }
}