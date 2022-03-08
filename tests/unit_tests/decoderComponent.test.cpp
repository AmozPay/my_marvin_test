/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** decoder4514.test
*/

#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <cstddef>
#include <iostream>
#include <vector>
#include "../../include/Core.hpp"
#include "../../include/Sequential.hpp"

Test(decoder4514, s0_1,  .init = nts::test::setTickCounter)
{
    nts::IComponent *gate = nts::components::createDecoder4514C("adder");
    nts::IComponent *input1 = nts::components::createFalseComponent("F1");
    nts::IComponent *input2 = nts::components::createFalseComponent("F2");
    nts::IComponent *input3 = nts::components::createFalseComponent("F3");
    nts::IComponent *input4 = nts::components::createFalseComponent("F4");
    nts::IComponent *strobe = nts::components::createInputComponent("C");

    dynamic_cast<nts::components::InputComponent *>(strobe)->setVal(nts::FALSE);
    strobe->simulate(1);
    gate->setLink(0, *strobe, 0);
    gate->setLink(1, *input1, 0);
    gate->setLink(2, *input2, 0);
    gate->setLink(20, *input3, 0);
    gate->setLink(21, *input4, 0);
    gate->simulate(2);

    cr_assert_eq(gate->compute(10), nts::TRUE);
    for (int i = 3; i < 10; i++)
        cr_assert_eq(gate->compute(i), nts::FALSE);
    for (int i = 12; i < 19; i++)
        cr_assert_eq(gate->compute(i), nts::FALSE);

}

Test(decoder4514, s1_1,  .init = nts::test::setTickCounter)
{
    nts::IComponent *gate = nts::components::createDecoder4514C("adder");
    nts::IComponent *input1 = nts::components::createTrueComponent("F1");
    nts::IComponent *input2 = nts::components::createFalseComponent("F2");
    nts::IComponent *input3 = nts::components::createFalseComponent("F3");
    nts::IComponent *input4 = nts::components::createFalseComponent("F4");
    nts::IComponent *strobe = nts::components::createInputComponent("C");

    dynamic_cast<nts::components::InputComponent *>(strobe)->setVal(nts::FALSE);
    strobe->simulate(1);
    gate->setLink(0, *strobe, 0);
    gate->setLink(1, *input1, 0);
    gate->setLink(2, *input2, 0);
    gate->setLink(20, *input3, 0);
    gate->setLink(21, *input4, 0);
    gate->simulate(2);

    cr_assert_eq(gate->compute(8), nts::TRUE);
    for (int i = 3; i < 8; i++)
        cr_assert_eq(gate->compute(i), nts::FALSE);
    cr_assert_eq(gate->compute(9), nts::FALSE);
    cr_assert_eq(gate->compute(10), nts::FALSE);
    for (int i = 12; i < 19; i++)
        cr_assert_eq(gate->compute(i), nts::FALSE);

}

Test(decoder4514, s15_1,  .init = nts::test::setTickCounter)
{
    nts::IComponent *gate = nts::components::createDecoder4514C("adder");
    nts::IComponent *input1 = nts::components::createTrueComponent("T1");
    nts::IComponent *input2 = nts::components::createTrueComponent("T2");
    nts::IComponent *input3 = nts::components::createTrueComponent("T3");
    nts::IComponent *input4 = nts::components::createTrueComponent("T4");
    nts::IComponent *strobe = nts::components::createInputComponent("C");

    dynamic_cast<nts::components::InputComponent *>(strobe)->setVal(nts::FALSE);
    strobe->simulate(1);
    gate->setLink(0, *strobe, 0);
    gate->setLink(1, *input1, 0);
    gate->setLink(2, *input2, 0);
    gate->setLink(20, *input3, 0);
    gate->setLink(21, *input4, 0);
    gate->simulate(2);

    cr_assert_eq(gate->compute(14), nts::TRUE);
    for (int i = 3; i < 11; i++)
        cr_assert_eq(gate->compute(i), nts::FALSE);
    for (int i = 15; i < 19; i++)
        cr_assert_eq(gate->compute(i), nts::FALSE);
    cr_assert_eq(gate->compute(12), nts::FALSE);
    cr_assert_eq(gate->compute(13), nts::FALSE);

}



// Test(decoder4514, msbs_1,  .init = nts::test::setTickCounter)
// {
//     nts::IComponent *gate = nts::components::createAdder4008C("adder");
//     nts::IComponent *input1 = nts::components::createInputComponent("I1");
//     nts::IComponent *input2 = nts::components::createInputComponent("I2");

//     dynamic_cast<nts::components::InputComponent *>(input1)->setVal(nts::TRUE);
//     dynamic_cast<nts::components::InputComponent *>(input2)->setVal(nts::TRUE);
//     gate->setLink(0, *input1, 0);
//     gate->setLink(14, *input2, 0);
//     gate->simulate(1);
//     cr_assert_eq(gate->compute(12), nts::FALSE);
//     cr_assert_eq(gate->compute(13), nts::TRUE);
// }

// Test(decoder4514, ab3_1,  .init = nts::test::setTickCounter)
// {
//     nts::IComponent *gate = nts::components::createAdder4008C("adder");
//     nts::IComponent *a3 = nts::components::createInputComponent("I1");
//     nts::IComponent *b3 = nts::components::createInputComponent("I2");

//     dynamic_cast<nts::components::InputComponent *>(a3)->setVal(nts::TRUE);
//     dynamic_cast<nts::components::InputComponent *>(b3)->setVal(nts::TRUE);
//     gate->setLink(2, *a3, 0);
//     gate->setLink(1, *b3, 0);
//     gate->simulate(1);
//     cr_assert_eq(gate->compute(11), nts::FALSE);
//     cr_assert_eq(gate->compute(13), nts::FALSE);
// }

// Test(decoder4514, lsbs_1_carry_1, .init = nts::test::setTickCounter)
// {
//     nts::IComponent *gate = nts::components::createAdder4008C("adder");
//     nts::IComponent *a1 = nts::components::createInputComponent("I1");
//     nts::IComponent *b1 = nts::components::createInputComponent("I2");
//     nts::IComponent *c1 = nts::components::createInputComponent("I3");

//     dynamic_cast<nts::components::InputComponent *>(a1)->setVal(nts::TRUE);
//     dynamic_cast<nts::components::InputComponent *>(b1)->setVal(nts::TRUE);
//     dynamic_cast<nts::components::InputComponent *>(c1)->setVal(nts::TRUE);
//     gate->setLink(6, *a1, 0);
//     gate->setLink(5, *b1, 0);
//     gate->setLink(8, *c1, 0);
//     gate->simulate(1);
//     cr_assert_eq(gate->compute(9), nts::TRUE);
//     cr_assert_eq(gate->compute(10), nts::TRUE);
//     cr_assert_eq(gate->compute(11), nts::FALSE);
//     cr_assert_eq(gate->compute(12), nts::FALSE);
//     cr_assert_eq(gate->compute(13), nts::FALSE);
// }
