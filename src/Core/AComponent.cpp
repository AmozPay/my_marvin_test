/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** Component
*/

#include "Core.hpp"
#include <Combinatorial.hpp>
#include <iomanip>
#include <iostream>
#include <ostream>

namespace nts {
    AComponent::AComponent(std::string name, std::size_t nbGates, std::vector<AGate *>gates, ComponentType type):
    _name(name), _nbGates(nbGates), _gates(gates), _type(type)
    {
        std::size_t nbPins = 0;

        for (std::size_t i = 0; i < nbGates; i++) {
            nbPins += _gates[i]->getNbPins();
        }
        _nbPins = nbPins;
        _pinLinks = std::vector<Pin *>(_type == C_BASIC ? nbPins + 2 : _nbPins, nullptr); // add 2 electric pins
    }

    void AComponent::assignPin(std::size_t componentPin, std::size_t componentGate, std::size_t gatePin)
    {
        _pinLinks[componentPin] = (*_gates[componentGate])[gatePin];
    }

    AComponent::~AComponent()
    {
        for (auto gate: _gates) {
            delete gate;
        }
    }

    void AComponent::simulate(std::size_t ticks)
    {
        for (std::size_t i = 0; i < ticks; i++) {
            for (std::size_t  j = 0; j < _nbGates; j++) {
                _gates[j]->simulate();
            }
        }
    }

    std::string AComponent::getName() const
    {
        return _name;
    }

    void AComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
    {
        Pin *selectedPin = this->operator[](pin);

        selectedPin->connectPin(other[otherPin], getName(), other.getName());
    }

    void AComponent::dump() const
    {
        std::cout << "  *** " << _name << " ***" <<std::endl;
        for (std::size_t i = 0; i < _nbGates; i++) {
            _gates[i]->dump(_name);
        }
    }
    Pin *AComponent::operator[](std::size_t pin)
    {
        if ((pin >= _nbPins && _type != C_BASIC) || (_type == C_BASIC && pin >= _nbPins + 2)) {
            throw ComponentException("Pin out of range");
        }
        if (_pinLinks[pin] == nullptr) {
            throw ComponentException("Pin not set");
        }
        return _pinLinks[pin];
    }

    void AComponent::assign2In1Out4() {
        // 1st gate
        assignPin(0, 0, 0);
        assignPin(1, 0, 1);
        assignPin(2, 0, 2);
        // 2nd gate (output first)
        assignPin(3, 1, 2);
        assignPin(4, 1, 0);
        assignPin(5, 1, 1);
        // skip pin 6 (electrical)
        // 3rd gate (output last)
        assignPin(7, 2, 0);
        assignPin(8, 2, 1);
        assignPin(9, 2, 2);
        // 4th gate (output first)
        assignPin(10, 3, 2);
        assignPin(11, 3, 0);
        assignPin(12, 3, 1);
    }

    Tristate AComponent::compute(std::size_t pin)
    {
        if (pin >= this->_nbPins)
            throw ComponentException("Pin out of range");
        if (!_pinLinks[pin])
            throw ComponentException("Pin not set by user");
        return _pinLinks[pin]->getVal();
    }

    ComponentType AComponent::getType() const
    {
        return _type;
    }
}
