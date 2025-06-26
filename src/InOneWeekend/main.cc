#include <iostream>

int main() {

    //image

    int image_width = 256;
    int image_height = 256;

    //render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto r = double(i) / (255);
            auto g = double(j) / (255);
            auto b = 79.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';


        }
    }

    std::clog << "\nDone.                       \n";
}