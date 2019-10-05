#ifndef __StationaryOrbit_Graphics_Rectangle__
#define __StationaryOrbit_Graphics_Rectangle__
#include "DataClass/Graphics/Point.hpp"
namespace StationaryOrbit
{
namespace Graphics
{

	struct Rectangle final
	{
	private:

		Point _p1;
		Point _p2;

	public:

		Rectangle();

		Rectangle(const Point& p1, const Point& p2);

		~Rectangle() = default;

		Point getP1() const;

		Point getP2() const;

		int32_t getTop() const;

		int32_t getBottom() const;

		int32_t getLeft() const;

		int32_t getRight() const;

		int32_t getHeight() const;

		int32_t getWidth() const;

		double Distance() const;

	};

}
}
#endif // __StationaryOrbit_Graphics_Rectangle__