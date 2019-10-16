#ifndef __StationaryOrbit_IComparable__
#define __StationaryOrbit_IComparable__
namespace StationaryOrbit
{

	///	指定された型と比較する機能を実装します。
	template<typename T> class IComparable
	{
	public:

		///	このオブジェクトを指定したオブジェクトと比較します。
		///	このオブジェクトが大きければ>0を、小さければ<0を、等しければ0を返します。
		virtual int Compare(const T& value) const = 0;

	};

}
#endif // __StationaryOrbit_IComparable__