#include <vector>
#include "boundingarea.hpp"
#include "glm/glm.hpp"


struct BAHNode{
    BAHNode *parent = nullptr;
    BAHNode *left = nullptr;
    BAHNode *right = nullptr;
    AABR area;
};



class BAH{
        private:
                std::vector<AABR> m_bounding_boxes;
                BAHNode* m_head;
                void sort(int axis, int start, int end); // Sort according to axis (axis = 0 -> x, =1 -> y)
                void buildTree(BAHNode* node, int start, int end); // Build the tree starting at node, and using only the AABRs in between start and end
                int getAxisForCut(int start, int end); //By looking at the spread, get the axis cutting along which we'll get the more symmetric rectangles
                AABR computeBA(int start, int end); // calculate the area that is occupied by the bounding areas between the indices start and end in the vector
                int split(int start, int end); // might sort m_bounding_boxes and return the value at which to bisect the interval. The returned value has to be kept in the left interval
        public:
                BAH(std::vector<AABR> bounding_boxes): m_bounding_boxes(bounding_boxes){}
                void buildTree(){ // Build the tree
                        buildTree(m_head, 0, m_bounding_boxes.size() - 1);
                }
};
