#include "bvh.hpp"

#include "glm/glm.hpp"

int BVH::sort(int start, int end, BVH::Axis axis){
    // Returns the index at which we split.
    if(axis == Axis::R){
        axis = getAxisForCut(start, end);
    }
    auto sort_func = [](AABB &a, AABB &b){
            return(a.centre().x < b.centre().x);
    };
    
    if(axis == Axis::Y){
       // y axis
        auto sort_func = [](AABB &a, AABB &b){
            return(a.centre().y < b.centre().y);
        }; 
    }

    std::sort(std::next(m_bounding_boxes.begin(), start),std::next(m_bounding_boxes.begin(), end+1) , sort_func);
    return (start+(end-start)/2); // Split by median object (tree will be more balanced)
}



BVH::Axis BVH::getAxisForCut(int start, int end){
        glm::vec2 min(m_bounding_boxes[start].centre());
        glm::vec2 max(m_bounding_boxes[start].centre());
        for(int i = start; i<= end; i++){
            min = glm::min(min, m_bounding_boxes[i].centre());
            max  = glm::max (max, m_bounding_boxes[i].centre());
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
        node->volume = m_bounding_boxes[start];
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
        AABB bv = m_bounding_boxes[start];
        for(int i = start+1; i<= end; i++){
                bv = bv.getEnclosingBV(m_bounding_boxes[i]);
        }

        return bv;
}


