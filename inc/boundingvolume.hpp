#include <cmath>
#include "glm/glm.hpp"
namespace Physicc2D{
        // struct Vec2d{
        //     double x, y;
        //     Vec2d(){
        //         x = y = 0;
        //     }

        //     Vec2d(double a, double b): x(a), y(b){}
        //     Vec2d operator+(const Vec2d &b)const{
        //         return Vec2d((x+b.x)/2, (y+b.y)/2);
        //     }
        //     Vec2d operator/(double a){
        //         return Vec2d(x/a, y/a);
        //     }
        // };

        // Vec2d vmin(Vec2d a, Vec2d b){
        //     return Vec2d(std::fmin(a.x, b.x), std::fmin(a.y, b.y));
        // }

        // Vec2d vmax(Vec2d a, Vec2d b){
        //     return Vec2d(std::fmax(a.x, b.x), std::fmax(a.y, b.y));
        // }

        class BaseBV{
                private:
                        /* virtual bool intersectingWith(const BaseBV &) const = 0; */
                        /* virtual double getArea() const = 0; */
                        /* virtual BaseBV getEnclosingBA(const BaseBV&) const = 0; */
        };

        class AABB{
                private: 
                        glm::vec2 bottomleft, topright;
                public:
                        AABB(): bottomleft(), topright(){}
                        AABB(glm::vec2 bl, glm::vec2 tr): bottomleft(bl), topright(tr){}
                        double getArea() const{
                                return abs((bottomleft.x - topright.x) * (bottomleft.y - topright.y));
                        }

                        AABB getEnclosingBV(const AABB& other) const{ // This gives error with g++ if we make this a subclass of BaseBV but not with clang, TODO
                                return AABB(glm::min(bottomleft, other.bottomleft), glm::max(topright, other.topright));
                        }

                        glm::vec2 centre() const{
                                return (bottomleft + topright)*(float)(1/2.0);
                        }

                        bool overlapsWith(const AABB& other) const{
                            if(this->bottomleft.x > other.bottomleft.x){
                                return (this->topright.y > other.bottomleft.y && this->topright.y < other.topright.y);
                            }
                            else{
                                return (other.topright.y > this->bottomleft.y && other.topright.y < this->topright.y);
                            }
                        }
        };

}
