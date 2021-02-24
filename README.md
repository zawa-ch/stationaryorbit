# stationaryorbit

![Lisence](https://img.shields.io/github/license/zawa-ch/stationaryorbit)
![Lines of code](https://img.shields.io/tokei/lines/github/zawa-ch/stationaryorbit)

簡単なことを簡単に行うためのライブラリ

## 概要

stationaryorbit はC++で記述された、いくつかのライブラリ モジュールの集合です。  
このソースのビルドにはC++17に準拠したコンパイラが必要になります。  

- core: 基本的な要素、あるいはC++標準ライブラリの拡張
- graphics
  - core: 色と画像の基本的な操作
  - dib: Windows Bitmap形式イメージのサポート
- mathematics: 基本的な数値計算

## このライブラリでできること

- core
  - 値の範囲型(`Range`)
    (c++20にて標準ライブラリに組み込まれる予定の`std::range`と同程度の機能)
  - ハンドラー型(`Delegate`)
  - プロパティ(`Property`)
  - 平面上の点・大きさ・および矩形(`Point2D`/`Rect2DSize`/`Rectangle2D`)
  - true/falseのいずれでもない状態を持つbool値(`Logic`)
  - 二次元ベクトル(`Vector2D`)
  - 0..1間の値を表す型(`Proportion`)
  - データのビット単位でのアクセス(`BitReference`)
  - ビットマスク型(`BitMask`)
- graphics-core
  - 色の表現  
    グレースケール/RGB/CMY/CMYK/YUV/XYZ  
    8/16/32/64bit 整数  
    1.15/1.31/1.63bit 固定小数点数  
    32/64bit 浮動小数点数  
  - 色の合成(`ColorBlender`/`ColorCompositer`)
  - 画像の表現(`Pixmap`/`PixArray`)
  - 画像の反転(`ImageHorizonalFlip`/`ImageVerticalFlip`)
  - 画像のスケーリング(`ImageScaling`)
- graphics-dib
  - Windowsビットマップの読み込み  
    COREHEADER/INFOHEADER  
    RGB(16/24/32ビット)  
  - Windowsビットマップの書き込み  
    COREHEADER/INFOHEADER  
    RGB(16/24/32ビット)  
- mathematics
  - 基本的な多項式の表現(PolynomialFunction)
  - 基本的なテイラー級数の表現(TaylorSeries)
  - ニュートン補完(NewtonCoef)
  - 数値微分(Differencial)
  - 数値積分(Integral)
  - 集合(CrispSet)
  - ファジィ集合(FuzzySet)

## ライセンス

このライブラリは、GNU一般公衆ライセンス v3.0(GPLv3)、またはそれ以降のライセンスで提供されます。  
ライセンスに関する詳細は[LISENCE](./LICENSE)ファイル、または[ライセンス - GNUプロジェクト](http://www.gnu.org/licenses/)のページをご確認ください。  

また、コミット`e4fa05c54a6d7b77884d64b787423cbdf678bde1`以前はGNU劣等一般公衆ライセンス v3.0(LGPLv3)、またはそれ以降で提供されていました。  
それらのコードは引き続きLGPLv3(or later)で提供されます。  
当該コミットのLICENSEファイルを確認することでライセンス条文を確認することができます。  

## 注意: 開発中のリポジトリ

現在このリポジトリは開発中です。そのため、オブジェクトの名前および配置が大きく変化する可能性があります。  
同様の理由で、ドキュメント等も不十分な可能性があります。  
