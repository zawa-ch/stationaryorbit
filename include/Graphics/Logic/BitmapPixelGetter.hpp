#ifndef __StationaryOrbit_Graphics_BitmapPixelGetter__
#define __StationaryOrbit_Graphics_BitmapPixelGetter__
#include "General/Exception"
#include "../Structure/Point.hpp"
#include "../Interface/IBitmapBuffer.hpp"
#include "../Interface/IImageInfomation.hpp"
#include "../Logic/Graphics.hpp"
#include "../Logic/Color.hpp"
namespace StationaryOrbit::Graphics
{

	///	Bitmapのピクセルへの読み取り専用の参照を表します。
	///
	///	@note
	///	このオブジェクトは指定されたオブジェクトへの参照を保持します。
	///	このとき、参照先にオブジェクトが存在するかどうかは確認されません。
	///	そのため、このオブジェクトは返り値として渡すことは推奨されません。
	class BitmapPixelGetter
	{
	protected:

		const IBitmapBuffer& buf;	///< 参照先のBitmapBuffer。
		const IImageInfomation& info;	///< 参照先のImageInfomation。
		Point pos;	///< 参照先の座標。

		///	指定したBitmapBufferの指定した座標が存在するかを取得します。
		///
		///	@param	[in]buffer
		///	参照先の @a BitmapBuffer 。
		///
		///	@param	[in]position
		///	参照先の座標。
		///
		///	@return
		///	参照先にピクセルが存在すれば @a true 、そうでなければ @a false が返ります。
		static bool HasValue(const IBitmapBuffer& buffer, const Point& position);

	public:

		///	Bitmapのあるピクセルへの参照を作成します。
		///
		///	@param	[in]buffer
		///	参照先の @a BitmapBuffer 。
		///
		///	@param	[in]infomation
		///	参照先の @a ImageInfomation 。
		///
		///	@param	[in]position
		///	参照先の座標。
		///
		///	@exception	std::invalid_argument
		///	参照先の座標が @a Bitmap の領域を超えています。
		BitmapPixelGetter(const IBitmapBuffer& buffer, const IImageInfomation& infomation, const Point& position);

		///	この参照が指し示す @a BitmapBuffer を取得します。
		const IBitmapBuffer& getBuffer() const { return buf; }

		///	この参照が指し示す @a Bitmap の @a BitmapInfomation を取得します。
		const IImageInfomation& getInfomation() const { return info; }

		///	この参照が指し示す座標を @a Point で取得します。
		Point getPosition() const { return pos; }

		///	参照先の値を @a Color で取得します。
		Color getValue() const;

		///	この参照に指定されたオフセットを加えた参照に、参照先が存在するかを取得します。
		///
		///	@param	[in]offset
		///	座標のオフセット。
		///
		///	@return
		///	参照先が存在すれば @a true 、存在しなければ @a false が返ります。
		bool HasOffset(const Point& offset) const;

		///	この参照に指定されたオフセットを加えた参照を取得します。
		///
		///	@param	[in]offset
		///	座標のオフセット。
		///
		///	@return
		///	オフセットを加えた参照が返ります。
		///
		///	@exception	std::invalid_argument
		///	参照先の座標が @a Bitmap の領域を超えています。
		BitmapPixelGetter Offset(const Point& offset) const;

	};

}
#endif // __StationaryOrbit_Graphics_BitmapPixelGetter__