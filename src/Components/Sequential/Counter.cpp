/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** Clock
*/

#include "../../../include/Sequential.hpp"

namespace nts {
    namespace gates {
        CounterGate::CounterGate():
        AGate(2, 12), _state(0)
        {}


        CounterGate::~CounterGate()
        {}

        void CounterGate::simulate()
        {
            if (isTickSync())
                return;
            _tickCounter++;
            for (auto it: _inPins)
                it->reduceInput(); //just simulate
            if (_inPins[0]->reduceInput() == UNDEFINED) {
                for (int i = 0; i < 12; i++)
                    _outPins[i]->setVal(UNDEFINED);
                return;
            }
            if (_inPins[0]->reduceInput() == TRUE) {
                for (int i = 0; i < 12; i++)
                    _outPins[i]->setVal(FALSE);
                _state = 0;
                return;
            }
            if (_inPins[1]->reduceInput() == UNDEFINED) {
                for (int i = 0; i < 12; i++)
                    _outPins[i]->setVal(UNDEFINED);
                return;
            }
            if (_inPins[1]->reduceInput() == FALSE)
                _state++;
            if (_state > 4096 * 2 - 1)
                _state = 0;
            std::vector<Tristate> list = decToBin(_state);
            for (size_t i = 0; i < 12; i++)
                _outPins[i]->setVal(FALSE);
            for (int i = list.size() - 1; i >= 0; i--) {
                _outPins[i]->setVal(list[i]);
            }
        }
    }

    namespace components {
        Counter4040C::Counter4040C(std::string name, std::vector<AGate *>gates):
        AComponent(name, 1, gates)
        {
            assignPin(0, 0, 13);
            assignPin(1, 0, 7);
            assignPin(2, 0, 6);
            assignPin(3, 0, 8);
            assignPin(4, 0, 5);
            assignPin(5, 0, 4);
            assignPin(6, 0, 3);

            assignPin(8, 0, 2);
            assignPin(9, 0, 1);
            assignPin(10, 0, 0);
            assignPin(11, 0, 10);
            assignPin(12, 0, 9);
            assignPin(13, 0, 11);
            assignPin(14, 0, 12);
        }

        IComponent *createCounter4040C(std::string name)
        {
            std::vector<AGate *> gates = std::vector<AGate *>(1, nullptr);
            gates[0] = new gates::CounterGate;

            return new Counter4040C(name, gates);
        }
    }
}