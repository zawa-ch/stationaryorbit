#ifndef __stationaryorbit_graphics_core_bitmapframe__
#define __stationaryorbit_graphics_core_bitmapframe__
#include "stationaryorbit/core/numeral"
#include "stationaryorbit/core/delegate"
#include "point.hpp"
#include "bitmapbuffer.hpp"
#include "imageinfomation.hpp"
#include "bitmappixelreference.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	///	画像情報へのピクセル単位でのアクセスを行います。
	///	このクラスは抽象クラスです。
	template<class T>
	class BitmapFrame
	{
	public:

		typedef IBitmapBuffer<T> IBufferType;
		typedef BitmapPixelReference<T> PxRefType;

		virtual ~BitmapFrame() = default;

		///	このオブジェクトに関連付けられているバッファを取得します。
		virtual IBufferType& Buffer() = 0;

		///	このオブジェクトに関連付けられているバッファを取得します。
		virtual const IBufferType& Buffer() const = 0;

		///	このオブジェクトの情報を取得します。
		virtual const IImageInfomation& Infomation() const = 0;

		///	このオブジェクトの指定されたピクセルの参照を取得します。
		virtual PxRefType Index(const Point& position) = 0;

		///	このオブジェクトの指定されたピクセルの参照を取得します。
		virtual const PxRefType Index(const Point& position) const = 0;

		template<class ... argsT>
		void ForEach(const Delegate<PxRefType, argsT ...>& action, argsT ... args)
		{
			for (auto y : Range<size_t>(0, Buffer().getVerticalSize()))
			{
				for (auto x : Range<size_t>(0, Buffer().getHorizonalSize()))
				{
					action.Invoke(Index(Point(x, y)), args...);
				}
			}
		}

		virtual BitmapFrame<T>& Assign(const BitmapFrame<T>& value) = 0;

	};

}
#endif // __stationaryorbit_graphics_core_bitmapframe__