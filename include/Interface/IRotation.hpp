#ifndef __IROTATION_HPP__
#define __IROTATION_HPP__
namespace StationaryOrbit
{

	///	角度の情報を保持し、度またはラジアンへの変換を実装します。
	class IRotation
	{
	public:

		///	このオブジェクトの内容をRadian(ラジアン)で取得します。
		virtual double getRadian() const = 0;

		///	このオブジェクトの内容をDegree(度)で取得します。
		virtual double getDegree() const = 0;

	};

}
#endif
