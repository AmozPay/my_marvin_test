/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** ram4801.test
*/

#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <cstddef>
#include <iostream>
#include <vector>
#include "../../include/Core.hpp"
#include "../../include/Sequential.hpp"

namespace ramCTest {
    nts::IComponent *ram = nts::components::createRam4801C("ramC");
    std::vector<nts::IComponent *> addressInputs(10, nts::components::createInputComponent("I"));
    std::vector<nts::IComponent *> writeInputs(10, nts::components::createInputComponent("I"));
    nts::IComponent *ce = nts::components::createTrueComponent("ce");
    nts::IComponent *we = nts::components::createInputComponent("we");
    nts::IComponent *oe = nts::components::createInputComponent("oe");

    void setup()
    {
        for (int i = 0; i < 8; i++)
            ramCTest::ram->setLink(i, *(ramCTest::addressInputs[i]), 0);
        for (int i = 7; i >= 3; i--) {
            ramCTest::ram->setLink(i + 9, *(ramCTest::writeInputs[i]), 0);
        }
        ramCTest::ram->setLink(10, *(ramCTest::writeInputs[2]), 0);
        ramCTest::ram->setLink(9, *(ramCTest::writeInputs[1]), 0);
        ramCTest::ram->setLink(8, *(ramCTest::writeInputs[0]), 0);
        ramCTest::ram->setLink(22, *(ramCTest::addressInputs[8]), 0);
        ramCTest::ram->setLink(21, *(ramCTest::addressInputs[9]), 0);
        ramCTest::ram->setLink(17, *ramCTest::ce, 0);
        ramCTest::ram->setLink(20, *ramCTest::we, 0);
        ramCTest::ram->setLink(19, *ramCTest::oe, 0);
    }
}

Test(ram4801, write_read_0,  .init = ramCTest::setup)
{
    // Write
    nts::tickCounter++;
    for (auto it: ramCTest::addressInputs) {
        dynamic_cast<nts::components::InputComponent *>(it)->setVal(nts::FALSE);
        it->simulate(1);
    }
    for (auto it: ramCTest::writeInputs) {
        dynamic_cast<nts::components::InputComponent *>(it)->setVal(nts::FALSE);
        it->simulate(1);
    }
    dynamic_cast<nts::components::InputComponent *>(ramCTest::we)->setVal(nts::TRUE);
    dynamic_cast<nts::components::InputComponent *>(ramCTest::oe)->setVal(nts::FALSE);
    ramCTest::we->simulate(1);
    ramCTest::oe->simulate(1);
    ramCTest::ram->simulate(1); // write 00000000 to address 0d0

    for (int i = 7; i >= 3; i--)
        cr_assert_eq(ramCTest::ram->compute(i + 9), nts::FALSE);
    cr_assert_eq(ramCTest::ram->compute(10), nts::FALSE);
    cr_assert_eq(ramCTest::ram->compute(9), nts::FALSE);

    // Read
    nts::tickCounter++;
    for (auto it: ramCTest::addressInputs) {
        dynamic_cast<nts::components::InputComponent *>(it)->setVal(nts::FALSE);
        it->simulate(1);
    }
    for (auto it: ramCTest::writeInputs) {
        dynamic_cast<nts::components::InputComponent *>(it)->setVal(nts::FALSE);
        it->simulate(1);
    }
    dynamic_cast<nts::components::InputComponent *>(ramCTest::we)->setVal(nts::FALSE);
    dynamic_cast<nts::components::InputComponent *>(ramCTest::oe)->setVal(nts::TRUE);
    ramCTest::we->simulate(1);
    ramCTest::oe->simulate(1);
    ramCTest::ram->simulate(1); // output address 0d0

    for (int i = 7; i >= 3; i--)
        cr_assert_eq(ramCTest::ram->compute(i + 9), nts::FALSE);
    cr_assert_eq(ramCTest::ram->compute(10), nts::FALSE);
    cr_assert_eq(ramCTest::ram->compute(9), nts::FALSE);

    nts::tickCounter++;
    for (auto it: ramCTest::writeInputs) {
        dynamic_cast<nts::components::InputComponent *>(it)->setVal(nts::TRUE);
        it->simulate(1);
    }
    dynamic_cast<nts::components::InputComponent *>(ramCTest::we)->setVal(nts::TRUE);
    dynamic_cast<nts::components::InputComponent *>(ramCTest::oe)->setVal(nts::FALSE);
    ramCTest::we->simulate(1);
    ramCTest::oe->simulate(1);
    ramCTest::ram->simulate(1); // write 11111111 to address 0

    for (int i = 7; i >= 3; i--)
        cr_assert_eq(ramCTest::ram->compute(i + 9), nts::TRUE);
    cr_assert_eq(ramCTest::ram->compute(10), nts::TRUE);
    cr_assert_eq(ramCTest::ram->compute(9), nts::TRUE);

    // read
    nts::tickCounter++;
    dynamic_cast<nts::components::InputComponent *>(ramCTest::we)->setVal(nts::FALSE);
    dynamic_cast<nts::components::InputComponent *>(ramCTest::oe)->setVal(nts::TRUE);
    ramCTest::we->simulate(1);
    ramCTest::oe->simulate(1);
    ramCTest::ram->simulate(1); // output address 0

    for (int i = 7; i >= 3; i--)
        cr_assert_eq(ramCTest::ram->compute(i + 9), nts::TRUE);
    cr_assert_eq(ramCTest::ram->compute(10), nts::TRUE);
    cr_assert_eq(ramCTest::ram->compute(9), nts::TRUE);
}
