#include "../include/Particle.h"


Particle::Particle(double mass) {
    this->mass = mass;
}

Particle::Particle(double mass, vector3D pos) {
    this->mass = mass;
    this->pos = pos;
}

Particle::Particle(double mass, vector3D pos, vector3D speed) {
    this->mass = mass;
    this->pos = pos;
    this->speed = speed;
}

Particle::Particle(double mass, vector3D pos, vector3D speed, vector3D acceleration) {
    this->mass = mass;
    this->pos = pos;
    this->speed = speed;
    this->acceleration = acceleration;
}


void Particle::setMass(double mass) {
    this->mass = mass;
}

void Particle::setPos(vector3D pos) {
    this->pos = pos;
}

void Particle::setSpeed(vector3D speed) {
    this->speed = speed;
}

void Particle::setAcceleration(vector3D acceleration) {
    this->acceleration = acceleration;
}


double Particle::getMass() {
    return mass;
}

vector3D Particle::getPos() {
    return pos;
}

vector3D Particle::getSpeed() {
    return speed;
}

vector3D Particle::getAcceleration() {
    return acceleration;
}

void Particle::update(vector3D force, double delta) {
    pos += speed*delta + acceleration*delta*delta/2;
    speed += acceleration*delta;
    acceleration = force/mass;
}
