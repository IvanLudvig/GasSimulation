#include <Gas.h>
#include <iostream>

int main()
{
    Gas gas(1000, 0.0399, vector3D(100, 100, 100), 119.8*k, 1, 20);
    for (int i = 0; i < 2000; i++)
    {
        gas.update();
    }
    return 0;
}
