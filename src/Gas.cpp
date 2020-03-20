#include "Gas.h"

Gas::Gas(int N, double molarMass, vector3D tank, double e, double b) : N{N}, molarMass{molarMass}, tank{tank}, e{e},
                                                                       b{b}, V{tank.getX() * tank.getY() * tank.getZ()}
{
    std::mt19937 gen;
    std::uniform_real_distribution<double> dis{0, 1};
    for (int i = 0; i < N; i++)
    {
        particles.push_back(Particle(molarMass / Na, 0,
                                     vector3D(dis(gen) * tank.getX(),
                                              dis(gen) * tank.getY(),
                                              dis(gen) * tank.getZ()),
                                     (vector3D(dis(gen), dis(gen), dis(gen)))));
    }
    this->tree = Octree(vector3D(0, 0, 0), tank, 10);
    for (int i = 0; i < N; i++)
    {
        tree.add(particles.at(i));
    }
    std::cout << tree << std::endl;
}

Gas::Gas(std::vector<Particle> particles, vector3D tank)
{
    this->N = particles.size();
    this->particles = particles;

    this->tree = Octree(vector3D(0, 0, 0), tank, 10);
    for (int i = 0; i < N; i++)
    {
        tree.add(particles.at(i));
    }
    std::cout << tree << std::endl;
}

int Gas::getN()
{
    return N;
}

double Gas::getE()
{
    return e;
}

double Gas::getB()
{
    return b;
}

double Gas::getTemperature()
{
    return T;
}

double Gas::getPressure()
{
    return 0;
}

void Gas::update(double delta)
{
    //Particle collisions
    for (auto &p : particles)
    {
        p.update(delta);
        p.collideWithWalls(tank);
        tree.update(p, e, b);
    }

    //Computing gas parameters
    double rmsSpeed = 0;  //squared root-mean-square speed
    for (auto &p : particles)
    {
        rmsSpeed += p.getSpeed().length() * p.getSpeed().length();
    }
    rmsSpeed /= N;
    T = (rmsSpeed * molarMass) / (3 * R);
    P = (N * R * T) / (Na * V);
}


