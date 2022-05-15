#include <cmath>
struct Vec2d{
    double x, y;
    Vec2d(){
        x = y = 0;
    }

    Vec2d(double a, double b): x(a), y(b){}
    Vec2d operator+(const Vec2d &b)const{
        return Vec2d((x+b.x)/2, (y+b.y)/2);
    }
    Vec2d operator/(double a){
        return Vec2d(x/a, y/a);
    }
};

Vec2d vmin(Vec2d a, Vec2d b){
    return Vec2d(std::fmin(a.x, b.x), std::fmin(a.y, b.y));
}

Vec2d vmax(Vec2d a, Vec2d b){
    return Vec2d(std::fmax(a.x, b.x), std::fmax(a.y, b.y));
}

class BaseBA{
    private:
            /* virtual bool intersectingWith(const BaseBA &) const = 0; */
            /* virtual double getArea() const = 0; */
            /* virtual BaseBA getEnclosingBA(const BaseBA&) const = 0; */
};

class AABR{
    private: 
            Vec2d bottomleft, topright;
    public:
            AABR(): bottomleft(), topright(){}
            AABR(Vec2d bl, Vec2d tr): bottomleft(bl), topright(tr){}
            double getArea(){
                return abs((bottomleft.x - topright.x) * (bottomleft.y - topright.y));
            }

            AABR getEnclosingBA(AABR other){ // This gives error with g++ if we make this a subclass of BaseBA but not with clang, TODO
                    return AABR(vmin(bottomleft, other.bottomleft), vmax(topright, other.topright));
            }

            Vec2d centre(){
                return (bottomleft + topright)/2;
            }
};


