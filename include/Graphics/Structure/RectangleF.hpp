#ifndef __StationaryOrbit_Graphics_RectangleF__
#define __StationaryOrbit_Graphics_RectangleF__
#include "../Structure/PointF.hpp"
#include "../Structure/Rectangle.hpp"
namespace StationaryOrbit::Graphics
{

	///	PointFによって表されるディスプレイ上の矩形範囲を表します。
	struct RectangleF final
	{
	private:

		PointF _p1;
		PointF _p2;

	public:

		///	空のRectangleFを初期化します。
		RectangleF() = default;

		///	Rectangleから値を変換します。
		RectangleF(const Rectangle& value);

		///	二つのPointFを指定して新しいRectangleFを初期化します。
		RectangleF(const PointF& p1, const PointF& p2);

		~RectangleF() = default;

		///	このオブジェクトで指定されているひとつ目のPointFを取得します。
		PointF getP1() const;

		///	このオブジェクトで指定されているふたつ目のPointFを取得します。
		PointF getP2() const;

		///	このオブジェクトの上辺のy軸位置を取得します。
		float getTop() const;

		///	このオブジェクトの下辺のy軸位置を取得します。
		float getBottom() const;

		///	このオブジェクトの左辺のx軸位置を取得します。
		float getLeft() const;

		///	このオブジェクトの右辺のx軸位置を取得します。
		float getRight() const;

		///	このオブジェクトの示す領域の高さを取得します。
		float getHeight() const;

		///	このオブジェクトの示す領域の幅を取得します。
		float getWidth() const;

		///	このオブジェクトの左上の頂点位置を示すPointFを取得します。
		PointF getTopLeft() const;

		///	このオブジェクトの左下の頂点位置を示すPointFを取得します。
		PointF getBottomLeft() const;

		///	このオブジェクトの右上の頂点位置を示すPointFを取得します。
		PointF getTopRight() const;

		///	このオブジェクトの右下の頂点位置を示すPointFを取得します。
		PointF getBottomRight() const;

		///	このオブジェクトで示されている二点間の距離を取得します。
		double Distance() const;

		///	このオブジェクトを指定した方向・大きさだけ移動します。
		RectangleF Shift(const PointF& value) const;

		///	指定されたオブジェクトがこのオブジェクトと等価であることを判定します。
		bool Equals(const RectangleF& value) const;
		bool operator==(const RectangleF& value) const { return Equals(value); }
		bool operator!=(const RectangleF& value) const { return !Equals(value); }

		///	内容をRectangleに変換します。
		explicit operator Rectangle() const;

	};

}
#endif // __StationaryOrbit_Graphics_RectangleF__