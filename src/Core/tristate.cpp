/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** tristate
*/

#include "../include/Core.hpp"
#include <cstddef>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

namespace nts {

    std::string fmtTristate(Tristate state)
    {
        if (state == TRUE)
            return "1";
        else if (state == FALSE)
            return "0";
        return "U";
    }

    Tristate operator&(Tristate a, Tristate b)
    {
        if (a == FALSE || b == FALSE)
            return FALSE;
        if (a == UNDEFINED || b == UNDEFINED)
            return UNDEFINED;
        return TRUE;
    }

    // see issues #19
    Tristate operator|(Tristate a, Tristate b)
    {
        if (a == TRUE || b == TRUE)
            return TRUE;
        if (a == UNDEFINED || b == UNDEFINED)
            return UNDEFINED;
        return FALSE;
    }

    Tristate operator!(Tristate a) {
        if (a == TRUE)
            return FALSE;
        if (a == FALSE)
            return TRUE;
        return UNDEFINED;
    }

    Tristate operator^(Tristate a, Tristate b) {
        if (a == FALSE && b == FALSE)
            return FALSE;
        if (a == TRUE && b == TRUE)
            return FALSE;
        if (a == UNDEFINED || b == UNDEFINED)
            return UNDEFINED;
        return TRUE;
    }

    // WARNING: this operateur is not safe to use with UNDEFINED
    int operator+(Tristate a, Tristate b) {
        int sum = 0;
        if (a == UNDEFINED || b == UNDEFINED)
            return -1;
        sum += (a == TRUE) ? 1 : 0;
        sum += (b == TRUE) ? 1 : 0;
        return sum;
    }

    int binToDec(std::vector<Tristate> vec) {
        int res = 0;
        if (std::find(vec.begin(), vec.end(), UNDEFINED) != vec.end())
            return -1;
        for (size_t i = 0; i < vec.size(); i++) {
            res += (vec[i] == TRUE) ? std::pow(2, i) : 0;
        }
        return res;
    }

    std::vector<Tristate> decToBin(unsigned int number) {
        std::vector<Tristate> res = std::vector<Tristate>();
        while (number > 0) {
            res.push_back(number % 2 == 1 ? TRUE : FALSE);
            number /= 2;
        }
        return res;
    }

    std::ostream& operator<<(std::ostream &s, const Tristate &state)
    {
        std::string str;
        switch (state)
        {
        case nts::Tristate::UNDEFINED:
            str = "U";
            break;
        case nts::Tristate::FALSE:
            str = "0";
            break;
        case nts::Tristate::TRUE:
            str = "1";
            break;
        default:
            break;
        }
        s << str;
        return s;
    }

    Tristate stoTristate(std::string & s)
    {
        if (s == "0")
            return FALSE;
        if (s == "1")
            return TRUE;
        if (s == "U")
            return UNDEFINED;
        throw ntsError("Invalid Tristate conversion");
    }
}