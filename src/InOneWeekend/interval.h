#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
    public:
        double min;
        double max;
        
        interval() : min(+infinity), max(-infinity) {}

        interval(double min, double max) : min(min), max(max) {}

        double size() const {
            return max - min;
        }

        //inclusive
        bool contains(double value) const {
            return min <= value && value <= max;
        }

        //noninclusive
        bool surrounds(double value) const {
            return min < value && value < max;
        }

        static const interval empty;
        static const interval universe;
};

const interval interval::empty      = interval(+infinity, -infinity);
const interval interval::universe   = interval(-infinity, +infinity);

#endif