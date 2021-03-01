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
#include "channelvalue.hpp"
#include "relativecolor.hpp"
#include "translucentcolor.hpp"
#include "image.hpp"
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
	private:
		template<class Tcolor, Tcolor blending(const Tcolor&, const Tcolor&)>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> AlphaBlending(const TranslucentColor<Tcolor>& backdrop, const TranslucentColor<Tcolor>& source)
		{
			return (source.Color() * (~backdrop.Alpha().Data())) + (blending(backdrop.Color(), source.Color()) * backdrop.Alpha().Data());
		}
	public:
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> Normal(const TranslucentColor<Tcolor>& backdrop, const TranslucentColor<Tcolor>& source) { return AlphaBlending<Tcolor, Normal>(backdrop, source); }
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> Multiply(const TranslucentColor<Tcolor>& backdrop, const TranslucentColor<Tcolor>& source) { return AlphaBlending<Tcolor, Multiply>(backdrop, source); }
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> Screen(const TranslucentColor<Tcolor>& backdrop, const TranslucentColor<Tcolor>& source) { return AlphaBlending<Tcolor, Screen>(backdrop, source); }
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> Overlay(const TranslucentColor<Tcolor>& backdrop, const TranslucentColor<Tcolor>& source) { return AlphaBlending<Tcolor, Overlay>(backdrop, source); }
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> Darken(const TranslucentColor<Tcolor>& backdrop, const TranslucentColor<Tcolor>& source) { return AlphaBlending<Tcolor, Darken>(backdrop, source); }
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> Lighten(const TranslucentColor<Tcolor>& backdrop, const TranslucentColor<Tcolor>& source) { return AlphaBlending<Tcolor, Lighten>(backdrop, source); }
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> ColorDodge(const TranslucentColor<Tcolor>& backdrop, const TranslucentColor<Tcolor>& source) { return AlphaBlending<Tcolor, ColorDodge>(backdrop, source); }
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> ColorBurn(const TranslucentColor<Tcolor>& backdrop, const TranslucentColor<Tcolor>& source) { return AlphaBlending<Tcolor, ColorBurn>(backdrop, source); }
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> HardLight(const TranslucentColor<Tcolor>& backdrop, const TranslucentColor<Tcolor>& source) { return AlphaBlending<Tcolor, HardLight>(backdrop, source); }
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> SoftLight(const TranslucentColor<Tcolor>& backdrop, const TranslucentColor<Tcolor>& source) { return AlphaBlending<Tcolor, SoftLight>(backdrop, source); }
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> Difference(const TranslucentColor<Tcolor>& backdrop, const TranslucentColor<Tcolor>& source) { return AlphaBlending<Tcolor, Difference>(backdrop, source); }
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> Exclusion(const TranslucentColor<Tcolor>& backdrop, const TranslucentColor<Tcolor>& source) { return AlphaBlending<Tcolor, Exclusion>(backdrop, source); }
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
	template<class Tblender>
	class ColorBlendImage : public Image<typename Tblender::ValueType>
	{
		static_assert(ColorBlenderTraits::IsColorBlender<Tblender>, "テンプレート引数型 Tblender はブレンダー型である必要があります。");
	public:
		typedef Tblender Blender;
		typedef typename Blender::ValueType ValueType;
		typedef Image<ValueType> InputImage;
	private:
		const InputImage& _back;
		const InputImage& _source;
		Blender _bl;
		DisplayRectangle _area;
	public:
		ColorBlendImage(const Blender& blender, const InputImage& backdrop, const InputImage& source) : _back(backdrop), _source(source), _bl(blender), _area(SolveArea(backdrop.Area(), source.Area())) {}
		ColorBlendImage(Blender&& blender, const InputImage& backdrop, const InputImage& source) : _back(backdrop), _source(source), _bl(std::exchange(_bl, blender)), _area(SolveArea(backdrop.Area(), source.Area())) {}

		[[nodiscard]] const Blender& GetBlender() const { return _bl; }
		[[nodiscard]] Blender& GetBlender() { return _bl; }

		[[nodiscard]] bool IsReadableAbyss() const noexcept { return _back.IsReadableAbyss() && _source.IsReadableAbyss(); }
		[[nodiscard]] const DisplayRectSize& Size() const noexcept { return _area.Size(); }
		[[nodiscard]] DisplayRectangle Area() const noexcept { return _area; }
		[[nodiscard]] ValueType At(const DisplayPoint& index) const { return _bl.Blend(_back.At(index), _source.At(index)); }
		[[nodiscard]] ValueType operator[](const DisplayPoint& index) const { return _bl.Blend(_back[index], _source[index]); }
	private:
		[[nodiscard]] constexpr static DisplayRectangle SolveArea(const DisplayRectangle& l, const DisplayRectangle& r)
		{
			return DisplayRectangle::FromEdge(std::max(l.Left(), r.Left()), std::min(l.Right(), r.Right()), std::max(l.Top(), r.Top()), std::min(l.Bottom(), r.Bottom()));
		}
	};

	template<class Tcolor> using ColorNormalBlender = ColorBlender<Tcolor, ColorBlendingAlgorithms::Normal>;
	template<class Tcolor> using ColorMultiplyBlender = ColorBlender<Tcolor, ColorBlendingAlgorithms::Multiply>;
	template<class Tcolor> using ColorScreenBlender = ColorBlender<Tcolor, ColorBlendingAlgorithms::Screen>;
	template<class Tcolor> using ColorOverlayBlender = ColorBlender<Tcolor, ColorBlendingAlgorithms::Overlay>;
	template<class Tcolor> using ColorDarkenBlender = ColorBlender<Tcolor, ColorBlendingAlgorithms::Darken>;
	template<class Tcolor> using ColorLightenBlender = ColorBlender<Tcolor, ColorBlendingAlgorithms::Lighten>;
	template<class Tcolor> using ColorDodgeBlender = ColorBlender<Tcolor, ColorBlendingAlgorithms::ColorDodge>;
	template<class Tcolor> using ColorBurnBlender = ColorBlender<Tcolor, ColorBlendingAlgorithms::ColorBurn>;
	template<class Tcolor> using ColorHardLightBlender = ColorBlender<Tcolor, ColorBlendingAlgorithms::HardLight>;
	template<class Tcolor> using ColorSoftLightBlender = ColorBlender<Tcolor, ColorBlendingAlgorithms::SoftLight>;
	template<class Tcolor> using ColorDifferenceBlender = ColorBlender<Tcolor, ColorBlendingAlgorithms::Difference>;
	template<class Tcolor> using ColorExclusionBlender = ColorBlender<Tcolor, ColorBlendingAlgorithms::Exclusion>;

	template<class Tcolor> using ColorNormalBlendImage = ColorBlendImage<ColorNormalBlender<Tcolor>>;
	template<class Tcolor> using ColorMultiplyBlendImage = ColorBlendImage<ColorMultiplyBlender<Tcolor>>;
	template<class Tcolor> using ColorScreenBlendImage = ColorBlendImage<ColorScreenBlender<Tcolor>>;
	template<class Tcolor> using ColorOverlayBlendImage = ColorBlendImage<ColorOverlayBlender<Tcolor>>;
	template<class Tcolor> using ColorDarkenBlendImage = ColorBlendImage<ColorDarkenBlender<Tcolor>>;
	template<class Tcolor> using ColorLightenBlendImage = ColorBlendImage<ColorLightenBlender<Tcolor>>;
	template<class Tcolor> using ColorDodgeBlendImage = ColorBlendImage<ColorDodgeBlender<Tcolor>>;
	template<class Tcolor> using ColorBurnBlendImage = ColorBlendImage<ColorBurnBlender<Tcolor>>;
	template<class Tcolor> using ColorHardLightBlendImage = ColorBlendImage<ColorHardLightBlender<Tcolor>>;
	template<class Tcolor> using ColorSoftLightBlendImage = ColorBlendImage<ColorSoftLightBlender<Tcolor>>;
	template<class Tcolor> using ColorDifferenceBlendImage = ColorBlendImage<ColorDifferenceBlender<Tcolor>>;
	template<class Tcolor> using ColorExclusionBlendImage = ColorBlendImage<ColorExclusionBlender<Tcolor>>;
}
#endif // __stationaryorbit_graphics_core_colorblending__
