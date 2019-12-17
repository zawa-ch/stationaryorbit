#ifndef __StationaryOrbit_Graphics_RGBColor__
#define __StationaryOrbit_Graphics_RGBColor__
namespace StationaryOrbit::Graphics
{

	///	赤(Red), 緑(Green), 青(Blue)の三要素で表される色。
	struct RGBColor final
	{
	private:

		float _r;
		float _g;
		float _b;

	public:

		///	空のRGBColorを初期化します。
		RGBColor() = default;

		///	RGB値を指定してRGBColorを初期化します。
		RGBColor(const float& r, const float& g, const float& b);

		~RGBColor() = default;

		///	このオブジェクトの赤要素を取得します。
		float getR() const;

		///	このオブジェクトの緑要素を取得します。
		float getG() const;

		///	このオブジェクトの青要素を取得します。
		float getB() const;

		///	このオブジェクトが正規化されているかを取得します。
		bool IsNormalized() const;

		///	このオブジェクトを正規化したRGBColorを取得します。
		RGBColor Normalize() const;

		///	二つのオブジェクトの和を算出します。
		RGBColor Add(const RGBColor& value) const;
		RGBColor operator+(const RGBColor& value) const { return Add(value); }

		///	二つのオブジェクトの差を算出します。
		RGBColor Sub(const RGBColor& value) const;
		RGBColor operator-(const RGBColor& value) const { return Sub(value); }

		///	二つのオブジェクトの積を算出します。
		RGBColor Multiple(const RGBColor& value) const;
		RGBColor operator*(const RGBColor& value) const { return Multiple(value); }

		///	このオブジェクトと実数の積を算出します。
		RGBColor Multiple(const float& value) const;
		RGBColor operator*(const float& value) const { return Multiple(value); }

		///	このオブジェクトと実数の商を算出します。
		RGBColor Divide(const float& value) const;
		RGBColor operator/(const float& value) const { return Divide(value); }

		///	このオブジェクトの値を反転した値を取得します。
		RGBColor Invert() const;
		RGBColor operator~() const { return Invert(); }

		///	指定されたオブジェクトがこのオブジェクトと等価であることを判定します。
		bool Equals(const RGBColor& value) const;
		bool operator==(const RGBColor& value) const { return Equals(value); }
		bool operator!=(const RGBColor& value) const { return !Equals(value); }

	};

}
#endif // __StationaryOrbit_Graphics_RGBColor__