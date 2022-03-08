/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** Inputs
*/

#include "../../../include/Combinatorial.hpp"
#include "../../../include/Sequential.hpp"


namespace nts {
    namespace gates {

        TrueGate::TrueGate():
        AGate(0, 1)
        {
            _outPins[0]->setVal(TRUE);
        }

        TrueGate::~TrueGate()
        {}

        void TrueGate::simulate()
        {}

        InputGate::InputGate():
        AGate(0, 1), _upcoming(UNDEFINED)
        {}


        InputGate::~InputGate()
        {}

        void InputGate::setVal(Tristate state)
        {
            _upcoming = state;
        }

        void InputGate::simulate()
        {
            _outPins[0]->setVal(_upcoming);
        }

        OutputGate::OutputGate():
        AGate(1, 0)
        {}


        OutputGate::~OutputGate()
        {}

        Tristate OutputGate::getVal() const
        {
            return _inPins[0]->reduceInput();
        }

        void OutputGate::simulate()
        {
            _inPins[0]->reduceInput();
        }

        FalseGate::FalseGate():
        AGate(0, 1)
        {
            _outPins[0]->setVal(FALSE);
        }

        FalseGate::~FalseGate()
        {}

        void FalseGate::simulate()
        {
            return;
        }

        UndefinedGate::UndefinedGate():
        AGate(0, 1)
        {}

        UndefinedGate::~UndefinedGate()
        {}

        void UndefinedGate::simulate()
        {
            return;
        }

    }

    namespace components {

        AInputC::AInputC(std::string name, std::vector<AGate *> gates, bool isClock):
        AComponent(name, 1, gates, ComponentType::C_INPUT),
        _isClock(isClock)
        {
        }

        void AInputC::setVal(Tristate state)
        {
            if (_isClock)
                dynamic_cast<gates::ClockGate *>(_gates[0])->setVal(state);
            else
                dynamic_cast<gates::InputGate *>(_gates[0])->setVal(state);
        }

        InputComponent::InputComponent(std::string name, std::vector<AGate *>gates):
        AInputC(name, gates, false)
        {
            assignPin(0, 0, 0);
        }

        IComponent *createInputComponent(std::string name)
        {
            std::vector<AGate *> gates = std::vector<AGate *>(1, nullptr);
            gates[0] = new gates::InputGate;

            return new InputComponent(name, gates);
        }

        void InputComponent::dump() const
        {
            std::cout << "  " << _name << ": " << _pinLinks[0]->getVal() << std::endl;
        }

        OutputComponent::OutputComponent(std::string name, std::vector<AGate *>gates):
        AComponent(name, 1, gates, ComponentType::C_OUTPUT)
        {
            assignPin(0, 0, 0);
        }

        IComponent *createOutputComponent(std::string name)
        {
            std::vector<AGate *> gates = std::vector<AGate *>(1, nullptr);
            gates[0] = new gates::OutputGate;

            return new OutputComponent(name, gates);
        }

        Tristate OutputComponent::getVal() const
        {
            return dynamic_cast<gates::OutputGate *>(_gates[0])->getVal();
        }

        void OutputComponent::dump() const
        {
            std::cout << "  " << _name << ": " << dynamic_cast<nts::gates::OutputGate *>(_gates[0])->getVal() << std::endl;
        }

        TrueComponent::TrueComponent(std::string name, std::vector<AGate *>gates):
        AComponent(name, 1, gates, ComponentType::C_STATIC_INPUT)
        {
            assignPin(0, 0, 0);
            this->operator[](0)->setVal(TRUE);
        }

        void TrueComponent::dump() const
        {
            std::cout << "  " << _name << ": " << _pinLinks[0]->getVal() << std::endl;
        }

        IComponent *createTrueComponent(std::string name)
        {
            std::vector<AGate *> gates =  std::vector<AGate *>(1, nullptr);
            gates[0] = new nts::gates::TrueGate;

            return new TrueComponent(name, gates);
        }

        FalseComponent::FalseComponent(std::string name, std::vector<AGate *>gates):
        AComponent(name, 1, gates, ComponentType::C_STATIC_INPUT)
        {
            assignPin(0, 0, 0);
            this->operator[](0)->setVal(FALSE);
        }

        void FalseComponent::dump() const
        {
            std::cout << "  " << _name << ": " << _pinLinks[0]->getVal() << std::endl;
        }

        IComponent *createFalseComponent(std::string name)
        {
            std::vector<AGate *> gates = std::vector<AGate *>(1, nullptr);
            gates[0] = new gates::FalseGate;

            return new FalseComponent(name, gates);
        }
    }
}