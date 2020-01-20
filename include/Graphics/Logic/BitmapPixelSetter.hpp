#ifndef __StationaryOrbit_Graphics_BitmapPixelSetter__
#define __StationaryOrbit_Graphics_BitmapPixelSetter__
#include "General/Exception"
#include "../Structure/Point.hpp"
#include "../Interface/IBitmapBuffer.hpp"
#include "../Interface/IImageInfomation.hpp"
#include "../Logic/Graphics.hpp"
#include "../Logic/BitmapPixelGetter.hpp"
namespace StationaryOrbit::Graphics
{

	///	Bitmapのピクセルへの書き込み専用の参照を表します。
	class BitmapPixelSetter
	{
	protected:

		IBitmapBuffer& buf;
		const IImageInfomation& info;
		Point pos;

		static bool HasValue(const IBitmapBuffer& buffer, const Point& position);

	public:

		///	Bitmapのあるピクセルへの参照を作成します。
		///
		///	@param	[in/out]buffer
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
		BitmapPixelSetter(IBitmapBuffer& buffer, const IImageInfomation& infomation, const Point& position);

		///	この参照が指し示す @a BitmapBuffer を取得します。
		IBitmapBuffer& Buffer() { return buf; }

		///	この参照が指し示す @a Bitmap の @a BitmapInfomation を取得します。
		const IImageInfomation& getInfomation() const { return info; }

		///	この参照が指し示す座標を @a Point で取得します。
		Point getPosition() const { return pos; }

		///	この参照が持つ画像のチャンネル数を取得します。
		uint getChannelCount() const;

		///	参照先の指定されたチャンネルの値を設定します。
		void setChannel(const uint& channel, const float& value);

		///	参照先の値を @a RGBColor で設定します。
		void setRGBValue(const RGBColor& value);

		///	参照先の値に @a BitmapPixelGetter の参照先の値を設定します。
		void setValue(const BitmapPixelGetter& reference);

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
		BitmapPixelSetter Offset(const Point& offset) const;

	};

}
#endif // __StationaryOrbit_Graphics_BitmapPixelSetter__