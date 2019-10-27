#ifndef __StationaryOrbit_InvalidOperationException__
#define __StationaryOrbit_InvalidOperationException__
#include <stdexcept>
namespace StationaryOrbit
{

	///	無効な状態で呼び出されたメソッドに対してスローされる例外。
	class InvalidOperationException
		: public std::logic_error
	{
	public:

		///	例外の説明を付け、このオブジェクトを初期化します。
		explicit InvalidOperationException(const std::string& what_arg);

		///	例外の説明を付け、このオブジェクトを初期化します。
		explicit InvalidOperationException(const char* what_arg);

	};

}
#endif // __StationaryOrbit_InvalidOperationException__