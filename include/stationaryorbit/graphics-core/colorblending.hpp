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
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor Normal(const Tcolor& destination, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// B(Cb, Cs) = Cs
			return source;
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor Multiply(const Tcolor& destination, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// B(Cb, Cs) = Cb x Cs
			return destination * source;
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor Screen(const Tcolor& destination, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// B(Cb, Cs) = 1 - [(1 - Cb) x (1 - Cs)]
			//           = Cb + Cs -(Cb x Cs)
			return ~((~destination) * (~source));
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor Overlay(const Tcolor& destination, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// B(Cb, Cs) = HardLight(Cs, Cb)
			throw NotImplementedException();
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor Darken(const Tcolor& destination, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// B(Cb, Cs) = min(Cb, Cs)
			return destination & source;
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor Lighten(const Tcolor& destination, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// B(Cb, Cs) = max(Cb, Cs)
			// Note: The result must be rounded down if it exceeds the range.
			return (destination | source).Normalize();
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor ColorDodge(const Tcolor& destination, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			return Tcolor(ColorDodge(destination.Data(), source.Data()));
		}
		template<class Tp, size_t N>
		[[nodiscard]] static constexpr RelativeColor<Tp, N> ColorDodge(const RelativeColor<Tp, N>& destination, const RelativeColor<Tp, N>& source)
		{
			// if(Cb == 0)
			//     B(Cb, Cs) = 0
			// else if(Cs == 1)
			//     B(Cb, Cs) = 1
			// else
			//     B(Cb, Cs) = min(1, Cb / (1 - Cs))
			return destination.Merge(source,
				[](auto cd, auto cs)
				{
					auto ncs = ~cs;
					if ((cd | ncs) == decltype(cd)::Min()) { return ( ((cd) == decltype(cd)::Min())?(cd):(cs) ); }
					else { return decltype(cd)::Max() & ( cd / ncs ); }
				}
			);
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor ColorBurn(const Tcolor& destination, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// if(Cb == 1)
			//     B(Cb, Cs) = 1
			// else if(Cs == 0)
			//     B(Cb, Cs) = 0
			// else
			//     B(Cb, Cs) = 1 - min(1, (1 - Cb) / Cs)
			throw NotImplementedException();
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor HardLight(const Tcolor& destination, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// if(Cs <= 0.5)
			//     B(Cb, Cs) = Multiply(Cb, 2 x Cs)
			// else
			//     B(Cb, Cs) = Screen(Cb, 2 x Cs -1)
			throw NotImplementedException();
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor SoftLight(const Tcolor& destination, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// if(Cs <= 0.5)
			//     B(Cb, Cs) = Cb - (1 - 2 x Cs) x Cb x (1 - Cb)
			// else
			//     B(Cb, Cs) = Cb + (2 x Cs - 1) x (D(Cb) - Cb)
			//
			// if(Cb <= 0.25)
			//     D(Cb) = ((16 * Cb - 12) x Cb + 4) x Cb
			// else
			//     D(Cb) = sqrt(Cb)
			throw NotImplementedException();
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor Difference(const Tcolor& destination, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// B(Cb, Cs) = | Cb - Cs |
			return (destination | source) - (destination & source);
		}
		template<class Tcolor>
		[[nodiscard]] static constexpr Tcolor Exclusion(const Tcolor& destination, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// B(Cb, Cs) = Cb + Cs - 2 x Cb x Cs
			throw NotImplementedException();
		}
	};
}
#endif // __stationaryorbit_graphics_core_colorblending__
