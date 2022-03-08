/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** xorGate
*/

#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <cstddef>
#include <iostream>
#include <vector>
#include "../../include/Core.hpp"
#include "../../include/Combinatorial.hpp"


Test(tristate, decToBin)
{
    std::vector<nts::Tristate> vec({nts::TRUE, nts::FALSE, nts::TRUE});

    int res = nts::binToDec(vec);
    cr_assert_eq(res, 5);
}

Test(tristate, decToBinEven)
{
    std::vector<nts::Tristate> vec({nts::FALSE, nts::FALSE, nts::TRUE});

    int res = nts::binToDec(vec);
    cr_assert_eq(res, 4);
}

Test(tristate, decToBinFail)
{
    std::vector<nts::Tristate> vec({nts::TRUE, nts::FALSE, nts::UNDEFINED});

    int res = nts::binToDec(vec);
    cr_assert_eq(res, -1);
}

Test(tristate, binToDec)
{
    std::vector<nts::Tristate> just = std::vector<nts::Tristate>({nts::TRUE, nts::TRUE, nts::TRUE});
    std::vector<nts::Tristate> vec = nts::decToBin(7);

    for (size_t i = 0; i < 3; i++) {
        cr_assert_eq(just[i], vec[i]);
    }
}

Test(tristate, binToDecEven)
{
    std::vector<nts::Tristate> just = std::vector<nts::Tristate>({nts::FALSE , nts::TRUE, nts::TRUE});
    std::vector<nts::Tristate> vec = nts::decToBin(6);

    for (size_t i = 0; i < 3; i++) {
        cr_assert_eq(just[i], vec[i]);
    }
}