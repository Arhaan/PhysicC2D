#ifndef __BVH_H__
#define __BVH_H__

#include <vector>
/* #include "boundingvolume.hpp" */
#include "rigidbody.hpp"
#include "glm/glm.hpp"

namespace Physicc2D{

        struct BVHNode{
                BVHNode *parent = nullptr;// Do we need this?
                BVHNode *left = nullptr;
                BVHNode *right = nullptr;
                AABB volume;
                RigidBody *body = nullptr;
                bool is_leaf = false;
        };



        class BVH{
                private:
                        std::vector<RigidBody> m_rigidbody_list;
                        BVHNode* m_head;
                        enum Axis{
                                X,
                                Y,
                                R, //Placeholder for random
                        };
                        int sort(int start, int end, Axis axis = Axis::R); // Sort according to axis (axis = 0 -> x, =1 -> y)
                        void buildTreeTopDown(BVHNode* node, int start, int end); // Build the tree starting at node, and using only the AABRs in between start and end
                        Axis getAxisForCut(int start, int end); //By looking at the spread, get the axis cutting along which we'll get the more symmetric rectangles
                        AABB computeBV(int start, int end); // calculate the area that is occupied by the bounding areas between the indices start and end in the vector

                        void printTable(BVHNode *node);
                public:
                        BVH(std::vector<RigidBody> rigidbody_list):m_rigidbody_list(rigidbody_list){
                        
                                m_head = new BVHNode();
                        }
                        void buildTree(){ // Build the tree
                                buildTreeTopDown(m_head, 0, m_rigidbody_list.size() - 1);
                        }
                        void ReportCollisionsDFS(); // Find all the ppssible collisions
                        void printTable(){
                            printTable(m_head);
                        }
        };

}
#endif // __BVH_H__
