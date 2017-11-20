#include "bvh.h"

#include "CMU462/CMU462.h"
#include "static_scene/triangle.h"

#include <iostream>
#include <stack>

using namespace std;

namespace CMU462 {
namespace StaticScene {


BVHAccel::BVHAccel(const std::vector<Primitive *> &_primitives,
                   size_t max_leaf_size) {
  this->primitives = _primitives;

  // TODO (PathTracer):
  // Construct a BVH from the given vector of primitives and maximum leaf
  // size configuration. The starter code build a BVH aggregate with a
  // single leaf node (which is also the root) that encloses all the
  // primitives.

  BBox bb;
  for (size_t i = 0; i < primitives.size(); ++i) {
    bb.expand(primitives[i]->get_bbox());
  }

  root = new BVHNode(bb, 0, primitives.size());
  construct_bvh(root, max_leaf_size);
}


BVHAccel::~BVHAccel() {
  // TODO (PathTracer):
  // Implement a proper destructor for your BVH accelerator aggregate
	if (root) {
		delete root;
	}
}

BBox BVHAccel::get_bbox() const { return root->bb; }

bool BVHAccel::intersect(const Ray &ray) const {
  // TODO (PathTracer):
  // Implement ray - bvh aggregate intersection test. A ray intersects
  // with a BVH aggregate if and only if it intersects a primitive in
  // the BVH that is not an aggregate.

  //bool hit = false;
  //for (size_t p = 0; p < primitives.size(); ++p) {
  //  if (primitives[p]->intersect(ray)) hit = true;
  //}

  //return hit;
  Intersection i;

  return intersect(ray, &i);
}

bool BVHAccel::intersect(const Ray &ray, Intersection *isect) const {
  // TODO (PathTracer):
  // Implement ray - bvh aggregate intersection test. A ray intersects
  // with a BVH aggregate if and only if it intersects a primitive in
  // the BVH that is not an aggregate. When an intersection does happen.
  // You should store the non-aggregate primitive in the intersection data
  // and not the BVH aggregate itself.

  //bool hit = false;
  //for (size_t p = 0; p < primitives.size(); ++p) {
  //  if (primitives[p]->intersect(ray, isect)) hit = true;
  //}

  //return hit;
	return intersect_helper(get_root(), ray, isect);
}

/* helper functions */
/* for a node, we check if we split it in mid x, mid y or mid z */
void BVHAccel::construct_bvh(BVHNode* root, size_t max_leaf_size) {

	//base case: less than max_leaf_size primitives in the node
	if (root->range <= max_leaf_size) {
		return;
	}

	size_t split_index;
	//size_t split_dim;

	size_t start_l = root->start;
	size_t range_l, start_r, range_r;
	BBox left_BB, right_BB;

	//decide which dimension and where to split, and sort the primitives in that dimension
	bool split = eval(root, &split_index);

	if (split) {

		range_l = split_index + 1;
		start_r = start_l + range_l;
		range_r = root->range - range_l;


		for (size_t l = start_l; l < (start_l + range_l); l++) {
			left_BB.expand(primitives[l]->get_bbox());
		}

		for (size_t r = start_r; r < (start_r + range_r); r++) {
			right_BB.expand(primitives[r]->get_bbox());
		}

		BVHNode* left = new BVHNode(left_BB, start_l, range_l);
		BVHNode* right = new BVHNode(right_BB, start_r, range_r);

		root->l = left;
		root->r = right;

		construct_bvh(left, max_leaf_size);
		construct_bvh(right, max_leaf_size);
	}

	return;

}

bool BVHAccel::eval(BVHNode* root, size_t* split_index) {

	//sort in x coordinate

	double cost_x;
	size_t index_x;
	std::sort(primitives.begin() + (root->start), primitives.begin() + (root->start + root->range), sort_xdir());
	eval_helper(root, &cost_x, &index_x);

	//sort in y coordinate
	double cost_y;
	size_t index_y;
	std::sort(primitives.begin() + (root->start), primitives.begin() + (root->start + root->range), sort_ydir());
	eval_helper(root, &cost_y, &index_y);

	//sort in z coordinate
	double cost_z;
	size_t index_z;
	std::sort(primitives.begin() + (root->start), primitives.begin() + (root->start + root->range), sort_zdir());
	eval_helper(root, &cost_z, &index_z);

	double cost_min = min(cost_x, min(cost_y, cost_z));

	if (cost_min == cost_x) {
		*split_index = index_x;
		std::sort(primitives.begin() + (root->start), primitives.begin() + (root->start + root->range), sort_xdir());
	}
	else if (cost_min == cost_y) {
		*split_index = index_y;
		std::sort(primitives.begin() + (root->start), primitives.begin() + (root->start + root->range), sort_ydir());
	}
	else {
		*split_index = index_z;
	}

	return true;
}

void BVHAccel::eval_helper(BVHNode* root, double* cost, size_t* index) {

	double cost_min = -1;
	double cost_cur;
	size_t index_min;

	BBox box_l;
	BBox box_r;

	for (size_t i = 0; i < root->range; i++) {

		auto cur = primitives[root->start + i];

		box_l.expand(cur->get_bbox());
		box_r = rest_bbox(root, i + 1, root->range);
		cost_cur = (i + 1) * box_l.surface_area() + (root->range - i - 1) * box_r.surface_area();

		if (cost_min < 0 || cost_cur < cost_min) {
			cost_min = cost_cur;
			index_min = i;
		}
	}
	*cost = cost_min;
	*index = index_min;

}

BBox BVHAccel::rest_bbox(BVHNode* root, size_t start, size_t end) {
	BBox box;
	for (size_t i = start; i < end; i++) {
		auto cur = primitives[root->start + i];
		box.expand(cur->get_bbox());
	}
	return box;
}

bool BVHAccel::intersect_helper(BVHNode* root, const Ray &ray, Intersection *i) const {

	//cout << "intersection helper" << endl;
	double t0, t1;
	bool hit = false;

	if (!(root->bb.intersect(ray, t0, t1))) {
		return false;
	}

	if (t0 > i->t) return false;

	if (root->isLeaf()) {
		//cout << "leaf" << endl;
		bool hit_cur;
		Intersection i_cur;

		for (size_t j = 0; j < root->range; j++) {

			hit_cur = primitives[root->start + j]->intersect(ray, &i_cur);

			if (hit_cur && (i_cur.t < i->t) && (i_cur.t <= ray.max_t) && (i_cur.t >= ray.min_t)) {
				//cout << "should be true" << endl;
				hit = true;
				*i = i_cur;
			}
		}
	}
	else {
		double t_left0, t_left1, t_right0, t_right1;
		double t_second;
		BVHNode* first;
		BVHNode* second;
		bool hit_temp;

		root->l->bb.intersect(ray, t_left0, t_left1);
		root->r->bb.intersect(ray, t_right0, t_right1);

		if (t_left0 <= t_right0) {
			first = root->l;
			second = root->r;
			t_second = t_right0;
		}
		else {
			first = root->r;
			second = root->l;
			t_second = t_left0;
		}

		hit = intersect_helper(first, ray, i);
		if (t_second < i->t) {
			hit_temp = intersect_helper(second, ray, i);
		}
		if (hit_temp) {
			hit = hit_temp;
		}
		//cout << "hit: " << hit << endl;
	}
	//cout << "hit: " << hit << endl;
	return hit;
}

}  // namespace StaticScene
}  // namespace CMU462
