#include <vector>
#include "boundingvolume.hpp"
#include "glm/glm.hpp"


struct BVHNode{
    BVHNode *parent = nullptr;// Do we need this?
    BVHNode *left = nullptr;
    BVHNode *right = nullptr;
    AABB volume;
    bool is_leaf = false;
};



class BVH{
        private:
                std::vector<AABB> m_bounding_boxes;
                BVHNode* m_head;
                void sort(int axis, int start, int end); // Sort according to axis (axis = 0 -> x, =1 -> y)
                void buildTreeTopDown(BVHNode* node, int start, int end); // Build the tree starting at node, and using only the AABRs in between start and end
                int getAxisForCut(int start, int end); //By looking at the spread, get the axis cutting along which we'll get the more symmetric rectangles
                AABB computeBV(int start, int end); // calculate the area that is occupied by the bounding areas between the indices start and end in the vector
                /* int split(int start, int end); // sort m_bounding_boxes and return the value at which to bisect the interval. The returned value has to be kept in the left interval */
                enum Axis{
                    X,
                    Y,
                    R, //Placeholder for random
                };
        public:
                BVH(std::vector<AABB> bounding_boxes): m_bounding_boxes(bounding_boxes){}
                void buildTree(){ // Build the tree
                        buildTree(m_head, 0, m_bounding_boxes.size() - 1);
                }
};
