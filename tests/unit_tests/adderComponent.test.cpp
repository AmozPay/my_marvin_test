/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** adder4008C.test
*/

#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <cstddef>
#include <iostream>
#include <vector>
#include "../../include/Core.hpp"
#include "../../include/Combinatorial.hpp"

Test(adder4008C, msb_1_0,  .init = nts::test::setTickCounter)
{
    nts::IComponent *gate = nts::components::createAdder4008C("adder");
    nts::IComponent *input = nts::components::createInputComponent("I");

    dynamic_cast<nts::components::InputComponent *>(input)->setVal(nts::TRUE);
    gate->setLink(0, *input, 0);
    gate->simulate(1);
    cr_assert_eq(gate->compute(12), nts::TRUE);
    cr_assert_eq(gate->compute(13), nts::FALSE);
}

Test(adder4008C, msbs_1,  .init = nts::test::setTickCounter)
{
    nts::IComponent *gate = nts::components::createAdder4008C("adder");
    nts::IComponent *input1 = nts::components::createInputComponent("I1");
    nts::IComponent *input2 = nts::components::createInputComponent("I2");

    dynamic_cast<nts::components::InputComponent *>(input1)->setVal(nts::TRUE);
    dynamic_cast<nts::components::InputComponent *>(input2)->setVal(nts::TRUE);
    gate->setLink(0, *input1, 0);
    gate->setLink(14, *input2, 0);
    gate->simulate(1);
    cr_assert_eq(gate->compute(12), nts::FALSE);
    cr_assert_eq(gate->compute(13), nts::TRUE);
}

Test(adder4008C, ab3_1,  .init = nts::test::setTickCounter)
{
    nts::IComponent *gate = nts::components::createAdder4008C("adder");
    nts::IComponent *a3 = nts::components::createInputComponent("I1");
    nts::IComponent *b3 = nts::components::createInputComponent("I2");

    dynamic_cast<nts::components::InputComponent *>(a3)->setVal(nts::TRUE);
    dynamic_cast<nts::components::InputComponent *>(b3)->setVal(nts::TRUE);
    gate->setLink(2, *a3, 0);
    gate->setLink(1, *b3, 0);
    gate->simulate(1);
    cr_assert_eq(gate->compute(11), nts::FALSE);
    cr_assert_eq(gate->compute(13), nts::FALSE);
}

Test(adder4008C, lsbs_1_carry_1, .init = nts::test::setTickCounter)
{
    nts::IComponent *gate = nts::components::createAdder4008C("adder");
    nts::IComponent *a1 = nts::components::createInputComponent("I1");
    nts::IComponent *b1 = nts::components::createInputComponent("I2");
    nts::IComponent *c1 = nts::components::createInputComponent("I3");

    dynamic_cast<nts::components::InputComponent *>(a1)->setVal(nts::TRUE);
    dynamic_cast<nts::components::InputComponent *>(b1)->setVal(nts::TRUE);
    dynamic_cast<nts::components::InputComponent *>(c1)->setVal(nts::TRUE);
    gate->setLink(6, *a1, 0);
    gate->setLink(5, *b1, 0);
    gate->setLink(8, *c1, 0);
    gate->simulate(1);
    cr_assert_eq(gate->compute(9), nts::TRUE);
    cr_assert_eq(gate->compute(10), nts::TRUE);
    cr_assert_eq(gate->compute(11), nts::FALSE);
    cr_assert_eq(gate->compute(12), nts::FALSE);
    cr_assert_eq(gate->compute(13), nts::FALSE);
}
