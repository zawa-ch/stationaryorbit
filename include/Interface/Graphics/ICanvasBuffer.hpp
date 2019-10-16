#ifndef __StationaryOrbit_Graphics_ICanvasBuffer__
#define __StationaryOrbit_Graphics_ICanvasBuffer__
#include "DataClass/Graphics/Point.hpp"
#include "LogicClass/Graphics/ImageInfomation.hpp"
namespace StationaryOrbit
{
namespace Graphics
{

    class ICanvasBuffer
    {
    public:

        ///	キャンバスの画像情報を取得します。
		virtual ImageInfomation getInfomation() const = 0;

		///	指定された1ピクセル・1チャネルにおける値を取得します。
		///	取得された値は dest に書き込まれます。
		///	書き込まれるサイズはこのオブジェクトを初期化する際に指定したフォーマットに依存します。
		virtual void getPixel(void* dest, const Point& pos, size_t ch) const = 0;

		///	指定された1ピクセル・1チャネルにおける値を設定します。
		///	読み込まれるサイズはこのオブジェクトを初期化する際に指定したフォーマットに依存します。
		virtual void setPixel(const void* value, const Point& pos, size_t ch) = 0;

    };

}
}
#endif // __StationaryOrbit_Graphics_ICanvasBuffer__