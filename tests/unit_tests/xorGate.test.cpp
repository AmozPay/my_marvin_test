/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** xorGate
*/

#include <criterion/criterion.h>
#include "../../include/Core.hpp"
#include "../../include/Combinatorial.hpp"


Test(xorGate, oneFalse, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> xorGate = std::unique_ptr<nts::AGate>(new nts::gates::XorGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::TrueGate());
    std::unique_ptr<nts::AGate> b = std::unique_ptr<nts::AGate>(new nts::gates::FalseGate());
    (*xorGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*xorGate)[1]->connectPin((*b)[0], "test1", "test2");
    xorGate->simulate();
    cr_assert_eq((*xorGate)[2]->getVal(), nts::TRUE);
}

Test(xorGatetwoFalse ,ok, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> xorGate = std::unique_ptr<nts::AGate>(new nts::gates::XorGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::FalseGate());
    std::unique_ptr<nts::AGate> b = std::unique_ptr<nts::AGate>(new nts::gates::FalseGate());
    (*xorGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*xorGate)[1]->connectPin((*b)[0], "test1", "test2");
    xorGate->simulate();
    cr_assert_eq((*xorGate)[2]->getVal(), nts::FALSE);
}

Test(xorGateuninitialized, ok, .init = nts::test::setTickCounter)
{
    nts::AGate *xorGate = new nts::gates::XorGate();
    cr_assert_eq((*xorGate)[2]->getVal(), nts::UNDEFINED);
}

Test(xorGateBothTrue ,ok, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> xorGate = std::unique_ptr<nts::AGate>(new nts::gates::XorGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::TrueGate());
    std::unique_ptr<nts::AGate> b = std::unique_ptr<nts::AGate>(new nts::gates::TrueGate());
    (*xorGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*xorGate)[1]->connectPin((*b)[0], "test1", "test2");
    xorGate->simulate();
    cr_assert_eq((*xorGate)[2]->getVal(), nts::FALSE);
}

Test(xorGateTrueUndefined ,ok, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> xorGate = std::unique_ptr<nts::AGate>(new nts::gates::XorGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::TrueGate());
    std::unique_ptr<nts::AGate> b = std::unique_ptr<nts::AGate>(new nts::gates::UndefinedGate());
    (*xorGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*xorGate)[1]->connectPin((*b)[0], "test1", "test2");
    xorGate->simulate();
    cr_assert_eq((*xorGate)[2]->getVal(), nts::UNDEFINED);
}

Test(xorGateFalseUndefined ,ok, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> xorGate = std::unique_ptr<nts::AGate>(new nts::gates::XorGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::FalseGate());
    std::unique_ptr<nts::AGate> b = std::unique_ptr<nts::AGate>(new nts::gates::UndefinedGate());
    (*xorGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*xorGate)[1]->connectPin((*b)[0], "test1", "test2");
    xorGate->simulate();
    cr_assert_eq((*xorGate)[2]->getVal(), nts::UNDEFINED);
}

Test(xorGateNoInput,ok, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> xorGate = std::unique_ptr<nts::AGate>(new nts::gates::XorGate());
    xorGate->simulate();
    cr_assert_eq((*xorGate)[2]->getVal(), nts::FALSE);
}
