#ifndef __StationaryOrbit_NullReferenceException__
#define __StationaryOrbit_NullReferenceException__
#include <stdexcept>
namespace zawa_ch::StationaryOrbit
{

	///	無効な参照を逆参照しようとした場合にスローされる例外。
	class NullReferenceException
		: public std::logic_error
	{
	public:

		///	例外の説明を付け、このオブジェクトを初期化します。
		explicit NullReferenceException(const std::string& what_arg) noexcept;

		///	例外の説明を付け、このオブジェクトを初期化します。
		explicit NullReferenceException(const char* what_arg) noexcept;

	};

}
#endif // __StationaryOrbit_NullReferenceException__