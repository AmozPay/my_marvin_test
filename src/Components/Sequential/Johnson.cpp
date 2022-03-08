/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** Johnson
*/

#include "../../../include/Sequential.hpp"
#include "Core.hpp"

namespace nts {
    namespace gates {
        JohnsonGate::JohnsonGate():
        AGate(3, 11)
        , _state(0)
        , _lastClock(FALSE)
        {}


        JohnsonGate::~JohnsonGate()
        {}


        void JohnsonGate::simulate()
        {
            Tristate reset = FALSE;
            Tristate clock = FALSE;
            Tristate invClock = FALSE;

            if (isTickSync())
                return;
            _tickCounter++;
            if (_inPins[0])
                reset = _inPins[0]->reduceInput();
            if (_inPins[1])
                clock = _inPins[1]->reduceInput();
            if (_inPins[2])
                invClock = _inPins[2]->reduceInput();
            if (clock == UNDEFINED || reset == UNDEFINED || clock == UNDEFINED) {
                setToState();
                return;
            }
            if (clock == invClock)
                return;
            if (clock == TRUE && _lastClock == FALSE) {
                _state++;
                if (_state >= 10)
                    _state = 0;
            }
            _lastClock = clock;
            if (reset == TRUE)
                _state = 0;
            setToState();
        }

        void JohnsonGate::setToState() {
            for (int i = 0; i < 10; i++) {
                _outPins[i]->setVal((_state == i) ? TRUE : FALSE);
            }
            _outPins[10]->setVal((_state >= 5) ? TRUE : FALSE);
        }
    }

    namespace components {
        Johnson4017::Johnson4017(std::string name, std::vector<AGate *>gates):
        AComponent(name, gates.size(), gates)
        , _counter(0)
        {
            assignPin(0, 0, 8);
            assignPin(1, 0, 4);
            assignPin(2, 0, 3);
            assignPin(3, 0, 5);
            assignPin(4, 0, 9);
            assignPin(5, 0, 10);
            assignPin(6, 0, 6);

            assignPin(8, 0, 11);
            assignPin(9, 0, 7);
            assignPin(10, 0, 12);
            assignPin(11, 0, 13);
            assignPin(12, 0, 2);
            assignPin(13, 0, 1);
            assignPin(14, 0, 0);
        }

        Tristate Johnson4017::compute(std::size_t pin)
        {
            if (pin >= this->_nbPins)
                throw ComponentException("Pin out of range");
            return _pinLinks[pin]->getVal();
        }

        IComponent *createJohnson4017(std::string name)
        {
            std::vector<AGate *> gates = std::vector<AGate *>(1, nullptr);
            gates[0] = new gates::JohnsonGate;

            return new Johnson4017(name, gates);
        }
    }
}