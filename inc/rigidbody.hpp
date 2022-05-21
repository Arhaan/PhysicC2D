#include "collider.hpp"
namespace Physicc2D{
        class RigidBody{
                private:
                        BoxCollider m_collider; // TODO: How to use polymorphism here
                public:
                        AABB getAABB(){
                            return m_collider.getAABB();
                        }

                        glm::vec2 centre(){
                            return m_collider.getCentroid();
                        }
        };
}
