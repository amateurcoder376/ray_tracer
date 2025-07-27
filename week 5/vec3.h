
#include <stdexcept>
#ifndef VEC3_H
#define VEC3_H
using namespace std;

class vec3 {
private:
    float x_coord;
    float y_coord;
    float z_coord;

public:
    vec3(float x = 0, float y = 0, float z = 0) {
        x_coord = x;
        y_coord = y;
        z_coord = z;
    }

    vec3 operator+(const vec3& other) const {
        return vec3(x_coord + other.x_coord, y_coord + other.y_coord, z_coord + other.z_coord);
    }

    vec3 operator-(const vec3& other) const {
        return vec3(x_coord - other.x_coord, y_coord - other.y_coord, z_coord - other.z_coord);
    }

    vec3 operator*(float scalar) const {
        return vec3(scalar * x_coord, scalar * y_coord, scalar * z_coord);
    }

    vec3 operator/(float scalar) const {
        if (scalar != 0) {
            return vec3(x_coord / scalar, y_coord / scalar, z_coord / scalar);
        }
        else {
            throw std::runtime_error("Division by zero");
        }
    }

    vec3 operator*(const vec3& other) const {
        return vec3(x_coord * other.x_coord, y_coord * other.y_coord, z_coord * other.z_coord);
    }

    vec3 operator-() const {
        return vec3(-x_coord, -y_coord, -z_coord);
    }

    vec3& operator+=(const vec3& other) {
        x_coord += other.x_coord;
        y_coord += other.y_coord;
        z_coord += other.z_coord;
        return *this;
    }

    float& operator[](int index) {
        if (index == 0) return x_coord;
        if (index == 1) return y_coord;
        if (index == 2) return z_coord;
        throw std::out_of_range("Index out of range");
    }

    float operator[](int index) const {
        if (index == 0) return x_coord;
        if (index == 1) return y_coord;
        if (index == 2) return z_coord;
        throw std::out_of_range("Index out of range");
    }

    float getLength() const {
        return sqrt(x_coord * x_coord + y_coord * y_coord + z_coord * z_coord);
    }
    static vec3 random() {
        return vec3(random_double(), random_double(), random_double());
    }

    static vec3 random(double min, double max) {
        return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
    }

    vec3 getUnitVector() const {
        float length = getLength();
        if (length != 0) {
            return *this / length;
        }
        else {
            throw std::runtime_error("Vector has zero length");
        }
    }

    float getDotProduct(const vec3& other) const {
        return x_coord * other.x_coord + y_coord * other.y_coord + z_coord * other.z_coord;
    }

    vec3 getCrossProduct(const vec3& other) const {
        // Standard cross product
        return vec3((y_coord * other.z_coord) - (z_coord * other.y_coord),
                    (z_coord * other.x_coord) - (x_coord * other.z_coord),
                    (x_coord * other.y_coord) - (y_coord * other.x_coord));
    }

    vec3 getReflection(const vec3& normal) const {
        // Reflect this vector about a normal
        vec3 unit_normal = normal.getUnitVector();
        float dot_product = 2 * getDotProduct(unit_normal);
        return *this - unit_normal * dot_product;
    }

    void print() const {
        cout << x_coord << " " << y_coord << " " << z_coord << endl;
    }

    float length_squared() const {
        return x_coord * x_coord + y_coord * y_coord + z_coord * z_coord;
    }
    bool near_zero() const {
        // Useful for avoiding floating point noise
        auto s = 1e-8;
        return (std::fabs(x_coord) < s) && (std::fabs(y_coord) < s) && (std::fabs(z_coord) < s);
    }
    
};

using point3 = vec3;

// Scalar * vector multiplication
inline vec3 operator*(float t, const vec3& v) {
    return v * t;
}

inline float dot(const vec3& u, const vec3& v) {
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

// Snell's law for refraction
inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = std::fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

inline vec3 random_unit_vector() {
    // Uniformly random unit vector
    while (true) {
        auto p = vec3::random(-1,1);
        auto lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1)
            return p / sqrt(lensq);
    }
}

inline vec3 random_on_hemisphere(const vec3& normal) {
    // Random unit vector in same hemisphere as normal
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0)
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}
#endif