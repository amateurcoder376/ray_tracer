#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
  public:
  sphere(const point3& center, double radius, shared_ptr<material> mat): center(center), radius(std::fmax(0,radius)), mat(mat) {}

    bool hit(const ray& input_ray, interval ray_t, hit_record& record) const override {
        vec3 oc = center - input_ray.getOrigin();
        auto a = input_ray.getDirection().getDotProduct(input_ray.getDirection());
        auto h = input_ray.getDirection().getDotProduct(oc);
        auto c = oc.getDotProduct(oc) - radius * radius;

        auto discriminant = h * h - a * c;
        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrtd) / a;
        if (!ray_t.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root))
                return false;
        }

        record.t = root;
        record.hit_point = input_ray.getPointAtDistance(record.t);
        vec3 outward_normal = (record.hit_point - center) / radius;
        record.set_face_normal(input_ray, outward_normal); // orient normal
        record.mat = mat; 

        return true;
    }
  private:
    point3 center;
    double radius;
    shared_ptr<material> mat;
};

#endif