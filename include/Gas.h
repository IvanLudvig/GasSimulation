#ifndef GASSIMULATION_GAS_H
#define GASSIMULATION_GAS_H

#include "Octree.h"
#include "Particle.h"
#include <cmath>
#include <random>

class Gas
{
  private:
    std::vector<Particle> particles;
    Octree tree;
    unsigned long int N; // number of particles
    double e, b;         // for determination of potential
    double P, V, T;
    double U, E; // energy
    double molarMass;
    vector3D tank; // gas tank: box with vector components as its sides
    double delta;

  public:
    const double R = 8.31;        // Gas constant
    const double Na = 6.02214e23; // Avogadro constant
    double time = 0;
    int i = 0;
    Gas(const unsigned long int N, const double molarMass, const vector3D &tank, const double e, const double b);

    // Particle parameters update, collision with walls and gas parameters update
    void update();

    double getEnergy() const;

    double getTemperature() const;

    double getPressure() const;

    int getN() const;

    void setMaxwellDistribution(double T);

    // Potential energy of the interaction of two molecules:
    double PotentialEnergy(const double r); // r - distance between molecules

    // Strength of the interaction of two molecules:
    double F(double r); // r - distance between molecules

    // this function calculates energy of interaction of each molecule with each.
    // O(N^2)
    double TotalSystemEnergy();

    long double distributionDensity(double x);
};

#endif // GASSIMULATION_GAS_H
