#ifndef GASSIMULATION_PARTICLE_H
#define GASSIMULATION_PARTICLE_H

#include "vector3D.h"

class Particle
{

private:
    double mass, radius;

    vector3D pos;
    vector3D speed;
    vector3D acceleration;
    vector3D force;

public:
    Particle(double mass, double radius);
    Particle(double mass, double radius, vector3D pos);
    Particle(double mass, double radius, vector3D pos, vector3D speed);
    Particle(double mass, double radius, vector3D pos, vector3D speed, vector3D acceleration);

    void setMass(double mass);
    void setPos(vector3D pos);
    void setSpeed(vector3D speed);
    void setAcceleration(vector3D acceleration);
    void setForce(vector3D force);

    double getMass();
    vector3D getPos();
    vector3D getSpeed();
    vector3D getAcceleration();
    vector3D getForce();

    void update(vector3D force, double delta);
    void collideWithWalls(vector3D tank);
    void collideWithParticle(Particle p);
    double particleSpacing(Particle p);
    bool isNear(Particle p);
};


#endif //GASSIMULATION_PARTICLE_H
