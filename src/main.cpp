#include <iostream>
#include <Gas.h>

int main()
{
    Gas gas(500, 1, vector3D(10, 10, 10), 1, 1);
    for (int i = 0; i < 10000; i++)
    {
        gas.update();
    }
    return 0;
}