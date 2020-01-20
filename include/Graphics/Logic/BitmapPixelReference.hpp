#ifndef __StationaryOrbit_Graphics_BitmapPixelReference__
#define __StationaryOrbit_Graphics_BitmapPixelReference__
#include "General/Exception"
#include "../Structure/Point.hpp"
#include "../Interface/IBitmapBuffer.hpp"
#include "../Interface/IImageInfomation.hpp"
#include "../Logic/BitmapPixelGetter.hpp"
#include "../Logic/BitmapPixelSetter.hpp"
namespace StationaryOrbit::Graphics
{

	///	Bitmapのピクセルへの参照を表します。
	class BitmapPixelReference final
		: private BitmapPixelGetter
		, private BitmapPixelSetter
	{
	private:

		BitmapPixelReference(const BitmapPixelGetter& getter, const BitmapPixelSetter& setter);

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
		BitmapPixelReference(IBitmapBuffer& buffer, const IImageInfomation& infomation, const Point& position);

		///	この参照が指し示す変更できない @a BitmapBuffer を取得します。
		IBitmapBuffer& Buffer() { return ((BitmapPixelSetter)*this).Buffer(); }

		///	この参照が指し示す @a BitmapBuffer を取得します。
		const IBitmapBuffer& getBuffer() const { return ((BitmapPixelGetter)*this).getBuffer(); }

		///	この参照が指し示す @a Bitmap の @a BitmapInfomation を取得します。
		const IImageInfomation& getInfomation() const { return ((BitmapPixelGetter)*this).getInfomation(); }

		///	この参照が指し示す座標を @a Point で取得します。
		Point getPosition() const { return ((BitmapPixelGetter)*this).getPosition(); }

		///	この参照が持つ画像のチャンネル数を取得します。
		uint getChannelCount() const { return ((BitmapPixelGetter)*this).getChannelCount(); }

		///	参照先の指定されたチャンネルの値を取得します。
		float getChannel(const uint& channel) const { return ((BitmapPixelGetter)*this).getChannel(channel); }

		///	参照先の指定されたチャンネルの値を設定します。
		void setChannel(const uint& channel, const float& value) { return ((BitmapPixelSetter)*this).setChannel(channel, value); }

		///	参照先の値を @a RGBColor で取得します。
		RGBColor getRGBValue() const { return ((BitmapPixelGetter)*this).getRGBValue(); }

		///	参照先の値を @a RGBColor で設定します。
		void setRGBValue(const RGBColor& value) { ((BitmapPixelSetter)*this).setRGBValue(value); }

		///	参照先の値に @a BitmapPixelGetter の参照先の値を設定します。
		void setValue(const BitmapPixelGetter& value) { ((BitmapPixelSetter)*this).setValue(value); }

		///	この参照に指定されたオフセットを加えた参照に、参照先が存在するかを取得します。
		///
		///	@param	[in]offset
		///	座標のオフセット。
		///
		///	@return
		///	参照先が存在すれば @a true 、存在しなければ @a false が返ります。
		bool HasOffset(const Point& offset) const { return ((BitmapPixelGetter)*this).HasOffset(offset); }

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
		BitmapPixelReference Offset(const Point& offset);

	};

}
#endif // __StationaryOrbit_Graphics_BitmapPixelReference__