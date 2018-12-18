#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include "vec3.h"
#include "util.h"

class Image {
  public:
    int width; //横幅
    int height; //縦幅
    Vec3* data; //ピクセルの配列

    Image(int _width, int _height) : width(_width), height(_height) {
      data = new Vec3[width*height];
    };
    ~Image() {
      delete[] data;
    };

    //ピクセル(i, j)の色を取り出す
    Vec3 getPixel(int i, int j) const {
      return data[i + width*j];
    };


    //ピクセル(i, j)に色をセットする
    void setPixel(int i, int j, const Vec3& c) {
      data[i + width*j] = c;
    };

    
    //ピクセル(i, j)に色を追加する
    void addPixel(int i, int j, const Vec3& c) {
      data[i + width*j] = data[i + width*j] + c;
    };


    //全てのピクセルを一定の値で割る
    void divide(double k) {
      for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
          this->setPixel(i, j, this->getPixel(i, j)/k);
        }
      }
    };


    //ガンマ補正
    void gamma_correction() {
      for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
          Vec3 c = this->getPixel(i, j);
          this->setPixel(i, j, Vec3(std::pow(c.x, 1/2.2), std::pow(c.y, 1/2.2), std::pow(c.z, 1/2.2)));
        }
      }
    };


    //PPM画像出力
    void ppm_output(const std::string& filename) const {
      std::ofstream file(filename);
      file << "P3" << std::endl;
      file << width << " " << height << std::endl;
      file << "255" << std::endl;
      for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
          Vec3 c = this->getPixel(i, j);
          int r = clamp(int(255*c.x), 0, 255);
          int g = clamp(int(255*c.y), 0, 255);
          int b = clamp(int(255*c.z), 0, 255);
          file << r << " " << g << " " << b << std::endl;
        }
      }
      file.close();
    };
};
#endif
