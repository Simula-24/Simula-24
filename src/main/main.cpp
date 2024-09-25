#include <cstdio>
#include <curses.h>
#include <simula24/core/stl/copy_on_write.h>
#include <simula24/core/stl/utility.h>
#include <simula24/core/stl/smart_ptr.h>
#include <utility>
int main(int argc, char** argv)
{
    simula24::shared_ptr<int> x = simula24::make_shared<int>(1);
    printf("%d\n",*x);
}