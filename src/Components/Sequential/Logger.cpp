/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** Logger
*/

#include "../../../include/Sequential.hpp"
#include <fstream>

namespace nts {

    namespace gates {
        LoggerGate::LoggerGate():
        AGate(10, 0)
        {}


        LoggerGate::~LoggerGate()
        {}

        void LoggerGate::simulate()
        {
            if (isTickSync())
                return;
            _tickCounter++;

            Tristate inhibit = _inPins[9]->reduceInput();
            Tristate clock = _inPins[8]->reduceInput();
            std::vector<Tristate> ins(8, UNDEFINED);

            for (int i = 0; i < 8; i++)
                ins[i] = _inPins[i]->reduceInput();
            if (inhibit != FALSE || clock != TRUE)
                return;

            char c = binToDec(ins);

            std::ofstream logFile;
            logFile.open("log.bin", std::ios_base::app);
            if (!logFile.is_open())
                throw ntsError("Could not open file log.bin");
            logFile << c;
            logFile.close();
        }
    } // namespace gates

    namespace components {
        LoggerC::LoggerC(std::string name, std::vector<AGate *>gates):
        AComponent(name, gates.size(), gates, C_DEVICE)
        {
            for (int i = 0; i < 10; i++)
                assignPin(i, 0, i);
        }

        Tristate LoggerC::compute(std::size_t pin)
        {
            if (pin >= this->_nbPins)
                throw ComponentException("Pin out of range");
            return _pinLinks[pin]->getVal();
        }

        IComponent *createLoggerC(std::string name)
        {
            std::vector<AGate *> gates = std::vector<AGate *>(1, nullptr);
            gates[0] = new gates::LoggerGate;

            return new LoggerC(name, gates);
        }
    } // namespace components
}