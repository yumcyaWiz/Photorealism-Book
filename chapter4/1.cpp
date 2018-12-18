#include <iostream>
#include <cmath>
#include <random>


std::random_device rnd_dev;
std::mt19937 mt(rnd_dev());
std::uniform_real_distribution<> dist(0, 1);
//一様乱数の生成
inline double rnd() {
  return dist(mt);
}


//被積分関数
inline double f(double x, double y) {
  return x*x + y*y;
}


int main() {
  //サンプリング数
  const int N = 10000;

  //モンテカルロ積分の計算
  double sum = 0;
  for(int i = 0; i < N; i++) {
    double x = rnd();
    double y = rnd();
    sum += f(x, y);
  }
  sum /= N;
  std::cout << sum << std::endl;

  return 0;
}
