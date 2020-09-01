#include <iostream>
#include <stdexcept>
#include "stationaryorbit/core.numeral.hpp"
using namespace zawa_ch::StationaryOrbit;

void Test_FixedPoint();
void Test_FractionalDec();
void Test_Logic();
void Test_Point();
void Test_Proportion();
void Test_Range();
void Test_Rectangle();
void Test_Rotation();
int Test_Vector2d();

void Test_Numeral()
{
	Test_FixedPoint();
	Test_FractionalDec();
	Test_Logic();
	Test_Point();
	Test_Proportion();
	Test_Range();
	Test_Rectangle();
	Test_Rotation();
	Test_Vector2d();
}

void Test_FixedPoint()
{
	std::cout << "<--- FixedPoint --->" << std::endl;
	auto f1 = FixedPoint16q8_t(16);
	auto f2 = FixedPoint16q8_t(0.125);
	if (double(f1) == 16) { std::cout << "f1 = " << double(f1) << std::endl; } else { throw std::exception(); }
	if (double(f2) == 0.125) { std::cout << "f2 = " << double(f2) << std::endl; } else { throw std::exception(); }
	if (double(f1 + f2) == 16.125) { std::cout << "f1 + f2 = " << double(f1 + f2) << std::endl; } else { throw std::exception(); }
	if (double(f1 - f2) == 15.875) { std::cout << "f1 - f2 = " << double(f1 - f2) << std::endl; } else { throw std::exception(); }
	if (double(f1 * f2) == 2) { std::cout << "f1 * f2 = " << double(f1 * f2) << std::endl; } else { throw std::exception(); }
	if (double(f1 / f2) == 128) { std::cout << "f1 / f2 = " << double(f1 / f2) << std::endl; } else { throw std::exception(); }
	if (FixedPoint32q16_t(f1) == FixedPoint32q16_t(16)) { std::cout << "f1 -> " << double(FixedPoint<uint32_t, 16>(16)) << std::endl; } else { throw std::exception(); }
	std::cout << "FixedPoint16q8_t::Max() = " << double(FixedPoint16q8_t::Max()) << std::endl;
	std::cout << "FixedPoint16q8_t::Min() = " << double(FixedPoint16q8_t::Min()) << std::endl;
	std::cout << "FixedPoint16q8_t::Epsiron() = " << double(FixedPoint16q8_t::Epsiron()) << std::endl;
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

void Test_Logic()
{
	std::cout << "<--- Logic --->" << std::endl;
	std::cout << Logic::True() << std::endl;
	if (bool(Logic::Indefinited() || Logic::True())) { std::cout << "I | T -> T" << std::endl; } else { throw std::exception(); }
	if (!bool(Logic::Indefinited() && Logic::False())) { std::cout << "I & F -> F" << std::endl; } else { throw std::exception(); }
	if ((!Logic::Indefinited()) == Logic::Indefinited()) { std::cout << "!I -> I" << std::endl; } else { throw std::exception(); }
	if (Logic::Undefined() != Logic::Undefined()) { std::cout << "U != U" << std::endl; } else { throw std::exception(); }
}

void Test_Point()
{
	std::cout << "<--- Point --->" << std::endl;
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

void Test_Proportion()
{
	std::cout << "<--- Proportion --->" << std::endl;
	auto p1 = Proportion8_t(0.5);
	auto p2 = Proportion8_t(0.25);
	std::cout.precision(16);
	std::cout << "p1 = " << double(p1) << std::endl;
	std::cout << "p2 = " << double(p2) << std::endl;
	if (p1 > p2) { std::cout << "p1 > p2" << std::endl; } else { throw std::exception(); }
	if (p1 + p2 == Proportion8_t::DirectConstruct(192)) { std::cout << "p1 + p2 = " << double(p1 + p2) << std::endl; } else { throw std::exception(); }
	if (p1 - p2 == Proportion8_t(0.25)) { std::cout << "p2 - p1 = " << double(p1 - p2) << std::endl; } else { throw std::exception(); }
	if (p1 * p2 == Proportion8_t(0.125)) { std::cout << "p1 * p2 = " << double(p1 * p2) << std::endl; } else { throw std::exception(); }
	if (p2 / p1 == Proportion8_t::DirectConstruct(127)) { std::cout << "p2 / p1 = " << double(p2 / p1) << std::endl; } else { throw std::exception(); }
	auto p3 = Proportion32_t(0.5);
	if (p1 == Proportion8_t(p3)) { std::cout << "p1 = p3 = " << double(p3) << std::endl; } else { throw std::exception(); }
	std::cout << "Proportion64_t(p2) = " << double(Proportion64_t(p2)) << std::endl;
	std::cout << "Proportion64_t(p2).Data = " << Proportion64_t(p2).Data() << std::endl;
	if (Proportion1_t::Max() == Proportion1_t(Proportion8_t(1.0))) { std::cout << "Proportion1_t::Max() = " << double(Proportion1_t::Max()) << std::endl; } else { throw std::exception(); }
}

void Test_Range()
{
	std::cout << "<--- Range --->" << std::endl;
	// 範囲forを用いて0..9の数値を列挙する
	for(auto i : Range(0, 10))
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
	// 逆イテレータを使用して5..11の数値を逆に列挙する
	auto range = Range(5, 12);
	auto rit = range.rbegin();
	do
	{
		auto i = *rit;
		std::cout << i << " ";
	} while((++rit)!=range.rend());
	std::cout << std::endl;
	// 0.5fが0.0f以上1.0f未満であることを検査する
	auto frange = Range(0.0f, 1.0f);
	if (frange.isIncluded(0.5f))
	{
		std::cout << "0.0 <= " << 0.5f << " < 1.0f" << std::endl;
	}
	else
	{
		throw std::exception();
	}
}

void Test_Rectangle()
{
	std::cout << "<--- Rectangle --->" << std::endl;
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

void Test_Rotation()
{
	std::cout << "<--- Rotation --->" << std::endl;
	Rotation rot1 = Rotation(30, RotationUnit::Degree);
	Rotation rot2 = Rotation(0.5 * M_PI, RotationUnit::Radian);
	Rotation rot3 = Rotation(60, RotationUnit::Degree);

	std::cout << "rot1 = " << rot1.getRadian() << "rad" << std::endl;
	std::cout << "rot2 = " << rot2.getDegree() << "deg" << std::endl;
	std::cout << "rot1 + rot2 = " << (rot1 + rot2).getDegree() << "deg" << std::endl;
	std::cout << "rot1 - rot2 = " << (rot1 - rot2).getDegree() << "deg" << std::endl;
	std::cout << "rot2 * 2.0 = " << (rot2 * 2.0).getDegree() << "deg" << std::endl;
	std::cout << "rot1 / 2.0 = " << (rot1 * 2.0).getDegree() << "deg" << std::endl;
}

int Test_Vector2d()
{
	std::cout << "<--- Vector2d --->" << std::endl;
	Vector2d vec1 = Vector2d(3, 4);
	Vector2d vec2 = Vector2d(10, Rotation(-30, RotationUnit::Degree));

	std::cout << "vec1 = (" << vec1.getMagnitude() << "∠" << vec1.getRotation().getDegree() << "deg)" << std::endl;
	std::cout << "vec2 = (" << vec2.getX() << ", " << vec2.getY() << ")" << std::endl;
	std::cout << "vec1 + vec2 = (" << (vec1 + vec2).getX() << ", " << (vec1 + vec2).getY() << ")" << std::endl;
	std::cout << "vec1 - vec2 = (" << (vec1 - vec2).getX() << ", " << (vec1 - vec2).getY() << ")" << std::endl;
	std::cout << "vec1 ・ vec2 = " << vec1.DotProduct(vec2) << std::endl;

	if (vec1 < vec2)
	{
		std::cout << "vec1 < vec2" << std::endl;
	}
	else
	{
		return -1;
	}

	return 0;
}
