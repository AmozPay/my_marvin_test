/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** selectorComponent.test
*/

#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <cstddef>
#include <iostream>
#include <vector>
#include "../../include/Core.hpp"
#include "../../include/Combinatorial.hpp"

Test(selectorComponent, inhibitorOn, .init = nts::test::setTickCounter)
{
    nts::IComponent *gate = nts::components::createSelector4512Component("Mux8");
    nts::IComponent *input = nts::components::createInputComponent("I");

    dynamic_cast<nts::components::InputComponent *>(input)->setVal(nts::TRUE);
    gate->setLink(9, *input, 0);
    gate->simulate(1);
    cr_assert_eq(gate->compute(13), nts::FALSE);
}

Test(selectorComponent, inhibitorUn, .init = nts::test::setTickCounter)
{
    nts::IComponent *gate = nts::components::createSelector4512Component("Mux8");
    nts::IComponent *input = nts::components::createInputComponent("I");

    dynamic_cast<nts::components::InputComponent *>(input)->setVal(nts::UNDEFINED);
    gate->setLink(9, *input, 0);
    gate->simulate(1);
    cr_assert_eq(gate->compute(13), nts::UNDEFINED);
}

Test(selectorComponent, OEUn, .init = nts::test::setTickCounter)
{
    nts::IComponent *gate = nts::components::createSelector4512Component("Mux8");
    nts::IComponent *input = nts::components::createInputComponent("I");

    gate->setLink(14, *input, 0);
    gate->simulate(1);
    cr_assert_eq(gate->compute(13), nts::UNDEFINED);
}


Test(selectorComponent, OEUOn, .init = nts::test::setTickCounter)
{
    nts::IComponent *gate = nts::components::createSelector4512Component("Mux8");
    nts::IComponent *input = nts::components::createInputComponent("I");

    dynamic_cast<nts::components::InputComponent *>(input)->setVal(nts::TRUE);
    gate->setLink(14, *input, 0);
    gate->simulate(1);
    cr_assert_eq(gate->compute(13), nts::UNDEFINED);
}

Test(selectorComponent, X2, .init = nts::test::setTickCounter)
{
    nts::IComponent *gate = nts::components::createSelector4512Component("Mux8");
    nts::IComponent *inputA = nts::components::createInputComponent("A");
    nts::IComponent *inputB = nts::components::createInputComponent("B");
    nts::IComponent *inputC = nts::components::createInputComponent("C");
    nts::IComponent *X2 = nts::components::createInputComponent("X2");


    dynamic_cast<nts::components::InputComponent *>(inputA)->setVal(nts::FALSE);
    dynamic_cast<nts::components::InputComponent *>(inputB)->setVal(nts::TRUE);
    dynamic_cast<nts::components::InputComponent *>(inputC)->setVal(nts::FALSE);
    dynamic_cast<nts::components::InputComponent *>(X2)->setVal(nts::TRUE);

    gate->setLink(2, *X2, 0);
    gate->setLink(10, *inputA, 0);
    gate->setLink(11, *inputB, 0);
    gate->setLink(12, *inputC, 0);

    gate->simulate(1);
    cr_assert_eq(gate->compute(13), X2->compute(0));
}

Test(selectorComponent, X2False, .init = nts::test::setTickCounter)
{
    nts::IComponent *gate = nts::components::createSelector4512Component("Mux8");
    nts::IComponent *inputA = nts::components::createInputComponent("A");
    nts::IComponent *inputB = nts::components::createInputComponent("B");
    nts::IComponent *inputC = nts::components::createInputComponent("C");
    nts::IComponent *X2 = nts::components::createInputComponent("X2");


    dynamic_cast<nts::components::InputComponent *>(inputA)->setVal(nts::FALSE);
    dynamic_cast<nts::components::InputComponent *>(inputB)->setVal(nts::TRUE);
    dynamic_cast<nts::components::InputComponent *>(inputC)->setVal(nts::FALSE);
    dynamic_cast<nts::components::InputComponent *>(X2)->setVal(nts::FALSE);

    gate->setLink(2, *X2, 0);
    gate->setLink(10, *inputA, 0);
    gate->setLink(11, *inputB, 0);
    gate->setLink(12, *inputC, 0);

    gate->simulate(1);
    cr_assert_eq(gate->compute(13), X2->compute(0));
}