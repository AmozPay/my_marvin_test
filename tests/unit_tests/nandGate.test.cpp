/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** nandGate
*/

#include <criterion/criterion.h>
#include "../../include/Core.hpp"
#include "../../include/Combinatorial.hpp"

Test(nandGate, oneFalse, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> nandGate = std::unique_ptr<nts::AGate>(new nts::gates::NandGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::TrueGate());
    std::unique_ptr<nts::AGate> b = std::unique_ptr<nts::AGate>(new nts::gates::FalseGate());
    (*nandGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*nandGate)[1]->connectPin((*b)[0], "test1", "test2");
    nandGate->simulate();
    cr_assert_eq((*nandGate)[2]->getVal(), nts::TRUE);
}

Test(nandGate, twoFalse, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> nandGate = std::unique_ptr<nts::AGate>(new nts::gates::NandGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::FalseGate());
    std::unique_ptr<nts::AGate> b = std::unique_ptr<nts::AGate>(new nts::gates::FalseGate());
    (*nandGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*nandGate)[1]->connectPin((*b)[0], "test1", "test2");
    nandGate->simulate();
    cr_assert_eq((*nandGate)[2]->getVal(), nts::TRUE);
}

Test(nandGate, uninitialized, .init = nts::test::setTickCounter)
{
    nts::AGate *nandGate = new nts::gates::NandGate();
    cr_assert_eq((*nandGate)[2]->getVal(), nts::UNDEFINED);
}

Test(nandGate, bothTrue, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> nandGate = std::unique_ptr<nts::AGate>(new nts::gates::NandGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::TrueGate());
    std::unique_ptr<nts::AGate> b = std::unique_ptr<nts::AGate>(new nts::gates::TrueGate());
    (*nandGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*nandGate)[1]->connectPin((*b)[0], "test1", "test2");
    nandGate->simulate();
    cr_assert_eq((*nandGate)[2]->getVal(), nts::FALSE);
}

Test(nandGate, trueUndefined, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> nandGate = std::unique_ptr<nts::AGate>(new nts::gates::NandGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::TrueGate());
    std::unique_ptr<nts::AGate> b = std::unique_ptr<nts::AGate>(new nts::gates::UndefinedGate());
    (*nandGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*nandGate)[1]->connectPin((*b)[0], "test1", "test2");
    nandGate->simulate();
    cr_assert_eq((*nandGate)[2]->getVal(), nts::UNDEFINED);
}

Test(nandGate, falseUndefined, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> nandGate = std::unique_ptr<nts::AGate>(new nts::gates::NandGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::FalseGate());
    std::unique_ptr<nts::AGate> b = std::unique_ptr<nts::AGate>(new nts::gates::UndefinedGate());
    (*nandGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*nandGate)[1]->connectPin((*b)[0], "test1", "test2");
    nandGate->simulate();
    cr_assert_eq((*nandGate)[2]->getVal(), nts::TRUE);
}

Test(nandGate, noInput, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> nandGate = std::unique_ptr<nts::AGate>(new nts::gates::NandGate());
    nandGate->simulate();
    cr_assert_eq((*nandGate)[2]->getVal(), nts::TRUE);
}
