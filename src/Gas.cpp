#include "Gas.h"
#include "vector3D.h"


Gas::Gas(int N, double molarMass, vector3D tank, double e, double b) : N{N}, molarMass{molarMass}, tank{tank}, e{e},
                                                                       b{b}, V{tank.getX() * tank.getY() * tank.getZ()}
{
    vector3D grid[1000];
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                grid[i + (j * 10) + (k * 100)] = vector3D((1.0 * (i + 1) / 10) * tank.getX(),
                                                          (1.0 * (j + 1) / 10) * tank.getY(),
                                                          (1.0 * (k + 1) / 10) * tank.getZ());
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        particles.emplace_back(Particle(1, 0, grid[i]));
    }
    this->tree = Octree(vector3D(0, 0, 0), tank, 10);
    for (int i = 0; i < N; i++)
    {
        tree.add(particles.at(i));
    }
    for (auto &p : particles)
    {
        tree.update(p, e, b);
    }
}

Gas::Gas(std::vector<Particle> particles, vector3D tank)
{
    this->N = particles.size();
    this->particles = particles;

    this->tree = Octree(vector3D(0, 0, 0), tank, 1000);
    for (int i = 0; i < N; i++)
    {
        tree.add(particles.at(i));
    }
    //std::cout << tree << std::endl;
}

void Gas::update()
{
    this->tree = Octree(vector3D(0, 0, 0), tank, 1000);
    for (int i = 0; i < N; i++)
    {
        tree.add(particles.at(i));
    }
    for (auto &p : particles)
    {
        p.setForce(vector3D(0, 0, 0));
        tree.update(p, e, b);
    }
    double delta = tree.getDelta();
    for (auto &p : particles)
    {
        p.update(delta);
        p.collideWithWalls(tank);
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


void Gas::setMaxwellDistribution(double T)
{
    int size = 0;
    int F;
    int v = 10;
    while (size < N)
    {
        F = 4 * 3.14 * pow((molarMass / (Na * 2 * 3.14 * k * T)), 1.5) * pow(v, 2) *
            exp(-molarMass * v * v / (2 * k * T));
        for (int i = size; i < size + F * N; i++)
        {
            vector3D V;
            switch (v % 3)
            {
                case 0:
                    V = vector3D(v, 0, 0);
                case 1:
                    V = vector3D(0, v, 0);
                case 2:
                    V = vector3D(0, 0, v);
            }
            particles[i].setSpeed(V);
        }
        size += F * N;
        v++;
    }
}