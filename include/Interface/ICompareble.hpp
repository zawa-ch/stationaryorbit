#ifndef __ICOMPAREBLE_HPP__
#define __ICOMPAREBLE_HPP__
namespace StationaryOrbit
{

	///	指定された型と比較する機能を実装します。
	template<typename T> class ICompareble
	{
	public:

		///	このオブジェクトを指定したオブジェクトと比較します。
		///	このオブジェクトが大きければ>0を、小さければ<0を、等しければ0を返します。
		virtual int Compare(const T& value) const = 0;

	};

}
#endif // __ICOMPAREBLE_HPP__