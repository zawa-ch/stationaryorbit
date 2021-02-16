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
#include "grayscalecolor.hpp"
#include "cmycolor.hpp"
#include "cmykcolor.hpp"
#include "rgbcolor.hpp"
#include "xyzcolor.hpp"
#include "yuvcolor.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	///	カラーブレンディングのアルゴリズムの実装です。
	///	このクラスは継承できません。
	class ColorBlendingAlgorithms final
	{
	private:
		ColorBlendingAlgorithms() = delete;
		ColorBlendingAlgorithms(const ColorBlendingAlgorithms&) = delete;
		ColorBlendingAlgorithms(ColorBlendingAlgorithms&&) = delete;
		~ColorBlendingAlgorithms() = delete;
	public:
		template<class Tp>
		[[nodiscard]] static constexpr ChannelValue<Tp> Normal(const ChannelValue<Tp>& backdrop, const ChannelValue<Tp>& source)
		{
			// B(Cb, Cs) = Cs
			return source;
		}
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
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
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
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
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
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
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
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
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
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
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
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
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
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
			return ~(ChannelValue<Tp>::Max() & div);
		}
		template<class Tp, size_t N>
		[[nodiscard]] static constexpr RelativeColor<Tp, N> ColorBurn(const RelativeColor<Tp, N>& backdrop, const RelativeColor<Tp, N>& source)
		{
			return backdrop.Merge(source, ColorBurn<Tp>);
		}
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
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
			auto c2 = Screen(backdrop, (source - ChannelValue<Tp>(Tp(0.5f))) + (source - ChannelValue<Tp>(Tp(0.5f))));
			return ((source <= ChannelValue<Tp>(Tp(0.5f)))?(c1):(c2));
		}
		template<class Tp, size_t N>
		[[nodiscard]] static constexpr RelativeColor<Tp, N> HardLight(const RelativeColor<Tp, N>& backdrop, const RelativeColor<Tp, N>& source)
		{
			return backdrop.Merge(source, HardLight<Tp>);
		}
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
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
			ChannelValue<Tp> D = ((backdrop <= ChannelValue<Tp>(Tp(0.25)))?(D1):(D2));
			ChannelValue<Tp> C1 = backdrop - ((~source) - source) * backdrop * (~backdrop);
			ChannelValue<Tp> C2 = backdrop + ((source - ChannelValue<Tp>(Tp(0.5))) + (source - ChannelValue<Tp>(Tp(0.5)))) * (D - backdrop);
			return ((source <= ChannelValue<Tp>(Tp(0.5)))?(C1):(C2));
		}
		template<class Tp, size_t N>
		[[nodiscard]] static constexpr RelativeColor<Tp, N> SoftLight(const RelativeColor<Tp, N>& backdrop, const RelativeColor<Tp, N>& source)
		{
			return backdrop.Merge(source, SoftLight<Tp>);
		}
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
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
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
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
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr Tcolor Exclusion(const Tcolor& backdrop, const Tcolor& source)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// B(Cb, Cs) = Cb + Cs - 2 x Cb x Cs
			return (backdrop * (~source)) + (source * (~backdrop));
		}
	};
	///	ふたつの色をアルゴリズムに従って混色します。
	template<class Tcolor, Tcolor algorithm(const Tcolor&, const Tcolor&)>
	class ColorBlender final
	{
	public:
		typedef Tcolor ValueType;

		ColorBlender() = default;
		[[nodiscard]] static constexpr Tcolor Blend(const Tcolor& backdrop, const Tcolor& source)
		{
			return algorithm(backdrop, source);
		}
	};
	///	混色を行うクラスを識別します。
	class ColorBlenderTraits final
	{
	private:
		ColorBlenderTraits() = delete;
		ColorBlenderTraits(const ColorBlenderTraits&) = delete;
		ColorBlenderTraits(ColorBlenderTraits&&) = delete;
		~ColorBlenderTraits() = delete;

		template<class T, class = void> struct IsColorBlender_Impl : std::false_type{};
		template<class T> struct IsColorBlender_Impl
		<
			T,
			std::void_t
			<
				typename T::ValueType,
				decltype( std::declval<const T&>().Blend(std::declval<const typename T::ValueType&>(), std::declval<const typename T::ValueType&>()) )
			>
		>
		: std::conjunction
		<
			std::is_same< decltype( std::declval<const T&>().Blend(std::declval<const typename T::ValueType&>(), std::declval<const typename T::ValueType&>()) ), typename T::ValueType>,
			std::is_default_constructible<T>
		>
		{};
	public:
		template<class T> using ValueType = typename T::ValueType;

		template<class T> static constexpr bool IsColorBlender = IsColorBlender_Impl<T>::value;
	};

	typedef ColorBlender<Channel8_t, ColorBlendingAlgorithms::Normal> Channel8NormalColorBlender_t;
	typedef ColorBlender<Channel16_t, ColorBlendingAlgorithms::Normal> Channel16NormalColorBlender_t;
	typedef ColorBlender<Channel32_t, ColorBlendingAlgorithms::Normal> Channel32NormalColorBlender_t;
	typedef ColorBlender<Channel64_t, ColorBlendingAlgorithms::Normal> Channel64NormalColorBlender_t;
	typedef ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::Normal> ChannelI16NormalColorBlender_t;
	typedef ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::Normal> ChannelI32NormalColorBlender_t;
	typedef ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::Normal> ChannelI64NormalColorBlender_t;
	typedef ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::Normal> ChannelF32NormalColorBlender_t;
	typedef ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::Normal> ChannelF64NormalColorBlender_t;
	typedef ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::Normal> GrayScale8NormalColorBlender_t;
	typedef ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::Normal> GrayScale16NormalColorBlender_t;
	typedef ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::Normal> GrayScale32NormalColorBlender_t;
	typedef ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::Normal> GrayScale64NormalColorBlender_t;
	typedef ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::Normal> GrayScaleI16NormalColorBlender_t;
	typedef ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::Normal> GrayScaleI32NormalColorBlender_t;
	typedef ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::Normal> GrayScaleI64NormalColorBlender_t;
	typedef ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::Normal> GrayScaleF32NormalColorBlender_t;
	typedef ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::Normal> GrayScaleF64NormalColorBlender_t;
	typedef ColorBlender<RGB8_t, ColorBlendingAlgorithms::Normal> RGB8NormalColorBlender_t;
	typedef ColorBlender<RGB16_t, ColorBlendingAlgorithms::Normal> RGB16NormalColorBlender_t;
	typedef ColorBlender<RGB32_t, ColorBlendingAlgorithms::Normal> RGB32NormalColorBlender_t;
	typedef ColorBlender<RGB64_t, ColorBlendingAlgorithms::Normal> RGB64NormalColorBlender_t;
	typedef ColorBlender<RGBI16_t, ColorBlendingAlgorithms::Normal> RGBI16NormalColorBlender_t;
	typedef ColorBlender<RGBI32_t, ColorBlendingAlgorithms::Normal> RGBI32NormalColorBlender_t;
	typedef ColorBlender<RGBI64_t, ColorBlendingAlgorithms::Normal> RGBI64NormalColorBlender_t;
	typedef ColorBlender<RGBF32_t, ColorBlendingAlgorithms::Normal> RGBF32NormalColorBlender_t;
	typedef ColorBlender<RGBF64_t, ColorBlendingAlgorithms::Normal> RGBF64NormalColorBlender_t;
	typedef ColorBlender<CMY8_t, ColorBlendingAlgorithms::Normal> CMY8NormalColorBlender_t;
	typedef ColorBlender<CMY16_t, ColorBlendingAlgorithms::Normal> CMY16NormalColorBlender_t;
	typedef ColorBlender<CMY32_t, ColorBlendingAlgorithms::Normal> CMY32NormalColorBlender_t;
	typedef ColorBlender<CMY64_t, ColorBlendingAlgorithms::Normal> CMY64NormalColorBlender_t;
	typedef ColorBlender<CMYI16_t, ColorBlendingAlgorithms::Normal> CMYI16NormalColorBlender_t;
	typedef ColorBlender<CMYI32_t, ColorBlendingAlgorithms::Normal> CMYI32NormalColorBlender_t;
	typedef ColorBlender<CMYI64_t, ColorBlendingAlgorithms::Normal> CMYI64NormalColorBlender_t;
	typedef ColorBlender<CMYF32_t, ColorBlendingAlgorithms::Normal> CMYF32NormalColorBlender_t;
	typedef ColorBlender<CMYF64_t, ColorBlendingAlgorithms::Normal> CMYF64NormalColorBlender_t;
	typedef ColorBlender<CMYK8_t, ColorBlendingAlgorithms::Normal> CMYK8NormalColorBlender_t;
	typedef ColorBlender<CMYK16_t, ColorBlendingAlgorithms::Normal> CMYK16NormalColorBlender_t;
	typedef ColorBlender<CMYK32_t, ColorBlendingAlgorithms::Normal> CMYK32NormalColorBlender_t;
	typedef ColorBlender<CMYK64_t, ColorBlendingAlgorithms::Normal> CMYK64NormalColorBlender_t;
	typedef ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::Normal> CMYKI16NormalColorBlender_t;
	typedef ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::Normal> CMYKI32NormalColorBlender_t;
	typedef ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::Normal> CMYKI64NormalColorBlender_t;
	typedef ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::Normal> CMYKF32NormalColorBlender_t;
	typedef ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::Normal> CMYKF64NormalColorBlender_t;
	typedef ColorBlender<Channel8_t, ColorBlendingAlgorithms::Multiply> Channel8MultiplyColorBlender_t;
	typedef ColorBlender<Channel16_t, ColorBlendingAlgorithms::Multiply> Channel16MultiplyColorBlender_t;
	typedef ColorBlender<Channel32_t, ColorBlendingAlgorithms::Multiply> Channel32MultiplyColorBlender_t;
	typedef ColorBlender<Channel64_t, ColorBlendingAlgorithms::Multiply> Channel64MultiplyColorBlender_t;
	typedef ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::Multiply> ChannelI16MultiplyColorBlender_t;
	typedef ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::Multiply> ChannelI32MultiplyColorBlender_t;
	typedef ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::Multiply> ChannelI64MultiplyColorBlender_t;
	typedef ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::Multiply> ChannelF32MultiplyColorBlender_t;
	typedef ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::Multiply> ChannelF64MultiplyColorBlender_t;
	typedef ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::Multiply> GrayScale8MultiplyColorBlender_t;
	typedef ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::Multiply> GrayScale16MultiplyColorBlender_t;
	typedef ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::Multiply> GrayScale32MultiplyColorBlender_t;
	typedef ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::Multiply> GrayScale64MultiplyColorBlender_t;
	typedef ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::Multiply> GrayScaleI16MultiplyColorBlender_t;
	typedef ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::Multiply> GrayScaleI32MultiplyColorBlender_t;
	typedef ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::Multiply> GrayScaleI64MultiplyColorBlender_t;
	typedef ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::Multiply> GrayScaleF32MultiplyColorBlender_t;
	typedef ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::Multiply> GrayScaleF64MultiplyColorBlender_t;
	typedef ColorBlender<RGB8_t, ColorBlendingAlgorithms::Multiply> RGB8MultiplyColorBlender_t;
	typedef ColorBlender<RGB16_t, ColorBlendingAlgorithms::Multiply> RGB16MultiplyColorBlender_t;
	typedef ColorBlender<RGB32_t, ColorBlendingAlgorithms::Multiply> RGB32MultiplyColorBlender_t;
	typedef ColorBlender<RGB64_t, ColorBlendingAlgorithms::Multiply> RGB64MultiplyColorBlender_t;
	typedef ColorBlender<RGBI16_t, ColorBlendingAlgorithms::Multiply> RGBI16MultiplyColorBlender_t;
	typedef ColorBlender<RGBI32_t, ColorBlendingAlgorithms::Multiply> RGBI32MultiplyColorBlender_t;
	typedef ColorBlender<RGBI64_t, ColorBlendingAlgorithms::Multiply> RGBI64MultiplyColorBlender_t;
	typedef ColorBlender<RGBF32_t, ColorBlendingAlgorithms::Multiply> RGBF32MultiplyColorBlender_t;
	typedef ColorBlender<RGBF64_t, ColorBlendingAlgorithms::Multiply> RGBF64MultiplyColorBlender_t;
	typedef ColorBlender<CMY8_t, ColorBlendingAlgorithms::Multiply> CMY8MultiplyColorBlender_t;
	typedef ColorBlender<CMY16_t, ColorBlendingAlgorithms::Multiply> CMY16MultiplyColorBlender_t;
	typedef ColorBlender<CMY32_t, ColorBlendingAlgorithms::Multiply> CMY32MultiplyColorBlender_t;
	typedef ColorBlender<CMY64_t, ColorBlendingAlgorithms::Multiply> CMY64MultiplyColorBlender_t;
	typedef ColorBlender<CMYI16_t, ColorBlendingAlgorithms::Multiply> CMYI16MultiplyColorBlender_t;
	typedef ColorBlender<CMYI32_t, ColorBlendingAlgorithms::Multiply> CMYI32MultiplyColorBlender_t;
	typedef ColorBlender<CMYI64_t, ColorBlendingAlgorithms::Multiply> CMYI64MultiplyColorBlender_t;
	typedef ColorBlender<CMYF32_t, ColorBlendingAlgorithms::Multiply> CMYF32MultiplyColorBlender_t;
	typedef ColorBlender<CMYF64_t, ColorBlendingAlgorithms::Multiply> CMYF64MultiplyColorBlender_t;
	typedef ColorBlender<CMYK8_t, ColorBlendingAlgorithms::Multiply> CMYK8MultiplyColorBlender_t;
	typedef ColorBlender<CMYK16_t, ColorBlendingAlgorithms::Multiply> CMYK16MultiplyColorBlender_t;
	typedef ColorBlender<CMYK32_t, ColorBlendingAlgorithms::Multiply> CMYK32MultiplyColorBlender_t;
	typedef ColorBlender<CMYK64_t, ColorBlendingAlgorithms::Multiply> CMYK64MultiplyColorBlender_t;
	typedef ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::Multiply> CMYKI16MultiplyColorBlender_t;
	typedef ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::Multiply> CMYKI32MultiplyColorBlender_t;
	typedef ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::Multiply> CMYKI64MultiplyColorBlender_t;
	typedef ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::Multiply> CMYKF32MultiplyColorBlender_t;
	typedef ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::Multiply> CMYKF64MultiplyColorBlender_t;
	typedef ColorBlender<Channel8_t, ColorBlendingAlgorithms::Screen> Channel8ScreenColorBlender_t;
	typedef ColorBlender<Channel16_t, ColorBlendingAlgorithms::Screen> Channel16ScreenColorBlender_t;
	typedef ColorBlender<Channel32_t, ColorBlendingAlgorithms::Screen> Channel32ScreenColorBlender_t;
	typedef ColorBlender<Channel64_t, ColorBlendingAlgorithms::Screen> Channel64ScreenColorBlender_t;
	typedef ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::Screen> ChannelI16ScreenColorBlender_t;
	typedef ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::Screen> ChannelI32ScreenColorBlender_t;
	typedef ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::Screen> ChannelI64ScreenColorBlender_t;
	typedef ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::Screen> ChannelF32ScreenColorBlender_t;
	typedef ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::Screen> ChannelF64ScreenColorBlender_t;
	typedef ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::Screen> GrayScale8ScreenColorBlender_t;
	typedef ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::Screen> GrayScale16ScreenColorBlender_t;
	typedef ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::Screen> GrayScale32ScreenColorBlender_t;
	typedef ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::Screen> GrayScale64ScreenColorBlender_t;
	typedef ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::Screen> GrayScaleI16ScreenColorBlender_t;
	typedef ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::Screen> GrayScaleI32ScreenColorBlender_t;
	typedef ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::Screen> GrayScaleI64ScreenColorBlender_t;
	typedef ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::Screen> GrayScaleF32ScreenColorBlender_t;
	typedef ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::Screen> GrayScaleF64ScreenColorBlender_t;
	typedef ColorBlender<RGB8_t, ColorBlendingAlgorithms::Screen> RGB8ScreenColorBlender_t;
	typedef ColorBlender<RGB16_t, ColorBlendingAlgorithms::Screen> RGB16ScreenColorBlender_t;
	typedef ColorBlender<RGB32_t, ColorBlendingAlgorithms::Screen> RGB32ScreenColorBlender_t;
	typedef ColorBlender<RGB64_t, ColorBlendingAlgorithms::Screen> RGB64ScreenColorBlender_t;
	typedef ColorBlender<RGBI16_t, ColorBlendingAlgorithms::Screen> RGBI16ScreenColorBlender_t;
	typedef ColorBlender<RGBI32_t, ColorBlendingAlgorithms::Screen> RGBI32ScreenColorBlender_t;
	typedef ColorBlender<RGBI64_t, ColorBlendingAlgorithms::Screen> RGBI64ScreenColorBlender_t;
	typedef ColorBlender<RGBF32_t, ColorBlendingAlgorithms::Screen> RGBF32ScreenColorBlender_t;
	typedef ColorBlender<RGBF64_t, ColorBlendingAlgorithms::Screen> RGBF64ScreenColorBlender_t;
	typedef ColorBlender<CMY8_t, ColorBlendingAlgorithms::Screen> CMY8ScreenColorBlender_t;
	typedef ColorBlender<CMY16_t, ColorBlendingAlgorithms::Screen> CMY16ScreenColorBlender_t;
	typedef ColorBlender<CMY32_t, ColorBlendingAlgorithms::Screen> CMY32ScreenColorBlender_t;
	typedef ColorBlender<CMY64_t, ColorBlendingAlgorithms::Screen> CMY64ScreenColorBlender_t;
	typedef ColorBlender<CMYI16_t, ColorBlendingAlgorithms::Screen> CMYI16ScreenColorBlender_t;
	typedef ColorBlender<CMYI32_t, ColorBlendingAlgorithms::Screen> CMYI32ScreenColorBlender_t;
	typedef ColorBlender<CMYI64_t, ColorBlendingAlgorithms::Screen> CMYI64ScreenColorBlender_t;
	typedef ColorBlender<CMYF32_t, ColorBlendingAlgorithms::Screen> CMYF32ScreenColorBlender_t;
	typedef ColorBlender<CMYF64_t, ColorBlendingAlgorithms::Screen> CMYF64ScreenColorBlender_t;
	typedef ColorBlender<CMYK8_t, ColorBlendingAlgorithms::Screen> CMYK8ScreenColorBlender_t;
	typedef ColorBlender<CMYK16_t, ColorBlendingAlgorithms::Screen> CMYK16ScreenColorBlender_t;
	typedef ColorBlender<CMYK32_t, ColorBlendingAlgorithms::Screen> CMYK32ScreenColorBlender_t;
	typedef ColorBlender<CMYK64_t, ColorBlendingAlgorithms::Screen> CMYK64ScreenColorBlender_t;
	typedef ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::Screen> CMYKI16ScreenColorBlender_t;
	typedef ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::Screen> CMYKI32ScreenColorBlender_t;
	typedef ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::Screen> CMYKI64ScreenColorBlender_t;
	typedef ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::Screen> CMYKF32ScreenColorBlender_t;
	typedef ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::Screen> CMYKF64ScreenColorBlender_t;
	typedef ColorBlender<Channel8_t, ColorBlendingAlgorithms::Overlay> Channel8OverlayColorBlender_t;
	typedef ColorBlender<Channel16_t, ColorBlendingAlgorithms::Overlay> Channel16OverlayColorBlender_t;
	typedef ColorBlender<Channel32_t, ColorBlendingAlgorithms::Overlay> Channel32OverlayColorBlender_t;
	typedef ColorBlender<Channel64_t, ColorBlendingAlgorithms::Overlay> Channel64OverlayColorBlender_t;
	typedef ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::Overlay> ChannelI16OverlayColorBlender_t;
	typedef ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::Overlay> ChannelI32OverlayColorBlender_t;
	typedef ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::Overlay> ChannelI64OverlayColorBlender_t;
	typedef ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::Overlay> ChannelF32OverlayColorBlender_t;
	typedef ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::Overlay> ChannelF64OverlayColorBlender_t;
	typedef ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::Overlay> GrayScale8OverlayColorBlender_t;
	typedef ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::Overlay> GrayScale16OverlayColorBlender_t;
	typedef ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::Overlay> GrayScale32OverlayColorBlender_t;
	typedef ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::Overlay> GrayScale64OverlayColorBlender_t;
	typedef ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::Overlay> GrayScaleI16OverlayColorBlender_t;
	typedef ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::Overlay> GrayScaleI32OverlayColorBlender_t;
	typedef ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::Overlay> GrayScaleI64OverlayColorBlender_t;
	typedef ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::Overlay> GrayScaleF32OverlayColorBlender_t;
	typedef ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::Overlay> GrayScaleF64OverlayColorBlender_t;
	typedef ColorBlender<RGB8_t, ColorBlendingAlgorithms::Overlay> RGB8OverlayColorBlender_t;
	typedef ColorBlender<RGB16_t, ColorBlendingAlgorithms::Overlay> RGB16OverlayColorBlender_t;
	typedef ColorBlender<RGB32_t, ColorBlendingAlgorithms::Overlay> RGB32OverlayColorBlender_t;
	typedef ColorBlender<RGB64_t, ColorBlendingAlgorithms::Overlay> RGB64OverlayColorBlender_t;
	typedef ColorBlender<RGBI16_t, ColorBlendingAlgorithms::Overlay> RGBI16OverlayColorBlender_t;
	typedef ColorBlender<RGBI32_t, ColorBlendingAlgorithms::Overlay> RGBI32OverlayColorBlender_t;
	typedef ColorBlender<RGBI64_t, ColorBlendingAlgorithms::Overlay> RGBI64OverlayColorBlender_t;
	typedef ColorBlender<RGBF32_t, ColorBlendingAlgorithms::Overlay> RGBF32OverlayColorBlender_t;
	typedef ColorBlender<RGBF64_t, ColorBlendingAlgorithms::Overlay> RGBF64OverlayColorBlender_t;
	typedef ColorBlender<CMY8_t, ColorBlendingAlgorithms::Overlay> CMY8OverlayColorBlender_t;
	typedef ColorBlender<CMY16_t, ColorBlendingAlgorithms::Overlay> CMY16OverlayColorBlender_t;
	typedef ColorBlender<CMY32_t, ColorBlendingAlgorithms::Overlay> CMY32OverlayColorBlender_t;
	typedef ColorBlender<CMY64_t, ColorBlendingAlgorithms::Overlay> CMY64OverlayColorBlender_t;
	typedef ColorBlender<CMYI16_t, ColorBlendingAlgorithms::Overlay> CMYI16OverlayColorBlender_t;
	typedef ColorBlender<CMYI32_t, ColorBlendingAlgorithms::Overlay> CMYI32OverlayColorBlender_t;
	typedef ColorBlender<CMYI64_t, ColorBlendingAlgorithms::Overlay> CMYI64OverlayColorBlender_t;
	typedef ColorBlender<CMYF32_t, ColorBlendingAlgorithms::Overlay> CMYF32OverlayColorBlender_t;
	typedef ColorBlender<CMYF64_t, ColorBlendingAlgorithms::Overlay> CMYF64OverlayColorBlender_t;
	typedef ColorBlender<CMYK8_t, ColorBlendingAlgorithms::Overlay> CMYK8OverlayColorBlender_t;
	typedef ColorBlender<CMYK16_t, ColorBlendingAlgorithms::Overlay> CMYK16OverlayColorBlender_t;
	typedef ColorBlender<CMYK32_t, ColorBlendingAlgorithms::Overlay> CMYK32OverlayColorBlender_t;
	typedef ColorBlender<CMYK64_t, ColorBlendingAlgorithms::Overlay> CMYK64OverlayColorBlender_t;
	typedef ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::Overlay> CMYKI16OverlayColorBlender_t;
	typedef ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::Overlay> CMYKI32OverlayColorBlender_t;
	typedef ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::Overlay> CMYKI64OverlayColorBlender_t;
	typedef ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::Overlay> CMYKF32OverlayColorBlender_t;
	typedef ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::Overlay> CMYKF64OverlayColorBlender_t;
	typedef ColorBlender<Channel8_t, ColorBlendingAlgorithms::Darken> Channel8DarkenColorBlender_t;
	typedef ColorBlender<Channel16_t, ColorBlendingAlgorithms::Darken> Channel16DarkenColorBlender_t;
	typedef ColorBlender<Channel32_t, ColorBlendingAlgorithms::Darken> Channel32DarkenColorBlender_t;
	typedef ColorBlender<Channel64_t, ColorBlendingAlgorithms::Darken> Channel64DarkenColorBlender_t;
	typedef ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::Darken> ChannelI16DarkenColorBlender_t;
	typedef ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::Darken> ChannelI32DarkenColorBlender_t;
	typedef ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::Darken> ChannelI64DarkenColorBlender_t;
	typedef ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::Darken> ChannelF32DarkenColorBlender_t;
	typedef ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::Darken> ChannelF64DarkenColorBlender_t;
	typedef ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::Darken> GrayScale8DarkenColorBlender_t;
	typedef ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::Darken> GrayScale16DarkenColorBlender_t;
	typedef ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::Darken> GrayScale32DarkenColorBlender_t;
	typedef ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::Darken> GrayScale64DarkenColorBlender_t;
	typedef ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::Darken> GrayScaleI16DarkenColorBlender_t;
	typedef ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::Darken> GrayScaleI32DarkenColorBlender_t;
	typedef ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::Darken> GrayScaleI64DarkenColorBlender_t;
	typedef ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::Darken> GrayScaleF32DarkenColorBlender_t;
	typedef ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::Darken> GrayScaleF64DarkenColorBlender_t;
	typedef ColorBlender<RGB8_t, ColorBlendingAlgorithms::Darken> RGB8DarkenColorBlender_t;
	typedef ColorBlender<RGB16_t, ColorBlendingAlgorithms::Darken> RGB16DarkenColorBlender_t;
	typedef ColorBlender<RGB32_t, ColorBlendingAlgorithms::Darken> RGB32DarkenColorBlender_t;
	typedef ColorBlender<RGB64_t, ColorBlendingAlgorithms::Darken> RGB64DarkenColorBlender_t;
	typedef ColorBlender<RGBI16_t, ColorBlendingAlgorithms::Darken> RGBI16DarkenColorBlender_t;
	typedef ColorBlender<RGBI32_t, ColorBlendingAlgorithms::Darken> RGBI32DarkenColorBlender_t;
	typedef ColorBlender<RGBI64_t, ColorBlendingAlgorithms::Darken> RGBI64DarkenColorBlender_t;
	typedef ColorBlender<RGBF32_t, ColorBlendingAlgorithms::Darken> RGBF32DarkenColorBlender_t;
	typedef ColorBlender<RGBF64_t, ColorBlendingAlgorithms::Darken> RGBF64DarkenColorBlender_t;
	typedef ColorBlender<CMY8_t, ColorBlendingAlgorithms::Darken> CMY8DarkenColorBlender_t;
	typedef ColorBlender<CMY16_t, ColorBlendingAlgorithms::Darken> CMY16DarkenColorBlender_t;
	typedef ColorBlender<CMY32_t, ColorBlendingAlgorithms::Darken> CMY32DarkenColorBlender_t;
	typedef ColorBlender<CMY64_t, ColorBlendingAlgorithms::Darken> CMY64DarkenColorBlender_t;
	typedef ColorBlender<CMYI16_t, ColorBlendingAlgorithms::Darken> CMYI16DarkenColorBlender_t;
	typedef ColorBlender<CMYI32_t, ColorBlendingAlgorithms::Darken> CMYI32DarkenColorBlender_t;
	typedef ColorBlender<CMYI64_t, ColorBlendingAlgorithms::Darken> CMYI64DarkenColorBlender_t;
	typedef ColorBlender<CMYF32_t, ColorBlendingAlgorithms::Darken> CMYF32DarkenColorBlender_t;
	typedef ColorBlender<CMYF64_t, ColorBlendingAlgorithms::Darken> CMYF64DarkenColorBlender_t;
	typedef ColorBlender<CMYK8_t, ColorBlendingAlgorithms::Darken> CMYK8DarkenColorBlender_t;
	typedef ColorBlender<CMYK16_t, ColorBlendingAlgorithms::Darken> CMYK16DarkenColorBlender_t;
	typedef ColorBlender<CMYK32_t, ColorBlendingAlgorithms::Darken> CMYK32DarkenColorBlender_t;
	typedef ColorBlender<CMYK64_t, ColorBlendingAlgorithms::Darken> CMYK64DarkenColorBlender_t;
	typedef ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::Darken> CMYKI16DarkenColorBlender_t;
	typedef ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::Darken> CMYKI32DarkenColorBlender_t;
	typedef ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::Darken> CMYKI64DarkenColorBlender_t;
	typedef ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::Darken> CMYKF32DarkenColorBlender_t;
	typedef ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::Darken> CMYKF64DarkenColorBlender_t;
	typedef ColorBlender<Channel8_t, ColorBlendingAlgorithms::Lighten> Channel8LightenColorBlender_t;
	typedef ColorBlender<Channel16_t, ColorBlendingAlgorithms::Lighten> Channel16LightenColorBlender_t;
	typedef ColorBlender<Channel32_t, ColorBlendingAlgorithms::Lighten> Channel32LightenColorBlender_t;
	typedef ColorBlender<Channel64_t, ColorBlendingAlgorithms::Lighten> Channel64LightenColorBlender_t;
	typedef ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::Lighten> ChannelI16LightenColorBlender_t;
	typedef ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::Lighten> ChannelI32LightenColorBlender_t;
	typedef ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::Lighten> ChannelI64LightenColorBlender_t;
	typedef ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::Lighten> ChannelF32LightenColorBlender_t;
	typedef ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::Lighten> ChannelF64LightenColorBlender_t;
	typedef ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::Lighten> GrayScale8LightenColorBlender_t;
	typedef ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::Lighten> GrayScale16LightenColorBlender_t;
	typedef ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::Lighten> GrayScale32LightenColorBlender_t;
	typedef ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::Lighten> GrayScale64LightenColorBlender_t;
	typedef ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::Lighten> GrayScaleI16LightenColorBlender_t;
	typedef ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::Lighten> GrayScaleI32LightenColorBlender_t;
	typedef ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::Lighten> GrayScaleI64LightenColorBlender_t;
	typedef ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::Lighten> GrayScaleF32LightenColorBlender_t;
	typedef ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::Lighten> GrayScaleF64LightenColorBlender_t;
	typedef ColorBlender<RGB8_t, ColorBlendingAlgorithms::Lighten> RGB8LightenColorBlender_t;
	typedef ColorBlender<RGB16_t, ColorBlendingAlgorithms::Lighten> RGB16LightenColorBlender_t;
	typedef ColorBlender<RGB32_t, ColorBlendingAlgorithms::Lighten> RGB32LightenColorBlender_t;
	typedef ColorBlender<RGB64_t, ColorBlendingAlgorithms::Lighten> RGB64LightenColorBlender_t;
	typedef ColorBlender<RGBI16_t, ColorBlendingAlgorithms::Lighten> RGBI16LightenColorBlender_t;
	typedef ColorBlender<RGBI32_t, ColorBlendingAlgorithms::Lighten> RGBI32LightenColorBlender_t;
	typedef ColorBlender<RGBI64_t, ColorBlendingAlgorithms::Lighten> RGBI64LightenColorBlender_t;
	typedef ColorBlender<RGBF32_t, ColorBlendingAlgorithms::Lighten> RGBF32LightenColorBlender_t;
	typedef ColorBlender<RGBF64_t, ColorBlendingAlgorithms::Lighten> RGBF64LightenColorBlender_t;
	typedef ColorBlender<CMY8_t, ColorBlendingAlgorithms::Lighten> CMY8LightenColorBlender_t;
	typedef ColorBlender<CMY16_t, ColorBlendingAlgorithms::Lighten> CMY16LightenColorBlender_t;
	typedef ColorBlender<CMY32_t, ColorBlendingAlgorithms::Lighten> CMY32LightenColorBlender_t;
	typedef ColorBlender<CMY64_t, ColorBlendingAlgorithms::Lighten> CMY64LightenColorBlender_t;
	typedef ColorBlender<CMYI16_t, ColorBlendingAlgorithms::Lighten> CMYI16LightenColorBlender_t;
	typedef ColorBlender<CMYI32_t, ColorBlendingAlgorithms::Lighten> CMYI32LightenColorBlender_t;
	typedef ColorBlender<CMYI64_t, ColorBlendingAlgorithms::Lighten> CMYI64LightenColorBlender_t;
	typedef ColorBlender<CMYF32_t, ColorBlendingAlgorithms::Lighten> CMYF32LightenColorBlender_t;
	typedef ColorBlender<CMYF64_t, ColorBlendingAlgorithms::Lighten> CMYF64LightenColorBlender_t;
	typedef ColorBlender<CMYK8_t, ColorBlendingAlgorithms::Lighten> CMYK8LightenColorBlender_t;
	typedef ColorBlender<CMYK16_t, ColorBlendingAlgorithms::Lighten> CMYK16LightenColorBlender_t;
	typedef ColorBlender<CMYK32_t, ColorBlendingAlgorithms::Lighten> CMYK32LightenColorBlender_t;
	typedef ColorBlender<CMYK64_t, ColorBlendingAlgorithms::Lighten> CMYK64LightenColorBlender_t;
	typedef ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::Lighten> CMYKI16LightenColorBlender_t;
	typedef ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::Lighten> CMYKI32LightenColorBlender_t;
	typedef ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::Lighten> CMYKI64LightenColorBlender_t;
	typedef ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::Lighten> CMYKF32LightenColorBlender_t;
	typedef ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::Lighten> CMYKF64LightenColorBlender_t;
	typedef ColorBlender<Channel8_t, ColorBlendingAlgorithms::ColorDodge> Channel8ColorDodgeColorBlender_t;
	typedef ColorBlender<Channel16_t, ColorBlendingAlgorithms::ColorDodge> Channel16ColorDodgeColorBlender_t;
	typedef ColorBlender<Channel32_t, ColorBlendingAlgorithms::ColorDodge> Channel32ColorDodgeColorBlender_t;
	typedef ColorBlender<Channel64_t, ColorBlendingAlgorithms::ColorDodge> Channel64ColorDodgeColorBlender_t;
	typedef ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::ColorDodge> ChannelI16ColorDodgeColorBlender_t;
	typedef ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::ColorDodge> ChannelI32ColorDodgeColorBlender_t;
	typedef ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::ColorDodge> ChannelI64ColorDodgeColorBlender_t;
	typedef ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::ColorDodge> ChannelF32ColorDodgeColorBlender_t;
	typedef ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::ColorDodge> ChannelF64ColorDodgeColorBlender_t;
	typedef ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::ColorDodge> GrayScale8ColorDodgeColorBlender_t;
	typedef ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::ColorDodge> GrayScale16ColorDodgeColorBlender_t;
	typedef ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::ColorDodge> GrayScale32ColorDodgeColorBlender_t;
	typedef ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::ColorDodge> GrayScale64ColorDodgeColorBlender_t;
	typedef ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::ColorDodge> GrayScaleI16ColorDodgeColorBlender_t;
	typedef ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::ColorDodge> GrayScaleI32ColorDodgeColorBlender_t;
	typedef ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::ColorDodge> GrayScaleI64ColorDodgeColorBlender_t;
	typedef ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::ColorDodge> GrayScaleF32ColorDodgeColorBlender_t;
	typedef ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::ColorDodge> GrayScaleF64ColorDodgeColorBlender_t;
	typedef ColorBlender<RGB8_t, ColorBlendingAlgorithms::ColorDodge> RGB8ColorDodgeColorBlender_t;
	typedef ColorBlender<RGB16_t, ColorBlendingAlgorithms::ColorDodge> RGB16ColorDodgeColorBlender_t;
	typedef ColorBlender<RGB32_t, ColorBlendingAlgorithms::ColorDodge> RGB32ColorDodgeColorBlender_t;
	typedef ColorBlender<RGB64_t, ColorBlendingAlgorithms::ColorDodge> RGB64ColorDodgeColorBlender_t;
	typedef ColorBlender<RGBI16_t, ColorBlendingAlgorithms::ColorDodge> RGBI16ColorDodgeColorBlender_t;
	typedef ColorBlender<RGBI32_t, ColorBlendingAlgorithms::ColorDodge> RGBI32ColorDodgeColorBlender_t;
	typedef ColorBlender<RGBI64_t, ColorBlendingAlgorithms::ColorDodge> RGBI64ColorDodgeColorBlender_t;
	typedef ColorBlender<RGBF32_t, ColorBlendingAlgorithms::ColorDodge> RGBF32ColorDodgeColorBlender_t;
	typedef ColorBlender<RGBF64_t, ColorBlendingAlgorithms::ColorDodge> RGBF64ColorDodgeColorBlender_t;
	typedef ColorBlender<CMY8_t, ColorBlendingAlgorithms::ColorDodge> CMY8ColorDodgeColorBlender_t;
	typedef ColorBlender<CMY16_t, ColorBlendingAlgorithms::ColorDodge> CMY16ColorDodgeColorBlender_t;
	typedef ColorBlender<CMY32_t, ColorBlendingAlgorithms::ColorDodge> CMY32ColorDodgeColorBlender_t;
	typedef ColorBlender<CMY64_t, ColorBlendingAlgorithms::ColorDodge> CMY64ColorDodgeColorBlender_t;
	typedef ColorBlender<CMYI16_t, ColorBlendingAlgorithms::ColorDodge> CMYI16ColorDodgeColorBlender_t;
	typedef ColorBlender<CMYI32_t, ColorBlendingAlgorithms::ColorDodge> CMYI32ColorDodgeColorBlender_t;
	typedef ColorBlender<CMYI64_t, ColorBlendingAlgorithms::ColorDodge> CMYI64ColorDodgeColorBlender_t;
	typedef ColorBlender<CMYF32_t, ColorBlendingAlgorithms::ColorDodge> CMYF32ColorDodgeColorBlender_t;
	typedef ColorBlender<CMYF64_t, ColorBlendingAlgorithms::ColorDodge> CMYF64ColorDodgeColorBlender_t;
	typedef ColorBlender<CMYK8_t, ColorBlendingAlgorithms::ColorDodge> CMYK8ColorDodgeColorBlender_t;
	typedef ColorBlender<CMYK16_t, ColorBlendingAlgorithms::ColorDodge> CMYK16ColorDodgeColorBlender_t;
	typedef ColorBlender<CMYK32_t, ColorBlendingAlgorithms::ColorDodge> CMYK32ColorDodgeColorBlender_t;
	typedef ColorBlender<CMYK64_t, ColorBlendingAlgorithms::ColorDodge> CMYK64ColorDodgeColorBlender_t;
	typedef ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::ColorDodge> CMYKI16ColorDodgeColorBlender_t;
	typedef ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::ColorDodge> CMYKI32ColorDodgeColorBlender_t;
	typedef ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::ColorDodge> CMYKI64ColorDodgeColorBlender_t;
	typedef ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::ColorDodge> CMYKF32ColorDodgeColorBlender_t;
	typedef ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::ColorDodge> CMYKF64ColorDodgeColorBlender_t;
	typedef ColorBlender<Channel8_t, ColorBlendingAlgorithms::ColorBurn> Channel8ColorBurnColorBlender_t;
	typedef ColorBlender<Channel16_t, ColorBlendingAlgorithms::ColorBurn> Channel16ColorBurnColorBlender_t;
	typedef ColorBlender<Channel32_t, ColorBlendingAlgorithms::ColorBurn> Channel32ColorBurnColorBlender_t;
	typedef ColorBlender<Channel64_t, ColorBlendingAlgorithms::ColorBurn> Channel64ColorBurnColorBlender_t;
	typedef ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::ColorBurn> ChannelI16ColorBurnColorBlender_t;
	typedef ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::ColorBurn> ChannelI32ColorBurnColorBlender_t;
	typedef ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::ColorBurn> ChannelI64ColorBurnColorBlender_t;
	typedef ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::ColorBurn> ChannelF32ColorBurnColorBlender_t;
	typedef ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::ColorBurn> ChannelF64ColorBurnColorBlender_t;
	typedef ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::ColorBurn> GrayScale8ColorBurnColorBlender_t;
	typedef ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::ColorBurn> GrayScale16ColorBurnColorBlender_t;
	typedef ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::ColorBurn> GrayScale32ColorBurnColorBlender_t;
	typedef ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::ColorBurn> GrayScale64ColorBurnColorBlender_t;
	typedef ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::ColorBurn> GrayScaleI16ColorBurnColorBlender_t;
	typedef ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::ColorBurn> GrayScaleI32ColorBurnColorBlender_t;
	typedef ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::ColorBurn> GrayScaleI64ColorBurnColorBlender_t;
	typedef ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::ColorBurn> GrayScaleF32ColorBurnColorBlender_t;
	typedef ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::ColorBurn> GrayScaleF64ColorBurnColorBlender_t;
	typedef ColorBlender<RGB8_t, ColorBlendingAlgorithms::ColorBurn> RGB8ColorBurnColorBlender_t;
	typedef ColorBlender<RGB16_t, ColorBlendingAlgorithms::ColorBurn> RGB16ColorBurnColorBlender_t;
	typedef ColorBlender<RGB32_t, ColorBlendingAlgorithms::ColorBurn> RGB32ColorBurnColorBlender_t;
	typedef ColorBlender<RGB64_t, ColorBlendingAlgorithms::ColorBurn> RGB64ColorBurnColorBlender_t;
	typedef ColorBlender<RGBI16_t, ColorBlendingAlgorithms::ColorBurn> RGBI16ColorBurnColorBlender_t;
	typedef ColorBlender<RGBI32_t, ColorBlendingAlgorithms::ColorBurn> RGBI32ColorBurnColorBlender_t;
	typedef ColorBlender<RGBI64_t, ColorBlendingAlgorithms::ColorBurn> RGBI64ColorBurnColorBlender_t;
	typedef ColorBlender<RGBF32_t, ColorBlendingAlgorithms::ColorBurn> RGBF32ColorBurnColorBlender_t;
	typedef ColorBlender<RGBF64_t, ColorBlendingAlgorithms::ColorBurn> RGBF64ColorBurnColorBlender_t;
	typedef ColorBlender<CMY8_t, ColorBlendingAlgorithms::ColorBurn> CMY8ColorBurnColorBlender_t;
	typedef ColorBlender<CMY16_t, ColorBlendingAlgorithms::ColorBurn> CMY16ColorBurnColorBlender_t;
	typedef ColorBlender<CMY32_t, ColorBlendingAlgorithms::ColorBurn> CMY32ColorBurnColorBlender_t;
	typedef ColorBlender<CMY64_t, ColorBlendingAlgorithms::ColorBurn> CMY64ColorBurnColorBlender_t;
	typedef ColorBlender<CMYI16_t, ColorBlendingAlgorithms::ColorBurn> CMYI16ColorBurnColorBlender_t;
	typedef ColorBlender<CMYI32_t, ColorBlendingAlgorithms::ColorBurn> CMYI32ColorBurnColorBlender_t;
	typedef ColorBlender<CMYI64_t, ColorBlendingAlgorithms::ColorBurn> CMYI64ColorBurnColorBlender_t;
	typedef ColorBlender<CMYF32_t, ColorBlendingAlgorithms::ColorBurn> CMYF32ColorBurnColorBlender_t;
	typedef ColorBlender<CMYF64_t, ColorBlendingAlgorithms::ColorBurn> CMYF64ColorBurnColorBlender_t;
	typedef ColorBlender<CMYK8_t, ColorBlendingAlgorithms::ColorBurn> CMYK8ColorBurnColorBlender_t;
	typedef ColorBlender<CMYK16_t, ColorBlendingAlgorithms::ColorBurn> CMYK16ColorBurnColorBlender_t;
	typedef ColorBlender<CMYK32_t, ColorBlendingAlgorithms::ColorBurn> CMYK32ColorBurnColorBlender_t;
	typedef ColorBlender<CMYK64_t, ColorBlendingAlgorithms::ColorBurn> CMYK64ColorBurnColorBlender_t;
	typedef ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::ColorBurn> CMYKI16ColorBurnColorBlender_t;
	typedef ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::ColorBurn> CMYKI32ColorBurnColorBlender_t;
	typedef ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::ColorBurn> CMYKI64ColorBurnColorBlender_t;
	typedef ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::ColorBurn> CMYKF32ColorBurnColorBlender_t;
	typedef ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::ColorBurn> CMYKF64ColorBurnColorBlender_t;
	typedef ColorBlender<Channel8_t, ColorBlendingAlgorithms::HardLight> Channel8HardLightColorBlender_t;
	typedef ColorBlender<Channel16_t, ColorBlendingAlgorithms::HardLight> Channel16HardLightColorBlender_t;
	typedef ColorBlender<Channel32_t, ColorBlendingAlgorithms::HardLight> Channel32HardLightColorBlender_t;
	typedef ColorBlender<Channel64_t, ColorBlendingAlgorithms::HardLight> Channel64HardLightColorBlender_t;
	typedef ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::HardLight> ChannelI16HardLightColorBlender_t;
	typedef ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::HardLight> ChannelI32HardLightColorBlender_t;
	typedef ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::HardLight> ChannelI64HardLightColorBlender_t;
	typedef ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::HardLight> ChannelF32HardLightColorBlender_t;
	typedef ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::HardLight> ChannelF64HardLightColorBlender_t;
	typedef ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::HardLight> GrayScale8HardLightColorBlender_t;
	typedef ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::HardLight> GrayScale16HardLightColorBlender_t;
	typedef ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::HardLight> GrayScale32HardLightColorBlender_t;
	typedef ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::HardLight> GrayScale64HardLightColorBlender_t;
	typedef ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::HardLight> GrayScaleI16HardLightColorBlender_t;
	typedef ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::HardLight> GrayScaleI32HardLightColorBlender_t;
	typedef ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::HardLight> GrayScaleI64HardLightColorBlender_t;
	typedef ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::HardLight> GrayScaleF32HardLightColorBlender_t;
	typedef ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::HardLight> GrayScaleF64HardLightColorBlender_t;
	typedef ColorBlender<RGB8_t, ColorBlendingAlgorithms::HardLight> RGB8HardLightColorBlender_t;
	typedef ColorBlender<RGB16_t, ColorBlendingAlgorithms::HardLight> RGB16HardLightColorBlender_t;
	typedef ColorBlender<RGB32_t, ColorBlendingAlgorithms::HardLight> RGB32HardLightColorBlender_t;
	typedef ColorBlender<RGB64_t, ColorBlendingAlgorithms::HardLight> RGB64HardLightColorBlender_t;
	typedef ColorBlender<RGBI16_t, ColorBlendingAlgorithms::HardLight> RGBI16HardLightColorBlender_t;
	typedef ColorBlender<RGBI32_t, ColorBlendingAlgorithms::HardLight> RGBI32HardLightColorBlender_t;
	typedef ColorBlender<RGBI64_t, ColorBlendingAlgorithms::HardLight> RGBI64HardLightColorBlender_t;
	typedef ColorBlender<RGBF32_t, ColorBlendingAlgorithms::HardLight> RGBF32HardLightColorBlender_t;
	typedef ColorBlender<RGBF64_t, ColorBlendingAlgorithms::HardLight> RGBF64HardLightColorBlender_t;
	typedef ColorBlender<CMY8_t, ColorBlendingAlgorithms::HardLight> CMY8HardLightColorBlender_t;
	typedef ColorBlender<CMY16_t, ColorBlendingAlgorithms::HardLight> CMY16HardLightColorBlender_t;
	typedef ColorBlender<CMY32_t, ColorBlendingAlgorithms::HardLight> CMY32HardLightColorBlender_t;
	typedef ColorBlender<CMY64_t, ColorBlendingAlgorithms::HardLight> CMY64HardLightColorBlender_t;
	typedef ColorBlender<CMYI16_t, ColorBlendingAlgorithms::HardLight> CMYI16HardLightColorBlender_t;
	typedef ColorBlender<CMYI32_t, ColorBlendingAlgorithms::HardLight> CMYI32HardLightColorBlender_t;
	typedef ColorBlender<CMYI64_t, ColorBlendingAlgorithms::HardLight> CMYI64HardLightColorBlender_t;
	typedef ColorBlender<CMYF32_t, ColorBlendingAlgorithms::HardLight> CMYF32HardLightColorBlender_t;
	typedef ColorBlender<CMYF64_t, ColorBlendingAlgorithms::HardLight> CMYF64HardLightColorBlender_t;
	typedef ColorBlender<CMYK8_t, ColorBlendingAlgorithms::HardLight> CMYK8HardLightColorBlender_t;
	typedef ColorBlender<CMYK16_t, ColorBlendingAlgorithms::HardLight> CMYK16HardLightColorBlender_t;
	typedef ColorBlender<CMYK32_t, ColorBlendingAlgorithms::HardLight> CMYK32HardLightColorBlender_t;
	typedef ColorBlender<CMYK64_t, ColorBlendingAlgorithms::HardLight> CMYK64HardLightColorBlender_t;
	typedef ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::HardLight> CMYKI16HardLightColorBlender_t;
	typedef ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::HardLight> CMYKI32HardLightColorBlender_t;
	typedef ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::HardLight> CMYKI64HardLightColorBlender_t;
	typedef ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::HardLight> CMYKF32HardLightColorBlender_t;
	typedef ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::HardLight> CMYKF64HardLightColorBlender_t;
	typedef ColorBlender<Channel8_t, ColorBlendingAlgorithms::SoftLight> Channel8SoftLightColorBlender_t;
	typedef ColorBlender<Channel16_t, ColorBlendingAlgorithms::SoftLight> Channel16SoftLightColorBlender_t;
	typedef ColorBlender<Channel32_t, ColorBlendingAlgorithms::SoftLight> Channel32SoftLightColorBlender_t;
	typedef ColorBlender<Channel64_t, ColorBlendingAlgorithms::SoftLight> Channel64SoftLightColorBlender_t;
	typedef ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::SoftLight> ChannelI16SoftLightColorBlender_t;
	typedef ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::SoftLight> ChannelI32SoftLightColorBlender_t;
	typedef ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::SoftLight> ChannelI64SoftLightColorBlender_t;
	typedef ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::SoftLight> ChannelF32SoftLightColorBlender_t;
	typedef ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::SoftLight> ChannelF64SoftLightColorBlender_t;
	typedef ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::SoftLight> GrayScale8SoftLightColorBlender_t;
	typedef ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::SoftLight> GrayScale16SoftLightColorBlender_t;
	typedef ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::SoftLight> GrayScale32SoftLightColorBlender_t;
	typedef ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::SoftLight> GrayScale64SoftLightColorBlender_t;
	typedef ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::SoftLight> GrayScaleI16SoftLightColorBlender_t;
	typedef ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::SoftLight> GrayScaleI32SoftLightColorBlender_t;
	typedef ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::SoftLight> GrayScaleI64SoftLightColorBlender_t;
	typedef ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::SoftLight> GrayScaleF32SoftLightColorBlender_t;
	typedef ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::SoftLight> GrayScaleF64SoftLightColorBlender_t;
	typedef ColorBlender<RGB8_t, ColorBlendingAlgorithms::SoftLight> RGB8SoftLightColorBlender_t;
	typedef ColorBlender<RGB16_t, ColorBlendingAlgorithms::SoftLight> RGB16SoftLightColorBlender_t;
	typedef ColorBlender<RGB32_t, ColorBlendingAlgorithms::SoftLight> RGB32SoftLightColorBlender_t;
	typedef ColorBlender<RGB64_t, ColorBlendingAlgorithms::SoftLight> RGB64SoftLightColorBlender_t;
	typedef ColorBlender<RGBI16_t, ColorBlendingAlgorithms::SoftLight> RGBI16SoftLightColorBlender_t;
	typedef ColorBlender<RGBI32_t, ColorBlendingAlgorithms::SoftLight> RGBI32SoftLightColorBlender_t;
	typedef ColorBlender<RGBI64_t, ColorBlendingAlgorithms::SoftLight> RGBI64SoftLightColorBlender_t;
	typedef ColorBlender<RGBF32_t, ColorBlendingAlgorithms::SoftLight> RGBF32SoftLightColorBlender_t;
	typedef ColorBlender<RGBF64_t, ColorBlendingAlgorithms::SoftLight> RGBF64SoftLightColorBlender_t;
	typedef ColorBlender<CMY8_t, ColorBlendingAlgorithms::SoftLight> CMY8SoftLightColorBlender_t;
	typedef ColorBlender<CMY16_t, ColorBlendingAlgorithms::SoftLight> CMY16SoftLightColorBlender_t;
	typedef ColorBlender<CMY32_t, ColorBlendingAlgorithms::SoftLight> CMY32SoftLightColorBlender_t;
	typedef ColorBlender<CMY64_t, ColorBlendingAlgorithms::SoftLight> CMY64SoftLightColorBlender_t;
	typedef ColorBlender<CMYI16_t, ColorBlendingAlgorithms::SoftLight> CMYI16SoftLightColorBlender_t;
	typedef ColorBlender<CMYI32_t, ColorBlendingAlgorithms::SoftLight> CMYI32SoftLightColorBlender_t;
	typedef ColorBlender<CMYI64_t, ColorBlendingAlgorithms::SoftLight> CMYI64SoftLightColorBlender_t;
	typedef ColorBlender<CMYF32_t, ColorBlendingAlgorithms::SoftLight> CMYF32SoftLightColorBlender_t;
	typedef ColorBlender<CMYF64_t, ColorBlendingAlgorithms::SoftLight> CMYF64SoftLightColorBlender_t;
	typedef ColorBlender<CMYK8_t, ColorBlendingAlgorithms::SoftLight> CMYK8SoftLightColorBlender_t;
	typedef ColorBlender<CMYK16_t, ColorBlendingAlgorithms::SoftLight> CMYK16SoftLightColorBlender_t;
	typedef ColorBlender<CMYK32_t, ColorBlendingAlgorithms::SoftLight> CMYK32SoftLightColorBlender_t;
	typedef ColorBlender<CMYK64_t, ColorBlendingAlgorithms::SoftLight> CMYK64SoftLightColorBlender_t;
	typedef ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::SoftLight> CMYKI16SoftLightColorBlender_t;
	typedef ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::SoftLight> CMYKI32SoftLightColorBlender_t;
	typedef ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::SoftLight> CMYKI64SoftLightColorBlender_t;
	typedef ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::SoftLight> CMYKF32SoftLightColorBlender_t;
	typedef ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::SoftLight> CMYKF64SoftLightColorBlender_t;
	typedef ColorBlender<Channel8_t, ColorBlendingAlgorithms::Difference> Channel8DifferenceColorBlender_t;
	typedef ColorBlender<Channel16_t, ColorBlendingAlgorithms::Difference> Channel16DifferenceColorBlender_t;
	typedef ColorBlender<Channel32_t, ColorBlendingAlgorithms::Difference> Channel32DifferenceColorBlender_t;
	typedef ColorBlender<Channel64_t, ColorBlendingAlgorithms::Difference> Channel64DifferenceColorBlender_t;
	typedef ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::Difference> ChannelI16DifferenceColorBlender_t;
	typedef ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::Difference> ChannelI32DifferenceColorBlender_t;
	typedef ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::Difference> ChannelI64DifferenceColorBlender_t;
	typedef ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::Difference> ChannelF32DifferenceColorBlender_t;
	typedef ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::Difference> ChannelF64DifferenceColorBlender_t;
	typedef ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::Difference> GrayScale8DifferenceColorBlender_t;
	typedef ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::Difference> GrayScale16DifferenceColorBlender_t;
	typedef ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::Difference> GrayScale32DifferenceColorBlender_t;
	typedef ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::Difference> GrayScale64DifferenceColorBlender_t;
	typedef ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::Difference> GrayScaleI16DifferenceColorBlender_t;
	typedef ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::Difference> GrayScaleI32DifferenceColorBlender_t;
	typedef ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::Difference> GrayScaleI64DifferenceColorBlender_t;
	typedef ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::Difference> GrayScaleF32DifferenceColorBlender_t;
	typedef ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::Difference> GrayScaleF64DifferenceColorBlender_t;
	typedef ColorBlender<RGB8_t, ColorBlendingAlgorithms::Difference> RGB8DifferenceColorBlender_t;
	typedef ColorBlender<RGB16_t, ColorBlendingAlgorithms::Difference> RGB16DifferenceColorBlender_t;
	typedef ColorBlender<RGB32_t, ColorBlendingAlgorithms::Difference> RGB32DifferenceColorBlender_t;
	typedef ColorBlender<RGB64_t, ColorBlendingAlgorithms::Difference> RGB64DifferenceColorBlender_t;
	typedef ColorBlender<RGBI16_t, ColorBlendingAlgorithms::Difference> RGBI16DifferenceColorBlender_t;
	typedef ColorBlender<RGBI32_t, ColorBlendingAlgorithms::Difference> RGBI32DifferenceColorBlender_t;
	typedef ColorBlender<RGBI64_t, ColorBlendingAlgorithms::Difference> RGBI64DifferenceColorBlender_t;
	typedef ColorBlender<RGBF32_t, ColorBlendingAlgorithms::Difference> RGBF32DifferenceColorBlender_t;
	typedef ColorBlender<RGBF64_t, ColorBlendingAlgorithms::Difference> RGBF64DifferenceColorBlender_t;
	typedef ColorBlender<CMY8_t, ColorBlendingAlgorithms::Difference> CMY8DifferenceColorBlender_t;
	typedef ColorBlender<CMY16_t, ColorBlendingAlgorithms::Difference> CMY16DifferenceColorBlender_t;
	typedef ColorBlender<CMY32_t, ColorBlendingAlgorithms::Difference> CMY32DifferenceColorBlender_t;
	typedef ColorBlender<CMY64_t, ColorBlendingAlgorithms::Difference> CMY64DifferenceColorBlender_t;
	typedef ColorBlender<CMYI16_t, ColorBlendingAlgorithms::Difference> CMYI16DifferenceColorBlender_t;
	typedef ColorBlender<CMYI32_t, ColorBlendingAlgorithms::Difference> CMYI32DifferenceColorBlender_t;
	typedef ColorBlender<CMYI64_t, ColorBlendingAlgorithms::Difference> CMYI64DifferenceColorBlender_t;
	typedef ColorBlender<CMYF32_t, ColorBlendingAlgorithms::Difference> CMYF32DifferenceColorBlender_t;
	typedef ColorBlender<CMYF64_t, ColorBlendingAlgorithms::Difference> CMYF64DifferenceColorBlender_t;
	typedef ColorBlender<CMYK8_t, ColorBlendingAlgorithms::Difference> CMYK8DifferenceColorBlender_t;
	typedef ColorBlender<CMYK16_t, ColorBlendingAlgorithms::Difference> CMYK16DifferenceColorBlender_t;
	typedef ColorBlender<CMYK32_t, ColorBlendingAlgorithms::Difference> CMYK32DifferenceColorBlender_t;
	typedef ColorBlender<CMYK64_t, ColorBlendingAlgorithms::Difference> CMYK64DifferenceColorBlender_t;
	typedef ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::Difference> CMYKI16DifferenceColorBlender_t;
	typedef ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::Difference> CMYKI32DifferenceColorBlender_t;
	typedef ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::Difference> CMYKI64DifferenceColorBlender_t;
	typedef ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::Difference> CMYKF32DifferenceColorBlender_t;
	typedef ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::Difference> CMYKF64DifferenceColorBlender_t;
	typedef ColorBlender<Channel8_t, ColorBlendingAlgorithms::Exclusion> Channel8ExclusionColorBlender_t;
	typedef ColorBlender<Channel16_t, ColorBlendingAlgorithms::Exclusion> Channel16ExclusionColorBlender_t;
	typedef ColorBlender<Channel32_t, ColorBlendingAlgorithms::Exclusion> Channel32ExclusionColorBlender_t;
	typedef ColorBlender<Channel64_t, ColorBlendingAlgorithms::Exclusion> Channel64ExclusionColorBlender_t;
	typedef ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::Exclusion> ChannelI16ExclusionColorBlender_t;
	typedef ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::Exclusion> ChannelI32ExclusionColorBlender_t;
	typedef ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::Exclusion> ChannelI64ExclusionColorBlender_t;
	typedef ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::Exclusion> ChannelF32ExclusionColorBlender_t;
	typedef ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::Exclusion> ChannelF64ExclusionColorBlender_t;
	typedef ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::Exclusion> GrayScale8ExclusionColorBlender_t;
	typedef ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::Exclusion> GrayScale16ExclusionColorBlender_t;
	typedef ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::Exclusion> GrayScale32ExclusionColorBlender_t;
	typedef ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::Exclusion> GrayScale64ExclusionColorBlender_t;
	typedef ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::Exclusion> GrayScaleI16ExclusionColorBlender_t;
	typedef ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::Exclusion> GrayScaleI32ExclusionColorBlender_t;
	typedef ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::Exclusion> GrayScaleI64ExclusionColorBlender_t;
	typedef ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::Exclusion> GrayScaleF32ExclusionColorBlender_t;
	typedef ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::Exclusion> GrayScaleF64ExclusionColorBlender_t;
	typedef ColorBlender<RGB8_t, ColorBlendingAlgorithms::Exclusion> RGB8ExclusionColorBlender_t;
	typedef ColorBlender<RGB16_t, ColorBlendingAlgorithms::Exclusion> RGB16ExclusionColorBlender_t;
	typedef ColorBlender<RGB32_t, ColorBlendingAlgorithms::Exclusion> RGB32ExclusionColorBlender_t;
	typedef ColorBlender<RGB64_t, ColorBlendingAlgorithms::Exclusion> RGB64ExclusionColorBlender_t;
	typedef ColorBlender<RGBI16_t, ColorBlendingAlgorithms::Exclusion> RGBI16ExclusionColorBlender_t;
	typedef ColorBlender<RGBI32_t, ColorBlendingAlgorithms::Exclusion> RGBI32ExclusionColorBlender_t;
	typedef ColorBlender<RGBI64_t, ColorBlendingAlgorithms::Exclusion> RGBI64ExclusionColorBlender_t;
	typedef ColorBlender<RGBF32_t, ColorBlendingAlgorithms::Exclusion> RGBF32ExclusionColorBlender_t;
	typedef ColorBlender<RGBF64_t, ColorBlendingAlgorithms::Exclusion> RGBF64ExclusionColorBlender_t;
	typedef ColorBlender<CMY8_t, ColorBlendingAlgorithms::Exclusion> CMY8ExclusionColorBlender_t;
	typedef ColorBlender<CMY16_t, ColorBlendingAlgorithms::Exclusion> CMY16ExclusionColorBlender_t;
	typedef ColorBlender<CMY32_t, ColorBlendingAlgorithms::Exclusion> CMY32ExclusionColorBlender_t;
	typedef ColorBlender<CMY64_t, ColorBlendingAlgorithms::Exclusion> CMY64ExclusionColorBlender_t;
	typedef ColorBlender<CMYI16_t, ColorBlendingAlgorithms::Exclusion> CMYI16ExclusionColorBlender_t;
	typedef ColorBlender<CMYI32_t, ColorBlendingAlgorithms::Exclusion> CMYI32ExclusionColorBlender_t;
	typedef ColorBlender<CMYI64_t, ColorBlendingAlgorithms::Exclusion> CMYI64ExclusionColorBlender_t;
	typedef ColorBlender<CMYF32_t, ColorBlendingAlgorithms::Exclusion> CMYF32ExclusionColorBlender_t;
	typedef ColorBlender<CMYF64_t, ColorBlendingAlgorithms::Exclusion> CMYF64ExclusionColorBlender_t;
	typedef ColorBlender<CMYK8_t, ColorBlendingAlgorithms::Exclusion> CMYK8ExclusionColorBlender_t;
	typedef ColorBlender<CMYK16_t, ColorBlendingAlgorithms::Exclusion> CMYK16ExclusionColorBlender_t;
	typedef ColorBlender<CMYK32_t, ColorBlendingAlgorithms::Exclusion> CMYK32ExclusionColorBlender_t;
	typedef ColorBlender<CMYK64_t, ColorBlendingAlgorithms::Exclusion> CMYK64ExclusionColorBlender_t;
	typedef ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::Exclusion> CMYKI16ExclusionColorBlender_t;
	typedef ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::Exclusion> CMYKI32ExclusionColorBlender_t;
	typedef ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::Exclusion> CMYKI64ExclusionColorBlender_t;
	typedef ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::Exclusion> CMYKF32ExclusionColorBlender_t;
	typedef ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::Exclusion> CMYKF64ExclusionColorBlender_t;

	extern template class ColorBlender<Channel8_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<Channel16_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<Channel32_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<Channel64_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<RGB8_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<RGB16_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<RGB32_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<RGB64_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<RGBI16_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<RGBI32_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<RGBI64_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<RGBF32_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<RGBF64_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<CMY8_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<CMY16_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<CMY32_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<CMY64_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<CMYI16_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<CMYI32_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<CMYI64_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<CMYF32_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<CMYF64_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<CMYK8_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<CMYK16_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<CMYK32_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<CMYK64_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::Normal>;
	extern template class ColorBlender<Channel8_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<Channel16_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<Channel32_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<Channel64_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<RGB8_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<RGB16_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<RGB32_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<RGB64_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<RGBI16_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<RGBI32_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<RGBI64_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<RGBF32_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<RGBF64_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<CMY8_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<CMY16_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<CMY32_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<CMY64_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<CMYI16_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<CMYI32_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<CMYI64_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<CMYF32_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<CMYF64_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<CMYK8_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<CMYK16_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<CMYK32_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<CMYK64_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::Multiply>;
	extern template class ColorBlender<Channel8_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<Channel16_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<Channel32_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<Channel64_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<RGB8_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<RGB16_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<RGB32_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<RGB64_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<RGBI16_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<RGBI32_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<RGBI64_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<RGBF32_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<RGBF64_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<CMY8_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<CMY16_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<CMY32_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<CMY64_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<CMYI16_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<CMYI32_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<CMYI64_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<CMYF32_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<CMYF64_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<CMYK8_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<CMYK16_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<CMYK32_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<CMYK64_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::Screen>;
	extern template class ColorBlender<Channel8_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<Channel16_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<Channel32_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<Channel64_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<RGB8_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<RGB16_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<RGB32_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<RGB64_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<RGBI16_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<RGBI32_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<RGBI64_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<RGBF32_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<RGBF64_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<CMY8_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<CMY16_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<CMY32_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<CMY64_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<CMYI16_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<CMYI32_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<CMYI64_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<CMYF32_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<CMYF64_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<CMYK8_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<CMYK16_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<CMYK32_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<CMYK64_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::Overlay>;
	extern template class ColorBlender<Channel8_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<Channel16_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<Channel32_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<Channel64_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<RGB8_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<RGB16_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<RGB32_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<RGB64_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<RGBI16_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<RGBI32_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<RGBI64_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<RGBF32_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<RGBF64_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<CMY8_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<CMY16_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<CMY32_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<CMY64_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<CMYI16_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<CMYI32_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<CMYI64_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<CMYF32_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<CMYF64_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<CMYK8_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<CMYK16_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<CMYK32_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<CMYK64_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::Darken>;
	extern template class ColorBlender<Channel8_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<Channel16_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<Channel32_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<Channel64_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<RGB8_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<RGB16_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<RGB32_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<RGB64_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<RGBI16_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<RGBI32_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<RGBI64_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<RGBF32_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<RGBF64_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<CMY8_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<CMY16_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<CMY32_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<CMY64_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<CMYI16_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<CMYI32_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<CMYI64_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<CMYF32_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<CMYF64_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<CMYK8_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<CMYK16_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<CMYK32_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<CMYK64_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::Lighten>;
	extern template class ColorBlender<Channel8_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<Channel16_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<Channel32_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<Channel64_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<RGB8_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<RGB16_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<RGB32_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<RGB64_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<RGBI16_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<RGBI32_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<RGBI64_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<RGBF32_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<RGBF64_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<CMY8_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<CMY16_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<CMY32_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<CMY64_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<CMYI16_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<CMYI32_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<CMYI64_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<CMYF32_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<CMYF64_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<CMYK8_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<CMYK16_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<CMYK32_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<CMYK64_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::ColorDodge>;
	extern template class ColorBlender<Channel8_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<Channel16_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<Channel32_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<Channel64_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<RGB8_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<RGB16_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<RGB32_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<RGB64_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<RGBI16_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<RGBI32_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<RGBI64_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<RGBF32_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<RGBF64_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<CMY8_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<CMY16_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<CMY32_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<CMY64_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<CMYI16_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<CMYI32_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<CMYI64_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<CMYF32_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<CMYF64_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<CMYK8_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<CMYK16_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<CMYK32_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<CMYK64_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::ColorBurn>;
	extern template class ColorBlender<Channel8_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<Channel16_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<Channel32_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<Channel64_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<RGB8_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<RGB16_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<RGB32_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<RGB64_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<RGBI16_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<RGBI32_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<RGBI64_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<RGBF32_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<RGBF64_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<CMY8_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<CMY16_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<CMY32_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<CMY64_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<CMYI16_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<CMYI32_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<CMYI64_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<CMYF32_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<CMYF64_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<CMYK8_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<CMYK16_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<CMYK32_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<CMYK64_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::HardLight>;
	extern template class ColorBlender<Channel8_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<Channel16_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<Channel32_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<Channel64_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<RGB8_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<RGB16_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<RGB32_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<RGB64_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<RGBI16_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<RGBI32_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<RGBI64_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<RGBF32_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<RGBF64_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<CMY8_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<CMY16_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<CMY32_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<CMY64_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<CMYI16_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<CMYI32_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<CMYI64_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<CMYF32_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<CMYF64_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<CMYK8_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<CMYK16_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<CMYK32_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<CMYK64_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::SoftLight>;
	extern template class ColorBlender<Channel8_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<Channel16_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<Channel32_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<Channel64_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<RGB8_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<RGB16_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<RGB32_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<RGB64_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<RGBI16_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<RGBI32_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<RGBI64_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<RGBF32_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<RGBF64_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<CMY8_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<CMY16_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<CMY32_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<CMY64_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<CMYI16_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<CMYI32_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<CMYI64_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<CMYF32_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<CMYF64_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<CMYK8_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<CMYK16_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<CMYK32_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<CMYK64_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::Difference>;
	extern template class ColorBlender<Channel8_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<Channel16_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<Channel32_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<Channel64_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<ChannelI16_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<ChannelI32_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<ChannelI64_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<ChannelF32_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<ChannelF64_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<GrayScale8_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<GrayScale16_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<GrayScale32_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<GrayScale64_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<GrayScaleI16_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<GrayScaleI32_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<GrayScaleI64_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<GrayScaleF32_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<GrayScaleF64_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<RGB8_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<RGB16_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<RGB32_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<RGB64_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<RGBI16_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<RGBI32_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<RGBI64_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<RGBF32_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<RGBF64_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<CMY8_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<CMY16_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<CMY32_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<CMY64_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<CMYI16_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<CMYI32_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<CMYI64_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<CMYF32_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<CMYF64_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<CMYK8_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<CMYK16_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<CMYK32_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<CMYK64_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<CMYKI16_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<CMYKI32_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<CMYKI64_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<CMYKF32_t, ColorBlendingAlgorithms::Exclusion>;
	extern template class ColorBlender<CMYKF64_t, ColorBlendingAlgorithms::Exclusion>;
}
#endif // __stationaryorbit_graphics_core_colorblending__
