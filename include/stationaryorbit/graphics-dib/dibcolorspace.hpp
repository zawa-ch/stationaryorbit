#ifndef __stationaryorbit_graphics_dib_dibcolorspace__
#define __stationaryorbit_graphics_dib_dibcolorspace__
#include "stationaryorbit/graphics-core/colorspace"
#include "ciexyz.hpp"
namespace zawa_ch::StationaryOrbit::Graphics::DIB
{
	struct DIBColorSpace
	{
		CIEXYZTriple_t Matrix;
		uint32_t GammaR;
		uint32_t GammaG;
		uint32_t GammaB;

		explicit operator XYZMatrixRGBColorSpace() const;
		static DIBColorSpace FromXYZMatrixRGBColorSpace(const XYZMatrixRGBColorSpace& value);
	};
}
#endif // __stationaryorbit_graphics_dib_dibcolorspace__