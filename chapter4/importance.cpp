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
inline double f(double x) {
  return (x + 1)*std::cos(x);
}


//確率密度関数
inline double p(double x) {
  return std::cos(x);
}
//累積分布関数の逆関数
inline double Pinv(double x) {
  return std::asin(x);
}


int main() {
  //サンプリング数
  const int N = 100000;

  //モンテカルロ積分の計算
  double sum = 0;
  for(int i = 0; i < N; i++) {
    //一様乱数
    double u = rnd();
    //サンプリング点
    double x = Pinv(u);
    //モンテカルロ積分の中の式
    sum += f(x)/p(x);
  }
  sum /= N;
  std::cout << sum << std::endl;

  return 0;
}
