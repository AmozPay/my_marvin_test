/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** Ram
*/

#include "../../../include/Sequential.hpp"


namespace nts {

    namespace gates
    {
        RamGate::RamGate():
        AGate(13, 0, 10), _memory(std::vector<std::vector<Tristate>>(1024, std::vector<Tristate>(10, UNDEFINED)))
        {}


        RamGate::~RamGate()
        {}


        int RamGate::getAddress()
        {
            std::vector<Tristate> address_bus(10, UNDEFINED);
            const int nbControlPins = 3;
            for (int i = 0; i < 10; i++)
                address_bus[9 - i] = _inPins[i + nbControlPins]->reduceInput();
            return binToDec(address_bus);

        }

        void RamGate::readData()
        {
            int selAddress = getAddress();

            if (selAddress == -1) {
                Pin::setAll(_dualPins, UNDEFINED);
                return;
            }
            for (int i = 0; i < 8; i++)
                _dualPins[i]->setVal(_memory[selAddress][i]);
        }

        void RamGate::writeData()
        {
            int selAddress = getAddress();

            if (selAddress == -1)
                return;
            for (int i = 0; i < 8; i++) {
                _memory[selAddress][i] = _dualPins[i]->reduceInput();
                _dualPins[i]->setVal(_memory[selAddress][i]);
            }
        }

        void RamGate::simulate()
        {
            if (isTickSync())
                return;
            _tickCounter++;
            if (_inPins[ramInPins::CE]->reduceInput() == UNDEFINED ||
            _inPins[ramInPins::CE]->reduceInput() == FALSE ||
            _inPins[ramInPins::WE]->reduceInput() == UNDEFINED) {
                Pin::setAll(_dualPins, UNDEFINED);
                return;
            }
            if (_inPins[ramInPins::WE]->reduceInput() == TRUE) {
                writeData();
                return;
            }
            if (_inPins[ramInPins::OE]->reduceInput() == TRUE) {
                readData();
                return;
            }
            Pin::setAll(_dualPins, UNDEFINED);
        }
    } // namespace gates

    namespace components
    {
        Ram4801C::Ram4801C(std::string name, std::vector<AGate *>gates):
        AComponent(name, 1, gates)
        {
            const int nbControlInputs = 3;
            const int nbInputs = nbControlInputs + 10;

            for (int i = 0; i < 8; i++) // A7 to A0
                assignPin(i, 0, 7 + nbControlInputs - i);
            for (int i = 8; i < 11; i++)
                assignPin(i, 0, i - 8 + nbInputs); // DQ0 to DQ2
            for (int i = 12; i < 17; i++)
                assignPin(i, 0, i - 9 + nbInputs); // DQ3 to DQ7
            assignPin(17, 0, gates::ramInPins::CE);
            assignPin(19, 0, gates::ramInPins::OE);
            assignPin(20, 0, gates::ramInPins::WE);
            assignPin(21, 0, nbInputs - 1); // A9
            assignPin(22, 0, nbInputs - 2); // A8
        }

        IComponent *createRam4801C(std::string name)
        {
            std::vector<AGate *> gates = std::vector<AGate *>(1, nullptr);
            gates[0] = new gates::RamGate;

            return new Ram4801C(name, gates);
        }
    } // namespace components

}