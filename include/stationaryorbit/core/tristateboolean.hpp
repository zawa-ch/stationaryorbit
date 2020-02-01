#ifndef __StationaryOrbit_TristateBoolean__
#define __StationaryOrbit_TristateBoolean__
#include <cstddef>
#include "../Logic/InvalidOperationException.hpp"
namespace StationaryOrbit
{

	/// 第三の状態を持つbool値を表します。
	///
	///	このオブジェクトは、 @a true 、 @a false とそのいずれでもない値の3つの状態を持つbool値です。
	struct TristateBoolean final
	{
	private:

		bool hasval;
		bool val;

	public:

		///	既定の値でこのオブジェクトを初期化します。
		constexpr TristateBoolean() noexcept : hasval(false), val() {}

		///	@a bool からオブジェクトを初期化します。
		constexpr TristateBoolean(const bool& value) noexcept : hasval(true), val(value) {}

		///	@a std::nullptr_t からオブジェクトを初期化します。
		constexpr TristateBoolean(const std::nullptr_t& value) noexcept : hasval(false), val() {}

		///	このオブジェクトが @a true 、または @a false の値を持っているかどうかを取得します。
		constexpr bool HasValue() const noexcept { return hasval; }

		///	このオブジェクトのブール値を取得します。
		///
		///	@exception	InvalidOperationException
		///	このオブジェクトは @a true でも @a false でもありません。
		constexpr bool getBoolean() const { if (hasval) { return val; } else { throw InvalidOperationException("This object has no value."); } }

		constexpr TristateBoolean operator~() const { if (hasval) { return TristateBoolean(~val); } else { return TristateBoolean(nullptr); } }

		constexpr TristateBoolean operator|(const TristateBoolean& value) const { if (hasval&&value.hasval) { return TristateBoolean(val | value.val); } else { return TristateBoolean(nullptr); } }

		constexpr TristateBoolean operator&(const TristateBoolean& value) const { if (hasval&&value.hasval) { return TristateBoolean(val & value.val); } else { return TristateBoolean(nullptr); } }

		constexpr TristateBoolean operator^(const TristateBoolean& value) const { if (hasval&&value.hasval) { return TristateBoolean(val ^ value.val); } else { return TristateBoolean(nullptr); } }

		constexpr TristateBoolean operator!() const { if (hasval) { return TristateBoolean(!val); } else { return TristateBoolean(nullptr); } }

		constexpr TristateBoolean operator||(const TristateBoolean& value) const { if (hasval&&value.hasval) { return TristateBoolean(val || value.val); } else { return TristateBoolean(nullptr); } }

		constexpr TristateBoolean operator&&(const TristateBoolean& value) const { if (hasval&&value.hasval) { return TristateBoolean(val && value.val); } else { return TristateBoolean(nullptr); } }

		///	指定されたオブジェクトがこのオブジェクトと等価であることを判定します。
		constexpr bool Equals(const TristateBoolean& value) const { if (hasval&&value.hasval) { return val == value.val; } else { return false; } }
		constexpr bool operator==(const TristateBoolean& value) const { return Equals(value); }

		constexpr explicit operator bool() const { return getBoolean(); }

		///	このオブジェクトにおける @a true 値を取得します。
		constexpr static TristateBoolean True() { return TristateBoolean(true); }

		///	このオブジェクトにおける @a false 値を取得します。
		constexpr static TristateBoolean False() { return TristateBoolean(false); }

		///	このオブジェクトにおける @a true でも @a false でもない値を取得します。
		constexpr static TristateBoolean Null() { return TristateBoolean(nullptr); }

	};

}
#endif // __StationaryOrbit_TristateBoolean__