/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** nandGate
*/

#include <criterion/criterion.h>
#include "../../include/Core.hpp"
#include "../../include/Combinatorial.hpp"


Test(inputGate, iUndefined)
{
    std::unique_ptr<nts::AGate> iGate = std::unique_ptr<nts::AGate>(new nts::gates::InputGate());
    iGate->simulate();
    cr_assert_eq((*iGate)[0]->getVal(), nts::UNDEFINED);
}

Test(inputGate, iTrue)
{
    nts::gates::InputGate *iGate = new nts::gates::InputGate();
    iGate->setVal(nts::TRUE);
    iGate->simulate();
    cr_assert_eq((*iGate)[0]->getVal(), nts::TRUE);
}

Test(inputGate, iFalse)
{
    nts::gates::InputGate *iGate = new nts::gates::InputGate();
    iGate->setVal(nts::FALSE);
    iGate->simulate();
    cr_assert_eq((*iGate)[0]->getVal(), nts::FALSE);
}
