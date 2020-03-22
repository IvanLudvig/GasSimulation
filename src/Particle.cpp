#include "../include/Particle.h"


Particle::Particle(const double &mass, const double &radius, const vector3D &pos, const vector3D &speed,
                   const vector3D &acceleration, const vector3D &force)
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

void Particle::addForce(vector3D force)
{
    //std::cout<<"Asd "<<force<<std::endl;
    this->force += force;
}

double Particle::getMass()
{
    return mass;
}

double Particle::getU()
{
    return U;
}


vector3D Particle::getPos() const
{
    return pos;
}

vector3D Particle::getSpeed() const
{
    return speed;
}

vector3D Particle::getAcceleration() const
{
    return acceleration;
}

vector3D Particle::getForce() const
{
    return force;
}

void Particle::update(double delta)
{
    pos += speed * delta + acceleration * delta * delta / 2;
    speed += acceleration * delta;
    acceleration = force / mass;
    std::cout << pos.getX()<<" "<<pos.getY()<< " "<<pos.getZ() << std::endl;
    //std::cout<<acceleration<<std::endl;
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

void Particle::collideWithParticle(Particle &p)
{
    vector3D e = p.getPos() - pos;
    vector3D temp = (e * (p.getSpeed() - speed) * e / ((p.getMass() + mass) * e.length() * e.length()))*2;
    speed += p.getMass() * temp;
    p.setSpeed(p.getSpeed() - mass * temp);
}

bool Particle::isNear(Particle p)
{
    return (p.getPos() - pos).length() <= radius;
}

double distance(const Particle &p1, const Particle &p2)
{
    return distance(p1.getPos(), p2.getPos());
}
