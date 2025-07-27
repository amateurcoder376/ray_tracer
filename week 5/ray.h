#ifndef RAY_H
#define RAY_H

#include "vec3.h"


class ray {
public:
    
    ray() {}
    
    
    ray(const point3& origin_point, const vec3& direction_vector) {
        ray_start_point = origin_point;
        ray_direction = direction_vector;
    }
    
    
    const point3& getOrigin() const {
        return ray_start_point;
    }
    
    
    const vec3& getDirection() const {
        return ray_direction;
    }
    
    
    point3 getPointAtDistance(double distance_along_ray) const {
        return ray_start_point + distance_along_ray * ray_direction;
    }

private:
    
    point3 ray_start_point;
    
    
    vec3 ray_direction;
};

#endif