#include "Gas.h"

Gas::Gas(int N, double molarMass, vector3D tank) {
    this->N = N;
    this->tank = tank;
    this->molarMass = molarMass;
    this->V = tank.getX() * tank.getY() * tank.getZ();
    particles = std::vector<Particle>(N);
    for (auto &particle : particles) {
        particle = Particle(molarMass / Na, 0);
    }
}

Gas::Gas(int N, std::vector<Particle> particles, vector3D tank) {
    this->N = N;
    this->particles = particles;
}

int Gas::getN() {
    return N;
}

double Gas::getTemperature() {
    return T;
}

double Gas::getPressure() {
    return 0;
}

void Gas::update(double delta) {
    //Particle collisions
    for (auto &particle : particles) {
        particle.update(vector3D(0, 0, 0), delta);
        particle.collideWithWalls(tank);
    }
    collide();

    //Computing gas parameters
    double rmsSpeed = 0;  //squared root-mean-square speed
    for (auto &particle : particles) {
        rmsSpeed += particle.getSpeed().length() * particle.getSpeed().length();
    }
    rmsSpeed /= N;
    T = (rmsSpeed * molarMass) / (3 * R);
    P = (N * R * T) / (Na * V);
}

void Gas::collide() {
    for (auto p1 = particles.begin(); p1 < particles.end() - 1; p1++) {
        for (auto p2 = p1 + 1; p2 < particles.end(); p2++) {
            if (p1->isNear(*p2)) {
                //TODO collision between particles
            }
        }
    }
}

