//	stationaryorbit/graphics-core/colorcomposition
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
#ifndef __stationaryorbit_graphics_core_colorcomposition__
#define __stationaryorbit_graphics_core_colorcomposition__
#include "translucentcolor.hpp"
#include "colorblending.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	///	コンポジッタとして用いるためのPorter-Duff演算子の実装です。
	///	このクラスは継承できません。
	class PorterDuffOperator final
	{
	private:
		PorterDuffOperator() = delete;
		PorterDuffOperator(const PorterDuffOperator&) = delete;
		PorterDuffOperator(PorterDuffOperator&&) = delete;
		~PorterDuffOperator() = delete;
	public:
		template<class Tcolor, class Tch = typename Tcolor::ValueType, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> Clear(const Tcolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// Fa = 0; Fb = 0
			// co = 0
			// αo = 0
			return TranslucentColor<Tcolor>(Zero);
		}
		template<class Tcolor, class Tch = typename Tcolor::ValueType, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> Copy(const Tcolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// Fa = 1; Fb = 0
			// co = αs x Cs
			// αo = αs
			return TranslucentColor(source, Opacity(alpha_s));
		}
		template<class Tcolor, class Tch = typename Tcolor::ValueType, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> Destination(const Tcolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// Fa = 0; Fb = 1
			// co = αb x Cb
			// αo = αb
			return TranslucentColor(backdrop, Opacity(alpha_b));
		}
		template<class Tcolor, class Tch = typename Tcolor::ValueType, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> SourceOver(const Tcolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// Fa = 1; Fb = 1 – αs
			// co = αs x Cs + αb x Cb x (1 – αs)
			// αo = αs + αb x (1 – αs)
			return TranslucentColor(source * alpha_s + backdrop * alpha_b * (~alpha_s), Opacity(alpha_s) + Opacity(alpha_b * (~alpha_s)));
		}
		template<class Tcolor, class Tch = typename Tcolor::ValueType, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> DestinationOver(const Tcolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// Fa = 1 – αb; Fb = 1
			// co = αs x Cs x (1 – αb) + αb x Cb
			// αo = αs x (1 – αb) + αb
			return TranslucentColor(source * alpha_s * (~alpha_b) + Tcolor(backdrop * alpha_b), Opacity(alpha_s * (~alpha_b)) + Opacity(alpha_b));
		}
		template<class Tcolor, class Tch = typename Tcolor::ValueType, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> SourceIn(const Tcolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// Fa = αb; Fb = 0
			// co = αs x Cs x αb
			// αo = αs x αb
			return TranslucentColor(source * alpha_s * alpha_b, Opacity(alpha_s * alpha_b));
		}
		template<class Tcolor, class Tch = typename Tcolor::ValueType, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> DestinationIn(const Tcolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// Fa = 0; Fb = αs
			// co = αb x Cb x αs 
			// αo = αb x αs
			return TranslucentColor(backdrop * alpha_s * alpha_b, Opacity(alpha_s * alpha_b));
		}
		template<class Tcolor, class Tch = typename Tcolor::ValueType, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> SourceOut(const Tcolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// Fa = 1 – αb; Fb = 0
			// co = αs x Cs x (1 – αb)
			// αo = αs x (1 – αb)
			return TranslucentColor(source * alpha_s * (~alpha_b), Opacity(alpha_s * (~alpha_b)));
		}
		template<class Tcolor, class Tch = typename Tcolor::ValueType, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> DestinationOut(const Tcolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// Fa = 0; Fb = 1 – αs
			// co = αb x Cb x (1 – αs)
			// αo = αb x (1 – αs)
			return TranslucentColor(backdrop * (~alpha_s) * alpha_b, Opacity((~alpha_s) * alpha_b));
		}
		template<class Tcolor, class Tch = typename Tcolor::ValueType, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> SourceAtop(const Tcolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// Fa = αb; Fb = 1 – αs
			// co = αs x Cs x αb + αb x Cb x (1 – αs)
			// αo = αs x αb + αb x (1 – αs)
			return TranslucentColor(source * alpha_s * alpha_b + backdrop * alpha_b * (~alpha_s), Opacity(alpha_s * alpha_b) + Opacity(alpha_b * (~alpha_s)));
		}
		template<class Tcolor, class Tch = typename Tcolor::ValueType, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> DestinationAtop(const Tcolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// Fa = 1 - αb; Fb = αs
			// co = αs x Cs x (1 - αb) + αb x Cb x αs
			// αo = αs x (1 - αb) + αb x αs
			return TranslucentColor(source * alpha_s * (~alpha_b) + backdrop * alpha_s * alpha_b, Opacity(alpha_s * (~alpha_b)) + Opacity(alpha_b * alpha_s));
		}
		template<class Tcolor, class Tch = typename Tcolor::ValueType, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> XOR(const Tcolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// Fa = 1 - αb; Fb = 1 – αs
			// co = αs x Cs x (1 - αb) + αb x Cb x (1 – αs)
			// αo = αs x (1 - αb) + αb x (1 – αs)
			return TranslucentColor(source * alpha_s * (~alpha_b) + backdrop * (~alpha_s) * alpha_b, Opacity(alpha_s * (~alpha_b)) + Opacity(alpha_b * (~alpha_s)));
		}
		template<class Tcolor, class Tch = typename Tcolor::ValueType, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> Lighter(const Tcolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// Fa = 1; Fb = 1
			// co = αs x Cs + αb x Cb;
			// αo = αs + αb
			return TranslucentColor(source * alpha_s + backdrop * alpha_b, Opacity(alpha_s + alpha_b));
		}
	private:
		template
		<
			class Tacolor,
			TranslucentColor<typename Tacolor::ColorType> algorithm(const typename Tacolor::ColorType&, const typename Tacolor::ValueType&, const typename Tacolor::ColorType&, const typename Tacolor::ValueType&),
			class Tcolor = typename Tacolor::ColorType,
			std::enable_if_t<ColorTraits::IsTranslucentColorType<Tacolor>, int> = 0
		>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> AlphaCompositing(const Tacolor& backdrop, const typename Tacolor::ValueType& alpha_b, const Tacolor& source, const typename Tacolor::ValueType& alpha_s)
		{
			return algorithm(backdrop.Color(), backdrop.Alpha() * alpha_b, source.Color(), source.Alpha() * alpha_s);
		}
	public:
		template<class Tacolor, class Tcolor = typename Tacolor::ColorType, class Tch = typename Tacolor::ValueType, std::enable_if_t<ColorTraits::IsTranslucentColorType<Tacolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> Clear(const Tacolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s) { return AlphaCompositing<Tacolor, Clear<Tcolor>>(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s); }
		template<class Tacolor, class Tcolor = typename Tacolor::ColorType, class Tch = typename Tacolor::ValueType, std::enable_if_t<ColorTraits::IsTranslucentColorType<Tacolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> Copy(const Tacolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s) { return AlphaCompositing<Tacolor, Copy<Tcolor>>(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s); }
		template<class Tacolor, class Tcolor = typename Tacolor::ColorType, class Tch = typename Tacolor::ValueType, std::enable_if_t<ColorTraits::IsTranslucentColorType<Tacolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> Destination(const Tacolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s) { return AlphaCompositing<Tacolor, Destination<Tcolor>>(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s); }
		template<class Tacolor, class Tcolor = typename Tacolor::ColorType, class Tch = typename Tacolor::ValueType, std::enable_if_t<ColorTraits::IsTranslucentColorType<Tacolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> SourceOver(const Tacolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s) { return AlphaCompositing<Tacolor, SourceOver<Tcolor>>(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s); }
		template<class Tacolor, class Tcolor = typename Tacolor::ColorType, class Tch = typename Tacolor::ValueType, std::enable_if_t<ColorTraits::IsTranslucentColorType<Tacolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> DestinationOver(const Tacolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s) { return AlphaCompositing<Tacolor, DestinationOver<Tcolor>>(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s); }
		template<class Tacolor, class Tcolor = typename Tacolor::ColorType, class Tch = typename Tacolor::ValueType, std::enable_if_t<ColorTraits::IsTranslucentColorType<Tacolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> SourceIn(const Tacolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s) { return AlphaCompositing<Tacolor, SourceIn<Tcolor>>(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s); }
		template<class Tacolor, class Tcolor = typename Tacolor::ColorType, class Tch = typename Tacolor::ValueType, std::enable_if_t<ColorTraits::IsTranslucentColorType<Tacolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> DestinationIn(const Tacolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s) { return AlphaCompositing<Tacolor, DestinationIn<Tcolor>>(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s); }
		template<class Tacolor, class Tcolor = typename Tacolor::ColorType, class Tch = typename Tacolor::ValueType, std::enable_if_t<ColorTraits::IsTranslucentColorType<Tacolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> SourceOut(const Tacolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s) { return AlphaCompositing<Tacolor, SourceOut<Tcolor>>(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s); }
		template<class Tacolor, class Tcolor = typename Tacolor::ColorType, class Tch = typename Tacolor::ValueType, std::enable_if_t<ColorTraits::IsTranslucentColorType<Tacolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> DestinationOut(const Tacolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s) { return AlphaCompositing<Tacolor, DestinationOut<Tcolor>>(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s); }
		template<class Tacolor, class Tcolor = typename Tacolor::ColorType, class Tch = typename Tacolor::ValueType, std::enable_if_t<ColorTraits::IsTranslucentColorType<Tacolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> SourceAtop(const Tacolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s) { return AlphaCompositing<Tacolor, SourceAtop<Tcolor>>(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s); }
		template<class Tacolor, class Tcolor = typename Tacolor::ColorType, class Tch = typename Tacolor::ValueType, std::enable_if_t<ColorTraits::IsTranslucentColorType<Tacolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> DestinationAtop(const Tacolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s) { return AlphaCompositing<Tacolor, DestinationAtop<Tcolor>>(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s); }
		template<class Tacolor, class Tcolor = typename Tacolor::ColorType, class Tch = typename Tacolor::ValueType, std::enable_if_t<ColorTraits::IsTranslucentColorType<Tacolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> XOR(const Tacolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s) { return AlphaCompositing<Tacolor, XOR<Tcolor>>(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s); }
		template<class Tacolor, class Tcolor = typename Tacolor::ColorType, class Tch = typename Tacolor::ValueType, std::enable_if_t<ColorTraits::IsTranslucentColorType<Tacolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> Lighter(const Tacolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s) { return AlphaCompositing<Tacolor, Lighter<Tcolor>>(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s); }
	};
	template<class Tcolor, auto algorithm(const Tcolor&, const typename Tcolor::ValueType&, const Tcolor&, const typename Tcolor::ValueType&)>
	class ColorCompositor final
	{
	public:
		typedef Tcolor InputType;
		typedef typename Tcolor::ValueType ChannelType;
		typedef decltype(algorithm) ValueType;
	private:
		ChannelType alpha_source;
		ChannelType alpha_backdrop;
	public:
		constexpr ColorCompositor() : alpha_source(ChannelType::Max()), alpha_backdrop(ChannelType::Max()) {}
		constexpr ColorCompositor(const ChannelType alpha_backdrop, const ChannelType alpha_source) : alpha_source(alpha_source), alpha_backdrop(alpha_backdrop) {}

		[[nodiscard]] constexpr const ChannelType& SourceAlpha() const { return alpha_source; }
		[[nodiscard]] constexpr ChannelType SourceAlpha() { return alpha_source; }
		[[nodiscard]] constexpr const ChannelType& BackdropAlpha() const { return alpha_backdrop; }
		[[nodiscard]] constexpr ChannelType BackdropAlpha() { return alpha_backdrop; }

		[[nodiscard]] constexpr ValueType Composite(const InputType& backdrop, const InputType& source) const
		{
			return algorithm(backdrop, alpha_backdrop, source, alpha_source);
		}
	};
	///	混色を行うクラスを識別します。
	class ColorCompositerTraits final
	{
	private:
		ColorCompositerTraits() = delete;
		ColorCompositerTraits(const ColorCompositerTraits&) = delete;
		ColorCompositerTraits(ColorCompositerTraits&&) = delete;
		~ColorCompositerTraits() = delete;

		template<class T, class = void> struct IsColorCompositer_Impl : std::false_type{};
		template<class T> struct IsColorCompositer_Impl
		<
			T,
			std::void_t
			<
				typename T::InputType,
				typename T::ChannelType,
				typename T::ValueType,
				decltype( std::declval<const T&>().Composite(std::declval<const typename T::InputType&>(), std::declval<const typename T::InputType&>()) ),
				decltype( std::declval<const T&>().SourceAlpha() ),
				decltype( std::declval<const T&>().BackdropAlpha() )
			>
		>
		: std::conjunction
		<
			std::is_same< decltype( std::declval<const T&>().Composite(std::declval<const typename T::InputType&>(), std::declval<const typename T::InputType&>()) ), typename T::ValueType>,
			std::is_same< decltype( std::declval<const T&>().SourceAlpha() ), const typename T::ChannelType&>,
			std::is_same< decltype( std::declval<const T&>().BackdropAlpha() ), const typename T::ChannelType&>,
			std::is_default_constructible<T>,
			std::is_constructible<T, typename T::ChannelType, typename T::ChannelType>
		>
		{};
	public:
		template<class T> using ValueType = typename T::ValueType;

		template<class T> static constexpr bool IsColorCompositer = IsColorCompositer_Impl<T>::value;
	};

	template<class Tcolor> using ColorClearCompositor = ColorCompositor<Tcolor, PorterDuffOperator::Clear<Tcolor>>;
	template<class Tcolor> using ColorCopyCompositor = ColorCompositor<Tcolor, PorterDuffOperator::Copy<Tcolor>>;
	template<class Tcolor> using ColorDestinationCompositor = ColorCompositor<Tcolor, PorterDuffOperator::Destination<Tcolor>>;
	template<class Tcolor> using ColorSourceOverCompositor = ColorCompositor<Tcolor, PorterDuffOperator::SourceOver<Tcolor>>;
	template<class Tcolor> using ColorDestinationOverCompositor = ColorCompositor<Tcolor, PorterDuffOperator::DestinationOver<Tcolor>>;
	template<class Tcolor> using ColorSourceInCompositor = ColorCompositor<Tcolor, PorterDuffOperator::SourceIn<Tcolor>>;
	template<class Tcolor> using ColorDestinationInCompositor = ColorCompositor<Tcolor, PorterDuffOperator::DestinationIn<Tcolor>>;
	template<class Tcolor> using ColorSourceOutCompositor = ColorCompositor<Tcolor, PorterDuffOperator::SourceOut<Tcolor>>;
	template<class Tcolor> using ColorDestinationOutCompositor = ColorCompositor<Tcolor, PorterDuffOperator::DestinationOut<Tcolor>>;
	template<class Tcolor> using ColorSourceAtopCompositor = ColorCompositor<Tcolor, PorterDuffOperator::SourceAtop<Tcolor>>;
	template<class Tcolor> using ColorDestinationAtopCompositor = ColorCompositor<Tcolor, PorterDuffOperator::DestinationAtop<Tcolor>>;
	template<class Tcolor> using ColorXORCompositor = ColorCompositor<Tcolor, PorterDuffOperator::XOR<Tcolor>>;
	template<class Tcolor> using ColorLighterCompositor = ColorCompositor<Tcolor, PorterDuffOperator::Lighter<Tcolor>>;
}
#endif // __stationaryorbit_graphics_core_colorcomposition__
