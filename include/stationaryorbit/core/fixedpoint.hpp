#ifndef __stationaryorbit_core_fixedpoint__
#define __stationaryorbit_core_fixedpoint__
#include <cstddef>
#include <cstdint>
#include <cmath>
#include <type_traits>
#include "range.hpp"
namespace zawa_ch::StationaryOrbit
{
	///	固定小数点数を表します。
	///	@param	Tp
	///	値の格納に用いる型。
	///	@param	Q
	///	小数部分のビット長。
	///	@note
	///	小数部分のビット長 @a Q は現在型 @a Tp のビット長を超えることはできませんが、今後の拡張によって実装される可能性はあります。
	template<class Tp, size_t Q>
	class FixedPoint final
	{
		static_assert(std::is_integral_v<Tp>, "テンプレート型 Tp は整数型である必要があります。");
		static_assert(Q <= (sizeof(Tp) * 8U), "小数のビット長は型のビット長を超えることはできません。");
	public:
		///	この型の値の表現のために内部で使用されている型。
		typedef Tp ValueType;
		constexpr const size_t QLength = Q;
	private:
		ValueType _value;
		constexpr static FixedPoint<Tp, Q> DirectConstruct(const ValueType& value) { return { value }; }
	public:
		///	既定の @a FixedPoint オブジェクトを作成します。
		constexpr FixedPoint() : _value() {}
		constexpr explicit FixedPoint(const float& value) : _value(convertFromFloat(value)) {}
		constexpr explicit FixedPoint(const double& value) : _value(convertFromFloat(value)) {}
		///	ほかの @a FixedPoint テンプレート型から変換します。
		template<class fromTp, size_t fromQ>
		constexpr explicit FixedPoint(const FixedPoint<fromTp, fromQ>& from) : FixedPoint(from.template CastTo<Tp, Q>()) {}
		constexpr FixedPoint(const FixedPoint<Tp, Q>&) = default;
		constexpr FixedPoint(FixedPoint<Tp, Q>&&) = default;
		constexpr ~FixedPoint() = default;
	public:
		///	この型で表すことのできる最大の値を取得します。
		constexpr static FixedPoint<Tp, Q> Max() { return FixedPoint<Tp, Q> { std::numeric_limits<Tp>::max() }; }
		///	この型で表すことのできる最小の値を取得します。
		constexpr static FixedPoint<Tp, Q> Min() { return FixedPoint<Tp, Q> { std::numeric_limits<Tp>::min() }; }
		///	この型で表すことのできる零値を取得します。
		constexpr static FixedPoint<Tp, Q> Zero() { return FixedPoint<Tp, Q> { 0 }; }
		///	空の @a FixedPoint を取得します。
		constexpr static FixedPoint<Tp, Q> Empty() { return FixedPoint<Tp, Q> {}; }
	public:
		constexpr FixedPoint<Tp, Q> Add(const FixedPoint<Tp, Q>& other) const { return { _value + other._value }; }
		constexpr FixedPoint<Tp, Q> Sub(const FixedPoint<Tp, Q>& other) const { return { _value - other._value }; }
		constexpr FixedPoint<Tp, Q> Multiple(const FixedPoint<Tp, Q>& other) const
		{
			const size_t width = sizeof(Tp) * 8U;
			auto result = Tp();
			for (auto i : Range<size_t>(0U, width))
			{
				result |=
					((other._value & (1U << (width - 1U - i))) != 0U)
					? (
						(0 <= (std::make_signed_t<size_t>(width - QLength) - 1 - i))
						? (_value << (width - QLength - 1U - i))
						: (_value >> (i + 1U + QLength - width))
					)
					: (0U);
			}
			return { result };
		}
		constexpr FixedPoint<Tp, Q> Divide(const FixedPoint<Tp, Q>& other) const
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
			return { result };
		}
		constexpr FixedPoint<Tp, Q> SaturateAdd(const FixedPoint<Tp, Q>& other) const
		{
			if (_value < (Max()._value - other._value)) { return Add(other); }
			else { return Max(); }
		}
		constexpr FixedPoint<Tp, Q> SaturateSub(const FixedPoint<Tp, Q>& other) const
		{
			if ((Min()._value + other._value) < _value) { return Sub(other); }
			else { return Min(); }
		}
		constexpr FixedPoint<Tp, Q> SaturateMultiple(const FixedPoint<Tp, Q>& other) const
		{
			// TODO: 乗算のオーバーフロー検出処理の実装
			return Multiple(other);
		}
		constexpr FixedPoint<Tp, Q> SaturateDivide(const FixedPoint<Tp, Q>& other) const
		{
			// TODO: 除算のオーバーフロー検出処理の実装
			return Divide(other);
		}

		constexpr FixedPoint<Tp, Q> operator+(const FixedPoint<Tp, Q>& other) const { return Add(other); }
		constexpr FixedPoint<Tp, Q> operator-(const FixedPoint<Tp, Q>& other) const { return Sub(other); }
		constexpr FixedPoint<Tp, Q> operator*(const FixedPoint<Tp, Q>& other) const { return Multiple(other); }
		constexpr FixedPoint<Tp, Q> operator/(const FixedPoint<Tp, Q>& other) const { return Divide(other); }
		constexpr FixedPoint<Tp, Q>& operator+=(const FixedPoint<Tp, Q>& other) { return *this = *this + other; }
		constexpr FixedPoint<Tp, Q>& operator-=(const FixedPoint<Tp, Q>& other) { return *this = *this - other; }
		constexpr FixedPoint<Tp, Q>& operator*=(const FixedPoint<Tp, Q>& other) { return *this = *this * other; }
		constexpr FixedPoint<Tp, Q>& operator/=(const FixedPoint<Tp, Q>& other) { return *this = *this / other; }

		constexpr bool Equals(const FixedPoint<Tp, Q>& other) const { return _value == other._value; }
		constexpr bool operator==(const FixedPoint<Tp, Q>& other) const { return Equals(other); }
		constexpr bool operator!=(const FixedPoint<Tp, Q>& other) const { return !Equals(other); }

		constexpr int Compare(const FixedPoint<Tp, Q>& other) const
		{
			if (_value > other._value) { return 1; }
			else if (_value < other._value) { return -1; }
			else { return 0; }
		}
		constexpr bool operator<(const FixedPoint<Tp, Q>& other) const { return Compare(other) < 0; }
		constexpr bool operator>(const FixedPoint<Tp, Q>& other) const { return Compare(other) > 0; }
		constexpr bool operator<=(const FixedPoint<Tp, Q>& other) const { return Compare(other) <= 0; }
		constexpr bool operator>=(const FixedPoint<Tp, Q>& other) const { return Compare(other) >= 0; }

		FixedPoint<Tp, Q>& operator=(const FixedPoint<Tp, Q>& value) = default;
		FixedPoint<Tp, Q>& operator=(FixedPoint<Tp, Q>&& value) = default;

		template<class castT, size_t castQ> constexpr FixedPoint<castT, castQ> CastTo() const
		{
			return this->template <castQ>convertQ().template <castT>convertT();
		}
		constexpr explicit operator float() const { return template convertToFloat<float>(); }
		constexpr explicit operator double() const { return template convertToFloat<double>(); }
	private:
		template<size_t newQ> constexpr FixedPoint<Tp, newQ> convertQ() const
		{
			if constexpr (newQ == Q) { return FixedPoint<Tp, newQ> { _value }; }
			if constexpr (newQ < Q) { return FixedPoint<Tp, newQ> { _value >> (Q - newQ) }; }
			if constexpr (newQ > Q) { return FixedPoint<Tp, newQ> { _value << (newQ - Q) }; }
		}
		template<class newT> constexpr FixedPoint<newT, Q> convertT() const
		{
			return FixedPoint<Tp, Q> { newT(_value) }; 
		}
		template<class fromT> constexpr Tp convertFromFloat(const fromT& from)
		{
			if ((from == std::numeric_limits<fromT>::quiet_NaN()) || (from == std::numeric_limits<fromT>::signaling_NaN())) { throw std::invalid_argument("指定する値はNaNであってはなりません。"); }
			if ((fromT(Min()) <= from) && (from <= fromT(Max()))) { return Tp(_value * std::exp2(QLength)); }
			else { throw std::overflow_error("指定された値がこの型で表せる範囲を超えています。"); }
		}
		template<class castT> constexpr castT convertToFloat() const
		{
			return castT(castT(_value) / std::exp2(QLength));
		}
	};
}
#endif // __stationaryorbit_core_fixedpoint__
