/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** aGate.test
*/

#include <criterion/criterion.h>
#include "../../include/Core.hpp"
#include "../../include/Combinatorial.hpp"
#include <iostream>
#include <sstream>

void nts::test::setTickCounter()
{
    nts::tickCounter = 4096;
}
class IORedirect
{
    public:
    IORedirect():
    coutbuf_(std::cout.rdbuf())
    {
        std::cout.rdbuf(out_.rdbuf());
    }

    ~IORedirect()
    {
        std::cout.rdbuf(coutbuf_);
    }

    std::string output() { return out_.str(); }

    private:
        std::streambuf *coutbuf_;
        std::ostringstream out_;
};

Test(AGate, ok, .init = nts::test::setTickCounter)
{
    std::unique_ptr<nts::AGate> andGate = std::unique_ptr<nts::AGate>(new nts::gates::AndGate());
    std::unique_ptr<nts::AGate> a = std::unique_ptr<nts::AGate>(new nts::gates::TrueGate());
    bool exceptionRaised = false;

    try {
        (*andGate)[5000]->connectPin((*a)[0], "test1", "test2");
    } catch (std::exception &e) {
        (void)e;
        exceptionRaised = true;
    }
    cr_assert_eq(exceptionRaised, true);
}