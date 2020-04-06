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
	public: // construct
		XYZMatrixRGBColorSpace();
		XYZMatrixRGBColorSpace(const XYZColor& redpoint, const XYZColor& greenpoint, const XYZColor& bluepoint);
	public: // member
		///	@a RGBColor を @a XYZColor に変換します。
		XYZColor ConvertXYZ(const RGBColor& color) const;
		std::unique_ptr<RGBColorSpace> Clone() const;

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
	public: // construct
		RGBMatrixXYZColorSpace();
		RGBMatrixXYZColorSpace(const RGBColor& xpoint, const RGBColor& ypoint, const RGBColor& zpoint);
	public: // member
		///	@a XYZColor を @a RGBColor に変換します。
		RGBColor ConvertRGB(const XYZColor& color) const;
		std::unique_ptr<RGBInvertedColorSpace> Clone() const;

		XYZMatrixRGBColorSpace Invert() const;

		bool Equals(const RGBMatrixXYZColorSpace& other) const;
	};
}
#endif // __stationaryorbit_graphics_core_colorspace__