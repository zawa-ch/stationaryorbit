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

		BitmapFrame() = default;

		BitmapFrame(const BitmapFrame& value) = delete;

		BitmapFrame(BitmapFrame&&) = delete;

		virtual ~BitmapFrame() = default;

		virtual const IBitmapBuffer& getBuffer() const = 0;

		virtual const IImageInfomation& getInfomation() const = 0;

		virtual const BitmapPixelGetter getPixel(const Point& position) const = 0;

		virtual IBitmapBuffer& Buffer() = 0;

		virtual BitmapPixelReference IndexAt(const Point& position) = 0;

		template<class ... argsT>
		void ForEach(const Delegate<BitmapPixelReference, argsT ...>& action, argsT ... args)
		{
			int sizex = getBuffer().getSize().getX();
			int sizey = getBuffer().getSize().getY();
			for (int y = 0; y < sizey; y++)
			{
				for (int x = 0; x < sizex; x++)
				{
					action.Invoke(IndexAt(Point(x, y)), args...);
				}
			}
		}

		virtual BitmapFrame& Assign(const BitmapFrame& value) = 0;

	};

}
#endif // __StationaryOrbit_Graphics_BitmapFrame__