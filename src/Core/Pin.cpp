/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** Pin
*/

#include "Core.hpp"
#include <vector>

namespace nts {

    Pin::Pin(nts::Pin::Type type, AGate *gate):
          _type(type)
        , _ins(std::vector<Pin *>())
        , _gate(gate)
        , _val(UNDEFINED)
    {}

    Pin::~Pin()
    {}

    const std::vector<Pin *> &Pin::getInput() const
    {
        if (_type != INPUT) {
            throw PinException("Cannot get connected input pin from output pin");
        }
        return _ins;
    }

    void Pin::connectPin(Pin *in, std::string thisName, std::string otherName)
    {
        if (_type == INPUT || _type == DUAL) {
            _ins.push_back(in);
        } else if (in->getType() == INPUT || in->getType() == DUAL) {
            in->connectPin(this, otherName, thisName);
        } else
            throw PinException("Cannot connect input pin " + thisName + "to another input pin " + otherName);
    }

    AGate *Pin::getGate() const
    {
        if (_type != OUTPUT && _type != DUAL) {
            throw PinException("Cannot get gate of input pin");
        }
        return _gate;
    }

    Pin::Type Pin::getType() const
    {
        return _type;
    }

    Tristate Pin::getVal() const {
        return _val;
    }

    void Pin::setVal(Tristate val) {
        _val = val;
    }

    bool Pin::isValidInput() const {
        if (_ins.empty())
            return false;
        return true;
    }

    // a simple static fonction for the default comportement
    Tristate Pin::baseReduce(Pin *pin) {
        try {
            pin->getGate()->simulate();
            return pin->getVal();
        } catch (std::exception &e) {
            return FALSE;
        }
    }

    // a static Methode when we juste have a Pin list
    Tristate Pin::reduceInput(const std::vector<Pin *> &pins ,Tristate (*actionOnIn)(Pin *))
    {
        Tristate res = FALSE;
        for (auto pin : pins) {
            res = res | actionOnIn(pin);
        }
        return res;
    }

    // a simpler function when we use a input and want to reduce all connection
    Tristate Pin::reduceInput(Tristate (*actionOnIn)(Pin *))
    {
        Tristate res = FALSE;

        if (_type != INPUT && _type != DUAL) {
            throw PinException("reduceInput(): Selected pin is not an input pin");
        }
        for (auto pin : _ins) {
            res = res | actionOnIn(pin);
        }
        return res;
    }

    void Pin::setAll(std::vector<Pin *> &pins, Tristate value)
    {
        for (auto it: pins)
            it->setVal(value);
    }
}
