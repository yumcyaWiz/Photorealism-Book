#ifndef CAMERA_H
#define CAMERA_H
#include "vec3.h"
#include "ray.h"
#include "random.h"


class Camera {
  public:
    Vec3 camPos; //カメラの位置
    Vec3 camForward; //カメラの前方向
    Vec3 camRight; //カメラの横方向
    Vec3 camUp; //カメラの上方向

    Camera(const Vec3& _camPos, const Vec3& _camForward) : camPos(_camPos), camForward(_camForward) {
      orthonormalBasis(camForward, camRight, camUp);

      std::cout << "camPos: " << camPos << std::endl;
      std::cout << "camForward: " << camForward << std::endl;
      std::cout << "camRight: " << camRight << std::endl;
      std::cout << "camUp: " << camUp << std::endl;
    };

    
    //(u, v)を受け取り、それに対応するレイを返す
    virtual Ray getRay(double u, double v) const = 0;
};


class PinholeCamera : public Camera {
  public:
    double pinholeDist; //イメージセンサーの中心位置からピンホールまでの距離

    PinholeCamera(const Vec3& _camPos, const Vec3& _camForward, double _pinholeDist) : Camera(_camPos, _camForward), pinholeDist(_pinholeDist) {};

    Ray getRay(double u, double v) const {
      //ピンホールの位置
      Vec3 pinholePos = camPos + pinholeDist*camForward;
      //(u, v)に対応するセンサー上の位置
      Vec3 sensorPos = camPos + u*camRight + v*camUp;
      
      return Ray(sensorPos, normalize(pinholePos - sensorPos));
    };
};


class ThinLensCamera : public Camera {
  public:
    double a; //イメージセンサーからレンズ中心までの距離
    double b; //レンズ中心からピントの合う平面までの距離
    double f; //焦点距離
    double lensRadius; //レンズの半径
    Vec3 lensCenter; //レンズの中心位置

    //focusPoint: ピントの合う位置
    //_a: aの値
    //_lensRadius: レンズの半径
    ThinLensCamera(const Vec3& _camPos, const Vec3& _camForward, const Vec3& focusPoint, double _a, double _lensRadius) : Camera(_camPos, _camForward), a(_a), lensRadius(_lensRadius) {
      double cos = dot(camForward, normalize(focusPoint - camPos));
      b = cos*(focusPoint - camPos).length() - a;
      f = 1/(1/a + 1/b); //レンズの式より
      lensCenter = camPos + a*camForward;
    };

    Ray getRay(double u, double v) const {
      //イメージセンサー上の点
      Vec3 sensorPos = camPos + u*camRight + v*camUp;
      //イメージセンサーからレンズ中心へ向かう方向
      Vec3 r = normalize(lensCenter - sensorPos);
      //ピントの合う位置
      Vec3 pf = sensorPos + (a + b)/dot(camForward, r) * r;

      //レンズ上の点をサンプリング
      double x, y;
      sampleDisk(x, y);
      Vec3 l = lensCenter + lensRadius*(x*camRight + y*camUp);

      return Ray(l, normalize(pf - l));
    };
};
#endif
