#include <iostream>
#include "vec3.h"


int main() {
  Vec3 v1(1, 2, 3);
  Vec3 v2(4, 5, 6);

  std::cout << v1 + v2 << std::endl;
  std::cout << v1 - v2 << std::endl;
  std::cout << v1 * v2 << std::endl;
  std::cout << v1 / v2 << std::endl;

  std::cout << v1 + 1 << std::endl;
  std::cout << v1 - 1 << std::endl;
  std::cout << v1 * 2 << std::endl;
  std::cout << v1 / 2 << std::endl;

  std::cout << dot(v1, v2) << std::endl;
  std::cout << cross(v1, v2) << std::endl;

  std::cout << v1.length() << std::endl;

  return 0;
}
