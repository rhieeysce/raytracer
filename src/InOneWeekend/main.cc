#include "color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

color ray_color(const ray& r) {
    auto unit_vec = unit_vector(r.direction());
    auto y01 = 0.5 * (unit_vec.y() + 1.0);
    return (1.0-y01) * color(1.0,0,0) + y01 * color(0,1.0,0);
};


int main() {

    //image
    auto aspect_ratio = 16.0 / 9.0;
    int image_height = 900;
    int image_width = int(image_height * aspect_ratio);

    //viewport sizing can be less than 1.0
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width) / double(image_height));

    //camera
    auto focal_length = 1.0;
    auto eye_point = point3(0,0,0);

    //vectors to help with viewport and pixels
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    //pixel spacing
    auto pixel_u = viewport_u / image_width;
    auto pixel_v = viewport_v / image_height;

    //starting point for scanning pixels
    auto viewport_upper_left = eye_point - vec3(0,0, focal_length) - (viewport_u/2) + (viewport_v/2);
    auto pixel00_location = viewport_upper_left + 0.5 * (pixel_u + pixel_v);    //middle of the pixel, not a corner



    //render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {

            // auto pixel_color = color(double(i)/(image_width-1), double(j)/(image_height-1),79.0);
            

            auto pixel_center = pixel00_location + (i * pixel_u) + (j * pixel_v);
            auto ray_direction = pixel_center - eye_point;

            ray r(eye_point, ray_direction);
            color pixel_color = ray_color(r);       //ray_color will be defined in main.cc



            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\nDone.                       \n";
}