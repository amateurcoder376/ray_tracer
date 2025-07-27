#ifndef HITTABLE_H
#define HITTABLE_H

class material;
class hit_record {
  public:
    point3 hit_point;
    vec3 surface_normal;
    double t;
    bool front_face;
    shared_ptr<material> mat;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.

        front_face = r.getDirection().getDotProduct(outward_normal) < 0.0f;
        surface_normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
  public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& input_ray, interval ray_t, hit_record& record) const = 0;
};

#endif