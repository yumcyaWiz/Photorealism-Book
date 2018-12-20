#include "vec3.h"
#include "ray.h"
#include "hit.h"
#include "camera.h"
#include "sphere.h"
#include "image.h"


int main() {
  //512x512の画像
  Image img(512, 512);

  //原点(0, 0, 0)に置かれ、方向(0, 0, -1)に向いているカメラ
  PinholeCamera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), 1.0);

  //(0, 0, -3)に置かれ、半径1の球
  Sphere sphere(Vec3(0, 0, -3), 1);

  //画像を作る処理
  for(int i = 0; i < img.width; i++) {
    for(int j = 0; j < img.height; j++) {
      //(u, v)を計算
      double u = (2.0*i - img.width)/img.width;
      double v = (2.0*j - img.height)/img.height;

      //レイを生成
      Ray ray = cam.getRay(-u, -v);

      //球と当たった場合は法線を色にして書き込む
      Vec3 col;
      Hit res;
      if(sphere.intersect(ray, res)) {
        img.setPixel(i, j, (res.hitNormal + 1)/2);
      }
      else {
        img.setPixel(i, j, Vec3(0, 0, 0));
      }
    }
  }

  //PPM画像出力
  img.ppm_output("single_sphere_tracing.ppm");

  return 0;
}
