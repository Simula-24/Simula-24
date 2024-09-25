#include <cstdio>
#include <curses.h>
#include <simula24/core/stl/copy_on_write.h>
int main(int argc, char** argv)
{
    simula24::copy_on_write<int> test;
}