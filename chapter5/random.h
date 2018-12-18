#ifndef RANDOM_H
#define RANDOM_H


//メルセンヌ・ツイスタを乱数生成器として使用する
std::random_device rnd_dev; //シードを決めるデバイス乱数
std::mt19937 mt(rnd_dev()); //メルセンヌ・ツイスタ
std::uniform_real_distribution<> dist(0, 1); //[0, 1]の一様乱数
inline double rnd() {
  return dist(mt);
}
#endif
