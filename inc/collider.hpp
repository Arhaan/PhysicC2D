#include "boundingvolume.hpp"
#include "glm/glm.hpp"
#include <vector>
class Collider{
    private:
            glm::vec2 m_position, m_scale; // m_position is the position of axis about which it is rotated, m_scale is a scaling factor in the two directions.
            double m_rotation; //angle about which it is rotated about the z-axis;
    public:
            Collider(glm::vec2 position = glm::vec2(0),
                            double rotation = 0,
                            glm::vec2 scale = glm::vec2(1));
            virtual AABB getAABB() const = 0;
            /* virtual OBB getOBB() const = 0; */
            virtual glm::vec2 getCentroid() const = 0;
};

class BoxCollider: public Collider{
        private: 
                std::vector<glm::vec3> m_vertices; // 2+1 dimensional
        public:

            BoxCollider(glm::vec2 position = glm::vec2(0),
                            double rotation = 0,
                            glm::vec2 scale = glm::vec2(1));
            AABB getAABB();
            /* OBB getOBB(); */
            glm::vec2 getCentroid();
};
