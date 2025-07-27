#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"
#include "vec3.h"

class material {
  public:
    virtual ~material() = default;
    // Returns true if the ray is scattered, false for absorption
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const {
        return false;
    }
};

class lambertian : public material {
    public:
      lambertian(const color& albedo) : albedo(albedo) {}
      bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
      const override {
          auto scatter_direction = rec.surface_normal + random_unit_vector();
          if (scatter_direction.near_zero())
            scatter_direction = rec.surface_normal; // catch degenerate case
          scattered = ray(rec.hit_point, scatter_direction);
          attenuation = albedo;
          return true;
      }
    private:
      color albedo;
};

class metal : public material {
    public:
      metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}
      bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
      const override {
          vec3 reflected = r_in.getDirection().getReflection(rec.surface_normal);
          // fuzz controls blur of reflection
          scattered = ray(rec.hit_point, reflected + fuzz * random_unit_vector());
          attenuation = albedo;
          return (scattered.getDirection().getDotProduct(rec.surface_normal) > 0);
      }
    private:
      color albedo;
      double fuzz;
};

class dielectric : public material {
  public:
    dielectric(double refraction_index) : refraction_index(refraction_index) {}
    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
    const override {
        attenuation = color(1.0, 1.0, 1.0); // glass absorbs nothing
        double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;

        vec3 unit_direction = r_in.getDirection().getUnitVector();
        double cos_theta = std::fmin(dot(-unit_direction, rec.surface_normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

        bool cannot_refract = ri * sin_theta > 1.0;
        vec3 direction;
        // Schlick's approximation for reflectance
        if (cannot_refract || reflectance(cos_theta, ri) > random_double()) {
            direction = unit_direction.getReflection(rec.surface_normal);
        } else {
            direction = refract(unit_direction, rec.surface_normal, ri);
        }
        scattered = ray(rec.hit_point, direction);
        return true;
    }
  private:
    double refraction_index;
    static double reflectance(double cosine, double ref_idx) {
        // Approximate reflectance for dielectrics
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }
};
#endif