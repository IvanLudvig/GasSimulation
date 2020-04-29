#include "Gas.h"

Gas::Gas(const unsigned long int N, const double molarMass, const vector3D &tank, const double e, const double b,
         int temp)
    : N{N}, molarMass{molarMass}, tank{tank}, e{e}, b{b}, V{tank.getX() * tank.getY() * tank.getZ()}
{
    // Grid for testing
    vector3D grid[N * 3];
    int n = pow(N, 1.0 / 3) + 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                grid[i + (j * n) + (k * n * n)] =
                    vector3D((1.0 * (i + 1) / (n + 1)) * tank.getX(), (1.0 * (j + 1) / (n + 1)) * tank.getY(),
                             (1.0 * (k + 1) / (n + 1)) * tank.getZ());
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        particles.emplace_back(Particle(1, 1, grid[i]));
    }
    setMaxwellDistribution(temp);
    this->tree = Octree(vector3D(0, 0, 0), tank);

    for (int i = 0; i < N; i++)
    {
        tree.add(particles.at(i));
    }

    for (auto &p : particles)
    {
        tree.update(p);
    }

    delta = tree.getDelta();
}

void Gas::update()
{
    tree.~Octree();
    tree = Octree(vector3D(0, 0, 0), tank);
#pragma omp parallel for shared(tree)
    for (int i = 0; i < N; i++)
    {
        tree.add(particles.at(i));
    }
#pragma omp parallel for shared(tree)
    for (auto &p : particles)
    {
        p.setForce(vector3D(0, 0, 0));
        p.setU(0);
        tree.update(p);
        p.updateSpeed(delta);
    }

    // Update particles and compute energy
    delta = tree.getDelta();
    time += delta;
    U = 0;
    E = 0;
    P = 0;

    for (auto &p : particles)
    {
        p.update(delta);
        U += p.getU() / 2;
        E += p.getE();

        P += p.collideWithWalls(tank);
    }
    T = getTemperature();

    P /= delta;
    P /= 6;
    std::cout << T << " delta: " << delta << std::endl;
}

double Gas::distributionDensity(double x)
{
    return (4 * 3.14 * pow((molarMass / (8.31 * 2 * 3.14 * T)), 1.5) * x * x *
            exp(-molarMass * x * x / (2 * 8.31 * T)));
}

double Gas::antiderivativeFunction(double x)
{
    x = x * pow(e * Na / molarMass, 0.5);
    double T0 = this->T * e / k;
    double Out = sqrt(2 / 3.14) * pow(molarMass / (8.31 * T0), 1.5);
    double InLeft = sqrt(3.14 / 2) * pow((8.31 * T0) / molarMass, 1.5) * erf(x * sqrt(molarMass / (8.31 * T0 * 2)));
    double InRight = (8.31 * T0 * x * exp(-(x * x * molarMass / (8.31 * T0 * 2)))) / molarMass;
    return Out * (InLeft - InRight);
}

double Gas::binResearch(std::vector<double> &a, double val)
{
    int l = 0, r = a.size() - 1;

    while (r > l)
    {
        int m = (l + r) / 2;

        if (a[m] < val)
        {
            l = m + 1;
        }
        else if (a[m] > val)
        {
            r = m - 1;
        }
        else
        {
            return m;
        }
    }
    if (a[l] == val)
    {
        return l;
    }
    else
    {
        return -1 * l;
    }
}

void Gas::setMaxwellDistribution(double T)
{
    this->T = T;
    int size = 0;
    std::vector<double> speed(20000);
    for (double i = 0; i < 20000 * pow(molarMass / (Na * e), 0.5); i += pow(molarMass / (Na * e), 0.5))
    {
        speed[i / pow(molarMass / (Na * e), 0.5)] = antiderivativeFunction(i);
        // std::cout << speed[i/pow(molarMass/(Na * e), 0.5)] << std::endl;
    }
    while (size < N)
    {
        double v;
        double derivative = (double)(rand()) / RAND_MAX;
        double number = binResearch(speed, derivative);
        if (number < 0)
        {
            number = -number;
            if (derivative > speed[number])
            {
                v = number + (derivative - speed[number]) / (speed[(number + 1)] - speed[number]);
            }
            else
                v = number - 1 + (derivative - speed[(number - 1)]) / (speed[number] - speed[(number - 1)]);
        }
        else
        {
            v = number;
        }
        v *= pow(molarMass / (Na * e), 0.5);
        // std::cout << v/pow(molarMass/(Na * e), 0.5) << std::endl;
        vector3D vec;
        switch (rand() % 8)
        {
        case 0: {
            vector3D n0(rand(), rand(), rand());
            n0 /= n0.length();
            vec = v * n0;
            break;
        }
        case 1: {
            vector3D n1(-rand(), rand(), rand());
            n1 /= n1.length();
            vec = v * n1;
            break;
        }
        case 2: {
            vector3D n2(rand(), -rand(), rand());
            n2 /= n2.length();
            vec = v * n2;
            break;
        }
        case 3: {
            vector3D n3(rand(), rand(), -rand());
            n3 /= n3.length();
            vec = v * n3;
            break;
        }
        case 4: {
            vector3D n4(-rand(), -rand(), rand());
            n4 /= n4.length();
            vec = v * n4;
            break;
        }
        case 5: {
            vector3D n5(-rand(), rand(), -rand());
            n5 /= n5.length();
            vec = v * n5;
            break;
        }
        case 6: {
            vector3D n6(rand(), -rand(), -rand());
            n6 /= n6.length();
            vec = v * n6;
            break;
        }
        case 7: {
            vector3D n7(-rand(), -rand(), -rand());
            n7 /= n7.length();
            vec = v * n7;
            break;
        }
        }
        // std::cout << vec << "   Length: " << vec.length() << std::endl;
        particles.at(size).setSpeed(vec);
        size++;
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
