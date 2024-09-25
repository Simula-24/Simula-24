#ifndef RTL_STR_TEST_H_
#define RTL_STR_TEST_H_

#include <gtest/gtest.h>
#include <simula24/core/stl/string.h>


TEST(stl_test, str_test_cow)
{
    simula24::string test = "hello";

    simula24::string test2 = test;

    EXPECT_EQ(test.c_str(), test2.c_str());

    test2 += "h";

    EXPECT_NE(test.c_str(), test2.c_str());

}

TEST(stl_test, str_test_equality)
{
    simula24::string test1 = "hello";
    simula24::string test2 = "hello";

    EXPECT_EQ(test1, test2);

    test2 += "1";

    EXPECT_NE(test1, test2);

    simula24::string test3 = "privet komrad";

    EXPECT_EQ(test3, "privet komrad");

    test1 = "hello";
    test2 = "world";

    simula24::string test4 = test1 + test2;

    EXPECT_EQ(test4, "helloworld");

}

TEST(stl_test, str_substr)
{
    simula24::string test = "#######privet komrad#######";

    simula24::string test2 = test.substr(7, 20);

    EXPECT_NE(test.c_str(), test2.c_str());

    EXPECT_EQ(test2, "privet komrad");

    test2 += ", stalin is waiting";
    EXPECT_TRUE(test2 == "privet komrad, stalin is waiting");

    simula24::string test3 = test2.substr(0, 6);

    EXPECT_TRUE(test3 == "privet");
}

TEST(stl_test, str_misc)
{
    simula24::string test = "abcdefghijklmnopqrtstuvwxyz1234567890";

    EXPECT_TRUE(test[0] == 'a');
    EXPECT_TRUE(test.front() == 'a');

    EXPECT_TRUE(test.back() == '0');


}
#endif // RTL_STR_TEST_H_