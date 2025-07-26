#ifndef RAY_H
#define RAY_H

#include "vec3.h"

using point3 = Vec3;

class ray{
    private :
        point3 orig;
        Vec3 dir;
    
    public:
    ray() {}

    ray(const point3& origin, const Vec3& direction) : orig(origin), dir(direction) {}

    const point3& origin() const  { return orig; }
    const 
    Vec3& direction() const { return dir; }

    point3 at(double t) const {
        return orig + dir*t;
    }
        
};


#endif