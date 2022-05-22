#include "bvh.hpp"
#include <vector>
#include <utility>
#include <iostream>
#include "glm/glm.hpp"

namespace Physicc2D{
        int BVH::sort(int start, int end, BVH::Axis axis){
                // Returns the index at which we split.
                if(axis == Axis::R){
                        axis = getAxisForCut(start, end);
                }
                auto sort_func = [](RigidBody &a, RigidBody &b){
                        return(a.centre().x < b.centre().x);
                };

                if(axis == Axis::Y){
                        // y axis
                        auto sort_func = [](RigidBody &a, RigidBody &b){
                                return(a.centre().y < b.centre().y);
                        }; 
                }

                std::sort(std::next(m_rigidbody_list.begin(), start),std::next(m_rigidbody_list.begin(), end+1) , sort_func);
                return (start+(end-start)/2); // Split by median object (tree will be more balanced)
        }



        BVH::Axis BVH::getAxisForCut(int start, int end){
                glm::vec2 min(m_rigidbody_list[start].centre());
                glm::vec2 max(m_rigidbody_list[start].centre());
                for(int i = start; i<= end; i++){
                        min = glm::min(min, m_rigidbody_list[i].centre());
                        max  = glm::max (max, m_rigidbody_list[i].centre());
                }

                glm::vec2 spreads = max-min;
                if(spreads.x > spreads.y) return Axis::Y; // Return the axis with lower spread
                else return Axis::X;
        }

        void BVH::buildTreeTopDown(BVHNode* node, int start, int end){
                // Builds the bvh in a topdown manner, using recursion
                // We assume everything in node is unitialised at the start of this function, apart from node->parent

                if(start == end){
                        // Leaf node
                        node->volume = m_rigidbody_list[start].getAABB();
                        node->body = &m_rigidbody_list[start];
                        node->is_leaf = true;
                }

                else{
                        node->volume = computeBV(start, end);
                        int splitindex = sort(start, end);
                        BVHNode* leftNode = new BVHNode;
                        BVHNode* rightNode = new BVHNode;
                        node->left = leftNode;
                        node->right = rightNode;

                        leftNode->parent = node;
                        rightNode->parent = node;

                        buildTreeTopDown(leftNode, start, splitindex);
                        buildTreeTopDown(rightNode, splitindex + 1, end);
                }
        }



        AABB BVH::computeBV(int start, int end){
                // Compute the BV that includes the objects between start and end
                AABB bv = m_rigidbody_list[start].getAABB();
                for(int i = start+1; i<= end; i++){
                        bv = bv.getEnclosingBV(m_rigidbody_list[i].getAABB());
                }

                return bv;
        }

        bool descendA(BVHNode* A, BVHNode* B){ // Should this be made inline?
            if(A->is_leaf) return false;
            if(B->is_leaf) return true;
            return A->volume.getVolume() > B->volume.getVolume(); // Descend according to larger volume. See page 255 of real time collison detection  by Christer Ericsen 2005
        }

        void BVH::ReportCollisionsDFS(){
                std::vector<std::pair<BVHNode*, BVHNode*> > stack;
                BVHNode* a = m_head->left, *b = m_head->right;
                while(true){
                        if(a->volume.overlapsWith(b->volume)){
                            if(a->is_leaf && b->is_leaf){
                                // Do narrowphase
                                // TODO
                                    std::cout << a->body->getName() << " and " << b->body->getName() << std::endl;
                            }
                            else if(descendA(a, b)){
                                stack.push_back(std::make_pair(a->right, b));
                                a = a->left;
                                continue;
                            }
                            else{
                                stack.push_back(std::make_pair(a, b->right));
                                b = b->left;
                                continue;
                            }
                        }



                        if(stack.empty()) break; 
                        std::pair<BVHNode*, BVHNode*> newvals = stack.back(); 
                        stack.pop_back();
                        a = newvals.first;
                        b = newvals.second;
                }
        }






}
