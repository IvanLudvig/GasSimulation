#include "../include/vector3D.h"

vector3D::vector3D() : x{0}, y{0}, z{0}
{
}

vector3D::vector3D(double x, double y, double z) : x{x}, y{y}, z{z}
{
}

void vector3D::setX(double x)
{
    this->x = x;
}

void vector3D::setY(double y)
{
    this->y = y;
}

void vector3D::setZ(double z)
{
    this->z = z;
}

double vector3D::getX()
{
    return x;
}

double vector3D::getY()
{
    return y;
}

double vector3D::getZ()
{
    return z;
}

vector3D vector3D::operator+(const vector3D &b)
{
    vector3D result = {x + b.x, y + b.y, z + b.z};
    return result;
}

vector3D vector3D::operator-(const vector3D &b)
{
    vector3D result = {x - b.x, y - b.y, z - b.z};
    return result;
}

vector3D vector3D::operator*(const double &b)
{
    vector3D result = {x * b, y * b, z * b};
    return result;
}

vector3D vector3D::operator/(const double &b)
{
    vector3D result = {x / b, y / b, z / b};
    return result;
}

//scalar multiplication: *
double vector3D::operator*(const vector3D &b)
{
    double result = x * b.x + y * b.y + z * b.z;
    return result;
}

//vector multiplication: ^
vector3D vector3D::operator^(const vector3D &b)
{
    vector3D result = {y * b.z - b.y * z, z * b.x - b.z * x, x * b.y - y * b.x};
    return result;
}

bool vector3D::operator==(const vector3D &b)
{
    if (x == b.x && y == b.y && z == b.z)
        return true;
    else
        return false;
}

bool vector3D::operator!=(const vector3D &b)
{
    if (x == b.x && y == b.y && z == b.z)
        return false;
    else
        return true;
}

vector3D vector3D::operator+=(const vector3D &b)
{
    x += b.x;
    y += b.y;
    z += b.z;
    return *this;
}

vector3D vector3D::operator-=(const vector3D &b)
{
    x -= b.x;
    y -= b.y;
    z -= b.z;
    return *this;
}

vector3D vector3D::operator*=(const double &b)
{
    x *= b;
    y *= b;
    z *= b;
    return *this;
}

vector3D vector3D::operator/=(const double &b)
{
    x /= b;
    y /= b;
    z /= b;
    return *this;
}

// vector's length:
double vector3D::module()
{
    return sqrt(x * x + y * y + z * z);
}

vector3D operator*(const double &b, vector3D &a)
{
    vector3D result = {a.getX() * b, a.getY() * b, a.getZ() * b};
    return result;
}

std::ostream &operator<<(std::ostream &out, vector3D a)
{
    out << "(" << a.getX() << ", " << a.getY() << ", " << a.getZ() << ")";
    return out;
}
//use () to display vector product of a, b
//example: cout << (a^b);
