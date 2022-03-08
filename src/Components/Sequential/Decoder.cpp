/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** Decoder
*/

#include "../../../include/Sequential.hpp"


namespace nts {

    namespace gates
    {
        DecoderGate::DecoderGate():
        AGate(6, 16), _state(std::vector<nts::Tristate>(4, UNDEFINED))
        {}


        DecoderGate::~DecoderGate()
        {}

        void DecoderGate::simulate()
        {
            if (isTickSync())
                return;
            _tickCounter++;
            for (auto it: _inPins)
                it->reduceInput(); // just simulate all
            if (_inPins[1]->reduceInput() == TRUE) {
                Pin::setAll(_outPins, FALSE);
                return;
            }
            if (_inPins[1]->reduceInput() == UNDEFINED ||
            _inPins[0]->reduceInput() == UNDEFINED) {
                Pin::setAll(_outPins, UNDEFINED);
                return;
            }
            if (_inPins[0]->reduceInput() == FALSE) { //strobe
                for (int i = 2; i < 6; i++)
                    _state[i - 2] = _inPins[i]->reduceInput();
            }
            bool undef = false;
            for (auto it: _state)
                undef |= it == UNDEFINED;
            if (undef) {
                Pin::setAll(_outPins, UNDEFINED);
                return;
            }
            Pin::setAll(_outPins, FALSE);

            int selectedOutput = binToDec(_state);
            _outPins[selectedOutput]->setVal(TRUE);
        }
    } // namespace gates

    namespace components
    {
        Decoder4514C::Decoder4514C(std::string name, std::vector<AGate *>gates):
        AComponent(name, 1, gates)
        {
            const int nbInputs = 6;
            assignPin(0, 0, 0); // strobe
            assignPin(22, 0, 1); // inhibit

            assignPin(1, 0, 2); //inputs A to D
            assignPin(2, 0, 3);
            assignPin(20, 0, 4);
            assignPin(21, 0, 5);


            assignPin(3, 0, 7 + nbInputs);
            assignPin(4, 0, 6 + nbInputs);
            assignPin(5, 0, 5 + nbInputs);
            assignPin(6, 0, 4 + nbInputs);
            assignPin(7, 0, 3 + nbInputs);
            assignPin(8, 0, 1 + nbInputs);
            assignPin(9, 0, 2 + nbInputs);
            assignPin(10, 0, 0 + nbInputs);

            assignPin(19, 0, 10 + nbInputs);
            assignPin(18, 0, 11 + nbInputs);
            assignPin(17, 0, 8 + nbInputs);
            assignPin(16, 0, 9 + nbInputs);
            assignPin(15, 0, 14 + nbInputs);
            assignPin(14, 0, 15 + nbInputs);
            assignPin(13, 0, 12 + nbInputs);
            assignPin(12, 0, 13 + nbInputs);
        }

        IComponent *createDecoder4514C(std::string name)
        {
            std::vector<AGate *> gates = std::vector<AGate *>(1, nullptr);
            gates[0] = new gates::DecoderGate;

            return new Decoder4514C(name, gates);
        }
    } // namespace components

}