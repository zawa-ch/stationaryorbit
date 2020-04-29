#include <iostream>
#include <stdexcept>
#include "stationaryorbit/core/numeral"
using namespace zawa_ch::StationaryOrbit;

void Test_Logic()
{
	std::cout << Logic::True() << std::endl;
	if (bool(Logic::Indefinited() || Logic::True())) { std::cout << "I | T -> T" << std::endl; } else { throw std::exception(); }
}

void Test_Point()
{
	auto p1 = Point<>(3, 4);
	auto p2 = Point<>(2, 8);
	if ((p1 + p2) != Point<>(5, 12)) { throw std::exception(); }
	std::cout << "p1 + p2 = (" << (p1 + p2).X() << ", " << (p1 + p2).Y() << ")" << std::endl;
	if ((p1 - p2) != Point<>(1, -4)) { throw std::exception(); }
	std::cout << "p1 - p2 = (" << (p1 - p2).X() << ", " << (p1 - p2).Y() << ")" << std::endl;
	auto p3 = Point<Quadrants::DownRight>(p1);
	if (p3 != Point<Quadrants::DownRight>(3, -4)) { throw std::exception(); }
	auto fp1 = GeometricPointF(0.3, 1.8);
	auto fp2 = GeometricPointF(-3.1, 2.0);
	std::cout << "fp1 + fp2 = (" << (fp1 + fp2).X() << ", " << (fp1 + fp2).Y() << ")" << std::endl;
	std::cout << "fp1 - fp2 = (" << (fp1 - fp2).X() << ", " << (fp1 - fp2).Y() << ")" << std::endl;
	auto p4 = fp1.Round();
	std::cout << "p4 = (" << p4.X() << ", " << p4.Y() << ")" << std::endl;
}

void Test_Rectangle()
{
	auto r1 = GeometricRectangle(0, 0, 3, 4);
	std::cout << "r1.left = " << r1.Left() << std::endl;
	std::cout << "r1.right = " << r1.Right() << std::endl;
	std::cout << "r1.top = " << r1.Top() << std::endl;
	std::cout << "r1.bottom = " << r1.Bottom() << std::endl;
	if (!r1.Contains(GeometricRectangle::PointType(1, 1))) { throw std::exception(); }
	auto r2 = r1.Offset(GeometricRectangle::PointType(-3, 6));
	std::cout << "r2.left = " << r2.Left() << std::endl;
	std::cout << "r2.right = " << r2.Right() << std::endl;
	std::cout << "r2.top = " << r2.Top() << std::endl;
	std::cout << "r2.bottom = " << r2.Bottom() << std::endl;
}
