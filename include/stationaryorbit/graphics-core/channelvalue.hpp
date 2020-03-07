#ifndef __stationaryorbit_graphics_core_channelvalue__
#define __stationaryorbit_graphics_core_channelvalue__
#include <cstdint>
#include <climits>
#include <type_traits>
#include <utility>
namespace zawa_ch::StationaryOrbit::Graphics
{

	///	色チャネルの値を表現するためのラッパーです。
	///	@param	T
	///	値を表現するために用いられる型。
	template<class T>
	struct ChannelValue
	{
		static_assert(std::is_arithmetic_v<T>, "テンプレート型 T は算術型である必要があります。");
		static_assert((std::is_floating_point_v<T>)||(std::is_integral_v<T>), "テンプレート型 T は整数型または浮動小数点数型のいずれかである必要があります。");

	public: // type

		typedef T ValueType;

	public: // contains

		ValueType value;

	public: // constructor

		constexpr ChannelValue() : value() {}
		constexpr explicit ChannelValue(const ValueType& value) : value(value) {}
		constexpr explicit ChannelValue(ValueType&& value) : value(std::exchange(value, ValueType())) {}

	public: // member

		constexpr bool IsNormalized() const { return (Min().value < value)&&(value < Max().value); }

		template<class destT>
		constexpr ChannelValue<destT> ConvertTo() const { return ChannelValue<destT>::ConvertFrom<T>(*this); }

	public: // static

		constexpr static ChannelValue<T> Max()
		{
			if constexpr (std::is_floating_point_v<T>) { return ChannelValue(ValueType(1.0)); }
			else if constexpr (std::is_integral_v<T>) { return ChannelValue(std::numeric_limits<T>::max()); }
			else { static_assert(std::false_type::value, "テンプレートの特殊化に失敗しました(テンプレート型 T は整数型または浮動小数点数型のいずれでもありません)。"); }
		}

		constexpr static ChannelValue<T> Min()
		{
			if constexpr (std::is_floating_point_v<T>) { return ChannelValue(ValueType(0.0)); }
			else if constexpr (std::is_integral_v<T>) { return ChannelValue(0); }
			else { static_assert(std::false_type::value, "テンプレートの特殊化に失敗しました(テンプレート型 T は整数型または浮動小数点数型のいずれでもありません)。"); }
		}

		template<class fromT>
		constexpr static ChannelValue<T> ConvertFrom(const ChannelValue<fromT>& value)
		{
			if constexpr (std::is_floating_point_v<T>)
			{
				if constexpr (std::is_floating_point_v<fromT>) { return ChannelValue(T(value.value)); }
				else if constexpr (std::is_integral_v<fromT>) { return ChannelValue(T(value.value) / Max().value); }
				else { static_assert(std::false_type::value, "テンプレートの特殊化に失敗しました(テンプレート型 T は整数型または浮動小数点数型のいずれでもありません)。"); }
			}
			else if constexpr (std::is_integral_v<T>)
			{
				if constexpr (std::is_floating_point_v<fromT>) { return ChannelValue(T(value.value * Max().value)); }
				else if constexpr (std::is_integral_v<fromT>)
				{
					if constexpr (sizeof(fromT) < sizeof(T)) { return ChannelValue(T(value.value) * (Max().value / value.Max().value)); }
					else { return ChannelValue(T(value.value / (value.Max().value / Max().value))); }
				}
				else { static_assert(std::false_type::value, "テンプレートの特殊化に失敗しました(テンプレート型 T は整数型または浮動小数点数型のいずれでもありません)。"); }
			}
			else { static_assert(std::false_type::value, "テンプレートの特殊化に失敗しました(テンプレート型 T は整数型または浮動小数点数型のいずれでもありません)。"); }
		}

	public: // equatability

		constexpr bool Equals(const ChannelValue<T>& other) const { return value == other.value; }
		constexpr bool operator==(const ChannelValue<T>& other) const { return Equals(other); }
		constexpr bool operator!=(const ChannelValue<T>& other) const { return !Equals(other); }

	public: // comparability

		constexpr int Compare(const ChannelValue<T>& other) const
		{
			if (value > other.value) { return 1; }
			else if (value < other.value) { return -1; }
			else { return 0; }
		}
		constexpr bool operator<(const ChannelValue<T>& other) const { return Compare(other) < 0; }
		constexpr bool operator>(const ChannelValue<T>& other) const { return Compare(other) > 0; }
		constexpr bool operator<=(const ChannelValue<T>& other) const { return Compare(other) <= 0; }
		constexpr bool operator>=(const ChannelValue<T>& other) const { return Compare(other) >= 0; }

	public: // assign

		ChannelValue<T>& operator=(const ValueType& value) { return *this = ChannelValue(value); }
		ChannelValue<T>& operator=(ValueType&& value) { std::swap(this->value, value); return *this; }

	public: // convert

		constexpr operator ValueType() const { return value; }

	public: // copy/move/destruct

		constexpr ChannelValue(const ChannelValue<T>&) = default;
		ChannelValue<T>& operator=(const ChannelValue<T>& value) = default;
		constexpr ChannelValue(ChannelValue<T>&&) = default;
		ChannelValue<T>& operator=(ChannelValue<T>&& value) = default;
		~ChannelValue() = default;

	};

}
#endif // __stationaryorbit_graphics_core_channelvalue__