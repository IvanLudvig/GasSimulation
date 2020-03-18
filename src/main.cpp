#include <iostream>
#include <Gas.h>

int main()
{
    Gas gas(5, 18, vector3D(10, 10, 10), 0.2, 1);
    for (int i = 0; i < 400; i++)
    {
        gas.update(0.1);
    }
    return 0;
}
