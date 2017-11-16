#include "sphere.h"

#include <cmath>

#include "../bsdf.h"
#include "../misc/sphere_drawing.h"

namespace CMU462 {
namespace StaticScene {

bool Sphere::test(const Ray& r, double& t1, double& t2) const {
  // TODO (PathTracer):
  // Implement ray - sphere intersection test.
  // Return true if there are intersections and writing the
  // smaller of the two intersection times in t1 and the larger in t2.

    double a = dot(r.d,r.d),
    b = 2*dot(r.o - o, r.d),
    c = dot(r.o-o,r.o-o) - r2,
    delta = b*b-4*a*c;
    
    if(delta >= 0){
        t2 = (-b+sqrt(delta))/(2*a);
        t1 = (-b-sqrt(delta))/(2*a);
        return true;
    }
    else{
        return false;
    }
}

bool Sphere::intersect(const Ray& r) const {
  // TODO (PathTracer):
  // Implement ray - sphere intersection.
  // Note that you might want to use the the Sphere::test helper here.

    double t1 = 0, t2 = 0, t = 0;
    if (test(r,t1,t2)){
        if(t1>=r.min_t && t1<=r.max_t){
            t = t1;
        }
        else if(t2>=r.min_t && t2<=r.max_t){
            t = t2;
        }
        else return false;
        r.max_t = t;
        return true;
    }
    else{
        return false;
    }
}

bool Sphere::intersect(const Ray& r, Intersection* i) const {
  // TODO (PathTracer):
  // Implement ray - sphere intersection.
  // Note again that you might want to use the the Sphere::test helper here.
  // When an intersection takes place, the Intersection data should be updated
  // correspondingly.

    double t1 = 0, t2 = 0, t = 0;
    if (test(r,t1,t2)){
        if(t1>=r.min_t && t1<=r.max_t){
            t = t1;
        }
        else if(t2>=r.min_t && t2<=r.max_t){
            t = t2;
        }
        else return false;
        r.max_t = t;
        i->t = t;
        i->primitive = this;
        i->n = normal(r.o+t1*r.d);
        i->bsdf = get_bsdf();
        return true;
    }
    else{
        return false;
    }

}

void Sphere::draw(const Color& c) const { Misc::draw_sphere_opengl(o, r, c); }

void Sphere::drawOutline(const Color& c) const {
  // Misc::draw_sphere_opengl(o, r, c);
}

}  // namespace StaticScene
}  // namespace CMU462
