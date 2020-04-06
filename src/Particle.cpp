#include "../include/Particle.h"

Particle::Particle(const double mass, const double radius, const vector3D &pos, const vector3D &speed,
                   const vector3D &acceleration)
    : mass{mass}, radius{radius}, pos{pos}, speed{speed}, acceleration{acceleration}
{
}

void Particle::update(const double delta)
{
    // 1 iteration back
    E = speed * speed / 2;
    pos += (speed * delta) + (acceleration * delta * delta / 2);
    prevAccel = acceleration;
    i++;
    if (i == 10)
    {
        //std::cout << pos.getX() << " " << pos.getY() << " " << pos.getZ() << std::endl;
        i = 0;
    }
}

void Particle::updateSpeed(const double delta)
{
    speed += (prevAccel + acceleration) * delta / 2;
}

double Particle::collideWithWalls(const vector3D &tank)
{
    double ParticlePressure = 0;
    if (pos.getX() >= tank.getX())
    {
        vector3D n = vector3D(-1, 0, 0);
        ParticlePressure += 2 * mass * abs((speed * n) / (tank.getY() * tank.getZ()));
        speed = speed - (2 * n * (speed * n));
        pos.setX(tank.getX());
    }
    if (pos.getX() <= 0)
    {
        vector3D n = vector3D(1, 0, 0);
        ParticlePressure += 2 * mass * abs((speed * n) / (tank.getY() * tank.getZ()));
        speed = speed - (2 * n * (speed * n));
        pos.setX(0);
    }
    if (pos.getY() >= tank.getY())
    {
        vector3D n = vector3D(0, -1, 0);
        ParticlePressure += 2 * mass * abs((speed * n) / (tank.getX() * tank.getZ()));
        speed = speed - (2 * n * (speed * n));
        pos.setY(tank.getY());
    }
    if (pos.getY() <= 0)
    {
        vector3D n = vector3D(0, 1, 0);
        ParticlePressure += 2 * mass * abs((speed * n) / (tank.getX() * tank.getZ()));
        speed = speed - (2 * n * (speed * n));
        pos.setY(0);
    }
    if (pos.getZ() >= tank.getZ())
    {
        vector3D n = vector3D(0, 0, -1);
        ParticlePressure += 2 * mass * abs((speed * n) / (tank.getY() * tank.getX()));
        speed = speed - (2 * n * (speed * n));
        pos.setZ(tank.getZ());
    }
    if (pos.getZ() <= 0)
    {
        vector3D n = vector3D(0, 0, 1);
        ParticlePressure += 2 * mass * abs((speed * n) / (tank.getY() * tank.getX()));
        speed = speed - (2 * n * (speed * n));
        pos.setZ(0);
    }
    return ParticlePressure;
}

void Particle::collideWithParticle(Particle &p)
{
    vector3D e = p.getPos() - pos;
    vector3D temp = (e * (p.getSpeed() - speed) * e / ((p.getMass() + mass) * e.length() * e.length())) * 2;
    speed += p.getMass() * temp;
    p.setSpeed(p.getSpeed() - mass * temp);
}

void Particle::setMass(const double mass)
{
    this->mass = mass;
}

void Particle::setU(const double U)
{
    this->U = U;
}

void Particle::setPos(const vector3D &pos)
{
    this->pos = pos;
}

void Particle::setSpeed(const vector3D &speed)
{
    this->speed = speed;
}

void Particle::setAcceleration(const vector3D &acceleration)
{
    this->acceleration = acceleration;
}

void Particle::setForce(vector3D force)
{
    this->acceleration = force / mass;
}

void Particle::addForce(vector3D force)
{
    this->acceleration += force / mass;
}

double Particle::getU() const
{
    return U;
}

void Particle::addU(double U)
{
    this->U += U;
}

double Particle::getE() const
{
    return E;
}

double Particle::getMass()
{
    return mass;
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
    return mass * acceleration;
}

bool Particle::isNear(const Particle &p)
{
    return (p.getPos() - pos).length() <= radius;
}

double distance(const Particle &p1, const Particle &p2)
{
    return distance(p1.getPos(), p2.getPos());
}