#ifndef GASSIMULATION_PARTICLE_H
#define GASSIMULATION_PARTICLE_H

#include "vector3D.h"

class Particle {

private:
    double mass;

    vector3D pos;
    vector3D speed;
    vector3D acceleration;

public:
    Particle(double mass);
    Particle(double mass, vector3D pos);
    Particle(double mass, vector3D pos, vector3D speed);
    Particle(double mass, vector3D pos, vector3D speed, vector3D acceleration);

    void setMass(double mass);
    void setPos(vector3D pos);
    void setSpeed(vector3D speed);
    void setAcceleration(vector3D acceleration);

    double getMass();
    vector3D getPos();
    vector3D getSpeed();
    vector3D getAcceleration();

    void update(vector3D force, double delta);
};


#endif //GASSIMULATION_PARTICLE_H
