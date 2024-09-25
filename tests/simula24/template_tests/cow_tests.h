#ifndef TESTS_SIMULA24_TEMPLATE_TESTS_COW_TESTS_H
#define TESTS_SIMULA24_TEMPLATE_TESTS_COW_TESTS_H

#include <simula24/core/stl/copy_on_write.h>
#include <gtest/gtest.h>

struct _test
{
    int x;
    int y;
};


TEST(stl_test, cow_test_primitive)
{
    simula24::copy_on_write<int> x;
    simula24::copy_on_write<int> y;
    EXPECT_EQ(x.get_total_size(), 0);
    x.resize(10);

    y = x;

    EXPECT_EQ(y.get_reference_count(), 2);
    EXPECT_EQ(x.get_reference_count(), 2);

    EXPECT_EQ(&y.reference(), &x.reference());
    y.resize(20);
    EXPECT_NE(&y.reference(), &x.reference());
    EXPECT_EQ(y.get_reference_count(), 1);
    EXPECT_EQ(x.get_reference_count(), 1);
}

#endif // TESTS_SIMULA24_TEMPLATE_TESTS_COW_TESTS_H