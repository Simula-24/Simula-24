#ifndef UNITTEST_FN_PTR_TEST_H_
#define UNITTEST_FN_PTR_TEST_H_

#include <gtest/gtest.h>
#include <simula24/core/stl/function.h>

static int getSpecialNumber() { return 1234; }


TEST(stl_test, function_ptr_test)
{

    simula24::function<int()> test = &getSpecialNumber;

    EXPECT_EQ(test(), 1234);

    simula24::function<int(int)> test2 = [](int x) -> int {
        return x * x;
        };


    EXPECT_EQ(test2(4), 16);




}

#endif // UNITTEST_FN_PTR_TEST_H_