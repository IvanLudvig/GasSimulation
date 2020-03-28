#include <Gas.h>
#include <iostream>

int main()
{
    Gas gas(100, 1, vector3D(10, 10, 10), 1, 1);
    for (int i = 0; i < 20000; i++)
    {
        gas.update();
    }
    return 0;
}