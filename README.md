# Photorealism-Book
C95で販売した"Photorealism"に出てくるコード例、画像の置き場です

## フォルダ構造
chapter2は第2章で出てくるコード例に対応します。
chapter4, chapter5 ...も同様です。

imgには本文中に出てきたレンダリング画像が入っています。

## 実行方法
chapter2, .., chapter5までは他に必要なファイルはありません。コンパイル方法はg\+\+を使う場合
```bash
g++ -fopenmp -O3 -mtune=native -march=native path_tracing.cpp
```
をターミナルに打ち込むことで行えます。すると実行ファイルが生成されるので、あとはそれを実行すればレンダリングが始まり、終わるとPPM画像が同じフォルダに出力されます。

chapter6のIBLを使う部分ではstb_image.hを同じフォルダに入れる必要があります。また、IBLの光源として利用するHDR画像を用意する必要があります。
