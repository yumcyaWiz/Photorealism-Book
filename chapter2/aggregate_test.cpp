#include <memory>
#include "vec3.h"
#include "ray.h"
#include "hit.h"
#include "sphere.h"
#include "camera.h"
#include "image.h"
#include "aggregate.h"


int main() {
  Image img(512, 512);
  PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1);

  Aggregate aggregate;
  //(0, 0, -3)に半径1の球
  aggregate.add(std::make_shared<Sphere>(Vec3(0, 0, -3), 1));
  //(0, -10001, 0)に半径10000の球　床として使える
  aggregate.add(std::make_shared<Sphere>(Vec3(0, -10001, 0), 10000));

  for(int i = 0; i < img.width; i++) {
    for(int j = 0; j < img.height; j++) {
      //(u, v)の計算
      double u = (2.0*i - img.width)/img.width;
      double v = (2.0*j - img.height)/img.height;

      //レイの生成
      Ray ray = cam.getRay(u, v);

      //法線で色付けする
      Hit res;
      if(aggregate.intersect(ray, res)) {
        img.setPixel(i, j, (res.hitNormal + 1)/2);
      }
      else {
        img.setPixel(i, j, Vec3(0));
      }
    }
  }

  img.ppm_output("aggregate_test.ppm");

  return 0;
}
