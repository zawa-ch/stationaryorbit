#ifndef __StationaryOrbit_Graphics_IBitmapBuffer__
#define __StationaryOrbit_Graphics_IBitmapBuffer__
#include <cstddef>
#include "../Structure/Point.hpp"
namespace StationaryOrbit::Graphics
{

	///	画像情報を保持するための記憶領域を提供し、アクセスを行うためのメソッドを実装します。
    class IBitmapBuffer
    {
    public:
		
		///	このバッファの画像サイズを取得します。
		virtual Point getSize() const = 0;

		///	このバッファのチャネル数を取得します。
		virtual size_t getChannel() const = 0;

		///	指定された1ピクセル・1チャネルにおける値を取得します。
		virtual float getPixel(const Point& pos, size_t ch) const = 0;

		///	指定された1ピクセル・1チャネルにおける値を設定します。
		virtual void setPixel(const Point& pos, size_t ch, const float& value) = 0;

    };

}
#endif // __StationaryOrbit_Graphics_IBitmapBuffer__