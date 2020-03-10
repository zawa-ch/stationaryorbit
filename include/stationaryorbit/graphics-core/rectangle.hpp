#ifndef __stationaryorbit_graphics_core_rectangle__
#define __stationaryorbit_graphics_core_rectangle__
#include "point.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	///	Pointによって表されるディスプレイ上の矩形範囲を表します。
	struct Rectangle final
	{
	private:

		Point _p1;
		Point _p2;

	public:

		///	空のRectangleを初期化します。
		Rectangle() = default;

		///	二つのPointを指定して新しいRectangleを初期化します。
		Rectangle(const Point& p1, const Point& p2);

		~Rectangle() = default;

		///	このオブジェクトで指定されているひとつ目のPointを取得します。
		Point getP1() const;

		///	このオブジェクトで指定されているふたつ目のPointを取得します。
		Point getP2() const;

		///	このオブジェクトの上辺のy軸位置を取得します。
		int32_t getTop() const;

		///	このオブジェクトの下辺のy軸位置を取得します。
		int32_t getBottom() const;

		///	このオブジェクトの左辺のx軸位置を取得します。
		int32_t getLeft() const;

		///	このオブジェクトの右辺のx軸位置を取得します。
		int32_t getRight() const;

		///	このオブジェクトの示す領域の高さを取得します。
		int32_t getHeight() const;

		///	このオブジェクトの示す領域の幅を取得します。
		int32_t getWidth() const;

		///	このオブジェクトの左上の頂点位置を示すPointを取得します。
		Point getTopLeft() const;

		///	このオブジェクトの左下の頂点位置を示すPointを取得します。
		Point getBottomLeft() const;

		///	このオブジェクトの右上の頂点位置を示すPointを取得します。
		Point getTopRight() const;

		///	このオブジェクトの右下の頂点位置を示すPointを取得します。
		Point getBottomRight() const;

		///	このオブジェクトが示す領域の大きさをPointで取得します。
		Point getSize() const;

		///	このオブジェクトで示されている二点間の距離を取得します。
		double Distance() const;

		///	指定されたPointが範囲内に含まれるかを取得します。
		bool InRange(const Point& value) const;

		///	このオブジェクトを指定した方向・大きさだけ移動します。
		Rectangle Shift(const Point& value) const;

		///	指定されたオブジェクトがこのオブジェクトと等価であることを判定します。
		bool Equals(const Rectangle& value) const;
		bool operator==(const Rectangle& value) const { return Equals(value); }
		bool operator!=(const Rectangle& value) const { return !Equals(value); }

	};

}
#endif // __stationaryorbit_graphics_core_rectangle__