/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** aGate.test
*/

#include <criterion/criterion.h>
#include "../../include/Core.hpp"
#include "../../include/Combinatorial.hpp"
#include "../../include/Sequential.hpp"
#include <iostream>
#include <sstream>


Test(test_tickCounter, clock)
{
    nts::tickCounter = 0;
    nts::gates::ClockGate *iGate = new nts::gates::ClockGate();
    iGate->setVal(nts::FALSE);
    iGate->simulate();
    cr_assert_eq((*iGate)[0]->getVal(), nts::UNDEFINED);
    iGate->simulate();
    cr_assert_eq((*iGate)[0]->getVal(), nts::UNDEFINED);
    nts::tickCounter++;
    iGate->simulate();
    cr_assert_eq((*iGate)[0]->getVal(), nts::FALSE);
    iGate->simulate();
    cr_assert_eq((*iGate)[0]->getVal(), nts::FALSE);
    nts::tickCounter++;
    iGate->simulate();
    cr_assert_eq((*iGate)[0]->getVal(), nts::TRUE);
}
