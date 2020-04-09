#include <Gas.h>
#include <iostream>

int main()
{
    Gas gas(100, 1, vector3D(100, 100, 100), 1, 1);
    for (int i = 0; i < 2000; i++)
    {
        gas.update();
    }
    return 0;
}