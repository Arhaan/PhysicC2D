#include "collider.hpp"
#include <string>
namespace Physicc2D{
        class RigidBody{
                private:
                        BoxCollider m_collider; // TODO: How to use polymorphism here
                        std::string m_name = "";
                public:
                        RigidBody(std::string name, glm::vec2 position = glm::vec2(0),
                                        double rotation = 0,
                                        glm::vec2 scale = glm::vec2(1)): m_name(name), m_collider(position, rotation, scale){
                        
                        }
                        AABB getAABB(){
                            return m_collider.getAABB();
                        }

                        glm::vec2 centre(){
                            return m_collider.getCentroid();
                        }
                        std::string getName(){
                            return this->m_name;
                        }
        };
}
