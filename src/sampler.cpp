#include "sampler.h"

namespace CMU462 {

// Uniform Sampler2D Implementation //

Vector2D UniformGridSampler2D::get_sample() const {
    double Xi1 = (double)(std::rand()) / RAND_MAX;
    double Xi2 = (double)(std::rand()) / RAND_MAX;
    return Vector2D(Xi1, Xi2);
}

// Uniform Hemisphere Sampler3D Implementation //

Vector3D UniformHemisphereSampler3D::get_sample() const {
  double Xi1 = (double)(std::rand()) / RAND_MAX;
  double Xi2 = (double)(std::rand()) / RAND_MAX;

  double theta = acos(Xi1);
  double phi = 2.0 * PI * Xi2;

  double xs = sinf(theta) * cosf(phi);
  double ys = sinf(theta) * sinf(phi);
  double zs = cosf(theta);

  return Vector3D(xs, ys, zs);
}

Vector3D CosineWeightedHemisphereSampler3D::get_sample() const {
  float f;
  return get_sample(&f);
}

Vector3D CosineWeightedHemisphereSampler3D::get_sample(float *pdf) const {
  // You may implement this, but don't have to.
    double Xi1 = (double)(std::rand()) / RAND_MAX;
    double Xi2 = (double)(std::rand()) / RAND_MAX;
    
    double theta = acos(Xi1);
    double phi = 2.0 * PI * Xi2;
    
    double xs = sinf(theta) * cosf(phi);
    double ys = sinf(theta) * sinf(phi);
    double zs = cosf(theta);
    
    *pdf = std::max(0., (zs)/PI);
    return Vector3D(xs, ys, zs);
    
}

}  // namespace CMU462
