#include "rigidbody.hpp"
#include "bvh.hpp"
#include "glm/glm.hpp"
#include "boundingvolume.hpp"
#include <vector>
#include <iostream>
using namespace std;
int main()
{
        Physicc2D::RigidBody b1("b1");
        Physicc2D::RigidBody b2("b2", glm::vec2(0.5, 0));
        std::vector<Physicc2D::RigidBody> rb_list;
        rb_list.push_back(b1);
        rb_list.push_back(b2);
        cout << "RB_list created"  << endl;
        Physicc2D::BVH bvh(rb_list);
        bvh.buildTree();
        cout << "Tree built"  << endl;
        bvh.ReportCollisionsDFS();

	return 0;
}
