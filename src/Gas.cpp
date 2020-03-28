#include "Gas.h"
#include "vector3D.h"

Gas::Gas(const unsigned long int N, const double molarMass, const vector3D &tank, const double e, const double b)
        : N{N}, molarMass{molarMass}, tank{tank}, e{e}, b{b}, V{tank.getX() * tank.getY() * tank.getZ()}
{
    // Grid for testing
    vector3D grid[1000];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                grid[i + (j * 5) + (k * 25)] =
                        vector3D((1.0 * (i + 1) / 5) * tank.getX(), (1.0 * (j + 1) / 5) * tank.getY(),
                                 (1.0 * (k + 1) / 5) * tank.getZ());
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        particles.emplace_back(Particle(1, 0, grid[i]));
    }
    setMaxwellDistribution(300);
    this->tree = Octree(vector3D(0, 0, 0), tank);
    for (int i = 0; i < N; i++)
    {
        std::cout << particles.at(i).getSpeed() << std::endl;
        tree.add(particles.at(i));
    }
    for (auto &p : particles)
    {
        tree.update(p);
    }
}

void Gas::update()
{
    // Rebuild tree
    tree.~Octree();
    tree = Octree(vector3D(0, 0, 0), tank);
    for (int i = 0; i < N; i++)
    {
        tree.add(particles.at(i));
    }
    for (auto &p : particles)
    {
        p.setForce(vector3D(0, 0, 0));
        p.setU(0);
        tree.update(p);
    }

    // Update particles and compute energy
    double delta = tree.getDelta();
    U = 0;
    E = 0;
    for (auto &p : particles)
    {
        p.update(delta);
        U += p.getU() / 2; // approximation
        E += p.getE();
        p.collideWithWalls(tank);
    }
    // std::cout<<TotalSystemEnergy()<<" "<<U+E<<std::endl;
}

long double Gas::distributionDensity(double x)
{
    return (4 * 3.14 * pow((molarMass / (8.31 * 2 * 3.14 * T)), 1.5) * x * x *
            exp(-molarMass * x * x / (2 * 8.31 * T)));
}

void Gas::setMaxwellDistribution(double T)
{
    this->T = T;
    bool stright = true;
    double v = sqrt(2 * R * T / molarMass);
    std::cout << v << " Sasha" << std::endl;
    double vN = v;
    int size = 0;
    int i = 0;
    long double Integral;
    double l;
    if (N < 700)
        l = N * 0.035;
    else if (N >= 700)
        l = 10000. / N;
    double step = l;
    double h = 0.1;
    double n;
    while (size < N)
    {
        int forC = size;
        double a = v - 10;

        double c = a + step;
        n = (c - a) * 1. / h;
        Integral = h * (distributionDensity(a) + distributionDensity(c)) / 6.0;
        for (i = 1; i <= n; i++)
            Integral = Integral + 4.0 / 6.0 * h * distributionDensity(a + h * (i - 0.5));
        for (i = 1; i <= n - 1; i++)
            Integral = Integral + 2.0 / 6.0 * h * distributionDensity(a + h * i);

        for (int k = forC; k < forC + int(Integral * N); k++)
        {
            vector3D vec;
            switch ((int) v % 3)
            {
                case 0:
                    vec = vector3D(v, 0, 0);
                    break;
                case 1:
                    vec = vector3D(0, v, 0);
                    break;
                case 2:
                    vec = vector3D(0, 0, v);
                    break;
            }
            particles.at(k).setSpeed(vec);
            size++;
            if (size >= N - 1)
                break;
        }
        l += step;
        if (stright)
        {
            v += l;
            stright = false;
        } else
        {
            v -= l;
            stright = true;
        }
        if (v <= 0)
            v = vN;
    }
}

// Potential energy of the interaction of two molecules:
double Gas::PotentialEnergy(const double r) // r - distance between molecules
{
    double temp = pow(b / r, 6);
    return 4 * e * (temp * temp - temp);
}

// Strength of the interaction of two molecules:
double Gas::F(const double r) // r - distance between molecules
{
    double temp = pow(b / r, 6);
    return 24 * e * (2 * temp * temp - temp) / r;
}

// this function calculates energy of interaction of each molecule with each.
// O(N^2)
double Gas::TotalSystemEnergy()
{
    double sum = 0;
    for (unsigned long int i = 0; i < N; ++i)
    {
        sum += particles[i].getMass() * (particles[i].getSpeed() * particles[i].getSpeed()) / 2;
        for (unsigned long int j = i + 1; j < N; j++)
        {
            sum += PotentialEnergy((particles[i].getPos() - particles[j].getPos()).length());
        }
    }
    return sum;
}

int Gas::getN() const
{
    return N;
}

double Gas::getEnergy() const
{
    return U + E;
}

double Gas::getTemperature() const
{
    return 2 * E / (3 * N);
}

double Gas::getPressure() const
{
    return 2 * E / (3 * V);
}