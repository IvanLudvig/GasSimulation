#ifndef GASSIMULATION_OCTREE_H
#define GASSIMULATION_OCTREE_H


#include <vector>
#include <climits>
#include "Particle.h"

class Octree
{
private:
    //8 subtrees, index using (left=4, right=0) + (bottom=2, top=0) + (far=1, near=0)
    Octree *children[8] = {NULL};

    //geometry
    vector3D farBottomLeft;
    vector3D nearTopRight;
    vector3D middle;

    //tree depth
    int level = 0;
    int N = 0;
    //total weight of containing particles
    double weight = 0;
    //weighted mean position
    vector3D meanPos;
    //threshold for interaction
    double maxSpeed = 0;
    double minDist = 0;
    double threshold = 0.5;
    double eps = 1e-6;

protected:
    std::vector<Particle> particles = {};

    bool isNear(const Particle &p) const;

    bool isLeaf() const;

public:
    Octree(vector3D farBottomLeft, vector3D nearTopRight, int maxDepth);

    Octree();

    ~Octree();

    void add(const Particle &p);

    void update(Particle &p, const double &e, const double &b);

    double getDelta() const;

    std::ostream &print(std::ostream &, const std::string &indent) const;

    friend std::ostream &operator<<(std::ostream &out, const Octree &o)
    {
        return o.print(out, {});
    }
};


#endif //GASSIMULATION_OCTREE_H
