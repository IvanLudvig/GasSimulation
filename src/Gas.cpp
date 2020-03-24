#include "Gas.h"
#include "vector3D.h"


Gas::Gas(int N, double molarMass, vector3D tank, double e, double b) : N{N}, molarMass{molarMass}, tank{tank}, e{e},
                                                                       b{b}, V{tank.getX() * tank.getY() * tank.getZ()}
{
    vector3D grid[1000];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                grid[i + (j * 5) + (k * 25)] = vector3D((1.0 * (i + 1) / 5) * tank.getX(),
                                                        (1.0 * (j + 1) / 5) * tank.getY(),
                                                        (1.0 * (k + 1) / 5) * tank.getZ());
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
        p.setU(0);
        tree.update(p, e, b);
    }
    double delta = tree.getDelta();
    double fullE= 0;
    double fullU = 0;
    for (auto &p : particles)
    {
        p.update(delta);
        //aproximation
        fullU += p.getU()/2;
        fullE += p.getE();
        p.collideWithWalls(tank);
    }
    std::cout<<fullU+fullE<<std::endl;
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
            particles.at(i).setSpeed(V);
        }
        size += F * N;
        v++;
    }
}