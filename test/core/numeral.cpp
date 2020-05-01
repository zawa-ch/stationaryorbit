#include <iostream>
#include <stdexcept>
#include "stationaryorbit/core.numeral.hpp"
using namespace zawa_ch::StationaryOrbit;

void Test_Logic()
{
	std::cout << Logic::True() << std::endl;
	if (bool(Logic::Indefinited() || Logic::True())) { std::cout << "I | T -> T" << std::endl; } else { throw std::exception(); }
}

void Test_FractionalDec()
{
	std::cout << "<--- FractionalDec --->" << std::endl;
    FractionalDec fr1 = FractionalDec(1, 5);
    FractionalDec fr2 = FractionalDec(3, 4);
    std::cout.precision(16);
	if (double(fr1) == 0.2) { std::cout << "fr1 = 1/5" << std::endl; } else { throw std::exception(); }
	if (double(fr2) == 0.75) { std::cout << "fr2 = 3/4" << std::endl; } else { throw std::exception(); }
	if (fr1 < fr2) { std::cout << "fr1 < fr2" << std::endl; } else { throw std::exception(); }
	if (double(fr1 + fr2) == 0.95) { std::cout << "fr1 + fr2 = 19/20" << std::endl; } else { throw std::exception(); }
	if (double(fr2 - fr1) == 0.55) { std::cout << "fr2 - fr1 = 11/20" << std::endl; } else { throw std::exception(); }
	if (double(fr1.Square()) == (1.0 / 25.0)) { std::cout << "fr1^2 = 1/25" << std::endl; } else { throw std::exception(); }
	if (double(fr2.Square()) == (9.0 / 16.0)) { std::cout << "fr2^2 = 9/16" << std::endl; } else { throw std::exception(); }
	if (double(fr1 * fr1) != double(fr1.Square())) { throw std::exception(); }
	if (double(fr2 * fr2) != double(fr2.Square())) { throw std::exception(); }
	if (double(FractionalDec::Max() - fr2) == 0.25) { std::cout << "~fr2 = 1/4" << std::endl; } else { throw std::exception(); }
	if (double((fr1 * fr1).Sqrt()) != double(fr1)) { throw std::exception(); }
    std::cout << "sqrt(fr1) = " << double((fr1).Sqrt()) << std::endl;
    std::cout << "epsiron = " << double(FractionalDec::Epsiron()) << std::endl;
    std::cout << "~epsiron = " << double(FractionalDec::Max() - FractionalDec::Epsiron()) << std::endl;
    std::cout << "1 == ~epsiron = " << bool((FractionalDec::Max())==(FractionalDec::Max() - FractionalDec::Epsiron())) << std::endl;
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
