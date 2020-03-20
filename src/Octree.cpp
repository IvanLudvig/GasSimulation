#include <algorithm>
#include "Octree.h"

Octree::Octree(vector3D farBottomLeft, vector3D nearTopRight, int maxDepth)
{
    this->farBottomLeft = farBottomLeft;
    this->nearTopRight = nearTopRight;
    middle = 0.5 * farBottomLeft + 0.5 * nearTopRight;
    level = maxDepth;
}

Octree::Octree()
{}

void Octree::add(const Particle &p)
{
    N++;
    if (level == 0 || (particles.empty() && isLeaf()))
    {
        particles.push_back(p);
        return;
    }
    const bool left = p.getPos().getX() < middle.getX();
    const bool down = p.getPos().getY() < middle.getY();
    const bool far = p.getPos().getZ() < middle.getZ();

    auto &child = children[4 * left + 2 * down + far];
    if (child == NULL)
    {
        vector3D fbl = farBottomLeft;
        vector3D ntr = nearTopRight;
        (left ? ntr : fbl).setX(middle.getX());
        (down ? ntr : fbl).setY(middle.getY());
        (far ? ntr : fbl).setZ(middle.getZ());

        child = new Octree(fbl, ntr, level - 1);
        auto to_move = std::move(particles);
        particles.clear();
        for (auto &o: to_move)
            add(o);
    }
    child->add(p);
}

void Octree::update(Particle &p, const double &e, const double &b)
{
    double U = 0;
    vector3D force;
    for (int i = 0; i < 8; i++)
    {
        if(children[i]==NULL){
            continue;
        }
        if (children[i]->isLeaf())
        {
            double dist = distance(p, children[i]->particles.at(0));
            vector3D n = (children[i]->particles.at(0).getPos() - p.getPos()) / dist;
            U += 4 * e * (pow(b / dist, 12) - pow(b / dist, 6));
            force -= U * n / dist;
        } else if (children[i]->isNear(p))
        {
            children[i]->update(p, e, b);
        } else
        {
            double dist = distance(children[i]->meanPos, p.getPos());
            vector3D n = (children[i]->meanPos - p.getPos()) / dist;
            U += children[i]->N * 4 * e * (pow(b / dist, 12) -
                          pow(b / dist, 6));
            force -= children[i]->N * U * n / dist;
        }
    }
    p.setU(U);
    p.setForce(force);
}

std::ostream &operator<<(std::ostream &os, Particle &p)
{
    return os << p.getPos();
}

std::ostream &Octree::print(std::ostream &os, const std::string &indent) const
{
    os << indent
       << "Octree " << farBottomLeft
       << " to " << nearTopRight << '\n';
    if (!os)
    { return os; }
    for (Particle e: particles)
    {
        os << indent << "- " << e.getPos() << '\n';
    }
    if (!os)
    { return os; }
    for (auto i = 0u; i < 8; ++i)
    {
        if (children[i])
        {
            os << indent
               << (i & 1 ? "far" : "near") << ' '
               << (i & 2 ? "bottom" : "top") << ' '
               << (i & 4 ? "left" : "right") << ": \n";
            children[i]->print(os, indent + "  ");
            if (!os)
            { return os; }
        }
    }
    return os;
}

bool Octree::isLeaf() const
{
    /*
    for (int i = 0; i < 8; i++)
    {
        if (children[i] != NULL)
        {
            return false;
        }
    }*/
    return N == 1;
}


Octree::~Octree()
{
    for (int i = 0; i < 8; i++)
    {
        delete children[i];
    }
}

bool Octree::isNear(const Particle &p) const
{
    return distance(farBottomLeft, nearTopRight) / distance(p.getPos(), meanPos) > threshold;
}

