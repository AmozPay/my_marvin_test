/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** Component
*/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <cstddef>
#include <memory>
#include <vector>
#include <exception>
#include <string>
#include <array>
#include <iostream>

namespace nts {
    class ntsError: public std::exception {
        public:
            ntsError(std::string msg):
            _msg(msg) {}
            const char *what() const noexcept override
            {
                return _msg.data();
            }
        private:
            const std::string _msg;
    };

    enum Tristate {
        UNDEFINED = (-true),
        TRUE = true,
        FALSE = false
    };

    class Pin;

    class AGate {
        public:
            AGate(size_t nbInputs, std::size_t nbOutput, std::size_t nbDual = 0);
            virtual ~AGate();
            virtual void simulate() = 0;
            virtual void dump(std::string name) const;
            virtual std::size_t getNbPins() const;
            Pin *operator[](std::size_t pin); // returns an input gate
            bool isTickSync() const;
        protected:
            size_t _nbInputs;
            size_t _nbOutputs;
            size_t _nbDual;
            std::vector<Pin *> _inPins;
            std::vector<Pin *> _outPins;
            std::vector<Pin *> _dualPins;
            size_t _tickCounter;


    };

    class Pin {
        public:
            class PinException: public std::exception {
                public:
                    PinException(std::string msg): _msg(msg) {}
                    const char *what() const noexcept override
                    {
                        return _msg.data();
                    }
                private:
                    const std::string _msg;
            };
            enum Type {
                INPUT,
                OUTPUT,
                DUAL
            };
            Pin(Type type, AGate *gate);
            ~Pin();
            Type getType() const;
            const std::vector<Pin *> &getInput() const;
            bool isValidInput() const;
            Tristate reduceInput(Tristate actionOnIn(Pin *) = Pin::baseReduce);
            static Tristate reduceInput(const std::vector<Pin *> &pins, Tristate actionOnIn(Pin *) = Pin::baseReduce);
            static Tristate baseReduce(Pin *pin);
            AGate *getGate() const;
            void connectPin(Pin *in, std::string thisName, std::string otherName);
            Tristate getVal() const;
            void setVal(Tristate val);
            static void setAll(std::vector<Pin *> &pins, Tristate value);
        private:
            Type _type;
            std::vector<Pin *> _ins;
            AGate *_gate;
            Tristate _val;
    };


    enum ComponentType {
        C_STATIC_INPUT,
        C_INPUT,
        C_OUTPUT,
        C_BASIC,
        C_DEVICE
    };
    class IComponent {
        public:
            virtual ~IComponent() = default;
            virtual void simulate(std::size_t ticks) = 0;
            virtual nts::Tristate compute(std::size_t pin) = 0;
            virtual void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) = 0;
            virtual void dump() const = 0;
            virtual Pin *operator[](std::size_t pin) = 0;
            virtual std::string getName() const = 0;
            virtual ComponentType getType() const = 0;
        protected:
        private:
    };

    class AComponent: public IComponent {
        public:
            class ComponentException: public std::exception {
                public:
                    ComponentException(std::string msg): _msg(msg) {}
                    const char *what() const noexcept override
                    {
                        return _msg.data();
                    }
                private:
                    const std::string _msg;
            };
            AComponent(std::string name, size_t nbGates, std::vector<AGate *>gates, ComponentType = ComponentType::C_BASIC);
            virtual ~AComponent() override;
            void simulate(std::size_t ticks = 1) override;
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
            void dump() const override;
            Pin *operator[](std::size_t pin) override;
            void assignPin(std::size_t pin, std::size_t gate, std::size_t gatePin);
            void assign2In1Out4();
            Tristate compute(std::size_t pin) override;
            std::string getName() const;
            ComponentType getType() const override;
            // this class is still abstract because IComponent::compute() is still not defined here
        protected:
            std::string _name;
            std::size_t _nbGates;
            std::vector<AGate *>_gates;
            std::vector<Pin *>_pinLinks;
            std::size_t _nbPins;
            ComponentType _type;
    };


    namespace components {


    }
    std::string fmtTristate(Tristate state);
    Tristate operator&(Tristate a, Tristate b);
    Tristate operator|(Tristate a, Tristate b);
    Tristate operator!(Tristate a);
    Tristate operator^(Tristate a, Tristate b);

    Tristate stoTristate(std::string & s);
    std::ostream& operator<<(std::ostream& os, const Tristate &state);
    int operator+(Tristate a, Tristate b);
    int binToDec(std::vector<Tristate> vec);
    std::vector<Tristate> decToBin(unsigned int number);

    extern std::size_t tickCounter;

    namespace test {
        void setTickCounter();
    }
}

#endif /* !COMPONENT_HPP_ */
