#ifndef GASSIMULATION_VECTOR3D_H
#define GASSIMULATION_VECTOR3D_H

#include <iostream>
#include <cmath>

class vector3D
{
    
private:
    double x;
    double y;
    double z;

public:
    vector3D();
    vector3D(double x, double y, double z);
        
    void setX (double x);
    void setY(double y);
    void setZ(double z);
        
    double getX();
    double getY();
    double getZ();

    vector3D operator+(const vector3D& b);
    vector3D operator-(const vector3D& b);
    vector3D operator*(const double& b);
    vector3D operator/(const double& b);
        
    double operator*(const vector3D& b); //scalar multiplication: *
    vector3D operator^(const vector3D& b); //vector multiplication: ^
        
    bool operator==(const vector3D& b);
    bool operator!=(const vector3D& b);

    vector3D operator+= (const vector3D &b);
    vector3D operator-= (const vector3D &b);
    vector3D operator*= (const double &b);
    vector3D operator/= (const double &b);

    double module();
};

vector3D operator*(const double& b, vector3D& a);

std::ostream& operator<<(std::ostream& out, vector3D a);
//use () to display vector product of a, b
//example: cout << (a^b);

#endif //GASSIMULATION_VECTOR3D_H
