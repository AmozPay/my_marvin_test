/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** Shift
*/

#include "../../../include/Sequential.hpp"

namespace nts {

    namespace gates {
        ShiftGate::ShiftGate():
        AGate(4, 10)
        , _values(std::vector<Tristate>(10, UNDEFINED))
        {}


        ShiftGate::~ShiftGate()
        {}

        void ShiftGate::simulate()
        {
            if (isTickSync())
                return;
            _tickCounter++;

            const Tristate strobe = _inPins[0]->reduceInput();
            const Tristate data = _inPins[1]->reduceInput();
            const Tristate clock = _inPins[2]->reduceInput();
            const Tristate oe = _inPins[3]->reduceInput();

            if (oe == FALSE || oe == UNDEFINED) {
                Pin::setAll(_outPins, UNDEFINED);
                if (clock == UNDEFINED)
                    return;
                if (clock == TRUE)
                    _values[8] = _values[6]; // Q_S = Q_7, no change for Q_SP
                else
                    _values[9] = _values[6]; // Q_SP = Q7, no change for Q_S
                _outPins[8]->setVal(_values[8]);
                _outPins[9]->setVal(_values[9]);
                return;
            }
            if (clock == UNDEFINED) {
                Pin::setAll(_outPins, UNDEFINED);
                return;
            }
            if (clock == TRUE) {
                _values[8] = _values[6];
                _outPins[8]->setVal(_values[8]);
                if (strobe == TRUE) {
                    for (int i = 7; i > 0; i--)
                        _values[i] = _values[i - 1];
                    _values[0] = data;
                }
                if (strobe != UNDEFINED) {
                    for (int i = 0; i < 10; i++)
                        _outPins[i]->setVal(_values[i]);
                } else {
                    Pin::setAll(_outPins, UNDEFINED);
                }
            } else {
                _values[9] = _values[6];
                _outPins[9]->setVal(_values[9]);
            }
        }
    } // namespace gates

    namespace components {
        Shift4094C::Shift4094C(std::string name, std::vector<AGate *>gates):
        AComponent(name, gates.size(), gates)
        {
            assignPin(0, 0, 0);
            assignPin(1, 0, 1);
            assignPin(2, 0, 2);
            assignPin(14, 0, 3);

            for (int i = 0; i < 4; i++)
                assignPin(i + 3, 0, i + 4);
            assignPin(13, 0, 8);
            assignPin(12, 0, 9);
            assignPin(11, 0, 10);
            assignPin(10, 0, 11);
            assignPin(9, 0, 12);
            assignPin(8, 0, 13);
        }

        Tristate Shift4094C::compute(std::size_t pin)
        {
            if (pin >= this->_nbPins)
                throw ComponentException("Pin out of range");
            return _pinLinks[pin]->getVal();
        }

        IComponent *createShift4094C(std::string name)
        {
            std::vector<AGate *> gates = std::vector<AGate *>(1, nullptr);
            gates[0] = new gates::ShiftGate;

            return new Shift4094C(name, gates);
        }
    } // namespace components
}