//	stationaryorbit/graphics-core/colorspace
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
#ifndef __stationaryorbit_graphics_core_colorspace__
#define __stationaryorbit_graphics_core_colorspace__
#include <memory>
#include "rgbcolor.hpp"
#include "xyzcolor.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	class ColorSpace;
	class RGBColorSpace;
	class RGBInvertedColorSpace;
	class XYZMatrixRGBColorSpace;
	class RGBMatrixXYZColorSpace;

	class ColorSpace
	{
	public:
		static const XYZMatrixRGBColorSpace sRGB;
		virtual ~ColorSpace() = default;
	};

	class RGBColorSpace
		: public ColorSpace
	{
	public:
		///	@a RGBColor を @a XYZColor に変換します。
		virtual XYZColor ConvertXYZ(const RGBColor& color) const = 0;
		virtual std::unique_ptr<RGBColorSpace> Clone() const = 0;
	};

	class RGBInvertedColorSpace
		: public ColorSpace
	{
	public:
		///	@a XYZColor を @a RGBColor に変換します。
		virtual RGBColor ConvertRGB(const XYZColor& color) const = 0;
		virtual std::unique_ptr<RGBInvertedColorSpace> Clone() const = 0;
	};

	class XYZMatrixRGBColorSpace
		: public RGBColorSpace
	{
	private: // contains
		XYZColor _r;
		XYZColor _g;
		XYZColor _b;
		RGBColor _gamma;
	public: // construct
		XYZMatrixRGBColorSpace();
		XYZMatrixRGBColorSpace(const XYZColor& redpoint, const XYZColor& greenpoint, const XYZColor& bluepoint, const RGBColor& gamma);
	public: // member
		///	@a RGBColor を @a XYZColor に変換します。
		XYZColor ConvertXYZ(const RGBColor& color) const;
		std::unique_ptr<RGBColorSpace> Clone() const;
		XYZColor& RedPoint();
		const XYZColor& RedPoint() const;
		XYZColor& GreenPoint();
		const XYZColor& GreenPoint() const;
		XYZColor& BluePoint();
		const XYZColor& BluePoint() const;
		RGBColor& Gamma();
		const RGBColor& Gamma() const;

		RGBMatrixXYZColorSpace Invert() const;

		bool Equals(const XYZMatrixRGBColorSpace& other) const;
	};

	class RGBMatrixXYZColorSpace
		: public RGBInvertedColorSpace
	{
	private: // contains
		RGBColor _x;
		RGBColor _y;
		RGBColor _z;
		RGBColor _gamma;
	public: // construct
		RGBMatrixXYZColorSpace();
		RGBMatrixXYZColorSpace(const RGBColor& xpoint, const RGBColor& ypoint, const RGBColor& zpoint, const RGBColor& gamma);
	public: // member
		///	@a XYZColor を @a RGBColor に変換します。
		RGBColor ConvertRGB(const XYZColor& color) const;
		std::unique_ptr<RGBInvertedColorSpace> Clone() const;
		RGBColor& XPoint();
		const RGBColor& XPoint() const;
		RGBColor& YPoint();
		const RGBColor& YPoint() const;
		RGBColor& ZPoint();
		const RGBColor& ZPoint() const;
		RGBColor& Gamma();
		const RGBColor& Gamma() const;

		XYZMatrixRGBColorSpace Invert() const;

		bool Equals(const RGBMatrixXYZColorSpace& other) const;
	};
}
#endif // __stationaryorbit_graphics_core_colorspace__