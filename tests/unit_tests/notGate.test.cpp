/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** andGate
*/

#include <criterion/criterion.h>
#include "../../include/Core.hpp"
#include "../../include/Combinatorial.hpp"


Test(notGate, inputFalse, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> notGate = std::unique_ptr<nts::AGate>(new nts::gates::NotGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::FalseGate());
    (*notGate)[0]->connectPin((*a)[0], "test1", "test2");
    notGate->simulate();
    cr_assert_eq((*notGate)[1]->getVal(), nts::TRUE);
}

Test(notGate, inputTrue, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> notGate = std::unique_ptr<nts::AGate>(new nts::gates::NotGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::TrueGate());
    (*notGate)[0]->connectPin((*a)[0], "test1", "test2");
    notGate->simulate();
    cr_assert_eq((*notGate)[1]->getVal(), nts::FALSE);
}

Test(notGate, inputUndefined, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> notGate = std::unique_ptr<nts::AGate>(new nts::gates::NotGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::UndefinedGate());
    (*notGate)[0]->connectPin((*a)[0], "test1", "test2");
    notGate->simulate();
    cr_assert_eq((*notGate)[1]->getVal(), nts::UNDEFINED);
}

Test(notGateNoInput, ok, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> notGate = std::unique_ptr<nts::AGate>(new nts::gates::NotGate());
    notGate->simulate();
    cr_assert_eq((*notGate)[1]->getVal(), nts::TRUE);
}
