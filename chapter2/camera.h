#ifndef CAMERA_H
#define CAMERA_H
#include "vec3.h"
#include "ray.h"


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
#endif
