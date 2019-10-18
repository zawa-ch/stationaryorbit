#ifndef __StationaryOrbit_Graphics_Canvas__
#define __StationaryOrbit_Graphics_Canvas__
#include "../Interface/ICanvasBuffer.hpp"
#include "../Logic/Color.hpp"
namespace StationaryOrbit::Graphics
{

	class Canvas
	{
	private:

		///	このオブジェクトに紐付けられたバッファ情報。
		ICanvasBuffer& buffer;

		float getChannel(const Point& pos, size_t ch) const;
		void setChannel(const Point& pos, size_t ch, const float& value);

	public:

		Canvas(ICanvasBuffer& buffer);

		virtual ~Canvas() = default;

		ICanvasBuffer& GetBuffer();

		Color getPixel(const Point& pos) const;

		void setPixel(const Point& pos, const Color& value);

	};

}
#endif // __StationaryOrbit_Graphics_Canvas__