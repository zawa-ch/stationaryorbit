#ifndef __stationaryorbit_graphics_core_channelvalue__
#define __stationaryorbit_graphics_core_channelvalue__
#include <cstdint>
#include <limits>
#include <type_traits>
#include <utility>
namespace zawa_ch::StationaryOrbit::Graphics
{

	///	色チャネルの値を表現するためのラッパーです。
	///	@param	Tp
	///	値を表現するために用いられる型。
	template<class Tp = float>
	struct ChannelValue
	{
		static_assert(std::is_arithmetic_v<Tp>, "テンプレート型 Tp は算術型である必要があります。");
		static_assert((std::is_floating_point_v<Tp>)||(std::is_integral_v<Tp>), "テンプレート型 Tp は整数型または浮動小数点数型のいずれかである必要があります。");
	public: // type
		typedef Tp ValueType;
	public: // contains
		ValueType value;
	public: // constructor
		constexpr ChannelValue() : value() {}
		constexpr explicit ChannelValue(const ValueType& value) : value(value) {}
		constexpr explicit ChannelValue(ValueType&& value) : value(std::exchange(value, ValueType())) {}
		template<class fromT>
		constexpr explicit ChannelValue(const ChannelValue<fromT>& from) : ChannelValue(from.template ConvertTo<Tp>()) {}
	public: // member
		constexpr bool IsNormalized() const { return (Min().value < value)&&(value < Max().value); }
	public: // static
		constexpr static ChannelValue<Tp> Max()
		{
			static_assert((std::is_floating_point_v<Tp>)||(std::is_integral_v<Tp>), "テンプレートの特殊化に失敗しました(テンプレート型 Tp は整数型または浮動小数点数型のいずれでもありません)。");
			if constexpr (std::is_floating_point_v<Tp>) { return ChannelValue(ValueType(1.0)); }
			if constexpr (std::is_integral_v<Tp>) { return ChannelValue(std::numeric_limits<Tp>::max()); }
		}
		constexpr static ChannelValue<Tp> Min()
		{
			static_assert((std::is_floating_point_v<Tp>)||(std::is_integral_v<Tp>), "テンプレートの特殊化に失敗しました(テンプレート型 Tp は整数型または浮動小数点数型のいずれでもありません)。");
			if constexpr (std::is_floating_point_v<Tp>) { return ChannelValue(ValueType(0.0)); }
			if constexpr (std::is_integral_v<Tp>) { return ChannelValue(0); }
		}
		constexpr ChannelValue<Tp> Abs() const { return ChannelValue(+value); }
		constexpr ChannelValue<Tp> Negative() const { return ChannelValue(-value); }
	public: // arithmetic operation
		constexpr ChannelValue<Tp> operator+() const { return Abs(); }
		constexpr ChannelValue<Tp> operator-() const { return Negative(); }
		constexpr ChannelValue<Tp> operator+(const ChannelValue<Tp>& other) const { return ChannelValue(value + other.value); }
		constexpr ChannelValue<Tp> operator+(const Tp& other) const { return ChannelValue(value + other); }
		constexpr ChannelValue<Tp> operator-(const ChannelValue<Tp>& other) const { return ChannelValue(value - other.value); }
		constexpr ChannelValue<Tp> operator-(const Tp& other) const { return ChannelValue(value - other); }
		constexpr ChannelValue<Tp> operator*(const ChannelValue<Tp>& other) const { return ChannelValue(value * other.value); }
		constexpr ChannelValue<Tp> operator*(const Tp& other) const { return ChannelValue(value * other); }
		constexpr ChannelValue<Tp> operator/(const ChannelValue<Tp>& other) const { return ChannelValue(value / other.value); }
		constexpr ChannelValue<Tp> operator/(const Tp& other) const { return ChannelValue(value / other); }
		constexpr ChannelValue<Tp>& operator+=(const ChannelValue<Tp>& other) const { return *this = ChannelValue(value + other.value); }
		constexpr ChannelValue<Tp>& operator+=(const Tp& other) const { return *this = ChannelValue(value + other); }
		constexpr ChannelValue<Tp>& operator-=(const ChannelValue<Tp>& other) const { return *this = ChannelValue(value - other.value); }
		constexpr ChannelValue<Tp>& operator-=(const Tp& other) const { return *this = ChannelValue(value - other); }
		constexpr ChannelValue<Tp>& operator*=(const ChannelValue<Tp>& other) const { return *this = ChannelValue(value * other.value); }
		constexpr ChannelValue<Tp>& operator*=(const Tp& other) const { return *this = ChannelValue(value * other); }
		constexpr ChannelValue<Tp>& operator/=(const ChannelValue<Tp>& other) const { return *this = ChannelValue(value / other.value); }
		constexpr ChannelValue<Tp>& operator/=(const Tp& other) const { return *this = ChannelValue(value / other); }
	public: // equatability
		constexpr bool Equals(const ChannelValue<Tp>& other) const { return value == other.value; }
		constexpr bool operator==(const ChannelValue<Tp>& other) const { return Equals(other); }
		constexpr bool operator!=(const ChannelValue<Tp>& other) const { return !Equals(other); }
	public: // comparability
		constexpr int Compare(const ChannelValue<Tp>& other) const
		{
			if (value > other.value) { return 1; }
			else if (value < other.value) { return -1; }
			else { return 0; }
		}
		constexpr bool operator<(const ChannelValue<Tp>& other) const { return Compare(other) < 0; }
		constexpr bool operator>(const ChannelValue<Tp>& other) const { return Compare(other) > 0; }
		constexpr bool operator<=(const ChannelValue<Tp>& other) const { return Compare(other) <= 0; }
		constexpr bool operator>=(const ChannelValue<Tp>& other) const { return Compare(other) >= 0; }
	public: // assign
		ChannelValue<Tp>& operator=(const ValueType& value) { return *this = ChannelValue(value); }
		ChannelValue<Tp>& operator=(ValueType&& value) { std::swap(this->value, value); return *this; }
	public: // convert
		constexpr operator ValueType() const { return value; }
		template<class castT>
		constexpr ChannelValue<castT> ConvertTo() const
		{
			static_assert((std::is_floating_point_v<Tp>)||(std::is_integral_v<Tp>), "テンプレートの特殊化に失敗しました(テンプレート型 Tp は整数型または浮動小数点数型のいずれでもありません)。");
			static_assert((std::is_floating_point_v<castT>)||(std::is_integral_v<castT>), "テンプレートの特殊化に失敗しました(テンプレート型 castT は整数型または浮動小数点数型のいずれでもありません)。");
			if constexpr (std::is_floating_point_v<Tp>)
			{
				// float -> float
				if constexpr (std::is_floating_point_v<castT>) { return ChannelValue<castT>(castT(value)); }
				// float -> integer
				if constexpr (std::is_integral_v<castT>) { return ChannelValue<castT>(castT(value * ChannelValue<castT>::Max().value)); }
			}
			if constexpr (std::is_integral_v<Tp>)
			{
				// integer -> float
				if constexpr (std::is_floating_point_v<castT>) { return ChannelValue<castT>(castT(value) / Max().value); }
				// integer -> integer
				if constexpr (std::is_integral_v<castT>)
				{
					if constexpr (sizeof(Tp) < sizeof(castT)) { return ChannelValue<castT>(castT(value) * (ChannelValue<castT>::Max().value / Max().value)); }
					else { return ChannelValue<castT>(castT(value / (Max().value / ChannelValue<castT>::Max().value))); }
				}
			}
		}
	public: // copy/move/destruct
		constexpr ChannelValue<Tp>(const ChannelValue<Tp>&) = default;
		ChannelValue<Tp>& operator=(const ChannelValue<Tp>& value) = default;
		constexpr ChannelValue(ChannelValue<Tp>&&) = default;
		ChannelValue<Tp>& operator=(ChannelValue<Tp>&& value) = default;
		~ChannelValue() = default;
	};

}
#endif // __stationaryorbit_graphics_core_channelvalue__