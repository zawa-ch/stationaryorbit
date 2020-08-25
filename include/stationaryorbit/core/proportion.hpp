#ifndef __stationaryorbit_core_proportion__
#define __stationaryorbit_core_proportion__
#include <cstdint>
#include <type_traits>
#include <ratio>
#include <stdexcept>
namespace zawa_ch::StationaryOrbit
{
	///	0.0から1.0の値を整数または浮動小数点数を用いて保持します。
	///	@param	Tp
	///	値の格納に用いる型。
	///	@note
	///	@a Proportion 型は0.0以上1.0以下の数値を型 @a Tp に格納できるようにします。
	template <class Tp>
	struct Proportion
	{
		static_assert((std::is_floating_point_v<Tp>)||(std::is_unsigned_v<Tp>), "テンプレート型 Tp は符号なし算術型または浮動小数点数型のいずれかである必要があります。");
	public:
		///	この型の値の表現のために内部で使用されている型。
		typedef Tp ValueType;
	private:
		ValueType _value;
		constexpr explicit Proportion(const ValueType& init) : _value(init) {}
	public:
		constexpr Proportion() : _value() {}
		template<class fromT>
		constexpr explicit Proportion(const Proportion<fromT>& from) : Proportion(from.template CastTo<Tp>()) {}
		constexpr Proportion(const Proportion<Tp>&) = default;
		constexpr Proportion(Proportion<Tp>&&) = default;
		~Proportion() = default;
	public:
		///	このオブジェクトが正規化されているかどうかを取得します。
		///	@note
		///	@a Tp が符号なし算術型の場合、常に @a true か返ります。
		constexpr bool IsNormalized() const { return (Min()._value < _value)&&(_value < Max()._value); }
		constexpr Proportion<Tp> Normalize() const { return Proportion((Min()._value <= _value)?((_value <= Max()._value)?(_value):(Max()._value)):(Min()._value)); }
		constexpr Proportion<Tp> Abs() const { return this->operator+(); }
		constexpr Proportion<Tp> Negative() const { return this->operator-(); }
	public:
		constexpr static Proportion<Tp> From(const ValueType& value)
		{
			return Proportion<Tp>(value);
		}
		///	この型で表すことのできる最大の値を取得します。
		///	@note
		///
		constexpr static Proportion<Tp> Max()
		{
			static_assert((std::is_floating_point_v<Tp>)||(std::is_unsigned_v<Tp>), "テンプレートの特殊化に失敗しました(テンプレート型 Tp は符号なし算術型または浮動小数点数型のいずれでもありません)。");
			if constexpr (std::is_floating_point_v<Tp>) { return Proportion(ValueType(1.0)); }
			if constexpr (std::is_unsigned_v<Tp>) { return Proportion(std::numeric_limits<Tp>::max()); }
		}
		///	この型で表すことのできる最小の値を取得します。
		constexpr static Proportion<Tp> Min()
		{
			static_assert((std::is_floating_point_v<Tp>)||(std::is_unsigned_v<Tp>), "テンプレートの特殊化に失敗しました(テンプレート型 Tp は符号なし算術型または浮動小数点数型のいずれでもありません)。");
			if constexpr (std::is_floating_point_v<Tp>) { return Proportion(ValueType(0.0)); }
			if constexpr (std::is_unsigned_v<Tp>) { return Proportion(0); }
		}
		///	この型で表すことのできる零値を取得します。
		constexpr static Proportion<Tp> Zero()
		{
			static_assert((std::is_floating_point_v<Tp>)||(std::is_signed_v<Tp>), "テンプレートの特殊化に失敗しました(テンプレート型 Tp は符号なし算術型または浮動小数点数型のいずれでもありません)。");
			if constexpr (std::is_floating_point_v<Tp>) { return Proportion(ValueType(0.0)); }
			if constexpr (std::is_signed_v<Tp>) { return Proportion(0); }
		}

		// TODO: 各種数値計算時のオーバーフローを検出する

		constexpr Proportion<Tp> operator+() const { return Proportion(+_value); }
		constexpr Proportion<Tp> operator-() const { return Proportion(-_value); }
		constexpr Proportion<Tp> operator+(const Proportion<Tp>& other) const { return Proportion(_value + other._value); }
		constexpr Proportion<Tp> operator-(const Proportion<Tp>& other) const { return Proportion(_value - other._value); }
		constexpr Proportion<Tp> operator*(const Proportion<Tp>& other) const { return Proportion(Multiple(_value, other._value)); }
		constexpr Proportion<Tp> operator/(const Proportion<Tp>& other) const { return Proportion(Fraction(_value, other._value)); }
		constexpr Proportion<Tp>& operator+=(const Proportion<Tp>& other) const { return *this = Proportion(_value + other._value); }
		constexpr Proportion<Tp>& operator-=(const Proportion<Tp>& other) const { return *this = Proportion(_value - other._value); }
		constexpr Proportion<Tp>& operator*=(const Proportion<Tp>& other) const { return *this = Proportion(Multiple(_value, other._value)); }
		constexpr Proportion<Tp>& operator/=(const Proportion<Tp>& other) const { return *this = Proportion(Fraction(_value, other._value)); }

		constexpr bool Equals(const Proportion<Tp>& other) const { return _value == other._value; }
		constexpr bool operator==(const Proportion<Tp>& other) const { return Equals(other); }
		constexpr bool operator!=(const Proportion<Tp>& other) const { return !Equals(other); }

		constexpr int Compare(const Proportion<Tp>& other) const
		{
			if (_value > other._value) { return 1; }
			else if (_value < other._value) { return -1; }
			else { return 0; }
		}
		constexpr bool operator<(const Proportion<Tp>& other) const { return Compare(other) < 0; }
		constexpr bool operator>(const Proportion<Tp>& other) const { return Compare(other) > 0; }
		constexpr bool operator<=(const Proportion<Tp>& other) const { return Compare(other) <= 0; }
		constexpr bool operator>=(const Proportion<Tp>& other) const { return Compare(other) >= 0; }

		Proportion<Tp>& operator=(const Proportion<Tp>& value) = default;
		Proportion<Tp>& operator=(Proportion<Tp>&& value) = default;

		constexpr explicit operator ValueType() const { return _value; }
		///	内部に使用する型のキャストを行います。
		///	@param	castT
		///	変換先の型。返ってくる値の型は @a Proportion<castT> となります。
		template<class castT>
		constexpr Proportion<castT> CastTo() const
		{
			static_assert((std::is_floating_point_v<Tp>)||(std::is_unsigned_v<Tp>), "テンプレートの特殊化に失敗しました(テンプレート型 Tp は符号なし算術型または浮動小数点数型のいずれでもありません)。");
			static_assert((std::is_floating_point_v<castT>)||(std::is_unsigned_v<castT>), "テンプレートの特殊化に失敗しました(テンプレート型 castT は符号なし算術型または浮動小数点数型のいずれでもありません)。");
			if constexpr (std::is_floating_point_v<Tp>)
			{
				if ((_value == std::numeric_limits<Tp>::quiet_NaN()) || (_value == std::numeric_limits<Tp>::signaling_NaN()))
				{ throw std::invalid_argument("指定する値はNaNであってはなりません。"); }
				// float -> float
				if constexpr (std::is_floating_point_v<castT>) { return Proportion<castT>(castT(_value)); }
				// float -> integer
				if constexpr (std::is_unsigned_v<castT>)
				{
					if ((_value < 0.0) || (1.0 < _value)) { throw std::invalid_argument("指定する値は0.0以上1.0以下である必要があります。"); }
					return Proportion<castT>(castT(_value * Proportion<castT>::Max()._value));
				}
			}
			if constexpr (std::is_unsigned_v<Tp>)
			{
				// integer -> float
				if constexpr (std::is_floating_point_v<castT>) { return Proportion<castT>(castT(_value) / Max()._value); }
				// integer -> integer
				if constexpr (std::is_unsigned_v<castT>)
				{
					if constexpr (sizeof(Tp) < sizeof(castT)) { return Proportion<castT>(castT(_value) * (Proportion<castT>::Max()._value / Max()._value)); }
					else { return Proportion<castT>(castT(_value / (Max()._value / Proportion<castT>::Max()._value))); }
				}
			}
		}

	private:
		///	除算を行います。
		///	@param	numerator
		///	除算時の被除数。
		///	@param	denominator
		///	除算時の除数。
		///	@exception
		///	std::invalid_argument
		///	0で除算することはできません。
		///	内部の型が整数型のときは0除算の結果を定義できないため、この例外がスローされます。
		///	std::overflow_error
		///	被除数が除数を超えました。
		///	内部の型が整数型のときは値域を超える値を表現することはできないため、この例外がスローされます。
		static constexpr ValueType Fraction(const ValueType& numerator, const ValueType& denominator)
		{
			if constexpr (std::is_floating_point_v<ValueType>) { return numerator / denominator; }
			if constexpr ((std::is_integral_v<ValueType>)&&(std::is_unsigned_v<ValueType>))
			{
				if (denominator == 0U) { throw std::invalid_argument("分母に0を指定することはできません。"); }
				if (denominator < numerator) { throw std::overflow_error("計算結果はこの型で表せる範囲を超えています。"); }
				ValueType unit = std::numeric_limits<ValueType>::max() / denominator;
				ValueType result = unit * numerator;
				ValueType surplus = std::numeric_limits<ValueType>::max() % denominator;
				if (surplus != 0U)
				{
					ValueType dv = 0U;
					ValueType md = 0U;
					for(size_t i = (sizeof(ValueType) * 8U); 0 < i; i--)
					{
						dv *= 2U;
						md *= 2U;
						if (numerator & (ValueType(1U) << (i - 1)))
						{
							md += surplus;
						}
						dv += md / denominator;
						md %= denominator;
					}
					result += dv;
				}
				return result;
			}
			if constexpr (std::is_same_v<ValueType, bool>)
			{
				if (denominator == false) { throw std::invalid_argument("分母に0を指定することはできません。"); }
				return numerator;
			}
		}
		static constexpr ValueType Multiple(const ValueType& left, const ValueType& right)
		{
			if constexpr (std::is_floating_point_v<ValueType>) { return left * right; }
			if constexpr ((std::is_integral_v<ValueType>)&&(std::is_unsigned_v<ValueType>))
			{
				ValueType result = 0UL;
				for(size_t i = 0U; i < (sizeof(ValueType) * 8U); i++)
				{
					ValueType ad = 0U;
					if (left & (ValueType(1U) << (i)))
					{
						ad = right;
					}
					bool cr = ((ad % 2U) != 0) && ((result % 2U) != 0);
					result >>= 1;
					ad >>= 1;
					result += ad + (cr?1U:0U);
				}
				return result;
			}
			if constexpr (std::is_same_v<ValueType, bool>)
			{
				return left && right;
			}
		}
	};
}
#endif // __stationaryorbit_core_proportion__
