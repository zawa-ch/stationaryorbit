//	stationaryorbit/core/rectanglesize
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
#ifndef __stationaryorbit_core_size__
#define __stationaryorbit_core_size__
#include <cmath>
#include "range.hpp"
namespace zawa_ch::StationaryOrbit
{
	struct RectangleSize;
	struct RectangleSizeF;

	///	幅・高さを持つオブジェクトの大きさを表します。
	struct RectangleSize final
	{
	private: // contains
		int _w;
		int _h;
	public: // construct
		constexpr RectangleSize() : _w(), _h() {}
		constexpr RectangleSize(const int& width, const int& height) : _w(width), _h(height) {}
	public: // copy/move/destruct
		RectangleSize(const RectangleSize&) = default;
		RectangleSize& operator=(const RectangleSize&) = default;
		RectangleSize(RectangleSize&&) = default;
		RectangleSize& operator=(RectangleSize&&) = default;
		~RectangleSize() = default;
	public: // member
		///	水平軸の値を取得します。
		constexpr const int& Width() const { return _w; }
		///	垂直軸の値を取得します。
		constexpr const int& Height() const { return _h; }
		///	水平軸コンポーネントの値の範囲を示す @a Range を取得します。
		constexpr Range<int> XRange() const { return Range(0, _w); }
		///	垂直軸コンポーネントの値の範囲を示す @a Range を取得します。
		constexpr Range<int> YRange() const { return Range(0, _h); }
		constexpr bool IsEmpty() const { return (_w==0)&&(_h==0); }

		constexpr RectangleSize operator+(const RectangleSize& other) const { return RectangleSize(_w + other._w, _h + other._h); }
		constexpr RectangleSize& operator+=(const RectangleSize& other) { return *this = *this + other; }
		constexpr RectangleSize operator-(const RectangleSize& other) const { return RectangleSize(_w - other._w, _h - other._h); }
		constexpr RectangleSize& operator-=(const RectangleSize& other) { return *this = *this - other; }

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const RectangleSize& value) const { return (_w == value._w)&&(_h == value._h); }
		constexpr bool operator==(const RectangleSize& value) const { return Equals(value); }
		constexpr bool operator!=(const RectangleSize& value) const { return !Equals(value); }

		///	空の @a RectangleSize を表します。
		static constexpr RectangleSize Empty() { return RectangleSize{}; }
	};
	///	幅・高さを持つオブジェクトの大きさを表します。
	struct RectangleSizeF final
	{
	private: // contains
		float _w;
		float _h;
	public: // construct
		constexpr RectangleSizeF() : _w(), _h() {}
		constexpr RectangleSizeF(const float& width, const float& height) : _w(width), _h(height) {}
		constexpr RectangleSizeF(const RectangleSize& value) : _w(value.Width()), _h(value.Height()) {}
	public: // copy/move/destruct
		RectangleSizeF(const RectangleSizeF&) = default;
		RectangleSizeF& operator=(const RectangleSizeF&) = default;
		RectangleSizeF(RectangleSizeF&&) = default;
		RectangleSizeF& operator=(RectangleSizeF&&) = default;
		~RectangleSizeF() = default;
	public: // member
		///	水平軸コンポーネントを取得します。
		constexpr const float& Width() const { return _w; }
		///	垂直軸コンポーネントを取得します。
		constexpr const float& Height() const { return _h; }
		constexpr bool IsEmpty() const { return (_w==0)&&(_h==0); }

		constexpr RectangleSizeF operator+(const RectangleSizeF& other) const { return RectangleSizeF(_w + other._w, _h + other._h); }
		constexpr RectangleSizeF& operator+=(const RectangleSizeF& other) { return *this = *this + other; }
		constexpr RectangleSizeF operator-(const RectangleSizeF& other) const { return RectangleSizeF(_w - other._w, _h - other._h); }
		constexpr RectangleSizeF& operator-=(const RectangleSizeF& other) { return *this = *this - other; }
		constexpr RectangleSizeF operator*(const RectangleSizeF& other) const { return RectangleSizeF(_w * other._w, _h * other._h); }
		constexpr RectangleSizeF operator*(const float& other) const { return RectangleSizeF(_w * other, _h * other); }
		constexpr RectangleSizeF& operator*=(const float& other) { return *this = *this * other; }
		constexpr RectangleSizeF operator/(const RectangleSizeF& other) const { return RectangleSizeF(_w / other._w, _h / other._h); }
		constexpr RectangleSizeF operator/(const float& other) const { return RectangleSizeF(_w / other, _h / other); }
		constexpr RectangleSizeF& operator/=(const float& other) { return *this = *this / other; }

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const RectangleSizeF& other) const { return (_w == other._w)&&(_h == other._h); }
		constexpr bool operator==(const RectangleSizeF& other) const { return Equals(other); }
		constexpr bool operator!=(const RectangleSizeF& other) const { return !Equals(other); }

		constexpr explicit operator RectangleSize() const { return RectangleSize(int(_w), int(_h)); }

		///	@a RectangleSizeF の小数部を抜き出します。
		RectangleSizeF Extract() const { return RectangleSizeF(_w - truncf(_w), _h - truncf(_h)); }
		///	@a RectangleSizeF を切り捨て方向に丸め、 @a RectangleSize に変換します。
		RectangleSize Floor() const { return RectangleSize(floorf(_w), floorf(_h)); }
		///	@a RectangleSizeF を切り上げ方向に丸め、 @a RectangleSize に変換します。
		RectangleSize Ceiling() const { return RectangleSize(ceilf(_w), ceilf(_h)); }
		/// @a RectangleSizeF を最も近い @a RectangleSize に変換します。
		RectangleSize Round() const { return RectangleSize(roundf(_w), roundf(_h)); }

		///	空の @a RectangleSizeF を表します。
		static constexpr RectangleSizeF Empty() { return RectangleSizeF{}; }
	};

}
#endif // __stationaryorbit_core_size__