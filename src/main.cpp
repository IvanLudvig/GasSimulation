#include <Gas.h>
#include <iostream>

int main()
{
    Gas gas(1000, 1, vector3D(100, 100, 100), 1, 1);
    int i = 0;
    //while(gas.time<=0.46e12)
    while(i<20)
    {
        gas.update();
        i++;
    }
    return 0;
}