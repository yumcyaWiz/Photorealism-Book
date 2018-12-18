#ifndef LIGHT_H
#define LIGHT_H
#include "vec3.h"


class Light {
  public:
    Vec3 color; //光源の色

    Light(const Vec3& _color) : color(_color) {};

    //レンダリング方程式のLeに対応する部分
    //全ての方向に等しい放射輝度を返すので
    //単純に保持している色を返すだけになる
    Vec3 Le() const {
      return color;
    };
};
#endif
