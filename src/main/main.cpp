#include <cstdio>
#include <curses.h>
#include <simula24/core/stl/copy_on_write.h>
#include <simula24/core/stl/utility.h>
#include <utility>
int main(int argc, char** argv)
{
    int x = 500;
    int&& y = std::move(x);

    printf("%d | %d\n", x, y);
}