//	stationaryorbit/graphics-core/colorblending
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
#ifndef __stationaryorbit_graphics_core_colorblending__
#define __stationaryorbit_graphics_core_colorblending__
#include "colortraits.hpp"
#include "relativecolor.hpp"
#include "cmycolor.hpp"
#include "cmykcolor.hpp"
#include "rgbcolor.hpp"
#include "xyzcolor.hpp"
#include "yuvcolor.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	class ColorBlending final
	{
	private:
		ColorBlending() = delete;
		ColorBlending(const ColorBlending&) = delete;
		ColorBlending(ColorBlending&&) = delete;
		~ColorBlending() = delete;
	public:
		template<class Tp>
		[[nodiscard]] static constexpr ChannelValue<Tp> Normal(const ChannelValue<Tp>& backdrop, const ChannelValue<Tp>& source)
		{
			// B(Cb, Cs) = Cs
			return source;
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor Normal(const Tcolor& backdrop, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// B(Cb, Cs) = Cs
			return source;
		}
		template<class Tp>
		[[nodiscard]] static constexpr ChannelValue<Tp> Multiply(const ChannelValue<Tp>& backdrop, const ChannelValue<Tp>& source)
		{
			// B(Cb, Cs) = Cb x Cs
			return backdrop * source;
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor Multiply(const Tcolor& backdrop, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// B(Cb, Cs) = Cb x Cs
			return backdrop * source;
		}
		template<class Tp>
		[[nodiscard]] static constexpr ChannelValue<Tp> Screen(const ChannelValue<Tp>& backdrop, const ChannelValue<Tp>& source)
		{
			// B(Cb, Cs) = 1 - [(1 - Cb) x (1 - Cs)]
			//           = Cb + Cs -(Cb x Cs)
			return ~((~backdrop) * (~source));
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor Screen(const Tcolor& backdrop, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// B(Cb, Cs) = 1 - [(1 - Cb) x (1 - Cs)]
			//           = Cb + Cs -(Cb x Cs)
			return ~((~backdrop) * (~source));
		}
		template<class Tp>
		[[nodiscard]] static constexpr ChannelValue<Tp> Overlay(const ChannelValue<Tp>& backdrop, const ChannelValue<Tp>& source)
		{
			// B(Cb, Cs) = HardLight(Cs, Cb)
			return HardLight(source, backdrop);
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor Overlay(const Tcolor& backdrop, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// B(Cb, Cs) = HardLight(Cs, Cb)
			return HardLight(source, backdrop);
		}
		template<class Tp>
		[[nodiscard]] static constexpr ChannelValue<Tp> Darken(const ChannelValue<Tp>& backdrop, const ChannelValue<Tp>& source)
		{
			// B(Cb, Cs) = min(Cb, Cs)
			return backdrop & source;
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor Darken(const Tcolor& backdrop, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// B(Cb, Cs) = min(Cb, Cs)
			return backdrop & source;
		}
		template<class Tp>
		[[nodiscard]] static constexpr ChannelValue<Tp> Lighten(const ChannelValue<Tp>& backdrop, const ChannelValue<Tp>& source)
		{
			// B(Cb, Cs) = max(Cb, Cs)
			// Note: The result must be rounded down if it exceeds the range.
			return (backdrop | source).Normalize();
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor Lighten(const Tcolor& backdrop, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// B(Cb, Cs) = max(Cb, Cs)
			// Note: The result must be rounded down if it exceeds the range.
			return (backdrop | source).Normalize();
		}
		template<class Tp>
		[[nodiscard]] static constexpr ChannelValue<Tp> ColorDodge(const ChannelValue<Tp>& backdrop, const ChannelValue<Tp>& source)
		{
			// if(Cb == 0)
			//     B(Cb, Cs) = 0
			// else if(Cs == 1)
			//     B(Cb, Cs) = 1
			// else
			//     B(Cb, Cs) = min(1, Cb / (1 - Cs))
			ChannelValue<Tp> ncs = ~source;
			ChannelValue<Tp> div;
			if (ncs != ChannelValue<Tp>::Min()) { div = backdrop / (ncs); }
			else { div = ChannelValue<Tp>::Max(); }
			return ChannelValue<Tp>::Max() & div;
		}
		template<class Tp, size_t N>
		[[nodiscard]] static constexpr RelativeColor<Tp, N> ColorDodge(const RelativeColor<Tp, N>& backdrop, const RelativeColor<Tp, N>& source)
		{
			return backdrop.Merge(source, ColorDodge<Tp>);
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor ColorDodge(const Tcolor& backdrop, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			return Tcolor(ColorDodge(backdrop.Data(), source.Data()));
		}
		template<class Tp>
		[[nodiscard]] static constexpr ChannelValue<Tp> ColorBurn(const ChannelValue<Tp>& backdrop, const ChannelValue<Tp>& source)
		{
			// if(Cb == 1)
			//     B(Cb, Cs) = 1
			// else if(Cs == 0)
			//     B(Cb, Cs) = 0
			// else
			//     B(Cb, Cs) = 1 - min(1, (1 - Cb) / Cs)
			ChannelValue<Tp> ncb = ~backdrop;
			ChannelValue<Tp> div;
			if (source != ChannelValue<Tp>::Min()) { div = ncb / source; }
			else { div = ChannelValue<Tp>::Max(); }
			return !(ChannelValue<Tp>::Max() & div);
		}
		template<class Tp, size_t N>
		[[nodiscard]] static constexpr RelativeColor<Tp, N> ColorBurn(const RelativeColor<Tp, N>& backdrop, const RelativeColor<Tp, N>& source)
		{
			return backdrop.Merge(source, ColorBurn<Tp>);
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor ColorBurn(const Tcolor& backdrop, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			return Tcolor(ColorBurn(backdrop.Data(), source.Data()));
		}
		template<class Tp>
		[[nodiscard]] static constexpr ChannelValue<Tp> HardLight(const ChannelValue<Tp>& backdrop, const ChannelValue<Tp>& source)
		{
			// if(Cs <= 0.5)
			//     B(Cb, Cs) = Multiply(Cb, 2 x Cs)
			// else
			//     B(Cb, Cs) = Screen(Cb, 2 x Cs -1)
			auto c1 = Multiply(backdrop, source + source);
			auto c2 = Screen(backdrop, (source - ChannelValue<Tp>(0.5f)) + (source - ChannelValue<Tp>(0.5f)));
			return ((source <= ChannelValue<Tp>(0.5f))?(c1):(c2));
		}
		template<class Tp, size_t N>
		[[nodiscard]] static constexpr RelativeColor<Tp, N> HardLight(const RelativeColor<Tp, N>& backdrop, const RelativeColor<Tp, N>& source)
		{
			return backdrop.Merge(source, HardLight<Tp>);
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor HardLight(const Tcolor& backdrop, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			return Tcolor(HardLight(backdrop.Data(), source.Data()));
		}
		template<class Tp>
		[[nodiscard]] static constexpr ChannelValue<Tp> SoftLight(const ChannelValue<Tp>& backdrop, const ChannelValue<Tp>& source)
		{
			// if(Cs <= 0.5)
			//     B(Cb, Cs) = Cb - (1 - 2 x Cs) x Cb x (1 - Cb)
			// else
			//     B(Cb, Cs) = Cb + (2 x Cs - 1) x (D(Cb) - Cb)
			//
			// if(Cb <= 0.25)
			//     D(Cb) = ((16 * Cb - 12) x Cb + 4) x Cb
			// else
			//     D(Cb) = sqrt(Cb)
			ChannelValue<Tp> D1 = [](auto cb)
			{
				// 4 * (~Cb - (~Cb - Cb) * Cb - (~Cb - Cb) * Cb) * Cb
				auto c1 = (~cb) - cb;
				auto c2 = (~cb) - c1 - c1;
				auto c3 = c2 * cb;
				return c3 + c3 + c3 + c3;
			}(backdrop);
			ChannelValue<Tp> D2 = ChannelValue<Tp>(BasicMathematics::Sqrt(backdrop.Data()));
			ChannelValue<Tp> D = ((backdrop <= ChannelValue<Tp>(0.25))?(D1):(D2));
			ChannelValue<Tp> C1 = backdrop - ((~source) - source) * backdrop * (~backdrop);
			ChannelValue<Tp> C2 = backdrop + ((source - ChannelValue<Tp>(0.5)) + (source - ChannelValue<Tp>(0.5))) * (D - backdrop);
			return ((source <= ChannelValue<Tp>(0.5))?(C1):(C2));
		}
		template<class Tp, size_t N>
		[[nodiscard]] static constexpr RelativeColor<Tp, N> SoftLight(const RelativeColor<Tp, N>& backdrop, const RelativeColor<Tp, N>& source)
		{
			return backdrop.Merge(source, SoftLight<Tp>);
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor SoftLight(const Tcolor& backdrop, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			return Tcolor(SoftLight(backdrop.Data(), source.Data()));
		}
		template<class Tp>
		[[nodiscard]] static constexpr ChannelValue<Tp> Difference(const ChannelValue<Tp>& backdrop, const ChannelValue<Tp>& source)
		{
			// B(Cb, Cs) = | Cb - Cs |
			return (backdrop | source) - (backdrop & source);
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor Difference(const Tcolor& backdrop, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// B(Cb, Cs) = | Cb - Cs |
			return (backdrop | source) - (backdrop & source);
		}
		template<class Tp>
		[[nodiscard]] static constexpr ChannelValue<Tp> Exclusion(const ChannelValue<Tp>& backdrop, const ChannelValue<Tp>& source)
		{
			// B(Cb, Cs) = Cb + Cs - 2 x Cb x Cs
			return (backdrop * (~source)) + (source * (~backdrop));
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor Exclusion(const Tcolor& backdrop, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// B(Cb, Cs) = Cb + Cs - 2 x Cb x Cs
			return (backdrop * (~source)) + (source * (~backdrop));
		}
	};
}
#endif // __stationaryorbit_graphics_core_colorblending__
