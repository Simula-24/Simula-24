#ifndef TT_PQ_TEST_H_
#define TT_PQ_TEST_H_

#include <gtest/gtest.h>
#include <core/stl/priority_queue.h>

#include <utility>
#include <algorithm>

TEST(stl_test, priority_queue_primative)
{
    stl::priority_queue<int> test(10);
    std::vector<int> s{ 76,4,6,24,93,2,5,8,72, 1 };
    std::make_heap(s.begin(), s.end());

    for (int j = 0; j < 10; j++)
    {
        test.push(s[j], s[j]);
     

    }

    for (int j = 0; j < 10; j++)
    {
        EXPECT_EQ(test.pop().priority, s[0]);
        std::pop_heap(s.begin(), s.end());
        s.pop_back();

    }

}


TEST(stl_test, priority_queue_adt)
{
    stl::priority_queue<stl::string> test(10);
    std::vector<int> s{ 76,4,6,24,93,2,5,8,72, 1 };
    std::make_heap(s.begin(), s.end());

    for (int j = 0; j < 10; j++)
    {
        test.push("" + (char)j, s[j]);


    }

    for (int j = 0; j < 10; j++)
    {
        EXPECT_EQ(test.pop().priority, s[0]);
        std::pop_heap(s.begin(), s.end());
        s.pop_back();

    }

}


#endif // TT_PQ_TEST_H_