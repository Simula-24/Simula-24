#ifndef TESTS_SIMULA24_TEMPLATE_TESTS_ARRAY_TESTS_H_
#define TESTS_SIMULA24_TEMPLATE_TESTS_ARRAY_TESTS_H_

#include <simula24/core/stl/string.h>
#include <simula24/core/stl/array.h>

#include <gtest/gtest.h>

TEST(stl_test, array_test_primatives)
{
    stl::array<int> test;
    test.resize(20);
    for (int i = 0; i < 20; i++)
        test.push_back(i);

    EXPECT_EQ(test.size(), 20);
    for (int i = 0; i < 20; i++)
    {
        ASSERT_EQ(test[i], i);
    }

    test.push_back(20);

    EXPECT_EQ(test[20], 20);
    EXPECT_EQ(test.size(), 21);

}

TEST(stl_test, array_test_adt)
{
    stl::array<stl::string> test;

    char testdata[][10] =
    {
        "test1",
        "test2",
        "test3",
        "test4",
        "test5",
        "test6",
        "test7",
        "test8",
        "test9",
        "test10",
    };

    for (int i = 0; i < 10; i++)
    {
        test.push_back({ testdata[i] });
    }

    for (int i = 0; i < 10; i++)
    {
        EXPECT_TRUE(test[i] == testdata[i]);
        test[i] += "mod";
        EXPECT_TRUE(test[i] != testdata[i]);

    }

}


#endif // TESTS_SIMULA24_TEMPLATE_TESTS_ARRAY_TESTS_H_