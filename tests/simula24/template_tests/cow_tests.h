#ifndef TESTS_SIMULA24_TEMPLATE_TESTS_COW_TESTS_H
#define TESTS_SIMULA24_TEMPLATE_TESTS_COW_TESTS_H

#include <simula24/core/stl/copy_on_write.h>
#include <gtest/gtest.h>

struct _test
{
    size_t x;
    size_t y;

    _test(size_t _x, size_t _y) : x(_x), y(_y) {}
};


TEST(stl_test, cow_test_primitive)
{
    simula24::copy_on_write<int> x;
    simula24::copy_on_write<int> y;
    EXPECT_EQ(x.get_total_size(), 0);
    x.resize(10);
    
    for (size_t i = 0; i < 10; i++)
    {
        x.at_m(i) = i * i;
    }

    y = x;

    EXPECT_EQ(y.get_reference_count(), 2);
    EXPECT_EQ(x.get_reference_count(), 2);

    EXPECT_EQ(&y.reference(), &x.reference());
    
  
    for (size_t i = 0; i < 10; i++)
    {
        EXPECT_EQ(y.at(i), i * i);
    }



    y.resize(20);
    EXPECT_NE(&y.reference(), &x.reference());
    EXPECT_EQ(y.get_reference_count(), 1);
    EXPECT_EQ(x.get_reference_count(), 1);


}

TEST(stl_test, cow_test_adt)
{
    simula24::copy_on_write<_test> x;
    simula24::copy_on_write<_test> y;
    EXPECT_EQ(x.get_total_size(), 0);

    x.resize(10);

    for (size_t i = 0; i < 10; i++)
        x.at_m(i) = _test{ i, i * i };

    y = x;
    for (size_t i = 0; i < 10; i++)
    {
        EXPECT_EQ(y.at(i).x, i);
        EXPECT_EQ(y.at(i).y, i * i);
    }

}

#endif // TESTS_SIMULA24_TEMPLATE_TESTS_COW_TESTS_H