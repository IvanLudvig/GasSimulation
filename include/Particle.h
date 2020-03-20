#ifndef GASSIMULATION_PARTICLE_H
#define GASSIMULATION_PARTICLE_H

#include "vector3D.h"

class Particle
{

private:
    double mass, radius;
    double U;

    vector3D pos;
    vector3D speed;
    vector3D acceleration;
    vector3D force;

public:
    Particle(const double &mass = 0, const double &radius = 0, const vector3D &pos = vector3D(0, 0, 0),
             const vector3D &speed = vector3D(0, 0, 0),
             const vector3D &acceleration = vector3D(0, 0, 0),
             const vector3D &force = vector3D(0, 0, 0));

    void setMass(double mass);

    void setU(double U);

    void setPos(vector3D pos);

    void setSpeed(vector3D speed);

    void setAcceleration(vector3D acceleration);

    void setForce(vector3D force);

    double getMass();

    double getU();

    vector3D getPos() const;

    vector3D getSpeed() const;

    vector3D getAcceleration() const;

    vector3D getForce() const;

    void update(double delta);

    void collideWithWalls(vector3D tank);

    void collideWithParticle(Particle &p);

    bool isNear(Particle p);
};

double distance(const Particle &p1, const Particle &p2);

#endif //GASSIMULATION_PARTICLE_H
