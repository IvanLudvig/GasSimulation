#ifndef GASSIMULATION_PARTICLE_H
#define GASSIMULATION_PARTICLE_H

#include "vector3D.h"

double const k = 1.38 * pow(10, -23);
double const Na = 6.022 * pow(10, 23);

class Particle
{

private:
    double mass, radius;
    double U = 0;
    double E = 0;
    int i = 0;

    vector3D pos;
    vector3D speed;
    vector3D acceleration;

public:
    Particle(const double mass = 0, const double radius = 0, const vector3D &pos = vector3D(),
             const vector3D &speed = vector3D(), const vector3D &acceleration = vector3D());

    void setMass(const double mass);

    void setU(const double U);

    void setPos(const vector3D &pos);

    void setSpeed(const vector3D &speed);

    void setAcceleration(const vector3D &acceleration);

    void setForce(vector3D force);

    void addForce(vector3D force);

    double getU() const;

    void addU(double U);

    double getE() const;

    double getMass();

    vector3D getPos() const;

    vector3D getSpeed() const;

    vector3D getAcceleration() const;

    vector3D getForce() const;

    void update(const double delta);

    void collideWithWalls(const vector3D &tank);

    void collideWithParticle(Particle &p);

    bool isNear(const Particle &p);
};

double distance(const Particle &p1, const Particle &p2);

#endif //GASSIMULATION_PARTICLE_H
