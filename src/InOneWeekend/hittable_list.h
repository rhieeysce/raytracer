#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <vector>

class hittable_list : public hittable {
    public:
    //list of pointers to hittables
    std::vector<shared_ptr<hittable>> objects;

    //constructors
    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) {
        add(object);
    }

    //functions for clearing and adding
    void clear() {
        objects.clear();
    }
    void add(shared_ptr<hittable> object) {
        objects.push_back(object);
    }

    //determines the closest object in the list that is hit by the ray
    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_tmax;

        for (const auto& object : objects) {
            if (object->hit(r, ray_tmin, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};





#endif