#ifndef GASSIMULATION_GAS_H
#define GASSIMULATION_GAS_H

#include <random>
#include "Particle.h"
#include "Octree.h"

class Gas
{
private:
    std::vector<Particle> particles;
    Octree tree;
    int N;  //number of particles
    double e, b;  //for determination of potential
    double P, V, T;
    double molarMass;
    vector3D tank;  //gas tank: box with vector components as its sides

public:
    const double R = 8.31;  //Gas constant
    const double Na = 6.02214e23;   //Avogadro constant
    Gas(int N, double molarMass, vector3D tank, double e, double b);

    Gas(std::vector<Particle> particles, vector3D tank);

    int getN();

    double getE();

    double getB();

    //Particle parameters update, collision with walls and gas parameters update
    void update();

    double getTemperature();

    double getPressure();

    void setMaxwellDistribution(double T);

    //Collision between particles
    void collide();
};


#endif //GASSIMULATION_GAS_H
