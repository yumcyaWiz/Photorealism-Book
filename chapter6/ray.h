#ifndef RAY_H
#define RAY_H
#include <iostream>
#include "vec3.h"

class Ray {
  public:
    Vec3 origin;
    Vec3 direction;
    double tmin = 0.001; //最小衝突距離

    Ray(const Vec3& _origin, const Vec3& _direction) : origin(_origin), direction(_direction) {};

    Vec3 operator()(double t) const {
      return origin + t*direction;
    };
};


std::ostream& operator<<(std::ostream& stream, const Ray& ray) {
  stream << "origin: " << ray.origin << " direction: " << ray.direction;
  return stream;
}

#endif
