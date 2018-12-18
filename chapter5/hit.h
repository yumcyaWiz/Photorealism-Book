#ifndef HIT_H
#define HIT_H
#include "vec3.h"


//Sphereクラスのプロトタイプ宣言
//単純にincludeすると循環参照になってしまうため
class Sphere;


class Hit {
  public:
    double t;           //衝突距離
    Vec3 hitPos;        //衝突位置
    Vec3 hitNormal;     //衝突法線
    const Sphere* hitSphere;  //衝突物体

    Hit() {
      t = 10000;
    };
};
#endif
