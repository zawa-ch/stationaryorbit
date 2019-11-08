#ifndef __StationaryOrbit_TristateBoolean__
#define __StationaryOrbit_TristateBoolean__
#include <cstddef>
#include "../Logic/InvalidOperationException.hpp"
namespace StationaryOrbit
{

	/// 第三の状態を持つbool値を表します。
	struct TristateBoolean final
	{
	private:

		bool hasval;
		bool val;

	public:

		constexpr TristateBoolean() : hasval(false), val() {}

		constexpr TristateBoolean(const bool& value) : hasval(true), val(value) {}

		constexpr TristateBoolean(const std::nullptr_t& value) : hasval(false), val() {}

		constexpr bool HasValue() const { return hasval; }

		constexpr bool getBoolean() const { if (hasval) { return val; } else { throw InvalidOperationException("This object has no value."); } }

		constexpr TristateBoolean operator~() const { if (hasval) { return TristateBoolean(~val); } else { return TristateBoolean(nullptr); } }

		constexpr TristateBoolean operator|(TristateBoolean& value) const { if (hasval) { return TristateBoolean(val | value.val); } else { return TristateBoolean(nullptr); } }

		constexpr TristateBoolean operator&(TristateBoolean& value) const { if (hasval) { return TristateBoolean(val & value.val); } else { return TristateBoolean(nullptr); } }

		constexpr TristateBoolean operator^(TristateBoolean& value) const { if (hasval) { return TristateBoolean(val ^ value.val); } else { return TristateBoolean(nullptr); } }

		constexpr TristateBoolean operator!() const { if (hasval) { return TristateBoolean(!val); } else { return TristateBoolean(nullptr); } }

		constexpr TristateBoolean operator||(TristateBoolean& value) const { if (hasval) { return TristateBoolean(val || value.val); } else { return TristateBoolean(nullptr); } }

		constexpr TristateBoolean operator&&(TristateBoolean& value) const { if (hasval) { return TristateBoolean(val && value.val); } else { return TristateBoolean(nullptr); } }

		constexpr explicit operator bool() const { return getBoolean(); }

	};

}
#endif // __StationaryOrbit_TristateBoolean__