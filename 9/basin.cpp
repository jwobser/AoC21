#include "basin.hpp"
#include <algorithm>
#include <compare>
#include <functional>

FloodPoint::FloodPoint(Point center, Origin source = Origin::none)
:Point{center.x, center.y} {
    switch (source){
        case Origin::bottom:
        down = false;
            break;
        case Origin::top:
        up = false;
            break;
        case Origin::left:
        left = false;
            break;
        case Origin::right:
        right = false;
            break;
        default:
            break;
    }
    if (x == 0){ left = false; }
    if (y == 0){ up = false; }
    if (x == WIDTH-1){ right = false; }
    if (y == HEIGHT-1){ down = false; }
}

size_t std::hash<FloodPoint>::operator()(const FloodPoint& fp) const{
return fp.y*100 + fp.x;
}

namespace Basin{
    std::strong_ordering Basin::operator <=>( const Basin& other) const {
        return this->basinSize <=> other.basinSize;
    }
};

