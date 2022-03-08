/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** Clock
*/

#include "../../../include/Sequential.hpp"

namespace nts {
    namespace gates {
        ClockGate::ClockGate():
        AGate(0, 1), _upcoming(UNDEFINED)
        {}


        ClockGate::~ClockGate()
        {}

        void ClockGate::setVal(Tristate state)
        {
            _upcoming = state;
        }

        void ClockGate::simulate()
        {
            if (isTickSync())
                return;
            _tickCounter++;
            _outPins[0]->setVal(_upcoming);
            _upcoming = !_upcoming;
        }
    }

    namespace components {
        ClockComponent::ClockComponent(std::string name, std::vector<AGate *>gates):
        AInputC(name, gates, true)
        {
            assignPin(0, 0, 0);
        }

        IComponent *createClockComponent(std::string name)
        {
            std::vector<AGate *> gates = std::vector<AGate *>(1, nullptr);
            gates[0] = new gates::ClockGate;

            return new ClockComponent(name, gates);
        }

        void ClockComponent::dump() const
        {
            std::cout << "  " << _name << ": " << _pinLinks[0]->getVal() << std::endl;
        }
    }
}