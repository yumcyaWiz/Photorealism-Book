#include "vec3.h"
#include "ray.h"
#include "hit.h"
#include "sphere.h"


int main() {
  Sphere s(Vec3(0, 0, 0), 1);
  Ray ray(Vec3(0, 0, -3), Vec3(0, 0, 1));
  Hit res;

  if(s.intersect(ray, res)) {
    std::cout << res.hitPos << std::endl;
  }

  return 0;
}
