/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** AGate
*/

#include "../../include/Core.hpp"
#include <iostream>

namespace nts {

    AGate::AGate(std::size_t nbInputs, std::size_t nbOutputs, std::size_t nbDual):
    _nbInputs(nbInputs)
    , _nbOutputs(nbOutputs)
    , _nbDual(nbDual)
    , _inPins(std::vector<nts::Pin *>(nbInputs, nullptr))
    , _outPins(std::vector<nts::Pin *>(nbOutputs, nullptr))
    , _dualPins(std::vector<nts::Pin *>(nbDual, nullptr))
    , _tickCounter(0)
    {
        for (std::size_t i = 0; i < nbInputs; i++)
            _inPins[i] = new Pin(Pin::INPUT, this);
        for (std::size_t i = 0; i < nbOutputs; i++) {
            _outPins[i] = new Pin(Pin::OUTPUT, this);
            _outPins[i]->setVal(UNDEFINED);
        }
        for (std::size_t i = 0; i < nbDual; i++) {
            _dualPins[i] = new Pin(Pin::DUAL, this);
            _dualPins[i]->setVal(UNDEFINED);
        }
    }


    AGate::~AGate()
    {
        for(auto pin: _inPins)
            delete pin;
        for(auto pin: _outPins)
            delete pin;
    }

    void AGate::dump(std::string name) const
    {
        for (size_t i = 0; i < _nbInputs; i++) {
            std::cout << "  " <<  name << i << ": " << _inPins[i]->reduceInput() << std::endl;
        }
        for (size_t i = 0; i < _nbOutputs; i++) {
            std::cout << "  " << name << i + _nbInputs << ": " << _outPins[i]->getVal() << std::endl;
        }
    }

    std::size_t AGate::getNbPins() const
    {
        return _nbInputs + _nbOutputs + _nbDual;
    }

    bool AGate::isTickSync() const
    {
        if (_tickCounter != tickCounter)
            return false;
        return true;
    }

    Pin *AGate::operator[](std::size_t pin)
    {
        if (pin > this->getNbPins())
            throw Pin::PinException("undefinded pin used");
        if (pin < _nbInputs)
            return this->_inPins[pin];
        if (pin < _nbInputs + _nbOutputs)
            return this->_outPins[pin - _nbInputs];
        return _dualPins[pin - (_nbInputs + _nbOutputs)];
    }
}
