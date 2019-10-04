#ifndef __BOOLEANSET_HPP__
#define __BOOLEANSET_HPP__
namespace StationaryOrbit
{

	///	ブーリアン、またはその集合の演算を実装します。
	template<typename T>
	class IBooleanSet
	{
	public:

		virtual static T Or(const T& left, const T& right) = 0;

		virtual static T And(const T& left, const T& right) = 0;

		virtual static T Not(const T& value) = 0;

		virtual static T Xor(const T& left, const T& right) = 0;
	};

}
#endif // __BOOLEANSET_HPP__