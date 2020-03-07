#ifndef __StationaryOrbit_Graphics_Bitmap__
#define __StationaryOrbit_Graphics_Bitmap__
#include "bitmapframe.hpp"
#include "bitmapbuffer.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	template<class T = float>
	class Bitmap final
		: virtual public BitmapFrame<T>
	{
	public: // type

		typedef BitmapFrame<T> FrameType;
		typedef IBitmapBuffer<T> IBufferType;
		typedef BitmapBuffer<T> BufferType;
		typedef BitmapPixelReference<T> PxRefType;

	private: // contains

		BufferType buf;
		ImageInfomation info;
	
	public: // constructor

		Bitmap() = default;

		explicit Bitmap(const ImageInfomation& infomation);

		Bitmap(const FrameType& value) : buf(value.Buffer()), info(value.Infomation()) {}

	public: // implement BitmapFrame

		///	このオブジェクトに関連付けられているバッファを取得します。
		const IBufferType& getBuffer() const { return buf; }

		///	このオブジェクトに関連付けられているバッファを取得します。
		IBufferType& getBuffer() { return buf; }

		///	このオブジェクトの情報を取得します。
		const IImageInfomation& getInfomation() const { return info; }

		///	このオブジェクトの指定されたピクセルの参照を取得します。
		PxRefType Index(const Point& position) { return PxRefType(buf, info, position); }

		///	このオブジェクトの指定されたピクセルの参照を取得します。
		const PxRefType Index(const Point& position) const { return PxRefType(buf, info, position); }

		FrameType& Assign(const FrameType& value) { return *this = Bitmap<T>(value); }

		FrameType& operator=(const FrameType& value) { return *this = Bitmap<T>(value); }

	};

}
#endif // __StationaryOrbit_Graphics_Bitmap__