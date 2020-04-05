#ifndef __stationaryorbit_graphics_core_colorspace__
#define __stationaryorbit_graphics_core_colorspace__
#include "rgbcolor.hpp"
#include "xyzcolor.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	class ColorSpace;
	class XYZMatrixRGBColorSpace;
	class RGBMatrixXYZColorSpace;

	class ColorSpace
	{
	public:
		static const XYZMatrixRGBColorSpace sRGB;
	};

	class XYZMatrixRGBColorSpace
		: public ColorSpace
	{
	private: // contains
		XYZColor _r;
		XYZColor _g;
		XYZColor _b;
	public: // construct
		XYZMatrixRGBColorSpace();
		XYZMatrixRGBColorSpace(const XYZColor& redpoint, const XYZColor& greenpoint, const XYZColor& bluepoint);
	public: // member
		///	@a RGBColor を @a XYZColor に変換します。
		XYZColor ConvertXYZ(const RGBColor& color) const;

		RGBMatrixXYZColorSpace Invert() const;

		bool Equals(const XYZMatrixRGBColorSpace& other) const;
	};

	class RGBMatrixXYZColorSpace
		: public ColorSpace
	{
	private: // contains
		RGBColor _x;
		RGBColor _y;
		RGBColor _z;
	public: // construct
		RGBMatrixXYZColorSpace();
		RGBMatrixXYZColorSpace(const RGBColor& xpoint, const RGBColor& ypoint, const RGBColor& zpoint);
	public: // member
		///	@a XYZColor を @a RGBColor に変換します。
		RGBColor ConvertRGB(const XYZColor& color) const;

		XYZMatrixRGBColorSpace Invert() const;

		bool Equals(const RGBMatrixXYZColorSpace& other) const;
	};
}
#endif // __stationaryorbit_graphics_core_colorspace__