#ifndef __stationaryorbit_core_bitmask__
#define __stationaryorbit_core_bitmask__
#include <limits>
#include <type_traits>
#include <vector>
#include "stationaryorbit/exception/soexcept"
#include "range.hpp"
namespace zawa_ch::StationaryOrbit
{

	template<class T>
	class BitMask final
	{
		static_assert(std::is_integral_v<T>, "実体化を行うためのテンプレート型は整数型である必要があります。");
	public: // contains
		T Mask;
	public: // constructor
		constexpr BitMask() = default;
		explicit constexpr BitMask(const T& value) : Mask(value) {}
	public: // member
		constexpr T GetFrom(const T& source) const { return source & Mask; }
		constexpr T SetTo(const T& source, const T& value) const { return (source & ~Mask) | (value & Mask); }
		constexpr T GetAlignedFrom(const T& source) const { return GetFrom(source) >> GetBeginIndex(Mask); }
		constexpr T SetAlignedTo(const T& source, const T& value) const { return SetTo(source, value << GetBeginIndex(Mask)); }
		constexpr Range<std::size_t> ToRange() const
		{
			const size_t length = sizeof(T) * 8;
			std::size_t begin = GetBeginIndex(Mask);
			if (length <= begin) { return Range<std::size_t>(0, 0); }
			std::size_t end = GetEndIndex(Mask);
			return Range(begin, end);
		}
	public: // bit operation
		constexpr BitMask<T> operator~() const { return BitMask<T>(~Mask); }
		constexpr BitMask<T> operator|(const BitMask<T>& other) const { return BitMask<T>(Mask | other.Mask); }
		constexpr BitMask<T> operator&(const BitMask<T>& other) const { return BitMask<T>(Mask & other.Mask); }
		constexpr BitMask<T> operator^(const BitMask<T>& other) const { return BitMask<T>(Mask ^ other.Mask); }
		constexpr BitMask<T>& operator|=(const BitMask<T>& other) { return *this = BitMask<T>(Mask | other.Mask); }
		constexpr BitMask<T>& operator&=(const BitMask<T>& other) { return *this = BitMask<T>(Mask & other.Mask); }
		constexpr BitMask<T>& operator^=(const BitMask<T>& other) { return *this = BitMask<T>(Mask ^ other.Mask); }
	public: // equatability
		constexpr bool Equals(const BitMask<T>& other) const { return Mask == other.Mask; }
		constexpr bool operator==(const BitMask<T>& other) const { return Equals(other); }
		constexpr bool operator!=(const BitMask<T>& other) const { return !Equals(other); }
	public: // static
		static constexpr std::size_t GetBeginIndex(const T& value, const T& start = 0)
		{
			const size_t length = sizeof(T) * 8;
			for (std::size_t i = start; i < length; i++) { if ((value & (1 << i)) != 0) { return i; } }
			return length;
		}
		static constexpr std::size_t GetEndIndex(const T& value, const T& start = std::numeric_limits<T>::max())
		{
			const size_t length = sizeof(T) * 8;
			for (std::size_t i = ((start < length)?start:length); 0 < i; i--) { if ((value & (1 << (i - 1))) == 0) { return i; } }
			return length;
		}
		static constexpr BitMask<T> Zero() { return BitMask<T>(0); }
	};

}
#endif // __stationaryorbit_core_bitmask__