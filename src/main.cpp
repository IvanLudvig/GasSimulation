#include <Gas.h>
#include <iostream>

int main()
{
    int T[10] = {1, 2, 5, 10, 15, 20, 50};
    for (int t = 0; t < 2; t++)
    {
        Gas gas(1000, 0.0399, vector3D(100, 100, 100), 119.8 * k, 1, 20, T[t]);
        std::cout << std::endl << "TEMPERATURE " << T[t] << std::endl;
        for (int i = 0; i < 200; i++)
        {
            gas.update();
        }
    }
    return 0;
}
