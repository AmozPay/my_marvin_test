/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** andGate
*/

#include <criterion/criterion.h>
#include "../../include/Core.hpp"
#include "../../include/Combinatorial.hpp"


Test(andGate, oneFalse, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> andGate = std::unique_ptr<nts::AGate>(new nts::gates::AndGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::TrueGate());
    std::unique_ptr<nts::AGate> b = std::unique_ptr<nts::AGate>(new nts::gates::FalseGate());
    (*andGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*andGate)[1]->connectPin((*b)[0], "test1", "test2");
    andGate->simulate();
    cr_assert_eq((*andGate)[2]->getVal(), nts::FALSE);
}

Test(andGatetwoFalse ,ok, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> andGate = std::unique_ptr<nts::AGate>(new nts::gates::AndGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::FalseGate());
    std::unique_ptr<nts::AGate> b = std::unique_ptr<nts::AGate>(new nts::gates::FalseGate());
    (*andGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*andGate)[1]->connectPin((*b)[0], "test1", "test2");
    andGate->simulate();
    cr_assert_eq((*andGate)[2]->getVal(), nts::FALSE);
}

Test(andGateuninitialized, ok, .init = nts::test::setTickCounter)
{
    nts::AGate *andGate = new nts::gates::AndGate();
    cr_assert_eq((*andGate)[2]->getVal(), nts::UNDEFINED);
}

Test(andGateBothTrue ,ok, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> andGate = std::unique_ptr<nts::AGate>(new nts::gates::AndGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::TrueGate());
    std::unique_ptr<nts::AGate> b = std::unique_ptr<nts::AGate>(new nts::gates::TrueGate());
    (*andGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*andGate)[1]->connectPin((*b)[0], "test1", "test2");
    andGate->simulate();
    cr_assert_eq((*andGate)[2]->getVal(), nts::TRUE);
}

Test(andGateTrueUndefined ,ok, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> andGate = std::unique_ptr<nts::AGate>(new nts::gates::AndGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::TrueGate());
    std::unique_ptr<nts::AGate> b = std::unique_ptr<nts::AGate>(new nts::gates::UndefinedGate());
    (*andGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*andGate)[1]->connectPin((*b)[0], "test1", "test2");
    andGate->simulate();
    cr_assert_eq((*andGate)[2]->getVal(), nts::UNDEFINED);
}

Test(andGateFalseUndefined ,ok, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> andGate = std::unique_ptr<nts::AGate>(new nts::gates::AndGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::FalseGate());
    std::unique_ptr<nts::AGate> b = std::unique_ptr<nts::AGate>(new nts::gates::UndefinedGate());
    (*andGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*andGate)[1]->connectPin((*b)[0], "test1", "test2");
    andGate->simulate();
    cr_assert_eq((*andGate)[2]->getVal(), nts::FALSE);
}

Test(andGateNoInput,ok, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> andGate = std::unique_ptr<nts::AGate>(new nts::gates::AndGate());
    andGate->simulate();
    cr_assert_eq((*andGate)[2]->getVal(), nts::FALSE);
}
