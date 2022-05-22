#include "collider.hpp"

namespace Physicc2D{
        Collider::Collider(glm::vec2 position, double rotation, glm::vec2 scale): m_position(position), m_rotation(rotation), m_scale(scale){}


        BoxCollider::BoxCollider(glm::vec2 position, double rotation, glm::vec2 scale):
                Collider(position, rotation, scale), 
                m_vertices(std::vector<glm::vec3>(8, glm::vec3(0, 0, 1.0f)))
         {
         m_vertices[0] = glm::vec3(scale.x* 0.5f, scale.y*0.5f, 0);
                m_vertices[1] = glm::vec3(-scale.x* 0.5f, scale.y*0.5f, 0);
                m_vertices[2] = glm::vec3(scale.x* 0.5f, -scale.y*0.5f, 0);
                m_vertices[3] = glm::vec3(-scale.x* 0.5f, -scale.y*0.5f, 0);
        }

        AABB BoxCollider::getAABB() const{
               return AABB(); // TODO
        }

        glm::vec2 BoxCollider::getCentroid() const{
            return m_position;
        }
}
