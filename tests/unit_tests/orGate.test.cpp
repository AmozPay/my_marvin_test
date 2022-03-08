/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** orGate
*/

#include <criterion/criterion.h>
#include "../../include/Core.hpp"
#include "../../include/Combinatorial.hpp"


Test(orGate, oneFalse, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> orGate = std::unique_ptr<nts::AGate>(new nts::gates::OrGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::TrueGate());
    std::unique_ptr<nts::AGate> b = std::unique_ptr<nts::AGate>(new nts::gates::FalseGate());
    (*orGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*orGate)[1]->connectPin((*b)[0], "test1", "test2");
    orGate->simulate();
    cr_assert_eq((*orGate)[2]->getVal(), nts::TRUE);
}

Test(orGatetwoFalse ,ok, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> orGate = std::unique_ptr<nts::AGate>(new nts::gates::OrGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::FalseGate());
    std::unique_ptr<nts::AGate> b = std::unique_ptr<nts::AGate>(new nts::gates::FalseGate());
    (*orGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*orGate)[1]->connectPin((*b)[0], "test1", "test2");
    orGate->simulate();
    cr_assert_eq((*orGate)[2]->getVal(), nts::FALSE);
}

Test(orGateuninitialized, ok, .init = nts::test::setTickCounter)
{
    nts::AGate *orGate = new nts::gates::OrGate();
    cr_assert_eq((*orGate)[2]->getVal(), nts::UNDEFINED);
}

Test(orGateBothTrue ,ok, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> orGate = std::unique_ptr<nts::AGate>(new nts::gates::OrGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::TrueGate());
    std::unique_ptr<nts::AGate> b = std::unique_ptr<nts::AGate>(new nts::gates::TrueGate());
    (*orGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*orGate)[1]->connectPin((*b)[0], "test1", "test2");
    orGate->simulate();
    cr_assert_eq((*orGate)[2]->getVal(), nts::TRUE);
}

Test(orGateTrueUndefined ,ok, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> orGate = std::unique_ptr<nts::AGate>(new nts::gates::OrGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::TrueGate());
    std::unique_ptr<nts::AGate> b = std::unique_ptr<nts::AGate>(new nts::gates::UndefinedGate());
    (*orGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*orGate)[1]->connectPin((*b)[0], "test1", "test2");
    orGate->simulate();
    cr_assert_eq((*orGate)[2]->getVal(), nts::TRUE);
}

Test(orGateFalseUndefined ,ok, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> orGate = std::unique_ptr<nts::AGate>(new nts::gates::OrGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::FalseGate());
    std::unique_ptr<nts::AGate> b = std::unique_ptr<nts::AGate>(new nts::gates::UndefinedGate());
    (*orGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*orGate)[1]->connectPin((*b)[0], "test1", "test2");
    orGate->simulate();
    cr_assert_eq((*orGate)[2]->getVal(), nts::UNDEFINED);
}

Test(orGateNoInput,ok, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> orGate = std::unique_ptr<nts::AGate>(new nts::gates::OrGate());
    orGate->simulate();
    cr_assert_eq((*orGate)[2]->getVal(), nts::FALSE);
}
