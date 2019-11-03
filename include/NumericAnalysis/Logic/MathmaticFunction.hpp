#ifndef __StationaryOrbit_NumericAnalysis_MathmaticFunction__
#define __StationaryOrbit_NumericAnalysis_MathmaticFunction__
#include "General/Exception"
#include "../Interface/IMathmaticFunction.hpp"
namespace StationaryOrbit::NumericAnalysis
{

	template<class T>
	class MathmaticFunction
		: public IMathmaticFunction<T>
	{
	public:

		typedef T (*BaseFunc)(T);

	private:

		BaseFunc func;

	public:

		explicit MathmaticFunction(BaseFunc function) : func(function) {}

		T Calc(const T& value) const
		{
			if (func == NULL) throw NullReferenceException("function pointer must be non-null value");
			return func(value);
		}
		T operator()(const T& value) const { return Calc(value); }

	};

}
#endif // __StationaryOrbit_NumericAnalysis_MathmaticFunction__