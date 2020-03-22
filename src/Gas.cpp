#include "Gas.h"

Gas::Gas(int N, double molarMass, vector3D tank, double e, double b) : N{N}, molarMass{molarMass}, tank{tank}, e{e},
                                                                       b{b}, V{tank.getX() * tank.getY() * tank.getZ()}
{
    for (int i = 0; i < N; i++)
    {
        particles.emplace_back(Particle(molarMass / Na, 0,
                                        vector3D(((double) rand() / RAND_MAX) * tank.getX(),
                                                 ((double) rand() / RAND_MAX) * tank.getY(),
                                                 ((double) rand() / RAND_MAX) * tank.getZ())));
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
    //Particle collisions
    double delta = tree.getDelta();
    //std::cout<<"delta "<<delta<<std::endl;
    this->tree = Octree(vector3D(0, 0, 0), tank, 1000);
    for (int i = 0; i < N; i++)
    {
        tree.add(particles.at(i));
    }
    int i =0;
    for (auto &p : particles)
    {
        //std::cout<<i<<std::endl;
        tree.update(p, e, b);
        p.update(delta);
        p.collideWithWalls(tank);
        i++;
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
