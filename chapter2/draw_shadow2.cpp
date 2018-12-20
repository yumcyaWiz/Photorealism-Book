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
  PinholeCamera cam(Vec3(0), Vec3(0, 0, -1), 1);

  Aggregate aggregate;
  aggregate.add(std::make_shared<Sphere>(Vec3(0, 0, -3), 1));
  aggregate.add(std::make_shared<Sphere>(Vec3(0, -10001, 0), 10000));

  Vec3 sunDir = normalize(Vec3(1, 1, 1));

  for(int i = 0; i < img.width; i++) {
    for(int j = 0; j < img.height; j++) {
      //(u, v)の計算
      double u = (2.0*i - img.width)/img.width;
      double v = (2.0*j - img.height)/img.height;

      //レイを生成
      Ray ray = cam.getRay(-u, -v);
      
      //colにはデフォルトで(0, 0, 0) = 黒が入る
      Vec3 col;
      Hit res;
      if(aggregate.intersect(ray, res)) {
        Ray shadowRay(res.hitPos + 0.001*res.hitNormal, sunDir);
        Hit res_temp;
        //光源の方向へ飛ばしたレイが衝突しなかったら光の強さを計算
        if(!aggregate.intersect(shadowRay, res_temp)) {
          col = std::max(dot(res.hitNormal, sunDir), 0.0) * Vec3(1);
        }
      }

      img.setPixel(i, j, col);
    }
  }

  //PPM出力
  img.ppm_output("draw_shadow2.ppm");

  return 0;
}
