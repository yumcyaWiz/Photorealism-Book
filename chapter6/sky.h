#ifndef SKY_H
#define SKY_H
#include <string>
#include "vec3.h"
#include "ray.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif


class Sky {
  public:
    //受け取ったレイの方から来る空の放射輝度の値を返す
    //戻り値: 空の放射輝度
    //ray: 放射輝度を取る方向のレイ
    virtual Vec3 getRadiance(const Ray& ray) const = 0;
};


class UniformSky : public Sky {
  public:
    Vec3 color; //空の色

    UniformSky(const Vec3& _color) : color(_color) {};

    Vec3 getRadiance(const Ray& ray) const {
      return color;
    };
};


class SimpleSky : public Sky {
  public:
    SimpleSky() {};

    Vec3 getRadiance(const Ray& ray) const {
      double t = (ray.direction.y + 1)/2;
      return (1 - t)*Vec3(1) + t*Vec3(0.7, 0.8, 1);
    };
};


class IBL : public Sky {
  public:
    int width; //画像の横幅
    int height; //画像の縦幅
    float* hdr_image; //HDR画像

    IBL(const std::string& filename) {
      int n;
      hdr_image = stbi_loadf(filename.c_str(), &width, &height, &n, 0);
    };
    ~IBL() {
      stbi_image_free(hdr_image);
    };

    Vec3 getRadiance(const Ray& ray) const {
      //方向を球面座標系に変換
      double theta = std::acos(ray.direction.y);
      double phi = std::atan2(ray.direction.z, ray.direction.x);
      if(phi < 0) phi += 2*M_PI;

      //(i, j)を計算
      int i = phi/(2*M_PI) * width;
      int j = theta/M_PI * height;

      //(i, j)の配列内におけるインデックスを計算
      int index = 3*i + 3*width*j;

      return Vec3(hdr_image[index], hdr_image[index+1], hdr_image[index+2]);
    };
};
#endif
