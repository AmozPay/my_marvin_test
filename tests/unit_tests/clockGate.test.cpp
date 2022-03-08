/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** nandGate
*/

#include <criterion/criterion.h>
#include "../../include/Core.hpp"
#include "../../include/Combinatorial.hpp"
#include "../../include/Sequential.hpp"


Test(clockGate, iUndefined)
{
    std::unique_ptr<nts::AGate> iGate = std::unique_ptr<nts::AGate>(new nts::gates::ClockGate());
    iGate->simulate();
    cr_assert_eq((*iGate)[0]->getVal(), nts::UNDEFINED);
}

Test(clockGate, iTrue)
{
    nts::gates::ClockGate *iGate = new nts::gates::ClockGate();
    iGate->setVal(nts::TRUE);
    nts::tickCounter = 1;
    iGate->simulate();
    cr_assert_eq((*iGate)[0]->getVal(), nts::TRUE);
}

Test(clockGate, iFalse)
{
    nts::tickCounter = 1;
    nts::gates::ClockGate *iGate = new nts::gates::ClockGate();
    iGate->setVal(nts::FALSE);
    iGate->simulate();
    cr_assert_eq((*iGate)[0]->getVal(), nts::FALSE);
    nts::tickCounter++;
    iGate->simulate();
    cr_assert_eq((*iGate)[0]->getVal(), nts::TRUE);
}
