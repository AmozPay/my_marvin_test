/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** Sequential
*/

#ifndef SEQUENTIAL_HPP_
#define SEQUENTIAL_HPP_

#include "Core.hpp"
#include "Combinatorial.hpp"

namespace nts {
    namespace gates {
        class ClockGate: public AGate {
            public:
                ClockGate();
                ~ClockGate();
                void setVal(Tristate state);
                void simulate() final;
            private:
                Tristate _upcoming;

        };
        class JohnsonGate: public AGate {
            public:
                JohnsonGate();
                ~JohnsonGate();
                void setVal(Tristate state);
                void simulate() final;
            private:
                int _state;
                Tristate _lastClock;
                void setToState();
        };

        class ShiftGate: public AGate {
            public:
                ShiftGate();
                ~ShiftGate();
                void simulate() final;
            private:
                std::vector<Tristate> _values;
        };

        class CounterGate: public AGate {
            public:
                CounterGate();
                ~CounterGate();
                void simulate() final;
            private:
                int _state;
        };

        class DecoderGate: public AGate {
            public:
                DecoderGate();
                ~DecoderGate();
                void simulate() final;
            private:
                std::vector<nts::Tristate> _state;
        };

        enum ramInPins {
            WE,
            OE,
            CE,
        };
        class RamGate: public AGate {
            public:
                RamGate();
                ~RamGate();
                void simulate() final;
            private:
                std::vector<std::vector<nts::Tristate>> _memory;
                int getAddress();
                void readData();
                void writeData();
        };

        class RomGate: public AGate {
            public:
                RomGate();
                ~RomGate();
                void simulate() final;
            private:
                std::vector<char> _memory;
                int getAddress();
                void readData();
        };

        class FlipFlopGate: public AGate {
            public:
                enum inputs {
                    CLOCK,
                    RESET,
                    DATA,
                    SET
                };
                FlipFlopGate();
                ~FlipFlopGate();
                void simulate() final;

        };


        class LoggerGate: public AGate {
            public:
                LoggerGate();
                ~LoggerGate();
                void simulate() final;

        };
    } // namespace gates

    namespace components {
        class ClockComponent: public AInputC {
            public:
                ClockComponent(std::string name, std::vector<AGate *>gates);
                void dump() const;
        };
        class Counter4040C: public AComponent {
            public:
                Counter4040C(std::string name, std::vector<AGate *>gates);
        };

        class Decoder4514C: public AComponent {
            public:
                Decoder4514C(std::string name, std::vector<AGate *>gates);
        };

        class Ram4801C: public AComponent {
            public:
                Ram4801C(std::string name, std::vector<AGate *>gates);
        };

        class Rom2716C: public AComponent {
            public:
                Rom2716C(std::string name, std::vector<AGate *>gates);
        };

        class Johnson4017: public AComponent {
            public:
                Johnson4017(std::string name, std::vector<AGate *>gates);
                Tristate compute(size_t pin);
            protected:
                int _counter;
        };

        class FlipFlop4013C: public AComponent {
            public:
                FlipFlop4013C(std::string name, std::vector<AGate *>gates);
                Tristate compute(size_t pin);
                void setVal(Tristate state);
        };
        class Shift4094C: public AComponent {
            public:
                Shift4094C(std::string name, std::vector<AGate *>gates);
                Tristate compute(size_t pin);
        };

        class LoggerC: public AComponent {
            public:
                LoggerC(std::string name, std::vector<AGate *>gates);
                Tristate compute(size_t pin);
        };

        IComponent *createClockComponent(std::string name);
        IComponent *createJohnson4017(std::string name);
        IComponent *createCounter4040C(std::string name);
        IComponent *createDecoder4514C(std::string name);
        IComponent *createRam4801C(std::string name);
        IComponent *createRom2716C(std::string name);
        IComponent *createFlipFlop4013C(std::string name);
        IComponent *createShift4094C(std::string name);
        IComponent *createLoggerC(std::string name);
    }
}

#endif /* !SEQUENTIAL_HPP_ */
