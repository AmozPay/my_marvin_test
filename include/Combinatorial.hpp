/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** LogicalGates
*/

#ifndef LOGICALGATES_HPP_
#define LOGICALGATES_HPP_

#include "Core.hpp"

namespace nts {

    namespace gates {
        class TrueGate: public AGate {
            public:
                TrueGate();
                ~TrueGate();
                void simulate() final;
        };

        class UndefinedGate: public AGate {
            public:
                UndefinedGate();
                ~UndefinedGate();
                void simulate() final;
        };


        class FalseGate: public AGate {
            public:
                FalseGate();
                ~FalseGate();
                void simulate() final;
        };

        class AndGate: public AGate {
            public:
                AndGate();
                ~AndGate();
                void simulate() final;
        };

        class OrGate: public AGate {
            public:
                OrGate();
                ~OrGate();
                void simulate() final;
        };

        class NandGate: public AGate {
            public:
                NandGate();
                ~NandGate();
                void simulate() final;
        };

        class NorGate: public AGate {
            public:
                NorGate();
                ~NorGate();
                void simulate() final;
        };

        class NotGate: public AGate {
            public:
                NotGate();
                ~NotGate();
                void simulate() final;
        };

        class XorGate: public AGate {
            public:
                XorGate();
                ~XorGate();
                void simulate() final;
        };
        class AdderGate: public AGate {
            public:
                AdderGate();
                ~AdderGate();
                void simulate() final;
                void resetOutput(Tristate state = FALSE);

        };
        class InputGate: public AGate {
            public:
                InputGate();
                ~InputGate();
                void setVal(Tristate state);
                void simulate() final;
            private:
                Tristate _upcoming;
        };


        class OutputGate: public AGate {
            public:
                OutputGate();
                ~OutputGate();
                Tristate getVal() const;
                void simulate() final;
            private:
                Tristate _val;
        };

        class Selector8Gate: public AGate {
            public:
                Selector8Gate();
                ~Selector8Gate();
                void simulate() final;
        };
    }

    namespace components {

        class AInputC: public AComponent {
            public:
                AInputC(std::string name, std::vector<AGate *>gates, bool isClock = false);
                void setVal(Tristate state);
            private:
                bool _isClock;
        };
        class TrueComponent: public AComponent {
            public:
                TrueComponent(std::string name, std::vector<AGate *>gates);
                void dump() const override;
        };
        class FalseComponent: public AComponent {
            public:
                FalseComponent(std::string name, std::vector<AGate *>gates);
                void dump() const override;
        };

        class InputComponent: public AInputC {
            public:
                InputComponent(std::string name, std::vector<AGate *>gates);
                void dump() const override;
        };

        class OutputComponent: public AComponent {
            public:
                OutputComponent(std::string name, std::vector<AGate *>gates);
                Tristate getVal() const;
                void dump() const override;
        };

        class Nand4011C: public AComponent {
            public:
                Nand4011C(std::string name, std::vector<AGate *>gates);
                Tristate compute(std::size_t pin) override;
        };
        class Nor4001C: public AComponent {
            public:
                Nor4001C(std::string name, std::vector<AGate *>gates);
                Tristate compute(std::size_t pin) override;
        };
        class Xor4030C: public AComponent {
            public:
                Xor4030C(std::string name, std::vector<AGate *>gates);
                Tristate compute(std::size_t pin) override;
        };
        class And4081C: public AComponent {
            public:
                And4081C(std::string name, std::vector<AGate *>gates);
                Tristate compute(std::size_t pin) override;
        };
        class Or4071C: public AComponent {
            public:
                Or4071C(std::string name, std::vector<AGate *>gates);
                Tristate compute(std::size_t pin) override;
        };
        class Not4069C: public AComponent {
            public:
                Not4069C(std::string name, std::vector<AGate *>gates);
                Tristate compute(std::size_t pin) override;
        };

        class Adder4008C: public AComponent {
            public:
                Adder4008C(std::string name, std::vector<AGate *>gates);
                ~Adder4008C();
                Tristate compute(std::size_t pin) override;
        };
        class Selector4512C: public AComponent {
            public:
                Selector4512C(std::string name, std::vector<AGate *>gates);
                ~Selector4512C();
                Tristate compute(std::size_t pin) override;
        };

        IComponent *createTrueComponent(std::string name);
        IComponent *createFalseComponent(std::string name);
        IComponent *createInputComponent(std::string name);
        IComponent *createNand4011C(std::string name);
        IComponent *createNor4001C(std::string name);
        IComponent *createXor4030C(std::string name);
        IComponent *createAnd4081C(std::string name);
        IComponent *createOr4071C(std::string name);
        IComponent *createNot4069C(std::string name);
        IComponent *createAdder4008C(std::string name);
        IComponent *createSelector4512Component(std::string name);
        IComponent *createOutputComponent(std::string name);
    }

}



#endif /* !LOGICALGATES_HPP_ */
