/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** LogicalGates
*/

#include "../../../include/Core.hpp"
#include "../../../include/Combinatorial.hpp"
#include "../../../include/Sequential.hpp"

namespace nts {
    namespace gates {
        AndGate::AndGate():
        AGate(2, 1)
        {}

        AndGate::~AndGate()
        {}

        void AndGate::simulate()
        {
            Tristate a;
            Tristate b;

            if (isTickSync())
                return;
            _tickCounter++;
            if (!_inPins[0] || !_inPins[1]) {
                _outPins[0]->setVal(FALSE);
                return;
            }
            a = _inPins[0]->reduceInput();
            b = _inPins[1]->reduceInput();
            _outPins[0]->setVal(a & b);
        }

        OrGate::OrGate():
        AGate(2, 1)
        {}

        OrGate::~OrGate()
        {}

        void OrGate::simulate()
        {
            Tristate a = FALSE;
            Tristate b = FALSE;

            if (isTickSync())
                return;
            _tickCounter++;
            if (_inPins[0])
                a = _inPins[0]->reduceInput();
            if (_inPins[1])
                b = _inPins[1]->reduceInput();
            _outPins[0]->setVal(a | b);
        }

        NandGate::NandGate():
        AGate(2, 1)
        {}

        NandGate::~NandGate()
        {}

        void NandGate::simulate()
        {
            Tristate a = FALSE;
            Tristate b = FALSE;

            if (isTickSync())
                return;
            _tickCounter++;
            if (_inPins[0])
                a = _inPins[0]->reduceInput();
            if (_inPins[1])
                b = _inPins[1]->reduceInput();
            _outPins[0]->setVal(!(a & b));
        }

        XorGate::XorGate():
        AGate(2, 1)
        {}

        XorGate::~XorGate()
        {}

        void XorGate::simulate()
        {
            Tristate a = FALSE;
            Tristate b = FALSE;

            if (isTickSync())
                return;
            _tickCounter++;
            if (_inPins[0])
                a = _inPins[0]->reduceInput();
            if (_inPins[1])
                b = _inPins[1]->reduceInput();
            _outPins[0]->setVal(a ^ b);
        }

        NorGate::NorGate():
        AGate(2, 1)
        {}

        NorGate::~NorGate()
        {}

        void NorGate::simulate()
        {
            Tristate a = FALSE;
            Tristate b = FALSE;

            if (isTickSync())
                return;
            _tickCounter++;
            if (_inPins[0])
                a = _inPins[0]->reduceInput();
            if (_inPins[1])
                b = _inPins[1]->reduceInput();
            _outPins[0]->setVal(!(a | b));
        }


        NotGate::NotGate():
        AGate(1, 1)
        {}

        NotGate::~NotGate()
        {}

        void NotGate::simulate()
        {
            Tristate a = FALSE;

            if (isTickSync())
                return;
            _tickCounter++;
            if (_inPins[0])
                a = _inPins[0]->reduceInput();
            a = _inPins[0]->reduceInput();
            _outPins[0]->setVal(!a);
        }
    }
}
