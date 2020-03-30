# stationaryorbit

個人製作の雑多なライブラリ群

## 概要

stationaryorbit はC++で記述された、いくつかのライブラリ モジュールの集合です。  
このソースのビルドにはC++17に準拠したコンパイラが必要になります。  

- core: 基本的な要素、あるいはC++標準ライブラリの拡張
- exception: ライブラリで使用される基本的な例外
- graphics
  - core: 画像の入出力と基本的な加工
  - dib: Windows Bitmap形式イメージのサポート
- analysis: 基本的な数値計算

## このライブラリでできること

- core
  - 値の範囲型(Range)
    (c++20にて標準ライブラリに組み込まれる予定の`std::range`と同程度の機能)
  - ハンドラー型(Delegate)
  - プロパティ(Property)
  - 平面上の点・大きさ・および矩形(Point/RectangleSize/Rectangle)
  - true/falseのいずれでもない状態を持つbool値(TristateBoolean)
  - 二次元ベクトル(Vector2D)
  - 0..1間の値を表す型(FractionalDec)
  - データのビット単位でのアクセス(BitReference)
  - ビットマスク型(BitMask)
- graphics-core
  - ビットマップ画像の表現
  - ビットマップの反転・切り抜き・拡大縮小の加工
- graphics-dib
  - Windowsビットマップの読み込み  
    RGB(16/24/32ビット)
  - Windowsビットマップの書き込み  
    RGB(16/24/32ビット)
- analysis
  - 基本的な多項式の表現(PolynomialFunction)
  - 基本的なテイラー級数の表現(TaylorSeries)
  - ニュートン補完(NewtonCoef)
  - 数値微分(Differencial)
  - 数値積分(Integral)
  - 集合(CrispSet)
  - ファジィ集合(FuzzySet)

## 注意: 開発中のリポジトリ

現在このリポジトリは開発中です。そのため、オブジェクトの名前および配置が大きく変化する可能性があります。  
同様の理由で、ドキュメント等も不十分な可能性があります。  
