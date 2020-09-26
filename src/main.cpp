#include <Gas.h>
#include <chrono>
#include <iostream>

int VOLUMES[10] = {30, 31, 32, 33, 34, 35, 36};
int ITERATIONS = 2000;

int main()
{
    for (int v = 0; v < 1; v++)
    {
        float time = 0;
        Gas gas(1000, 0.0399, vector3D(VOLUMES[v], VOLUMES[v], VOLUMES[v]), 119.8 * k, 1, 1.25);
        std::cout << std::endl << "VOLUME " << VOLUMES[v] << std::endl;
        for (int i = 0; i < ITERATIONS; i++)
        {
            auto t1 = std::chrono::high_resolution_clock::now();
            gas.update();
            auto t2 = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
            time += duration / 1e6;
        }

        std::cout << "COMPUTATION TIME: " << time << std::endl;
        std::cout << "SIMULATION TIME: " << gas.time << std::endl;
    }
    return 0;
}
