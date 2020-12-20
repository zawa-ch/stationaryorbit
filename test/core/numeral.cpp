//	stationaryorbit.test.core:/numeral
//	Copyright 2020 zawa-ch.
//	GPLv3 (or later) license
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//	See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.
//	If not, see <http://www.gnu.org/licenses/>.
//
#include <iostream>
#include <stdexcept>
#include "stationaryorbit/core.traits.hpp"
#include "stationaryorbit/core.numeral.hpp"
using namespace zawa_ch::StationaryOrbit;

void Test_FixedPoint();
void Test_Logic();
void Test_Point();
void Test_Proportion();
void Test_Range();
void Test_Rectangle();
void Test_Rotation();
int Test_Vector2d();
void Test_ZeroValue();

void Test_Numeral()
{
	Test_FixedPoint();
	Test_Logic();
	Test_Point();
	Test_Proportion();
	Test_Range();
	Test_Rectangle();
	Test_Rotation();
	Test_Vector2d();
	Test_ZeroValue();
}

void Test_FixedPoint()
{
	std::cout << "<--- FixedPoint --->" << std::endl;
	if (!Traits::HasArithmeticOperation<FixedPoint16q8_t>) { throw std::exception(); }
	auto f1 = FixedPoint16q8_t(16);
	auto f2 = FixedPoint16q8_t(0.125);
	if (double(f1) == 16) { std::cout << "f1 = " << double(f1) << std::endl; } else { throw std::exception(); }
	if (double(f2) == 0.125) { std::cout << "f2 = " << double(f2) << std::endl; } else { throw std::exception(); }
	if (double(f1 + f2) == 16.125) { std::cout << "f1 + f2 = " << double(f1 + f2) << std::endl; } else { throw std::exception(); }
	if (double(f1 - f2) == 15.875) { std::cout << "f1 - f2 = " << double(f1 - f2) << std::endl; } else { throw std::exception(); }
	if (double(f1 * f2) == 2) { std::cout << "f1 * f2 = " << double(f1 * f2) << std::endl; } else { throw std::exception(); }
	if (double(f1 / f2) == 128) { std::cout << "f1 / f2 = " << double(f1 / f2) << std::endl; } else { throw std::exception(); }
	if (FixedPoint32q16_t(f1) == FixedPoint32q16_t(16)) { std::cout << "f1 -> " << double(FixedPoint<uint32_t, 16>(16)) << std::endl; } else { throw std::exception(); }
	if (FixedPoint16q15_t(Proportion16_t(3, 4)) == FixedPoint16q15_t(0.75)) { std::cout << "(3/4) = 0.75" << std::endl; } else { throw std::exception(); }
	std::cout << "FixedPoint16q8_t::Max() = " << double(FixedPoint16q8_t::Max()) << std::endl;
	std::cout << "FixedPoint16q8_t::Min() = " << double(FixedPoint16q8_t::Min()) << std::endl;
	std::cout << "FixedPoint16q8_t::Epsilon() = " << double(FixedPoint16q8_t::Epsilon()) << std::endl;
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
	auto p1 = GeometricPoint(3, 4);
	auto p2 = GeometricPoint(2, 8);
	if ((p1 + p2) != GeometricPoint(5, 12)) { throw std::exception(); }
	std::cout << "p1 + p2 = (" << (p1 + p2).X() << ", " << (p1 + p2).Y() << ")" << std::endl;
	if ((p1 - p2) != GeometricPoint(1, -4)) { throw std::exception(); }
	std::cout << "p1 - p2 = (" << (p1 - p2).X() << ", " << (p1 - p2).Y() << ")" << std::endl;
	auto p3 = Point2D<int, Quadrants::DownRight>(p1);
	if (p3 != Point2D<int, Quadrants::DownRight>(3, -4)) { throw std::exception(); }
	auto fp1 = GeometricPointF(0.3, 1.8);
	auto fp2 = GeometricPointF(-3.1, 2.0);
	std::cout << "fp1 + fp2 = (" << (fp1 + fp2).X() << ", " << (fp1 + fp2).Y() << ")" << std::endl;
	std::cout << "fp1 - fp2 = (" << (fp1 - fp2).X() << ", " << (fp1 - fp2).Y() << ")" << std::endl;
	auto p4 = GeometricPoint(fp1.Round());
	std::cout << "p4 = (" << p4.X() << ", " << p4.Y() << ")" << std::endl;
}

void Test_Proportion()
{
	std::cout << "<--- Proportion --->" << std::endl;

	// 型トレイト
	static_assert(Traits::HasArithmeticOperation<Proportion8_t>, "ProportionがTraitsHasArithmeticOperationの要件を満たしません。");
	static_assert(!Traits::HasBitOperation<Proportion8_t>, "ProportionがTraitsHasBitOperationの要件を満たしました。");
	static_assert(!Traits::IsIntegerType<Proportion8_t>, "ProportionがTraitsIsIntegerTypeの要件を満たしました。");
	static_assert(Traits::IsComparable<Proportion8_t>, "ProportionがTraitsComparableの要件を満たしません。");
	static_assert(Traits::IsEquatable<Proportion8_t>, "ProportionがTraitsEquatableの要件を満たしません。");
	static_assert(Traits::HasSaturateOperation<Proportion8_t>, "ProportionがTraitsHasSaturateOperationの要件を満たしません。");
	static_assert(Traits::HasCheckedOperation<Proportion8_t>, "ProportionがTraitsHasCheckedOperationの要件を満たしません。");

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
	if (Proportion16_t(FixedPoint16q15_t(0.125)) == Proportion16_t(0.125)) { std::cout << "FP(0.125) == Prop(0.125)" << std::endl; } else { throw std::exception(); }
	static_assert(Proportion1_t::Max() == Proportion1_t(Proportion8_t::Max()), "Proportion1_t::Max() == Proportion1_t(Proportion8_t::Max())を満たしませんでした。");
}

void Test_Range()
{
	std::cout << "<--- Range --->" << std::endl;
	static_assert(IteratorTraits::IsIterator<Range<size_t>::IteratorType>, "Range<size_t>::IteratorTypeがIteratorTraits::IsIteratorの要件を満たしません。");
	static_assert(IteratorTraits::IsSequencialOrderIterator<Range<size_t>::IteratorType>, "Range<size_t>::IteratorTypeがIteratorTraits::IsIteratorの要件を満たしません。");
	static_assert(IteratorTraits::IsBidirectionalOrderIterator<Range<size_t>::IteratorType>, "Range<size_t>::IteratorTypeがIteratorTraits::IsBidirectionalOrderIteratorの要件を満たしません。");
	static_assert(Traits::IsSequencialOrder<Range<size_t>::IteratorType>, "Range<size_t>::IteratorTypeがTraits::IsSequencialOrderの要件を満たしません。");
	static_assert(Traits::IsBidirectionalOrder<Range<size_t>::IteratorType>, "Range<size_t>::IteratorTypeがTraits::IsBidirectionalOrderの要件を満たしません。");
	// 範囲forを用いて0..9の数値を列挙する
	for(auto i : Range(0, 10).GetStdIterator())
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
	// 逆イテレータを使用して5..11の数値を逆に列挙する
	for(auto i : Range(5, 12).GetStdReverseIterator())
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
	// 0.5fが0.0f以上1.0f未満であることを検査する
	static_assert(Range(0.0f, 1.0f).isIncluded(0.5f), "0.5fが0.0f以上1.0f未満ではありません。");
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

void Test_ZeroValue()
{
	static_assert(Zero == false, "Zero == false ではありません。");
	static_assert(Zero == 0, "Zero == 0 ではありません。");
	static_assert(Zero == 0L, "Zero == 0L ではありません。");
	static_assert(Zero == 0UL, "Zero == 0UL ではありません。");
	static_assert(Zero == 0.0, "Zero == 0.0 ではありません。");
	static_assert(Zero == '\0', "Zero == '\\0' ではありません。");
	static_assert(Zero == (void*)(0), "Zero == (void*)0 ではありません。");
	static_assert((5 + Zero) == 5, "5 + Zero == 5 ではありません。");
}
