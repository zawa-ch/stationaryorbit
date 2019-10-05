#ifndef __StationaryOrbit_Graphics_RectangleF__
#define __StationaryOrbit_Graphics_RectangleF__
#include "DataClass/Graphics/PointF.hpp"
namespace StationaryOrbit
{
namespace Graphics
{

	struct RectangleF final
	{
	private:

		PointF _p1;
		PointF _p2;

	public:

		RectangleF();

		RectangleF(const PointF& p1, const PointF& p2);

		~RectangleF() = default;

		PointF getP1() const;

		PointF getP2() const;

		float getTop() const;

		float getBottom() const;

		float getLeft() const;

		float getRight() const;

		float getHeight() const;

		float getWidth() const;

		double Distance() const;

	};

}
}
#endif // __StationaryOrbit_Graphics_RectangleF__