#pragma once
#include <compare>
#include <cstdint>
#include <functional>

extern const unsigned int HEIGHT, WIDTH;

struct Point{
    int x,y;
};

namespace Basin{
    class Basin{
        public:
        Point center;
        Basin(int x, int y): center{x,y}{}
        Basin(Point center): center{center}{}
        std::strong_ordering operator <=> (const Basin&) const;
        unsigned int basinSize{1};

        private:
    };
};


struct FloodPoint: public Point{
    enum class Origin{bottom, top, left, right, none};
    bool up = true;
	bool down = true;
	bool left = true;
	bool right = true;

    FloodPoint(int x, int y, Origin source): FloodPoint(Point{x,y}, source){}
    FloodPoint(Basin::Basin center)
        :FloodPoint(center.center, Origin::none){}

    FloodPoint(Point center, Origin source);
    FloodPoint(int x, int y): FloodPoint(Point{x,y}, Origin::none){};
    bool operator==(const FloodPoint& other) const {
        return (x==other.x && y == other.y);
    }
};

namespace std{
    template<>
    class hash<FloodPoint>{
        public:
        size_t operator()(const FloodPoint&) const;
    };
}