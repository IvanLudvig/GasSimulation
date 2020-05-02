#include <Gas.h>
#include <chrono>
#include <iostream>

int main()
{
    int T[10] = {3, 10, 15, 20, 50};
    for (int t = 0; t < 1; t++)
    {
        float time = 0;
        Gas gas(10000, 0.0399, vector3D(100, 100, 100), 119.8 * k, 1, T[t]);
        std::cout << std::endl << "TEMPERATURE " << T[t] << std::endl;
        for (int i = 0; i < 100; i++)
        {
            auto t1 = std::chrono::high_resolution_clock::now();
            gas.update();
            auto t2 = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
            std::cout << duration / 1e6 << std::endl;
            time += duration / 1e6;
        }

        std::cout << "COMPUTATION TIME: " << time << std::endl;
        std::cout << "SIMULATION TIME: " << gas.time << std::endl;
    }
    return 0;
}
