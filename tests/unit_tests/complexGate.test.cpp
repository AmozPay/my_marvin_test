/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** andGate
*/

#include <criterion/criterion.h>
#include "../../include/Core.hpp"
#include "../../include/Combinatorial.hpp"


Test(complexGate, ok, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> andGate = std::unique_ptr<nts::AGate>(new nts::gates::AndGate());
    std::unique_ptr<nts::AGate> andGate2 = std::unique_ptr<nts::AGate>(new nts::gates::AndGate());
    std::unique_ptr<nts::AGate> orGate = std::unique_ptr<nts::AGate>(new nts::gates::OrGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::TrueGate());
    std::unique_ptr<nts::AGate> b = std::unique_ptr<nts::AGate>(new nts::gates::FalseGate());
    std::unique_ptr<nts::AGate> c = std::unique_ptr<nts::AGate>(new nts::gates::TrueGate());
    (*andGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*andGate)[1]->connectPin((*c)[0], "test1", "test2");
    (*orGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*orGate)[1]->connectPin((*b)[0], "test1", "test2");
    (*andGate2)[0]->connectPin((*andGate)[2], "test1", "test2");
    (*andGate2)[0]->connectPin((*b)[0], "test1", "test2");
    (*andGate2)[1]->connectPin((*orGate)[2], "test1", "test2");
    (*andGate2)[1]->connectPin((*b)[0], "test1", "test2");
    andGate2->simulate();
    cr_assert_eq((*andGate2)[2]->getVal(), nts::TRUE);
}

Test(complexGate, doubleFalse, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> andGate = std::unique_ptr<nts::AGate>(new nts::gates::AndGate());
    std::unique_ptr<nts::AGate> andGate2 = std::unique_ptr<nts::AGate>(new nts::gates::AndGate());
    std::unique_ptr<nts::AGate> orGate = std::unique_ptr<nts::AGate>(new nts::gates::OrGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::TrueGate());
    std::unique_ptr<nts::AGate> b = std::unique_ptr<nts::AGate>(new nts::gates::FalseGate());
    std::unique_ptr<nts::AGate> c = std::unique_ptr<nts::AGate>(new nts::gates::TrueGate());
    (*andGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*andGate)[1]->connectPin((*b)[0], "test1", "test2");
    (*orGate)[0]->connectPin((*a)[0], "test1", "test2");
    (*orGate)[1]->connectPin((*b)[0], "test1", "test2");
    (*andGate2)[0]->connectPin((*andGate)[2], "test1", "test2");
    (*andGate2)[0]->connectPin((*b)[0], "test1", "test2");
    (*andGate2)[1]->connectPin((*orGate)[2], "test1", "test2");
    (*andGate2)[1]->connectPin((*b)[0], "test1", "test2");
    andGate2->simulate();
    cr_assert_eq((*andGate2)[2]->getVal(), nts::FALSE);
}