#include <stdio.h>
#include <gtest/gtest.h>
#include "simula24/simula24_tests.h"
#include <core/error/seh.h>
int main(int argc, char** argv)
{
    simula24::setSEHHandler();
    printf("Running unit tests...\n");
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}