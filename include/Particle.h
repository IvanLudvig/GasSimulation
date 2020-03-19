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
    Particle(double mass = 0, double radius = 0, vector3D pos = vector3D(0, 0, 0), vector3D speed = vector3D(0, 0, 0),
             vector3D acceleration = vector3D(0, 0, 0), vector3D force = vector3D(0, 0, 0));

    void setMass(double mass);

    void setU(double U);

    void setPos(vector3D pos);

    void setSpeed(vector3D speed);

    void setAcceleration(vector3D acceleration);

    void setForce(vector3D force);

    double getMass();

    double getU();

    vector3D getPos();

    vector3D getSpeed();

    vector3D getAcceleration();

    vector3D getForce();

    void update(vector3D force, double delta);

    void collideWithWalls(vector3D tank);

    void collideWithParticle(Particle& p);

    double particleSpacing(Particle p);

    bool isNear(Particle p);
};


#endif //GASSIMULATION_PARTICLE_H
