#ifndef __StationaryOrbit_Graphics_BitmapFrame__
#define __StationaryOrbit_Graphics_BitmapFrame__
#include "stationaryorbit/core/delegate"
#include "point.hpp"
#include "bitmapbuffer.hpp"
#include "imageinfomation.hpp"
#include "bitmappixelgetter.hpp"
#include "bitmappixelreference.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	///	画像情報へのピクセル単位でのアクセスを行います。
	///	このクラスは抽象クラスです。
	class BitmapFrame
	{
	public:

		///	空の @a BitmapFrame を初期化します。
		BitmapFrame() = default;

		BitmapFrame(const BitmapFrame& value) = delete;	///< [削除]コピーコンストラクタ

		///	継承されたクラスのデストラクタを使用してオブジェクトを破棄します。
		virtual ~BitmapFrame() = default;

		///	このオブジェクトに関連付けられているバッファを取得します。
		virtual const IBitmapBuffer& getBuffer() const = 0;

		///	このオブジェクトの情報を取得します。
		virtual const IImageInfomation& getInfomation() const = 0;

		///	このオブジェクトの指定されたピクセルの参照を取得します。
		virtual const BitmapPixelGetter getPixel(const Point& position) const = 0;

		///	このオブジェクトに関連付けられているバッファを取得します。
		virtual IBitmapBuffer& Buffer() = 0;

		virtual BitmapPixelReference Index(const Point& position) = 0;

		template<class ... argsT>
		void ForEach(const Delegate<BitmapPixelReference, argsT ...>& action, argsT ... args)
		{
			int sizex = getBuffer().getSize().getX();
			int sizey = getBuffer().getSize().getY();
			for (int y = 0; y < sizey; y++)
			{
				for (int x = 0; x < sizex; x++)
				{
					action.Invoke(Index(Point(x, y)), args...);
				}
			}
		}

		virtual BitmapFrame& Assign(const BitmapFrame& value) = 0;

	};

}
#endif // __StationaryOrbit_Graphics_BitmapFrame__