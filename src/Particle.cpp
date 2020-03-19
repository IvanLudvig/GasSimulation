#include "../include/Particle.h"


Particle::Particle(double mass, double radius, vector3D pos, vector3D speed, vector3D acceleration, vector3D force)
        : mass{mass},
          radius{radius},
          pos{pos},
          speed{speed},
          acceleration{acceleration},
          force{force}
{
}


void Particle::setMass(double mass)
{
    this->mass = mass;
}

void Particle::setU(double U)
{
    this->U = U;
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

void Particle::setForce(vector3D force)
{
    this->force = force;
}


double Particle::getMass()
{
    return mass;
}

double Particle::getU()
{
    return U;
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

vector3D Particle::getForce()
{
    return force;
}

void Particle::update(vector3D force, double delta)
{
    pos += speed * delta + acceleration * delta * delta / 2;
    speed += acceleration * delta;
    //acceleration = force / mass;
    std::cout << pos.getX() << " " << pos.getY() << " " << pos.getZ() << std::endl;
}

void Particle::collideWithWalls(vector3D tank)
{
    if (pos.getX() >= tank.getX())
    {
        vector3D n = vector3D(-1, 0, 0);
        speed = speed - (2 * n * (speed * n));
        pos.setX(tank.getX());
    }
    if (pos.getX() <= 0)
    {
        vector3D n = vector3D(1, 0, 0);
        speed = speed - (2 * n * (speed * n));
        pos.setX(0);
    }
    if (pos.getY() >= tank.getY())
    {
        vector3D n = vector3D(0, -1, 0);
        speed = speed - (2 * n * (speed * n));
        pos.setY(tank.getY());
    }
    if (pos.getY() <= 0)
    {
        vector3D n = vector3D(0, 1, 0);
        speed = speed - (2 * n * (speed * n));
        pos.setY(0);
    }
    if (pos.getZ() >= tank.getZ())
    {
        vector3D n = vector3D(0, 0, -1);
        speed = speed - (2 * n * (speed * n));
        pos.setZ(tank.getZ());
    }
    if (pos.getZ() <= 0)
    {
        vector3D n = vector3D(0, 0, 1);
        speed = speed - (2 * n * (speed * n));
        pos.setZ(0);
    }
}

void Particle::collideWithParticle(Particle& p)
{
    vector3D e = p.getPos() - getPos();
    vector3D temp = 2 * (e * (p.getSpeed() - getSpeed()) * e / ((p.getMass() + getMass()) * e.module() * e.module());
    speed += p.getMass() * temp;
    p.setSpeed(p.getSpeed() - mass * temp);
}

double Particle::particleSpacing(Particle p)
{
    return (getPos() - p.getPos()).module();
}

bool Particle::isNear(Particle p)
{
    return (p.getPos() - pos).module() <= radius;
}
