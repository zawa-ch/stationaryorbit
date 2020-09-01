#ifndef __stationaryorbit_core_fixedpoint__
#define __stationaryorbit_core_fixedpoint__
#include <cstddef>
#include <cstdint>
#include <cmath>
#include <type_traits>
#include "fundamental.hpp"
#include "range.hpp"
namespace zawa_ch::StationaryOrbit
{
	///	固定小数点数を表します。
	///	@param	Tp
	///	値の格納に用いる型。
	///	@param	Ql
	///	小数部分のビット長。
	///	@note
	///	小数部分のビット長 @a Ql は現在型 @a Tp のビット長を超えることはできませんが、今後の拡張によって実装される可能性はあります。
	///	テンプレート型 @a Tp は符号付きの整数型を使用することはできませんが、今後の拡張によって実装される可能性はあります。
	template<class Tp, size_t Ql>
	class FixedPoint final
	{
		static_assert(std::is_integral_v<Tp>, "テンプレート型 Tp は整数型である必要があります。");
		static_assert(std::is_unsigned_v<Tp>, "テンプレート型 Tp は符号なし算術型である必要があります。");
		static_assert(Ql <= (sizeof(Tp) * 8U), "小数のビット長は型のビット長を超えることはできません。");
	public:
		///	この型の値の表現のために内部で使用されている型。
		typedef Tp ValueType;
		constexpr static const size_t QLength = Ql;
	private:
		ValueType _value;
		constexpr FixedPoint(const Tp& value, const Unit&) : _value(value) {}
	public:
		///	既定の @a FixedPoint オブジェクトを作成します。
		constexpr FixedPoint() : _value() {}
		constexpr explicit FixedPoint(const double& value) : _value(convertFromFloat(value)) {}
		///	ほかの @a FixedPoint テンプレート型から変換します。
		template<class fromTp, size_t fromQ>
		constexpr explicit FixedPoint(const FixedPoint<fromTp, fromQ>& from) : FixedPoint(from.template CastTo<Tp, Ql>()) {}
		constexpr FixedPoint(const FixedPoint<Tp, Ql>&) = default;
		constexpr FixedPoint(FixedPoint<Tp, Ql>&&) = default;
		~FixedPoint() = default;
	public:
		[[nodiscard]] constexpr FixedPoint<Tp, Ql> Add(const FixedPoint<Tp, Ql>& other) const { return DirectConstruct(_value + other._value); }
		[[nodiscard]] constexpr FixedPoint<Tp, Ql> Sub(const FixedPoint<Tp, Ql>& other) const { return DirectConstruct(_value - other._value); }
		[[nodiscard]] constexpr FixedPoint<Tp, Ql> Multiple(const FixedPoint<Tp, Ql>& other) const
		{
			const size_t width = sizeof(Tp) * 8U;
			const size_t point = width - Ql;
			auto result = Tp();
			for (auto i : Range<size_t>(0U, width))
			{
				result |=
					((other._value & (1U << (width - 1U - i))) != 0U)
					? (
						(0 <= std::make_signed_t<size_t>(point - 1 - i))
						? (_value << (point - 1U - i))
						: (_value >> (i + 1U - point))
					)
					: (0U);
			}
			return DirectConstruct(result);
		}
		[[nodiscard]] constexpr FixedPoint<Tp, Ql> Divide(const FixedPoint<Tp, Ql>& other) const
		{
			auto result = Tp(_value / other._value);
			auto remain = Tp(_value % other._value);
			for (auto i : Range<size_t>(0U, QLength))
			{
				remain *= 2U;
				result = (result * 2U) + (remain / other._value);
				remain %= other._value;
			}
			// TODO: 端数処理が必要な場合ここに記述する(何も記述しなかった場合端数は切り捨てられる)
			return DirectConstruct(result);
		}
		[[nodiscard]] constexpr FixedPoint<Tp, Ql> SaturateAdd(const FixedPoint<Tp, Ql>& other) const
		{
			if (_value < (Max()._value - other._value)) { return Add(other); }
			else { return Max(); }
		}
		[[nodiscard]] constexpr FixedPoint<Tp, Ql> SaturateSub(const FixedPoint<Tp, Ql>& other) const
		{
			if ((Min()._value + other._value) < _value) { return Sub(other); }
			else { return Min(); }
		}
		[[nodiscard]] constexpr FixedPoint<Tp, Ql> SaturateMultiple(const FixedPoint<Tp, Ql>& other) const
		{
			// TODO: 乗算のオーバーフロー検出処理の実装
			return Multiple(other);
		}
		[[nodiscard]] constexpr FixedPoint<Tp, Ql> SaturateDivide(const FixedPoint<Tp, Ql>& other) const
		{
			// TODO: 除算のオーバーフロー検出処理の実装
			return Divide(other);
		}

		[[nodiscard]] constexpr FixedPoint<Tp, Ql> operator+(const FixedPoint<Tp, Ql>& other) const { return Add(other); }
		[[nodiscard]] constexpr FixedPoint<Tp, Ql> operator-(const FixedPoint<Tp, Ql>& other) const { return Sub(other); }
		[[nodiscard]] constexpr FixedPoint<Tp, Ql> operator*(const FixedPoint<Tp, Ql>& other) const { return Multiple(other); }
		[[nodiscard]] constexpr FixedPoint<Tp, Ql> operator/(const FixedPoint<Tp, Ql>& other) const { return Divide(other); }
		constexpr FixedPoint<Tp, Ql>& operator+=(const FixedPoint<Tp, Ql>& other) { return *this = *this + other; }
		constexpr FixedPoint<Tp, Ql>& operator-=(const FixedPoint<Tp, Ql>& other) { return *this = *this - other; }
		constexpr FixedPoint<Tp, Ql>& operator*=(const FixedPoint<Tp, Ql>& other) { return *this = *this * other; }
		constexpr FixedPoint<Tp, Ql>& operator/=(const FixedPoint<Tp, Ql>& other) { return *this = *this / other; }

		constexpr bool Equals(const FixedPoint<Tp, Ql>& other) const { return _value == other._value; }
		constexpr bool operator==(const FixedPoint<Tp, Ql>& other) const { return Equals(other); }
		constexpr bool operator!=(const FixedPoint<Tp, Ql>& other) const { return !Equals(other); }

		constexpr int Compare(const FixedPoint<Tp, Ql>& other) const
		{
			if (_value > other._value) { return 1; }
			else if (_value < other._value) { return -1; }
			else { return 0; }
		}
		constexpr bool operator<(const FixedPoint<Tp, Ql>& other) const { return Compare(other) < 0; }
		constexpr bool operator>(const FixedPoint<Tp, Ql>& other) const { return Compare(other) > 0; }
		constexpr bool operator<=(const FixedPoint<Tp, Ql>& other) const { return Compare(other) <= 0; }
		constexpr bool operator>=(const FixedPoint<Tp, Ql>& other) const { return Compare(other) >= 0; }

		FixedPoint<Tp, Ql>& operator=(const FixedPoint<Tp, Ql>& value) = default;
		FixedPoint<Tp, Ql>& operator=(FixedPoint<Tp, Ql>&& value) = default;

		template<class castT, size_t castQ> [[nodiscard]] constexpr FixedPoint<castT, castQ> CastTo() const
		{
			if constexpr (castQ == Ql) { return FixedPoint<castT, castQ>::DirectConstruct(castT(_value)); }
			if constexpr (castQ < Ql) { return FixedPoint<castT, castQ>::DirectConstruct(castT(_value >> (Ql - castQ))); }
			if constexpr (castQ > Ql) { return FixedPoint<castT, castQ>::DirectConstruct(castT(_value << (castQ - Ql))); }
		}
		[[nodiscard]] constexpr explicit operator float() const { return convertToFloat<float>(); }
		[[nodiscard]] constexpr explicit operator double() const { return convertToFloat<double>(); }

	public:
		///	この型で表すことのできる最大の値を取得します。
		[[nodiscard]] constexpr static FixedPoint<Tp, Ql> Max() { return DirectConstruct(std::numeric_limits<Tp>::max()); }
		///	この型で表すことのできる最小の値を取得します。
		[[nodiscard]] constexpr static FixedPoint<Tp, Ql> Min() { return DirectConstruct(std::numeric_limits<Tp>::min()); }
		///	この型で表すことのできる零値を取得します。
		[[nodiscard]] constexpr static FixedPoint<Tp, Ql> Zero() { return DirectConstruct(0); }
		///	この型で表すことのできる最小の刻み幅を取得します。
		[[nodiscard]] constexpr static FixedPoint<Tp, Ql> Epsiron() { return DirectConstruct(1); }
		///	空の @a FixedPoint を取得します。
		[[nodiscard]] constexpr static FixedPoint<Tp, Ql> Empty() { return FixedPoint<Tp, Ql> {}; }
		///	@a FixedPoint を直接構築します。
		[[nodiscard]] constexpr static FixedPoint<Tp, Ql> DirectConstruct(const ValueType& value) { return FixedPoint<Tp, Ql>(value, UnitValue); }

	private:
		template<class fromT> constexpr static Tp convertFromInteger(const fromT& from)
		{
			if (from <= (std::numeric_limits<Tp>::max() >> Ql)) { return Tp(from << Ql); }
			else { throw std::overflow_error("指定された値がこの型で表せる範囲を超えています。"); }
		}
		template<class fromT> constexpr static Tp convertFromFloat(const fromT& from)
		{
			if ((from == std::numeric_limits<fromT>::quiet_NaN()) || (from == std::numeric_limits<fromT>::signaling_NaN())) { throw std::invalid_argument("指定する値はNaNであってはなりません。"); }
			if ((fromT(Min()) <= from) && (from <= fromT(Max()))) { return Tp(from * std::exp2(QLength)); }
			else { throw std::overflow_error("指定された値がこの型で表せる範囲を超えています。"); }
		}
		template<class castT> constexpr castT convertToFloat() const
		{
			return castT(castT(_value) / std::exp2(QLength));
		}
	};
}
#endif // __stationaryorbit_core_fixedpoint__
