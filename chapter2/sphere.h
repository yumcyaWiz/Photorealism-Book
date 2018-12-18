#ifndef SPHERE_H
#define SPHERE_H
#include <cmath>
#include "vec3.h"
#include "ray.h"
#include "hit.h"


class Sphere {
  public:
    Vec3 center; //中心位置
    double radius; //半径

    Sphere(const Vec3& _center, double _radius) : center(_center), radius(_radius) {};

    //rayと交差しているか判定する。交差している場合は衝突情報をresに格納する
    bool intersect(const Ray& ray, Hit& res) const {
      //二次方程式の係数
      double b = dot(ray.direction, ray.origin - center);
      double c = (ray.origin - center).length2() - radius*radius;
      //判別式
      double D = b*b - c;

      //解の候補距離
      double t1 = -b - std::sqrt(D);
      double t2 = -b + std::sqrt(D);

      if(t1 > 10000 | t2 < 0) return false;
      double t = t1;
      if(t < 0) {
        t = t2;
        if(t2 > 10000) return false;
      }

      //衝突情報を格納
      res.t = t;
      res.hitPos = ray(t);
      res.hitNormal = normalize(res.hitPos - center);
      res.hitSphere = this;

      return true;
    };
};
#endif
