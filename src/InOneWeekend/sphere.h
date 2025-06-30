#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"


class sphere : public hittable {
    private:
        point3 center;
        double radius;

    public:
        sphere(const point3& c, double r) : center(c), radius(std::fmax(0,r)) {}

        bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
            vec3 oc = center - r.origin();
            auto a = r.direction().length_squared();
            auto h = dot(oc, r.direction());
            auto c = oc.length_squared() - radius*radius;
            auto discriminant = h*h - a*c;

            if (discriminant < 0) {
                return false;
            }

            auto sqrtd = std::sqrt(discriminant);
            
        }
};


#endif