#include <iostream>
#include <cmath>

class vector3D
{
private:
    double x;
    double y;
    double z;

public:
    vector3D()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    vector3D(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void set_x(double x)
    {
        this->x = x;
    }

    void set_y(double y)
    {
        this->y = y;
    }

    void set_z(double z)
    {
        this->z = z;
    }

    double get_x()
    {
        return x;
    }

    double get_y()
    {
        return y;
    }

    double get_z()
    {
        return z;
    }

    vector3D operator+(const vector3D& b)
    {
        vector3D result = {x + b.x, y + b.y, z + b.z};
        return result;
    }

    vector3D operator-(const vector3D& b)
    {
        vector3D result = {x - b.x, y - b.y, z - b.z};
        return result;
    }

    vector3D operator*(const double& b)
    {
        vector3D result = {x * b, y * b, z * b};
        return result;
    }

    vector3D operator/(const double& b)
    {
        vector3D result = {x / b, y / b, z / b};
        return result;
    }

    //scalar multiplication: *
    double operator*(const vector3D& b)
    {
        double result = x * b.x + y * b.y + z * b.z;
        return result;
    }

    //vector multiplication: ^
    vector3D operator^(const vector3D& b)
    {
        vector3D result = {y * b.z - b.y * z, z * b.x - b.z * x, x * b.y - y * b.x};
        return result;
    }

    bool operator==(const vector3D& b)
    {
        if(x == b.x && y == b.y && z == b.z)
            return true;
        else
            return false;
    }

    bool operator!=(const vector3D& b)
    {
        if(x == b.x && y == b.y && z == b.z)
            return false;
        else
            return true;
    }

    vector3D operator+= (const vector3D &b)
    {
        x += b.x;
        y += b.y;
        z += b.z;
        return *this;
    }

    vector3D operator-= (const vector3D &b)
    {
        x -= b.x;
        y -= b.y;
        z -= b.z;
        return *this;
    }

    vector3D operator*= (const double &b)
    {
        x *= b;
        y *= b;
        z *= b;
        return *this;
    }

    vector3D operator/= (const double &b)
    {
        x /= b;
        y /= b;
        z /= b;
        return *this;
    }

    // vector's length:
    double length()
    {
        return sqrt(x * x + y * y + z * z);
    }
};

vector3D operator*(const double& b, vector3D& a)
{
    vector3D result = {a.get_x() * b, a.get_y() * b, a.get_z() * b};
    return result;
}

std::ostream& operator<<(std::ostream& out, vector3D a)
{
    out << "("<<a.get_x()<<", "<<a.get_y()<<", "<<a.get_z()<<")";
    return out;
}
//use () to display vector product of a, b
//example: cout << (a^b);
