//	stationaryorbit/core/rectangle
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
#ifndef __stationaryorbit_core_rectangle__
#define __stationaryorbit_core_rectangle__
#include "range.hpp"
#include "rectanglesize.hpp"
#include "point.hpp"
namespace zawa_ch::StationaryOrbit
{
	///	@a Point2D と @a Rect2DSize によって表される矩形範囲を表します。
	template<class T, Quadrants quad, class = void>
	struct Rectangle2D final
	{
		static_assert(Traits::IsNumeralType<T>, "テンプレート引数型 T は算術型である必要があります。");
	public:
		typedef T ValueType;
		typedef Point2D<T, quad> PointType;
		typedef Rect2DSize<T> SizeType;
	private:
		PointType _o;
		SizeType _s;
	public:
		constexpr Rectangle2D() = default;
		constexpr Rectangle2D(const PointType& origin, const SizeType& size) : _o(origin), _s(size) {}
		constexpr Rectangle2D(const ValueType& originx, const ValueType& originy, const ValueType& width, const ValueType& height) : _o(originx, originy), _s(width, height) {}
		template<Quadrants fromquad>
		constexpr Rectangle2D(const Rectangle2D<T, fromquad>& from) : _o(from.Origin()), _s(from.Size()) {}
		template<class fromT, Quadrants fromquad, std::enable_if_t<std::is_convertible_v<fromT, T>, int> = 0>
		constexpr Rectangle2D(const Rectangle2D<fromT, fromquad>& from) : _o(from.Origin()), _s(from.Size()) {}
		template<class fromT, Quadrants fromquad, std::enable_if_t<std::conjunction_v<std::negation<std::is_convertible<fromT, T>>, std::is_constructible<T, fromT>>, int> = 0>
		constexpr explicit Rectangle2D(const Rectangle2D<fromT, fromquad>& from) : _o(from.Origin()), _s(from.Size()) {}
		constexpr Rectangle2D(const ZeroValue_t&) : _o(Zero), _s(Zero) {}

		///	@a Rectangle2D の原点を表す @a PointType を取得します。
		[[nodiscard]] constexpr const PointType& Origin() const noexcept { return _o; }
		///	@a Rectangle2D の大きさを表す @a SizeType を取得します。
		[[nodiscard]] constexpr const SizeType& Size() const noexcept { return _s; }

		///	@a Rectangle2D の左端のx座標の値を取得します。
		[[nodiscard]] constexpr ValueType Left() const { if constexpr ((quad==Quadrants::UpLeft)||(quad==Quadrants::DownLeft)) { return (_o + _s).X(); } else { return _o.X(); } }
		///	@a Rectangle2D の右端のx座標の値を取得します。
		[[nodiscard]] constexpr ValueType Right() const { if constexpr ((quad==Quadrants::UpRight)||(quad==Quadrants::DownRight)) { return (_o + _s).X(); } else { return _o.X(); } }
		///	@a Rectangle2D の上端のy座標の値を取得します。
		[[nodiscard]] constexpr ValueType Top() const { if constexpr ((quad==Quadrants::UpRight)||(quad==Quadrants::UpLeft)) { return (_o + _s).Y(); } else { return _o.Y(); } }
		///	@a Rectangle2D の下端のy座標の値を取得します。
		[[nodiscard]] constexpr ValueType Bottom() const { if constexpr ((quad==Quadrants::DownRight)||(quad==Quadrants::DownLeft)) { return (_o + _s).Y(); } else { return _o.Y(); } }
		///	@a Rectangle2D の示す矩形の幅を取得します。
		[[nodiscard]] constexpr ValueType Width() const { return _s.Width(); }
		///	@a Rectangle2D の示す矩形の高さを取得します。
		[[nodiscard]] constexpr ValueType Height() const { return _s.Height(); }
		///	水平軸コンポーネントの値の範囲を示す @a Range を取得します。
		[[nodiscard]] constexpr Range<ValueType> XRange() const { return Range<ValueType>(_o.X(), _o.X() + _s.Width()); }
		///	垂直軸コンポーネントの値の範囲を示す @a Range を取得します。
		[[nodiscard]] constexpr Range<ValueType> YRange() const { return Range<ValueType>(_o.Y(), _o.Y() + _s.Height()); }

		///	指定された点が @a Rectangle2D の領域に含まれるかをテストします。
		[[nodiscard]] constexpr bool Contains(const PointType& point) const { return (_o.X() <= point.X())&&(_o.Y() <= point.Y())&&(point.X() <= (_o + _s).X())&&(point.Y() <= (_o + _s).Y()); }
		///	指定された @a Rectangle2D の領域すべてが @a Rectangle2D の領域に含まれるかをテストします。
		[[nodiscard]] constexpr bool Contains(const Rectangle2D<T, quad>& rect) const { return (_o.X() <= rect._o.X())&&(_o.Y() <= rect._o.Y())&&(rect._s.Width() <= _s.Width())&&(rect._s.Height() <= _s.Height()); }

		///	@a Rectangle2D の位置を @a offset 分移動します。
		[[nodiscard]] constexpr Rectangle2D<T, quad> Offset(const PointType& offset) const { return Rectangle2D<T, quad>(_o + offset, _s); }
		///	@a Rectangle2D の大きさを @a size 分拡げます。
		[[nodiscard]] constexpr Rectangle2D<T, quad> Inflate(const SizeType& size) const { return Rectangle2D<T, quad>(_o, _s + size); }

		[[nodiscard]] constexpr bool Equals(const Rectangle2D<T, quad>& other) const { return (_o == other._o)&&(_s == other._s); }
		[[nodiscard]] constexpr bool operator==(const Rectangle2D<T, quad>& other) const { return Equals(other); }
		[[nodiscard]] constexpr bool operator!=(const Rectangle2D<T, quad>& other) const { return !Equals(other); }

		///	四辺の座標から @a Rectangle2D オブジェクトを作成します。
		///	@param	left
		///	矩形の左端に位置する辺のx座標。
		///	@param	right
		///	矩形の右端に位置する辺のx座標。
		///	@param	top
		///	矩形の上端に位置する辺のy座標。
		///	@param	bottom
		///	矩形の下端に位置する辺のy座標。
		[[nodiscard]] constexpr static Rectangle2D<T, quad> FromEdge(const ValueType& left, const ValueType& right, const ValueType& top, const ValueType& bottom)
		{
			if constexpr (quad == Quadrants::UpRight) { return Rectangle2D<T, quad>(left, bottom, right - left, top - bottom); }
			if constexpr (quad == Quadrants::UpLeft) { return Rectangle2D<T, quad>(right, bottom, left - right, top - bottom); }
			if constexpr (quad == Quadrants::DownLeft) { return Rectangle2D<T, quad>(right, top, left - right, bottom - top); }
			if constexpr (quad == Quadrants::DownRight) { return Rectangle2D<T, quad>(left, top, right - left, bottom - top); }
		}
	private:
		template<class fromT, Quadrants fromquad, std::enable_if_t<std::is_constructible_v<T, fromT>, int> = 0>
		[[nodiscard]] constexpr static PointType ConvertPoint(const Rectangle2D<fromT, fromquad>& from)
		{
			if constexpr (quad == Quadrants::UpRight) { return PointType(T(from.Left()), T(from.Bottom())); }
			if constexpr (quad == Quadrants::UpLeft) { return PointType(T(from.Right()), T(from.Bottom())); }
			if constexpr (quad == Quadrants::DownLeft) { return PointType(T(from.Right()), T(from.Top())); }
			if constexpr (quad == Quadrants::DownRight) { return PointType(T(from.Left()), T(from.Top())); }
		}
	};
	///	@a Point2D と @a Rect2DSize によって表される矩形範囲を表します。
	///	@note
	///	こちらは @a std::is_floting_point_v が @a true の場合の特殊化です。
	template<class T, Quadrants quad>
	struct Rectangle2D<T, quad, std::enable_if_t<std::is_floating_point_v<T>>> final
	{
		static_assert(Traits::IsNumeralType<T>, "テンプレート引数型 T は算術型である必要があります。");
	public:
		typedef T ValueType;
		typedef Point2D<T, quad> PointType;
		typedef Rect2DSize<T> SizeType;
	private:
		PointType _o;
		SizeType _s;
	public:
		constexpr Rectangle2D() = default;
		constexpr Rectangle2D(const PointType& origin, const SizeType& size) : _o(origin), _s(size) {}
		constexpr Rectangle2D(const ValueType& originx, const ValueType& originy, const ValueType& width, const ValueType& height) : _o(originx, originy), _s(width, height) {}
		template<Quadrants fromquad>
		constexpr Rectangle2D(const Rectangle2D<T, fromquad>& from) : _o(from.Origin()), _s(from.Size()) {}
		template<class fromT, Quadrants fromquad, std::enable_if_t<std::is_convertible_v<fromT, T>, int> = 0>
		constexpr Rectangle2D(const Rectangle2D<fromT, fromquad>& from) : _o(from.Origin()), _s(from.Size()) {}
		template<class fromT, Quadrants fromquad, std::enable_if_t<std::conjunction_v<std::negation<std::is_convertible<fromT, T>>, std::is_constructible<T, fromT>>, int> = 0>
		constexpr explicit Rectangle2D(const Rectangle2D<fromT, fromquad>& from) : _o(from.Origin()), _s(from.Size()) {}
		constexpr Rectangle2D(const ZeroValue_t&) : _o(Zero), _s(Zero) {}

		///	@a Rectangle2D の原点を表す @a PointType を取得します。
		[[nodiscard]] constexpr const PointType& Origin() const noexcept { return _o; }
		///	@a Rectangle2D の大きさを表す @a SizeType を取得します。
		[[nodiscard]] constexpr const SizeType& Size() const noexcept { return _s; }

		///	@a Rectangle2D の左端のx座標の値を取得します。
		[[nodiscard]] constexpr ValueType Left() const { if constexpr ((quad==Quadrants::UpLeft)||(quad==Quadrants::DownLeft)) { return (_o + _s).X(); } else { return _o.X(); } }
		///	@a Rectangle2D の右端のx座標の値を取得します。
		[[nodiscard]] constexpr ValueType Right() const { if constexpr ((quad==Quadrants::UpRight)||(quad==Quadrants::DownRight)) { return (_o + _s).X(); } else { return _o.X(); } }
		///	@a Rectangle2D の上端のy座標の値を取得します。
		[[nodiscard]] constexpr ValueType Top() const { if constexpr ((quad==Quadrants::UpRight)||(quad==Quadrants::UpLeft)) { return (_o + _s).Y(); } else { return _o.Y(); } }
		///	@a Rectangle2D の下端のy座標の値を取得します。
		[[nodiscard]] constexpr ValueType Bottom() const { if constexpr ((quad==Quadrants::DownRight)||(quad==Quadrants::DownLeft)) { return (_o + _s).Y(); } else { return _o.Y(); } }
		///	@a Rectangle2D の示す矩形の幅を取得します。
		[[nodiscard]] constexpr ValueType Width() const { return _s.Width(); }
		///	@a Rectangle2D の示す矩形の高さを取得します。
		[[nodiscard]] constexpr ValueType Height() const { return _s.Height(); }
		///	水平軸コンポーネントの値の範囲を示す @a Range を取得します。
		[[nodiscard]] constexpr Range<ValueType> XRange() const { return Range<ValueType>(_o.X(), _o.X() + _s.Width()); }
		///	垂直軸コンポーネントの値の範囲を示す @a Range を取得します。
		[[nodiscard]] constexpr Range<ValueType> YRange() const { return Range<ValueType>(_o.Y(), _o.Y() + _s.Height()); }

		///	指定された点が @a Rectangle2D の領域に含まれるかをテストします。
		[[nodiscard]] constexpr bool Contains(const PointType& point) const { return (_o.X() <= point.X())&&(_o.Y() <= point.Y())&&(point.X() <= (_o + _s).X())&&(point.Y() <= (_o + _s).Y()); }
		///	指定された @a Rectangle2D の領域すべてが @a Rectangle2D の領域に含まれるかをテストします。
		[[nodiscard]] constexpr bool Contains(const Rectangle2D<T, quad>& rect) const { return (_o.X() <= rect._o.X())&&(_o.Y() <= rect._o.Y())&&(rect._s.Width() <= _s.Width())&&(rect._s.Height() <= _s.Height()); }

		///	@a Rectangle2D の位置を @a offset 分移動します。
		[[nodiscard]] constexpr Rectangle2D<T, quad> Offset(const PointType& offset) const { return Rectangle2D<T, quad>(_o + offset, _s); }
		///	@a Rectangle2D の大きさを @a size 分拡げます。
		[[nodiscard]] constexpr Rectangle2D<T, quad> Inflate(const SizeType& size) const { return Rectangle2D<T, quad>(_o, _s + size); }

		///	@a RectangleF を切り捨て方向に丸め、 @a Rectangle2D に変換します。
		[[nodiscard]] Rectangle2D<T, quad> Floor() const { return Rectangle2D<T, quad>(_o.Floor(), _s.Floor()); }
		///	@a RectangleF を切り上げ方向に丸め、 @a Rectangle2D に変換します。
		[[nodiscard]] Rectangle2D<T, quad> Ceiling() const { return Rectangle2D<T, quad>(_o.Ceiling(), _s.Ceiling()); }
		/// @a RectangleF を最も近い @a Rectangle2D に変換します。
		[[nodiscard]] Rectangle2D<T, quad> Round() const { return Rectangle2D<T, quad>(_o.Round(), _s.Round()); }

		[[nodiscard]] constexpr bool Equals(const Rectangle2D<T, quad>& other) const { return (_o == other._o)&&(_s == other._s); }
		[[nodiscard]] constexpr bool operator==(const Rectangle2D<T, quad>& other) const { return Equals(other); }
		[[nodiscard]] constexpr bool operator!=(const Rectangle2D<T, quad>& other) const { return !Equals(other); }

		///	四辺の座標から @a Rectangle2D オブジェクトを作成します。
		///	@param	left
		///	矩形の左端に位置する辺のx座標。
		///	@param	right
		///	矩形の右端に位置する辺のx座標。
		///	@param	top
		///	矩形の上端に位置する辺のy座標。
		///	@param	bottom
		///	矩形の下端に位置する辺のy座標。
		[[nodiscard]] constexpr static Rectangle2D<T, quad> FromEdge(const ValueType& left, const ValueType& right, const ValueType& top, const ValueType& bottom)
		{
			if constexpr (quad == Quadrants::UpRight) { return Rectangle2D<T, quad>(left, bottom, right - left, top - bottom); }
			if constexpr (quad == Quadrants::UpLeft) { return Rectangle2D<T, quad>(right, bottom, left - right, top - bottom); }
			if constexpr (quad == Quadrants::DownLeft) { return Rectangle2D<T, quad>(right, top, left - right, bottom - top); }
			if constexpr (quad == Quadrants::DownRight) { return Rectangle2D<T, quad>(left, top, right - left, bottom - top); }
		}
	private:
		template<class fromT, Quadrants fromquad, std::enable_if_t<std::is_constructible_v<T, fromT>, int> = 0>
		[[nodiscard]] constexpr static PointType ConvertPoint(const Rectangle2D<fromT, fromquad>& from)
		{
			if constexpr (quad == Quadrants::UpRight) { return PointType(T(from.Left()), T(from.Bottom())); }
			if constexpr (quad == Quadrants::UpLeft) { return PointType(T(from.Right()), T(from.Bottom())); }
			if constexpr (quad == Quadrants::DownLeft) { return PointType(T(from.Right()), T(from.Top())); }
			if constexpr (quad == Quadrants::DownRight) { return PointType(T(from.Left()), T(from.Top())); }
		}
	};

	extern template struct Rectangle2D<uint8_t, Quadrants::UpRight>;
	extern template struct Rectangle2D<uint8_t, Quadrants::UpLeft>;
	extern template struct Rectangle2D<uint8_t, Quadrants::DownLeft>;
	extern template struct Rectangle2D<uint8_t, Quadrants::DownRight>;
	extern template struct Rectangle2D<uint16_t, Quadrants::UpRight>;
	extern template struct Rectangle2D<uint16_t, Quadrants::UpLeft>;
	extern template struct Rectangle2D<uint16_t, Quadrants::DownLeft>;
	extern template struct Rectangle2D<uint16_t, Quadrants::DownRight>;
	extern template struct Rectangle2D<uint32_t, Quadrants::UpRight>;
	extern template struct Rectangle2D<uint32_t, Quadrants::UpLeft>;
	extern template struct Rectangle2D<uint32_t, Quadrants::DownLeft>;
	extern template struct Rectangle2D<uint32_t, Quadrants::DownRight>;
	extern template struct Rectangle2D<uint64_t, Quadrants::UpRight>;
	extern template struct Rectangle2D<uint64_t, Quadrants::UpLeft>;
	extern template struct Rectangle2D<uint64_t, Quadrants::DownLeft>;
	extern template struct Rectangle2D<uint64_t, Quadrants::DownRight>;
	extern template struct Rectangle2D<int8_t, Quadrants::UpRight>;
	extern template struct Rectangle2D<int8_t, Quadrants::UpLeft>;
	extern template struct Rectangle2D<int8_t, Quadrants::DownLeft>;
	extern template struct Rectangle2D<int8_t, Quadrants::DownRight>;
	extern template struct Rectangle2D<int16_t, Quadrants::UpRight>;
	extern template struct Rectangle2D<int16_t, Quadrants::UpLeft>;
	extern template struct Rectangle2D<int16_t, Quadrants::DownLeft>;
	extern template struct Rectangle2D<int16_t, Quadrants::DownRight>;
	extern template struct Rectangle2D<int32_t, Quadrants::UpRight>;
	extern template struct Rectangle2D<int32_t, Quadrants::UpLeft>;
	extern template struct Rectangle2D<int32_t, Quadrants::DownLeft>;
	extern template struct Rectangle2D<int32_t, Quadrants::DownRight>;
	extern template struct Rectangle2D<int64_t, Quadrants::UpRight>;
	extern template struct Rectangle2D<int64_t, Quadrants::UpLeft>;
	extern template struct Rectangle2D<int64_t, Quadrants::DownLeft>;
	extern template struct Rectangle2D<int64_t, Quadrants::DownRight>;
	extern template struct Rectangle2D<float, Quadrants::UpRight>;
	extern template struct Rectangle2D<float, Quadrants::UpLeft>;
	extern template struct Rectangle2D<float, Quadrants::DownLeft>;
	extern template struct Rectangle2D<float, Quadrants::DownRight>;
	extern template struct Rectangle2D<double, Quadrants::UpRight>;
	extern template struct Rectangle2D<double, Quadrants::UpLeft>;
	extern template struct Rectangle2D<double, Quadrants::DownLeft>;
	extern template struct Rectangle2D<double, Quadrants::DownRight>;

	template<Quadrants quad> struct Rectangle;
	template<Quadrants quad> struct RectangleF;

	template<Quadrants quad = Quadrants::UpRight>
	///	@a Point と @a RectangleSize によって表される矩形範囲を表します。
	struct Rectangle final
	{
	public: // types
		///	矩形範囲の起点を表す @a Point 型。
		typedef Point<quad> PointType;
		///	矩形範囲の大きさを表す @a RectangleSize 型。
		typedef RectangleSize SizeType;
	private: // contains
		PointType _p;
		SizeType _s;
	public: // construct
		constexpr Rectangle() : _p(), _s() {}
		///	起点となる座標、および大きさから @a Rectangle を初期化します。
		constexpr Rectangle(const PointType& point, const SizeType& size) : _p(point), _s(size) {}
		///	起点となる座標、および大きさから @a Rectangle を初期化します。
		constexpr Rectangle(const int& x, const int& y, const int& width, const int& height) : _p(PointType(x, y)), _s(SizeType(width, height)) {}
		///	異なる @a Quadrants を持つ @a Rectangle を変換します。
		template<Quadrants fromquad>
		constexpr explicit Rectangle(const Rectangle<fromquad>& from) : _p(ConvertPoint(from)), _s(from.Size()) {}
	public: // copy/move/destruct
		~Rectangle() = default;
	public: // member
		///	@a Rectangle の原点を表す @a Point を取得します。
		constexpr const PointType& Location() const { return _p; }
		///	@a Rectangle の大きさを表す @a RectangleSize を取得します。
		constexpr const SizeType& Size() const { return _s; }
		///	@a Rectangle の左端のx座標の値を取得します。
		constexpr int Left() const { if constexpr ((quad==Quadrants::UpLeft)||(quad==Quadrants::DownLeft)) { return (_p + _s).X(); } else { return _p.X(); } }
		///	@a Rectangle の右端のx座標の値を取得します。
		constexpr int Right() const { if constexpr ((quad==Quadrants::UpRight)||(quad==Quadrants::DownRight)) { return (_p + _s).X(); } else { return _p.X(); } }
		///	@a Rectangle の上端のy座標の値を取得します。
		constexpr int Top() const { if constexpr ((quad==Quadrants::UpRight)||(quad==Quadrants::UpLeft)) { return (_p + _s).Y(); } else { return _p.Y(); } }
		///	@a Rectangle の下端のy座標の値を取得します。
		constexpr int Bottom() const { if constexpr ((quad==Quadrants::DownRight)||(quad==Quadrants::DownLeft)) { return (_p + _s).Y(); } else { return _p.Y(); } }
		///	@a Rectangle の示す矩形の幅を取得します。
		constexpr int Width() const { return _s.Width(); }
		///	@a Rectangle の示す矩形の高さを取得します。
		constexpr int Height() const { return _s.Height(); }
		///	水平軸コンポーネントの値の範囲を示す @a Range を取得します。
		constexpr Range<int> XRange() const { return Range(_p.X(), _p.X() + _s.Width()); }
		///	垂直軸コンポーネントの値の範囲を示す @a Range を取得します。
		constexpr Range<int> YRange() const { return Range(_p.Y(), _p.Y() + _s.Height()); }
		///	この @a Rectangle を空のオブジェクトと比較します。
		constexpr bool IsEmpty() const { return *this == Empty(); }

		///	指定された点が @a Rectangle の領域に含まれるかをテストします。
		constexpr bool Contains(const PointType& point) const { return (_p.X() <= point.X())&&(_p.Y() <= point.Y())&&(point.X() <= (_p + _s).X())&&(point.Y() <= (_p + _s).Y()); }
		///	指定された @a Rectangle の領域すべてが @a Rectangle の領域に含まれるかをテストします。
		constexpr bool Contains(const Rectangle<quad>& rect) const { return (_p.X() <= rect._p.X())&&(_p.Y() <= rect._p.Y())&&(rect._s.Width() <= _s.Width())&&(rect._s.Height() <= _s.Height()); }

		///	@a Rectangle の位置を @a offset 分移動します。
		constexpr Rectangle<quad> Offset(const PointType& offset) const { return Rectangle<quad>(_p + offset, _s); }
		///	@a Rectangle の大きさを @a size 分拡げます。
		constexpr Rectangle<quad> Inflate(const SizeType& size) const { return Rectangle<quad>(_p, _s + size); }

		///	四辺の座標から @a Rectangle オブジェクトを作成します。
		///	@param	left
		///	矩形の左端に位置する辺のx座標。
		///	@param	right
		///	矩形の右端に位置する辺のx座標。
		///	@param	top
		///	矩形の上端に位置する辺のy座標。
		///	@param	bottom
		///	矩形の下端に位置する辺のy座標。
		constexpr static Rectangle<quad> FromEdge(const int& left, const int& right, const int& top, const int& bottom)
		{
			if constexpr (quad == Quadrants::UpRight) { return Rectangle<quad>(left, bottom, right - left, top - bottom); }
			if constexpr (quad == Quadrants::UpLeft) { return Rectangle<quad>(right, bottom, left - right, top - bottom); }
			if constexpr (quad == Quadrants::DownLeft) { return Rectangle<quad>(right, top, left - right, bottom - top); }
			if constexpr (quad == Quadrants::DownRight) { return Rectangle<quad>(left, top, right - left, bottom - top); }
		}

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const Rectangle<quad>& other) const { return (_p == other._p)&&(_s == other._s); }
		constexpr bool operator==(const Rectangle<quad>& other) const { return Equals(other); }
		constexpr bool operator!=(const Rectangle<quad>& other) const { return !Equals(other); }

		///	空の @a Rectangle を表します。
		constexpr static Rectangle<quad> Empty() { return Rectangle<quad>{ PointType::Empty(), SizeType::Empty() }; }
	private:
		template<Quadrants fromquad>
		constexpr static PointType ConvertPoint(const Rectangle<fromquad>& from)
		{
			if constexpr (quad == Quadrants::UpRight) { return PointType(from.Left(), from.Bottom()); }
			if constexpr (quad == Quadrants::UpLeft) { return PointType(from.Right(), from.Bottom()); }
			if constexpr (quad == Quadrants::DownLeft) { return PointType(from.Right(), from.Top()); }
			if constexpr (quad == Quadrants::DownRight) { return PointType(from.Left(), from.Top()); }
		}
	};
	template<Quadrants quad = Quadrants::UpRight>
	///	@a PointF と @a RectangleSizeF によって表される矩形範囲を表します。
	struct RectangleF final
	{
	public: // types
		///	矩形範囲の起点を表す @a PointF 型。
		typedef PointF<quad> PointType;
		///	矩形範囲の大きさを表す @a RectangleSizeF 型。
		typedef RectangleSizeF SizeType;
	private: // contains
		PointType _p;
		SizeType _s;
	public: // construct
		constexpr RectangleF() : _p(), _s() {}
		///	起点となる座標、および大きさから @a RectangleF を初期化します。
		constexpr RectangleF(const PointType& point, const SizeType& size) : _p(point), _s(size) {}
		///	起点となる座標、および大きさから @a RectangleF を初期化します。
		constexpr RectangleF(const float& x, const float& y, const float& width, const float& height) : _p(PointType(x, y)), _s(SizeType(width, height)) {}
		///	@a Rectangle を @a RectangleF に変換します。
		constexpr RectangleF(const Rectangle<quad>& rect) : _p(rect.Location()), _s(rect.Size()) {}
		///	異なる @a Quadrants を持つ @a RectangleF を変換します。
		template<Quadrants fromquad>
		constexpr explicit RectangleF(const RectangleF<fromquad>& from) : _p(ConvertPoint(from)), _s(from.SizeType()) {}
	public: // copy/move/destruct
		~RectangleF() = default;
	public: // member
		///	@a RectangleF の原点を表す @a PointF を取得します。
		constexpr const PointType& Location() const { return _p; }
		///	@a RectangleF の大きさを表す @a SizeType を取得します。
		constexpr const SizeType& Size() const { return _s; }
		///	@a RectangleF の左端のx座標の値を取得します。
		constexpr float Left() const { if constexpr ((quad==Quadrants::UpLeft)||(quad==Quadrants::DownLeft)) { return (_p + _s).X(); } else { return _p.X(); } }
		///	@a RectangleF の右端のx座標の値を取得します。
		constexpr float Right() const { if constexpr ((quad==Quadrants::UpRight)||(quad==Quadrants::DownRight)) { return (_p + _s).X(); } else { return _p.X(); } }
		///	@a RectangleF の上端のy座標の値を取得します。
		constexpr float Top() const { if constexpr ((quad==Quadrants::UpRight)||(quad==Quadrants::UpLeft)) { return (_p + _s).Y(); } else { return _p.Y(); } }
		///	@a RectangleF の下端のy座標の値を取得します。
		constexpr float Bottom() const { if constexpr ((quad==Quadrants::DownRight)||(quad==Quadrants::DownLeft)) { return (_p + _s).Y(); } else { return _p.Y(); } }
		///	@a RectangleF の示す矩形の幅を取得します。
		constexpr float Width() const { return _s.Width(); }
		///	@a RectangleF の示す矩形の高さを取得します。
		constexpr float Height() const { return _s.Height(); }
		///	水平軸コンポーネントの値の範囲を示す @a Range を取得します。
		constexpr Range<float> XRange() const { return Range(_p.X(), _p.X() + _s.Width()); }
		///	垂直軸コンポーネントの値の範囲を示す @a Range を取得します。
		constexpr Range<float> YRange() const { return Range(_p.Y(), _p.Y() + _s.Height()); }
		///	この @a RectangleF を空のオブジェクトと比較します。
		constexpr bool IsEmpty() const { return *this == Empty(); }

		///	指定された点が @a RectangleF の領域に含まれるかをテストします。
		constexpr bool Contains(const PointType& point) const { return (_p.X() <= point.X())&&(_p.Y() <= point.Y())&&(point.X() <= (_p + _s).X())&&(point.Y() <= (_p + _s).Y()); }
		///	指定された @a RectangleF の領域すべてが @a RectangleF の領域に含まれるかをテストします。
		constexpr bool Contains(const RectangleF<quad>& rect) const { return (_p.X() <= rect._p.X())&&(_p.Y() <= rect._p.Y())&&(rect._s.Width() <= _s.Width())&&(rect._s.Height() <= _s.Height()); }

		///	@a RectangleF の位置を @a offset 分移動します。
		constexpr RectangleF<quad> Offset(const PointType& offset) const { return RectangleF<quad>(_p + offset, _s); }
		///	@a RectangleF の大きさを @a size 分拡げます。
		constexpr RectangleF<quad> Inflate(const SizeType& size) const { return RectangleF<quad>(_p, _s + size); }

		///	四辺の座標から @a RectangleF オブジェクトを作成します。
		///	@param	left
		///	矩形の左端に位置する辺のx座標。
		///	@param	right
		///	矩形の右端に位置する辺のx座標。
		///	@param	top
		///	矩形の上端に位置する辺のy座標。
		///	@param	bottom
		///	矩形の下端に位置する辺のy座標。
		constexpr static RectangleF<quad> FromEdge(const float& left, const float& right, const float& top, const float& bottom)
		{
			if constexpr (quad == Quadrants::UpRight) { return RectangleF<quad>(left, bottom, right - left, top - bottom); }
			if constexpr (quad == Quadrants::UpLeft) { return RectangleF<quad>(right, bottom, left - right, top - bottom); }
			if constexpr (quad == Quadrants::DownLeft) { return RectangleF<quad>(right, top, left - right, bottom - top); }
			if constexpr (quad == Quadrants::DownRight) { return RectangleF<quad>(left, top, right - left, bottom - top); }
		}

		constexpr explicit operator Rectangle<quad>() const { return Rectangle<quad>(Point(_p), SizeType(_s)); }

		///	@a RectangleF を切り捨て方向に丸め、 @a Rectangle に変換します。
		Rectangle<quad> Floor() const { return Rectangle<quad>(_p.Floor(), _s.Floor()); }
		///	@a RectangleF を切り上げ方向に丸め、 @a Rectangle に変換します。
		Rectangle<quad> Ceiling() const { return Rectangle<quad>(_p.Ceiling(), _s.Ceiling()); }
		/// @a RectangleF を最も近い @a Rectangle に変換します。
		Rectangle<quad> Round() const { return Rectangle<quad>(_p.Round(), _s.Round()); }

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const RectangleF<quad>& other) const { return (_p == other._p)&&(_s == other._s); }
		constexpr bool operator==(const RectangleF<quad>& other) const { return Equals(other); }
		constexpr bool operator!=(const RectangleF<quad>& other) const { return !Equals(other); }

		///	空の @a RectangleF を表します。
		constexpr static RectangleF<quad> Empty() { return RectangleF<quad>{ PointType::Empty(), SizeType::Empty() }; }
	private:
		template<Quadrants fromquad>
		constexpr static PointType ConvertPoint(const RectangleF<fromquad>& from)
		{
			if constexpr (quad == Quadrants::UpRight) { return PointType(from.Left(), from.Bottom()); }
			if constexpr (quad == Quadrants::UpLeft) { return PointType(from.Right(), from.Bottom()); }
			if constexpr (quad == Quadrants::DownLeft) { return PointType(from.Right(), from.Top()); }
			if constexpr (quad == Quadrants::DownRight) { return PointType(from.Left(), from.Top()); }
		}
	};

	///	幾何学的な座標軸上で表される @a Rectangle 。
	typedef Rectangle2D<int, Quadrants::UpRight> GeometricRectangle;
	///	幾何学的な座標軸上で表される @a RectangleF 。
	typedef Rectangle2D<float, Quadrants::UpRight> GeometricRectangleF;

}
#endif // __stationaryorbit_core_rectangle__