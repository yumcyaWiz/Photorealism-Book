#ifndef RANDOM_H
#define RANDOM_H


//メルセンヌ・ツイスタを乱数生成器として使用する
std::random_device rnd_dev; //シードを決めるデバイス乱数
std::mt19937 mt(rnd_dev()); //メルセンヌ・ツイスタ
std::uniform_real_distribution<> dist(0, 1); //[0, 1]の一様乱数
inline double rnd() {
  return dist(mt);
}


//半径1の円上で点を一様サンプリングする
//x: サンプリングされたx座標の値
//y: サンプリングされｔy座標の値
void sampleDisk(double& x, double& y) {
  double u1 = rnd();
  double u2 = rnd();
  x = std::sqrt(u1)*std::cos(2*M_PI*u2);
  y = std::sqrt(u1)*std::sin(2*M_PI*u2);
}
#endif
