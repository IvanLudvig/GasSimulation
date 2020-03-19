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
    for (auto &particle : particles)
    {
        particle.update(vector3D(0, 0, 0), delta);
        particle.collideWithWalls(tank);
    }
    //collide();

    //Computing gas parameters
    double rmsSpeed = 0;  //squared root-mean-square speed
    for (auto &particle : particles)
    {
        rmsSpeed += particle.getSpeed().module() * particle.getSpeed().module();
    }
    rmsSpeed /= N;
    T = (rmsSpeed * molarMass) / (3 * R);
    P = (N * R * T) / (Na * V);
}

void Gas::collide()
{
    for (auto p1 = particles.begin(); p1 < particles.end() - 1; p1++)
    {
        for (auto p2 = p1 + 1; p2 < particles.end(); p2++)
        {
            if (p1->isNear(*p2))
            {
                p1->setU(p1->getU() + 4 * getE() *
                                      (pow((getB() / p1->particleSpacing(*p2)), 12) -
                                       pow((getB() / p1->particleSpacing(*p2)), 6)));
                vector3D n = (p2->getPos() - p1->getPos()) / p1->particleSpacing(*p2);
                p1->setForce(p1->getForce() + (-1) * (p1->getU()) * (n) / (p1->particleSpacing(*p2)));
            }
        }
    }
}

