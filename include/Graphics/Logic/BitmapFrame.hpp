#ifndef __StationaryOrbit_Graphics_BitmapFrame__
#define __StationaryOrbit_Graphics_BitmapFrame__
#include "../Interface/IBitmapBuffer.hpp"
#include "../Logic/Color.hpp"
#include "../Logic/ImageInfomation.hpp"
namespace StationaryOrbit::Graphics
{

	///	画像情報へのピクセル単位でのアクセスを行います。
	class BitmapFrame
	{
	private:

		IBitmapBuffer& _buffer;

		IImageInfomation& _info;

	public:

		BitmapFrame(IBitmapBuffer& buffer, IImageInfomation& info);

		virtual ~BitmapFrame() = default;

		IBitmapBuffer& getBuffer() { return _buffer; }

		const IImageInfomation& getInfomation() const { return _info; }

		Color getPixel(const Point& pos) const;

		void setPixel(const Point& pos, const Color& value);

	};

}
#endif // __StationaryOrbit_Graphics_BitmapFrame__