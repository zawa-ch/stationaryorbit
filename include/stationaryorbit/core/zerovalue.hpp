#ifndef __stationaryorbit_zerovalue__
#define __stationaryorbit_zerovalue__
#include <cstddef>
#include <stdexcept>
namespace zawa_ch::StationaryOrbit
{
	///	他の型に変換可能な零値を表します。
	struct ZeroValue_t
	{
	public:
		constexpr ZeroValue_t() = default;
		constexpr ZeroValue_t(const ZeroValue_t&) = default;
		constexpr ZeroValue_t(ZeroValue_t&&) = default;

		constexpr operator bool() const { return 0; }
		constexpr operator std::nullptr_t() const { return nullptr; }
		constexpr operator std::byte() const { return std::byte('\0'); }

		constexpr ZeroValue_t operator+() const { return Zero; }
		constexpr ZeroValue_t operator-() const { return Zero; }
		constexpr ZeroValue_t operator+(const ZeroValue_t&) const { return Zero; }
		constexpr ZeroValue_t operator-(const ZeroValue_t&) const { return Zero; }
		constexpr ZeroValue_t operator*(const ZeroValue_t&) const { return Zero; }
		constexpr ZeroValue_t operator/(const ZeroValue_t&) const { throw std::range_error("結果は NaN となりますが、 ZeroValue_t は NaN を表現できません。"); }
		constexpr ZeroValue_t operator%(const ZeroValue_t&) const { throw std::range_error("結果は NaN となりますが、 ZeroValue_t は NaN を表現できません。"); }
		constexpr ZeroValue_t operator~() const { throw std::range_error("結果は ~0 となりますが、 ZeroValue_t は ~0 を表現できません。"); }
		constexpr ZeroValue_t operator|(const ZeroValue_t&) const { return Zero; }
		constexpr ZeroValue_t operator&(const ZeroValue_t&) const { return Zero; }
		constexpr ZeroValue_t operator^(const ZeroValue_t&) const { return Zero; }
		constexpr ZeroValue_t operator<<(const int&) const { return Zero; }
		constexpr ZeroValue_t operator>>(const int&) const { return Zero; }

		constexpr ZeroValue_t& operator++() { throw std::range_error("結果は >0 となりますが、 ZeroValue_t は >0 を表現できません。"); }
		constexpr ZeroValue_t& operator--() { throw std::range_error("結果は <0 となりますが、 ZeroValue_t は <0 を表現できません。"); }
		constexpr ZeroValue_t operator++(int) { throw std::range_error("結果は >0 となりますが、 ZeroValue_t は >0 を表現できません。"); }
		constexpr ZeroValue_t operator--(int) { throw std::range_error("結果は <0 となりますが、 ZeroValue_t は <0 を表現できません。"); }

		constexpr ZeroValue_t operator!() const { throw std::range_error("結果は true となりますが、 ZeroValue_t は true を表現できません。"); }
		constexpr ZeroValue_t operator||(const ZeroValue_t&) const { return Zero; }
		constexpr ZeroValue_t operator&&(const ZeroValue_t&) const { return Zero; }

		constexpr ZeroValue_t& operator+=(const ZeroValue_t&) { return *this; }
		constexpr ZeroValue_t& operator-=(const ZeroValue_t&) { return *this; }
		constexpr ZeroValue_t& operator*=(const ZeroValue_t&) { return *this; }
		constexpr ZeroValue_t& operator/=(const ZeroValue_t&) { throw std::range_error("結果は NaN となりますが、 ZeroValue_t は NaN を表現できません。"); }
		constexpr ZeroValue_t& operator%=(const ZeroValue_t&) { throw std::range_error("結果は NaN となりますが、 ZeroValue_t は NaN を表現できません。"); }
		constexpr ZeroValue_t& operator|=(const ZeroValue_t&) { return *this; }
		constexpr ZeroValue_t& operator&=(const ZeroValue_t&) { return *this; }
		constexpr ZeroValue_t& operator^=(const ZeroValue_t&) { return *this; }
		constexpr ZeroValue_t& operator<<=(const int&) { return *this; }
		constexpr ZeroValue_t& operator>>=(const int&) { return *this; }

		constexpr bool Equals(const ZeroValue_t&) const { return true; }
		constexpr bool operator==(const ZeroValue_t&) const { return true; }
		constexpr bool operator!=(const ZeroValue_t&) const { return false; }
		constexpr int Compare(const ZeroValue_t&) const { return 0; }
		constexpr bool operator<(const ZeroValue_t&) const { return false; }
		constexpr bool operator>(const ZeroValue_t&) const { return false; }
		constexpr bool operator<=(const ZeroValue_t&) const { return true; }
		constexpr bool operator>=(const ZeroValue_t&) const { return true; }
	};
	constexpr ZeroValue_t Zero = ZeroValue_t();
}
#endif // __stationaryorbit_zerovalue__