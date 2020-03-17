#ifndef GASSIMULATION_OCTREE_H
#define GASSIMULATION_OCTREE_H


#include <vector>
#include "Particle.h"

class Octree
{
private:
    //8 subtrees, index using (left=4, right=0) + (bottom=2, top=0) + (far=1, near=0)
    Octree* children[8] = {NULL};
    std::vector<Particle> particles = {};

    //geometry
    vector3D farBottomLeft;
    vector3D nearTopRight;
    vector3D middle;

    //tree depth
    int level = 0;
    //total weight of containing particles
    float weight = 0;
    //weighted mean position
    vector3D meanPos;
    bool isLeaf() const;
public:
    Octree(vector3D farBottomLeft, vector3D nearTopRight, int maxDepth);

    Octree();


    void add(Particle p);
    std::ostream& print(std::ostream&, const std::string& indent) const;

    friend std::ostream& operator<<(std::ostream& out, const Octree& o) {
        return o.print(out, {});
    }
};


#endif //GASSIMULATION_OCTREE_H
