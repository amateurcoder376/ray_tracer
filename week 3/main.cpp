#include "constants.h"
#include "hittable_list.h"
#include "sphere.h"


using namespace std;



color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, interval(0, infinity), rec)) {
        return (rec.normal + color(1.0f, 1.0f, 1.0f))*0.5f;
    }

    Vec3 unit_direction = (r.direction()).unit();
    auto a = 0.5f * (unit_direction[1] + 1.0f);
    return color(1.0f, 1.0f, 1.0f) * (1.0f - a) + color(0.5f, 0.7f, 1.0f) * a;
}

int main() {
    // Image settings
    double aspect_ratio = 16.0f / 9.0f;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // World

    hittable_list world;

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    // Camera settings
    double focal_length = 1.0f;
    double viewport_height = 2.0f;
    double viewport_width = viewport_height * (float(image_width) / float(image_height));
    point3 camera_center = point3(0.0f, 0.0f, 0.0f);

    // Calculate the vectors across the horizontal and down the vertical viewport edges
    Vec3 viewport_horizontal = Vec3((float)viewport_width, 0.0f, 0.0f);
    Vec3 viewport_vertical = Vec3(0.0f, -((float)viewport_height), 0.0f);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel
    Vec3 pixel_delta_horizontal = viewport_horizontal / float(image_width);
    Vec3 pixel_delta_vertical = viewport_vertical / float(image_height);

    // Calculate the location of the upper left pixel
    point3 viewport_upper_left = camera_center
                               - Vec3(0.0f, 0.0f, (float)focal_length) 
                               - viewport_horizontal / 2.0f 
                               - viewport_vertical / 2.0f;
    point3 pixel00_location = viewport_upper_left + (pixel_delta_horizontal + pixel_delta_vertical) * 0.5f;

    // Render image
    cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int row = 0; row < image_height; row++) {
        clog << "\rScanlines remaining: " << (image_height - row) << ' ' << flush;
        
        for (int column = 0; column < image_width; column++) {
            point3 pixel_center = pixel00_location + pixel_delta_horizontal * float(column) + pixel_delta_vertical * float(row);
            Vec3 ray_direction = pixel_center - camera_center;
            ray current_ray(camera_center, ray_direction);

            color pixel_color = ray_color(current_ray, world);
            write_color(cout, pixel_color);
        }
    }

    clog << "\rDone.                 \n";
    return 0;
}