#ifndef HEADER_H
#define HEADER_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>


// C++ Std Usings

using std::make_shared;
using std::shared_ptr;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

//returns a random real number in [0,1)
inline double random_double() {
    return std::rand() / (RAND_MAX + 1.0);
}

//returns a random real in [min, max)
inline double random_double(double min, double max) {
    return min + (max-min)*random_double();
}

// Common Headers

#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif