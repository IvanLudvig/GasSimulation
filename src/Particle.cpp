#include "../include/Particle.h"


Particle::Particle(double mass, double radius)
{
    this->mass = mass;
    this->radius = radius;
    pos = vector3D(0, 0, 0);
    speed = vector3D(0, 0, 0);
    acceleration = vector3D(0, 0, 0);
}

Particle::Particle(double mass, double radius, vector3D pos)
{
    this->mass = mass;
    this->pos = pos;
    this->radius = radius;
    speed = vector3D(0, 0, 0);
    acceleration = vector3D(0, 0, 0);
}

Particle::Particle(double mass, double radius, vector3D pos, vector3D speed)
{
    this->mass = mass;
    this->radius = radius;
    this->pos = pos;
    this->speed = speed;
    acceleration = vector3D(0, 0, 0);
    std::cout << pos << " " << speed << std::endl;
}

Particle::Particle(double mass, double radius, vector3D pos, vector3D speed, vector3D acceleration)
{
    this->mass = mass;
    this->radius = radius;
    this->pos = pos;
    this->speed = speed;
    this->acceleration = acceleration;
}


void Particle::setMass(double mass)
{
    this->mass = mass;
}

void Particle::setPos(vector3D pos)
{
    this->pos = pos;
}

void Particle::setSpeed(vector3D speed)
{
    this->speed = speed;
}

void Particle::setAcceleration(vector3D acceleration)
{
    this->acceleration = acceleration;
}


double Particle::getMass()
{
    return mass;
}

vector3D Particle::getPos()
{
    return pos;
}

vector3D Particle::getSpeed()
{
    return speed;
}

vector3D Particle::getAcceleration()
{
    return acceleration;
}

void Particle::update(vector3D force, double delta)
{
    pos += speed * delta + acceleration * delta * delta / 2;
    speed += acceleration * delta;
    acceleration = force / mass;
    std::cout << pos << " " << speed << std::endl;
}

void Particle::collideWithWalls(vector3D tank)
{
    if ((pos.getX() >= tank.getX()) || (pos.getX() <= 0))
    {
        vector3D n = vector3D(1, 0, 0);
        vector3D proj = (n * (speed * n)) - speed;
        speed = (2 * proj) - speed;
        pos.setX(tank.getX());
    }
    if ((pos.getY() >= tank.getY()) || (pos.getY() <= 0))
    {
        vector3D n = vector3D(0, 1, 0);
        vector3D proj = (n * (speed * n)) - speed;
        speed = (2 * proj) - speed;
        pos.setY(tank.getY());
    }
    if ((pos.getZ() >= tank.getZ()) || (pos.getZ() <= 0))
    {
        vector3D n = vector3D(0, 0, 1);
        vector3D proj = (n * (speed * n)) - speed;
        speed = (2 * proj) - speed;
        pos.setZ(tank.getZ());
    }
}

bool Particle::isNear(Particle p)
{
    return (p.getPos() - pos).length() <= radius;
}

