#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera {
    public:

            //image
        double aspect_ratio = 1.0;      //width divided by height
        int image_width = 100;
        int samples_per_pixel = 10;     //count of random samples for each pixel

        void render(const hittable& world) {
            initialize();

            std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

            for (int j = 0; j < image_height; j++) {
                std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
                for (int i = 0; i < image_width; i++) {                    

                    color pixel_color(0,0,0);

                    for (int sample = 0; sample < samples_per_pixel; sample++) {
                        ray r = get_ray(i, j);
                        pixel_color += ray_color(r, world);
                    }
                    write_color(std::cout, pixel_samples_scale * pixel_color);
                    // auto pixel_center = pixel00_location + (i * pixel_u) + (j * pixel_v);
                    // auto ray_direction = pixel_center - eye_point;

                    // ray r(eye_point, ray_direction);

                    // color pixel_color = ray_color(r,world);
                    // write_color(std::cout, pixel_color);
                }
            }

            std::clog << "\rDone.                       \n";

        }


    private:

        int image_height;
        double pixel_samples_scale;     //color scale factor for a sum of pixel samples
        point3 eye_point;
        point3 pixel00_location;
        vec3 pixel_u;
        vec3 pixel_v;

        void initialize() {
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            pixel_samples_scale = 1.0 / samples_per_pixel;

            eye_point = point3(0, 0, 0);

            // Determine viewport dimensions.
            auto focal_length = 1.0;
            auto viewport_height = 2.0;
            auto viewport_width = viewport_height * (double(image_width)/image_height);

            // Calculate the vectors across the horizontal and down the vertical viewport edges.
            auto viewport_u = vec3(viewport_width, 0, 0);
            auto viewport_v = vec3(0, -viewport_height, 0);

            // Calculate the horizontal and vertical delta vectors from pixel to pixel.
            pixel_u = viewport_u / image_width;
            pixel_v = viewport_v / image_height;

            // Calculate the location of the upper left pixel.
            auto viewport_upper_left =
                eye_point - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
            pixel00_location = viewport_upper_left + 0.5 * (pixel_u + pixel_v);
        }

        //shoot camera ray at randomly sampled point around the pixel (i,j)
        ray get_ray(int i, int j) const {
            auto offset = sample_square();
            auto pixel_sample = pixel00_location
                                + ((i + offset.x()) * pixel_u)
                                + ((j + offset.y()) * pixel_v);
            auto ray_origin = eye_point;
            auto ray_direction = pixel_sample - ray_origin;

            return ray(ray_origin, ray_direction);
        }

        //returns a vector to a random point in the [-.5,-.5] to [.5,.5] unit square
        vec3 sample_square() const {
            return vec3(random_double() - 0.5, random_double() - 0.5, 0);
        }

        color ray_color(const ray& r, const hittable& world) const {

            hit_record rec;
            if (world.hit(r, interval(0,infinity), rec)) {
                return 0.5 * (rec.normal + color(1,1,1));
            }

            vec3 unit_vec = unit_vector(r.direction());
            auto y01 = 0.5 * (unit_vec.y() + 1.0);
            return (1.0-y01) * color(1.0,1.0,1.0) + y01 * color(0.5,0.7,1.0);
        }

};


#endif