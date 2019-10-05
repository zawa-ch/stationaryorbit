#ifndef __StationaryOrbit_DefaultDirection2d__
#define __StationaryOrbit_DefaultDirection2d__
namespace StationaryOrbit
{

	///	既定の正軸方向を示す列挙体。
	enum class DefaultDirection2d
	{
		///	右上方向、左手系。
		L1,

		///	左上方向、左手系。
		L2,

		///	左下方向、左手系。
		L3,

		///	右下方向、左手系。
		L4,

		///	右上方向、右手系。
		R1,

		///	左上方向、右手系。
		R2,

		///	左下方向、右手系。
		R3,

		///	右下方向、右手系。
		R4,
	};

}
#endif // __StationaryOrbit_DefaultDirection2d__
