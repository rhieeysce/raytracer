#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"


class sphere : public hittable {
    private:
        point3 center;
        double radius;
        shared_ptr<material> mat;

    public:
        //constructor
        sphere(const point3& c, double r) : center(c), radius(std::fmax(0,r)) {}

        //determines if a given ray hits this sphere
        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            vec3 oc = center - r.origin();
            auto a = r.direction().length_squared();
            auto h = dot(oc, r.direction());
            auto c = oc.length_squared() - radius*radius;
            auto discriminant = h*h - a*c;

            //negative discriminant means ray does not hit the sphere
            if (discriminant < 0) {
                return false;
            }

            auto sqrtd = std::sqrt(discriminant);

            //finding values for t with quadratic formula
            auto root = (h - sqrtd) / a;
            if (!ray_t.surrounds(root)) {
                root = (h + sqrtd) / a;
                if (!ray_t.surrounds(root)) {
                    return false;
                }
            }

            //updating hit record
            rec.t = root;
            rec.p = r.at(rec.t);
            rec.set_face_normal(r, (rec.p - center) / radius);

            return true;
        }
};


#endif