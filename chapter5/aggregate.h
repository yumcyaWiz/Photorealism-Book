#ifndef AGGREGATE_H
#define AGGREGATE_H
#include <memory>
#include <vector>
#include "ray.h"
#include "hit.h"
#include "sphere.h"


class Aggregate {
  public:
    std::vector<std::shared_ptr<Sphere>> spheres; //物体の配列

    Aggregate() {};
    Aggregate(const std::vector<std::shared_ptr<Sphere>>& _spheres) : spheres(_spheres) {};

    //物体を追加する
    void add(const std::shared_ptr<Sphere>& s) {
      spheres.push_back(s);
    };

    //与えられたレイと全ての物体との間で衝突計算を行う
    //衝突している場合は衝突情報をresに格納し、trueを返す
    bool intersect(const Ray& ray, Hit& res) const {
      bool hit = false;
      for(auto s : spheres) {
        Hit res_temp;
        if(s->intersect(ray, res_temp)) {
          //衝突した物体がさらに手前にある場合に当たったことにする
          if(res_temp.t < res.t) {
            hit = true;
            res = res_temp;
          }
        }
      }
      return hit;
    };
};
#endif
