#include "triangle.h"

#include "CMU462/CMU462.h"
#include "GL/glew.h"

namespace CMU462 {
namespace StaticScene {

Triangle::Triangle(const Mesh* mesh, vector<size_t>& v) : mesh(mesh), v(v) {}
Triangle::Triangle(const Mesh* mesh, size_t v1, size_t v2, size_t v3)
    : mesh(mesh), v1(v1), v2(v2), v3(v3) {}

BBox Triangle::get_bbox() const {
  // TODO (PathTracer):
  // compute the bounding box of the triangle
    Vector3D p1(mesh->positions[v1]);
    Vector3D p2(mesh->positions[v2]);
    Vector3D p3(mesh->positions[v3]);
    BBox a(p1);
    a.expand(p2);
    a.expand(p3);
    return a;
}

bool Triangle::intersect(const Ray& r) const {
  // TODO (PathTracer): implement ray-triangle intersection
    Vector3D p1(mesh->positions[v1]);
    Vector3D p2(mesh->positions[v2]);
    Vector3D p3(mesh->positions[v3]);
    Vector3D o = r.o;
    Vector3D d = r.d;
    Vector3D e1 = p2-p1;
    Vector3D e2 = p3-p1;
    Vector3D s = o-p1;
    Vector3D s1 = cross(d,e2);
    Vector3D s2 = cross(s,e1);
    double c1 = 1/(dot(s1,e1)), c2 = dot(s2,e2), c3 = dot(s1,s), c4 = dot(s2,d);
    double t = c1*c2, b1 = c1*c3, b2 = c1*c4;
    if (t>=r.min_t && t<=r.max_t && b1>0 && b2>0 && (1-b1-b2)>0){
        r.max_t = t;
        return true;
    }
    
    return false;
}

bool Triangle::intersect(const Ray& r, Intersection* isect) const {
  // TODO (PathTracer):
  // implement ray-triangle intersection. When an intersection takes
  // place, the Intersection data should be updated accordingly
    Vector3D p1(mesh->positions[v1]);
    Vector3D p2(mesh->positions[v2]);
    Vector3D p3(mesh->positions[v3]);
    Vector3D n1(mesh->normals[v1]);
    Vector3D n2(mesh->normals[v2]);
    Vector3D n3(mesh->normals[v3]);
    
    Vector3D o = r.o;
    Vector3D d = r.d;
    Vector3D e1 = p2-p1;
    Vector3D e2 = p3-p1;
    Vector3D s = o-p1;
    Vector3D s1 = cross(d,e2);
    Vector3D s2 = cross(s,e1);
    double c1 = 1/(dot(s1,e1));
    double c2 = dot(s2,e2);
    double c3 = dot(s1,s);
    double c4 = dot(s2,d);
    double t = c1*c2, b1 = c1*c3, b2 = c1*c4;
    if (t>=r.min_t && t<=r.max_t && b1>0 && b2>0 && (1-b1-b2)>0){
        r.max_t = t;
        isect->t = t;
        isect->n = n1*(1-b1-b2) + n2*b1 + n3*b2;
        // change the normal if its facing the back
        if(dot(isect->n, r.d)>0){
            isect->n = -1 * isect->n;
        }
        isect->primitive = this;
        isect->bsdf = get_bsdf();
        return true;
    }
    
    return false;
}

void Triangle::draw(const Color& c) const {
  glColor4f(c.r, c.g, c.b, c.a);
  glBegin(GL_TRIANGLES);
  glVertex3d(mesh->positions[v1].x, mesh->positions[v1].y,
             mesh->positions[v1].z);
  glVertex3d(mesh->positions[v2].x, mesh->positions[v2].y,
             mesh->positions[v2].z);
  glVertex3d(mesh->positions[v3].x, mesh->positions[v3].y,
             mesh->positions[v3].z);
  glEnd();
}

void Triangle::drawOutline(const Color& c) const {
  glColor4f(c.r, c.g, c.b, c.a);
  glBegin(GL_LINE_LOOP);
  glVertex3d(mesh->positions[v1].x, mesh->positions[v1].y,
             mesh->positions[v1].z);
  glVertex3d(mesh->positions[v2].x, mesh->positions[v2].y,
             mesh->positions[v2].z);
  glVertex3d(mesh->positions[v3].x, mesh->positions[v3].y,
             mesh->positions[v3].z);
  glEnd();
}

}  // namespace StaticScene
}  // namespace CMU462
