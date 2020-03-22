#include <iostream>
#include <Gas.h>

int main()
{
    Gas gas(5, 4.0e-3, vector3D(10, 10, 10), 10.22*(1.38e-23), 2.56);
    for (int i = 0; i < 5000; i++)
    {
        gas.update();
    }
    return 0;
}
