#include "Octree.h"
#include <algorithm>

Octree::Octree(vector3D farBottomLeft, vector3D nearTopRight, int maxDepth)
{
    this->farBottomLeft = farBottomLeft;
    this->nearTopRight = nearTopRight;
    middle = 0.5 * farBottomLeft + 0.5 * nearTopRight;
    level = maxDepth;
}

Octree::Octree() = default;

void Octree::add(const Particle &p)
{
    N++;
    meanPos = (((N - 1) * meanPos) + p.getPos()) / N;
    if (level == 0 || (particles.empty() && isLeaf()))
    {
        particles.emplace_back(p);
        return;
    }
    const bool left = p.getPos().getX() < middle.getX();
    const bool down = p.getPos().getY() < middle.getY();
    const bool far = p.getPos().getZ() < middle.getZ();

    auto &child = children[4 * left + 2 * down + far];
    if (child == nullptr)
    {
        vector3D fbl = farBottomLeft;
        vector3D ntr = nearTopRight;
        (left ? ntr : fbl).setX(middle.getX());
        (down ? ntr : fbl).setY(middle.getY());
        (far ? ntr : fbl).setZ(middle.getZ());

        child = new Octree(fbl, ntr, level - 1);
        auto to_move = std::move(particles);
        particles.clear();
        for (auto &o : to_move)
            add(o);
    }
    child->add(p);
}

void Octree::update(Particle &p)
{
    maxSpeed = std::max(maxSpeed, p.getSpeed().length());
    for (auto &child : children)
    {
        if (child == nullptr)
        {
            continue;
        }
        if (child->isLeaf())
        {
            double dist = distance(child->particles.at(0), p);
            if (dist <= eps)
            {
                continue; // same particle
            }
            vector3D r = (p.getPos() - child->particles.at(0).getPos());
            p.addU(4 * (pow(dist, -12) - pow(dist, -6)));
            p.addForce(48 * (pow(dist, -14) - (0.5 * pow(dist, -8))) * r);
            minDist = minDist == 0 ? dist : std::min(minDist, dist);
            //std::cout<<minDist<<" "<<dist<<std::endl;
        }
        else if (child->isNear(p))
        {
            child->update(p);
            minDist = minDist == 0 ? child->minDist : std::min(minDist, child->minDist);
        }
        else
        {
            double dist = distance(p.getPos(), child->meanPos);
            vector3D r = (p.getPos() - child->meanPos);
            p.addU(child->N * 4 * (pow(dist, -12) - pow(dist, -6)));
            p.addForce(child->N * 48 * (pow(dist, -14) - (0.5 * pow(dist, -8))) * r);
        }
    }
}

std::ostream &operator<<(std::ostream &os, Particle &p)
{
    return os << p.getPos();
}

std::ostream &Octree::print(std::ostream &os, const std::string &indent) const
{
    os << indent << "Octree " << farBottomLeft << " to " << nearTopRight << '\n';
    if (!os)
    {
        return os;
    }
    for (Particle e : particles)
    {
        os << indent << "- " << e.getPos() << '\n';
    }
    if (!os)
    {
        return os;
    }
    for (auto i = 0u; i < 8; ++i)
    {
        if (children[i])
        {
            os << indent << (i & 1 ? "far" : "near") << ' ' << (i & 2 ? "bottom" : "top") << ' '
               << (i & 4 ? "left" : "right") << ": \n";
            children[i]->print(os, indent + "  ");
            if (!os)
            {
                return os;
            }
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

double Octree::getDelta() const
{
    double delta = (maxSpeed <= eps) ? 0.1 : minDist / (100 * maxSpeed);
    return delta;
}
