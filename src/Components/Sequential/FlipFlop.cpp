/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** FlipFlop
*/

#include "../../../include/Sequential.hpp"

namespace nts {
    namespace gates {
        FlipFlopGate::FlipFlopGate():
        AGate(4, 2)
        {}


        FlipFlopGate::~FlipFlopGate()
        {}


        void FlipFlopGate::simulate()
        {
            Tristate set = FALSE;
            Tristate reset = FALSE;
            Tristate clock = FALSE;

            if (isTickSync())
                return;
            _tickCounter++;
            reset = _inPins[RESET]->reduceInput();
            set = _inPins[SET]->reduceInput();
            clock = _inPins[CLOCK]->reduceInput();
            if (set == FALSE && reset == FALSE) {
                if (_inPins[CLOCK]) {
                    clock = _inPins[CLOCK]->reduceInput();
                    if (clock == TRUE) {
                        _outPins[0]->setVal(_inPins[DATA]->getVal());
                        _outPins[1]->setVal(!_inPins[DATA]->getVal());
                    } else if (clock == FALSE) {
                        return; // preserve data from last tick
                    } else {
                        _outPins[0]->setVal(UNDEFINED);
                        _outPins[1]->setVal(UNDEFINED);
                    }
                }
                return;
            }
            _outPins[0]->setVal(_inPins[SET]->getVal()); // Q = SET
            _outPins[1]->setVal(_inPins[RESET]->getVal()); // Q_ = RESET
        }
    }

    namespace components {
        FlipFlop4013C::FlipFlop4013C(std::string name, std::vector<AGate *>gates):
        AComponent(name, gates.size(), gates)
        {
            //FlipFlop 1
            assignPin(0, 0, 4);
            assignPin(1, 0, 5);
            assignPin(2, 0, gates::FlipFlopGate::CLOCK);
            assignPin(3, 0, gates::FlipFlopGate::RESET);
            assignPin(4, 0, gates::FlipFlopGate::DATA);
            assignPin(5, 0, gates::FlipFlopGate::SET);

            //FlipFlop 2
            assignPin(12, 1, 4);
            assignPin(11, 1, 5);
            assignPin(10, 1, gates::FlipFlopGate::CLOCK);
            assignPin(9, 1, gates::FlipFlopGate::RESET);
            assignPin(8, 1, gates::FlipFlopGate::DATA);
            assignPin(7, 1, gates::FlipFlopGate::SET);
        }

        // FlipFlop4013C::~FlipFlop4013C()
        // {}

        Tristate FlipFlop4013C::compute(std::size_t pin)
        {
            if (pin >= this->_nbPins)
                throw ComponentException("Pin out of range");
            return _pinLinks[pin]->getVal();
        }

        IComponent *createFlipFlop4013C(std::string name)
        {
            std::vector<AGate *> gates = std::vector<AGate *>(2, nullptr);
            gates[0] = new gates::FlipFlopGate;
            gates[1] = new gates::FlipFlopGate;

            return new FlipFlop4013C(name, gates);
        }
    }
}