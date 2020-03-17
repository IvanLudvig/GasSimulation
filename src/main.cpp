#include <iostream>
#include <Gas.h>

int main()
{
    Gas gas(10, 18, vector3D(10, 10, 10));
    for (int i = 0; i < 10; i++)
    {
        std::cout<<i*0.1<<std::endl;
        gas.update(0.1);
    }
    return 0;
}
