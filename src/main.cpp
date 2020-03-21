#include <iostream>
#include <Gas.h>

int main()
{
    Gas gas(3, 4.0 / 1000, vector3D(10, 10, 10), 0.2, 1);
    for (int i = 0; i < 3; i++)
    {
        gas.update();
        std::cout << std::endl;
    }
    return 0;//984
}
