/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** Rom
*/

#include "../../../include/Sequential.hpp"
#include "Core.hpp"
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>


namespace nts {

    namespace gates
    {
        RomGate::RomGate():
        AGate(13, 8), _memory(std::vector<char>(1024, -1))
        {
            std::ifstream file("./rom.bin", std::ios::binary | std::ios::in);
            char c;
            int i = 0;
            while(file.read(&c, 1)) {
                _memory[i++] = c;
            }
        }


        RomGate::~RomGate()
        {}


        int RomGate::getAddress()
        {
            std::vector<Tristate> address_bus(11, UNDEFINED);
            const int nbControlPins = 2;
            for (int i = 0; i < 11; i++)
                address_bus[i] = _inPins[i + nbControlPins]->reduceInput();
            return binToDec(address_bus);
        }

        void RomGate::readData()
        {
            int selAddress = getAddress();
            std::vector<Tristate> res;

            if (selAddress == -1) {
                Pin::setAll(_outPins, UNDEFINED);
                return;
            }
            res = decToBin(_memory[selAddress]);
            for (int i = 0; i < 8; i++)
                _outPins[i]->setVal(res[i]);
        }

        /*void RomGate::writeData()
        {
            int selAddress = getAddress();

            if (selAddress == -1)
                return;
            for (int i = 0; i < 8; i++) {
                _memory[selAddress][i] = _dualPins[i]->reduceInput();
                _dualPins[i]->setVal(_memory[selAddress][i]);
            }
        }*/

        void RomGate::simulate()
        {
            if (isTickSync())
                return;
            _tickCounter++;
            if (_inPins[0]->reduceInput() == UNDEFINED || _inPins[1]->reduceInput() == UNDEFINED) {
                Pin::setAll(_outPins, UNDEFINED);
                return;
            }
            if (_inPins[0]->reduceInput() == TRUE || _inPins[1]->reduceInput() == TRUE) {
                Pin::setAll(_outPins, FALSE);
                return;
            }
            /*if (_inPins[ramInPins::WE]->reduceInput() == TRUE) {
                writeData();
                return;
            }*/
            readData();
        }
    } // namespace gates

    namespace components
    {
        Rom2716C::Rom2716C(std::string name, std::vector<AGate *>gates):
        AComponent(name, 1, gates)
        {
            const int nbControlInputs = 2;
            const int nbInputs = nbControlInputs + 11;

            for (int i = 0; i < 8; i++) // A7 to A0
                assignPin(i, 0, 7 + nbControlInputs - i);
            assignPin(8, 0, nbInputs);
            assignPin(9, 0, nbInputs + 1);
            assignPin(10, 0, nbInputs + 2);

            for (int i = 0; i < 5; i++)
                assignPin(12 + i, 0, nbInputs + 3 + i);
            assignPin(17, 0, 0);
            assignPin(18, 0, nbInputs - 1); // A10
            assignPin(19, 0, 1);
            assignPin(21, 0, nbInputs - 2); // A9
            assignPin(22, 0, nbInputs - 3); // A8
        }

        IComponent *createRom2716C(std::string name)
        {
            std::vector<AGate *> gates = std::vector<AGate *>(1, nullptr);
            gates[0] = new gates::RomGate;

            return new Rom2716C(name, gates);
        }
    } // namespace components

}