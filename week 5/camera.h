#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include "hittable.h"
#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"
#include "constants.h"
#include "material.h"

class camera {
  public:
    double aspect_ratio         = 1.0;  // Ratio of image width over height
    int    image_width          = 100;  // Rendered image width in pixel count
    int    samples_per_pixel    = 10;
    int    max_depth         = 10;   // Number of samples per pixel for anti-aliasing

    void render(const hittable& world) {
        initialize();

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                color pixel_color(0,0,0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_camera_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }
                write_color(std::cout, pixel_sample_scale * pixel_color);
            }
        }

        std::clog << "\rDone.                 \n";
    }

  private:
    int    image_height;              // Rendered image height
    double pixel_sample_scale;        // Scale factor for averaging pixel samples
    point3 camera_center;             // Camera center
    point3 pixel00_location;          // Location of pixel 0, 0
    vec3   pixel_delta_u;             // Offset to pixel to the right
    vec3   pixel_delta_v;             // Offset to pixel below

    void initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_sample_scale = 1.0 / samples_per_pixel;

        camera_center = point3(0, 0, 0);

        // Determine viewport dimensions.
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(image_width)/image_height);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left =
            camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        pixel00_location = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    ray get_camera_ray(int pixel_x, int pixel_y) const {
        // Construct a camera ray originating from the camera center and directed at a randomly sampled
        // point within the pixel (pixel_x, pixel_y).
        auto offset = random_subpixel_offset();
        auto pixel_sample = pixel00_location
                          + ((pixel_x + offset[0]) * pixel_delta_u)
                          + ((pixel_y + offset[1]) * pixel_delta_v);
        auto ray_origin = camera_center;
        auto ray_direction = pixel_sample - ray_origin;
        return ray(ray_origin, ray_direction);
    }

    vec3 random_subpixel_offset() const {
        // Returns a random offset in the [-.5,-.5]-[+.5,+.5] unit square for subpixel sampling.
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    color ray_color(const ray& r, int depth, const hittable& world) const {
        // If we've exceeded the ray bounce limit, no more light is gathered.
        if (depth <= 0)
            return color(0,0,0);
        hit_record rec;
        if (world.hit(r, interval(0.001, infinity), rec)) {
            ray scattered;
            color attenuation;
            if (rec.mat->scatter(r, rec, attenuation, scattered))
                return attenuation * ray_color(scattered, depth-1, world);
            return color(0,0,0);    
        }
        vec3 unit_direction = r.getDirection().getUnitVector();
        auto a = 0.5f * (unit_direction[1] + 1.0f);
        return (1.0f - a) * color(1.0f, 1.0f, 1.0f) + a * color(0.5f, 0.7f, 1.0f);
    }
};

#endif 