#ifndef GASSIMULATION_VECTOR3D_H
#define GASSIMULATION_VECTOR3D_H

#include <cmath>
#include <iostream>

class vector3D
{

  private:
    double x;
    double y;
    double z;

  public:
    vector3D();

    vector3D(double x, double y, double z);

    void setX(double x);

    void setY(double y);

    void setZ(double z);

    double getX() const;

    double getY() const;

    double getZ() const;

    vector3D operator+(const vector3D &b);

    vector3D operator-(const vector3D &b) const;

    vector3D operator*(const double &b);

    vector3D operator/(const double &b);

    double operator*(const vector3D &b);   // scalar multiplication: *
    vector3D operator^(const vector3D &b); // vector multiplication: ^

    bool operator==(const vector3D &b);

    bool operator!=(const vector3D &b);

    vector3D operator+=(const vector3D &b);

    vector3D operator-=(const vector3D &b);

    vector3D operator*=(const double &b);

    vector3D operator/=(const double &b);

    double length();      // vector's length
    vector3D norm();      // this function doesn't change vector
    vector3D normalize(); // this function change vector
};

double distance(const vector3D &v1, const vector3D &v2);

vector3D operator*(const double &b, const vector3D &a);

std::ostream &operator<<(std::ostream &out, const vector3D a);
// use () to display vector product of a, b
// example: cout << (a^b);

#endif // GASSIMULATION_VECTOR3D_H
