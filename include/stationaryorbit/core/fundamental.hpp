#ifndef __stationaryorbit_core_fundamental__
#define __stationaryorbit_core_fundamental__
#include <cstdint>
namespace zawa_ch::StationaryOrbit
{
	///	対応する値が存在しない型を表します。
	struct Unit final {};
	///	@a Unit の唯一のインスタンスを表します。
	static constexpr Unit UnitValue = {};

	///	決してインスタンス化することのできない型を表します。
	typedef void Bottom;

	//	<-- C++基本型に対して与えられる型エイリアスの定義 -->

	typedef float float32_t;
	typedef double float64_t;
	typedef long double floatmax_t;
}
#endif // __stationaryorbit_core_fundamental__
