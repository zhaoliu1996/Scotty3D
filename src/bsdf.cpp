#include "bsdf.h"

#include <algorithm>
#include <iostream>
#include <utility>


using std::min;
using std::max;
using std::swap;

namespace CMU462 {

void make_coord_space(Matrix3x3& o2w, const Vector3D& n) {
  Vector3D z = Vector3D(n.x, n.y, n.z);
  Vector3D h = z;
  if (fabs(h.x) <= fabs(h.y) && fabs(h.x) <= fabs(h.z))
    h.x = 1.0;
  else if (fabs(h.y) <= fabs(h.x) && fabs(h.y) <= fabs(h.z))
    h.y = 1.0;
  else
    h.z = 1.0;

  z.normalize();
  Vector3D y = cross(h, z);
  y.normalize();
  Vector3D x = cross(z, y);
  x.normalize();

  o2w[0] = x;
  o2w[1] = y;
  o2w[2] = z;
}

// Diffuse BSDF //

Spectrum DiffuseBSDF::f(const Vector3D& wo, const Vector3D& wi) {
  return albedo * (1.0 / PI);
}

Spectrum DiffuseBSDF::sample_f(const Vector3D& wo, Vector3D* wi, float* pdf) {
  // TODO (PathTracer):
  // Implement DiffuseBSDF
    *wi = sampler.get_sample(pdf);
    return f(wo, *wi);
}

// Mirror BSDF //

Spectrum MirrorBSDF::f(const Vector3D& wo, const Vector3D& wi) {
    Vector3D w_in;
    reflect(wo, &w_in);
    if (w_in == wi) {
        return reflectance*(1/wo.z);
    }
    else {
        return Spectrum();
    }
}

Spectrum MirrorBSDF::sample_f(const Vector3D& wo, Vector3D* wi, float* pdf) {
  // TODO (PathTracer):
  // Implement MirrorBSDF
    reflect(wo, wi);
    *pdf = 1;
    return reflectance*(1/wo.z);
}

// Glossy BSDF //

/*
Spectrum GlossyBSDF::f(const Vector3D& wo, const Vector3D& wi) {
  return Spectrum();
}

Spectrum GlossyBSDF::sample_f(const Vector3D& wo, Vector3D* wi, float* pdf) {
  *pdf = 1.0f;
  return reflect(wo, wi, reflectance);
}
*/

// Refraction BSDF //

Spectrum RefractionBSDF::f(const Vector3D& wo, const Vector3D& wi) {
    Vector3D w_in;
    if (refract(wo, &w_in, ior)) {
        if (w_in == wi) {
            return transmittance*(1/abs_cos_theta(wo));
        }
    }
    return Spectrum();
}

Spectrum RefractionBSDF::sample_f(const Vector3D& wo, Vector3D* wi,
                                  float* pdf) {
  // TODO (PathTracer):
  // Implement RefractionBSDF
    refract(wo, wi, ior);
    *pdf = 1;
    return f(wo, *wi);
}

// Glass BSDF //

Spectrum GlassBSDF::f(const Vector3D& wo, const Vector3D& wi) {
  return Spectrum();
}

Spectrum GlassBSDF::sample_f(const Vector3D& wo, Vector3D* wi, float* pdf) {
  // TODO (PathTracer):
  // Compute Fresnel coefficient and either reflect or refract based on it.

    if (!refract(wo, wi, ior)) {
        *pdf = 1;
        reflect(wo, wi);
        return reflectance*(1/cos_theta(wo));
    } else {
        double r0, r;
        if (cos_theta(wo) > 0) {
            r0 = pow((1-ior),2)/pow((1+ior),2);
        } else {
            r0 = pow((ior-1),2)/pow((1+ior),2);
        }
        r = r0 + (1-r0)*pow((1-abs_cos_theta(wo)), 5);
        r = clamp(r, 0, 1);
        if (((float)rand()) / ((float)RAND_MAX) < r) {
            *pdf = r;
            reflect(wo, wi);
            return r*reflectance*(1/abs_cos_theta(*wi));
        } else {
            *pdf = 1-r;
            // refract(wo, wi, ior);
            if (cos_theta(wo) > 0) {
                // printf("%f and %f\n",ior*ior, abs_cos_theta(*wi));
                return (1-r)*transmittance*(1/abs_cos_theta(*wi));
            } else {
                return (1-r)*transmittance*(ior*ior)*(1/abs_cos_theta(*wi));
            }
        }
    }
}

void BSDF::reflect(const Vector3D& wo, Vector3D* wi) {
  // TODO (PathTracer):
  // Implement reflection of wo about normal (0,0,1) and store result in wi.
    *wi = Vector3D(0., 0., 2*(wo.z)) - wo;
}

bool BSDF::refract(const Vector3D& wo, Vector3D* wi, float ior) {
  // TODO (PathTracer):
  // Use Snell's Law to refract wo surface and store result ray in wi.
  // Return false if refraction does not occur due to total internal reflection
  // and true otherwise. When dot(wo,n) is positive, then wo corresponds to a
  // ray entering the surface through vacuum.


    if (cos_theta(wo) > 0) {
        // enter in the surface
        *wi = Vector3D(-sin_theta(wo)*cos_phi(wo)/ior,
                       -sin_theta(wo)*sin_phi(wo)/ior,
                       -sqrt(1 - sin_theta(wo)*sin_theta(wo)/(ior*ior)));
        if (sin_theta(wo) >= ior) {
            return false;
        } else {
            return true;
        }
    } else {
        // from material to air
        *wi = Vector3D(-sin_theta(wo)*cos_phi(wo)*ior,
                       -sin_theta(wo)*sin_phi(wo)*ior,
                       sqrt(1 - sin_theta(wo)*sin_theta(wo)*(ior*ior)));
        if (ior*sin_theta(wo) >= 1) {
            return false;
        } else {
            return true;
        }
    }
}

// Emission BSDF //

Spectrum EmissionBSDF::f(const Vector3D& wo, const Vector3D& wi) {
  return Spectrum();
}

Spectrum EmissionBSDF::sample_f(const Vector3D& wo, Vector3D* wi, float* pdf) {
  *wi = sampler.get_sample(pdf);
  return Spectrum();
}

}  // namespace CMU462
