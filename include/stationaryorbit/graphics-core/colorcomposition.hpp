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
	};
	class ColorComposition final
	{
		template<class Tcolor, class Tch = typename Tcolor::ValueType, std::enable_if_t<ColorTraits::IsColorType<Tcolor>, int> = 0>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> Clear(const Tcolor& backdrop, const Tch& alpha_b, const Tcolor& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// Fa = 0; Fb = 0
			// co = 0
			// αo = 0
			return TranslucentColor(Zero);
		}
		template<class Tcolor, class Tch = typename Tcolor::ValueType>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> Clear(const TranslucentColor<Tcolor>& backdrop, const Tch& alpha_b, const TranslucentColor<Tcolor>& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// Fa = 0; Fb = 0
			// co = 0
			// αo = 0
			return TranslucentColor(Zero);
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
		template<class Tcolor, class Tch = typename Tcolor::ValueType>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> Copy(const TranslucentColor<Tcolor>& backdrop, const Tch& alpha_b, const TranslucentColor<Tcolor>& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// Fa = 1; Fb = 0
			// co = αs x Cs
			// αo = αs
			return TranslucentColor(source.Color(), source.Alpha() * Opacity(alpha_s));
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
		template<class Tcolor, class Tch = typename Tcolor::ValueType>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> Destination(const TranslucentColor<Tcolor>& backdrop, const Tch& alpha_b, const TranslucentColor<Tcolor>& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			// Fa = 0; Fb = 1
			// co = αb x Cb
			// αo = αb
			return TranslucentColor(backdrop.Color(), backdrop.Alpha() * Opacity(alpha_b));
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
		template<class Tcolor, class Tch = typename Tcolor::ValueType>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> SourceOver(const TranslucentColor<Tcolor>& backdrop, const Tch& alpha_b, const TranslucentColor<Tcolor>& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			return SourceOver(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s);
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
		template<class Tcolor, class Tch = typename Tcolor::ValueType>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> DestinationOver(const TranslucentColor<Tcolor>& backdrop, const Tch& alpha_b, const TranslucentColor<Tcolor>& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			return DestinationOver(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s);
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
		template<class Tcolor, class Tch = typename Tcolor::ValueType>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> SourceIn(const TranslucentColor<Tcolor>& backdrop, const Tch& alpha_b, const TranslucentColor<Tcolor>& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			return SourceIn(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s);
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
		template<class Tcolor, class Tch = typename Tcolor::ValueType>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> DestinationIn(const TranslucentColor<Tcolor>& backdrop, const Tch& alpha_b, const TranslucentColor<Tcolor>& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			return DestinationIn(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s);
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
		template<class Tcolor, class Tch = typename Tcolor::ValueType>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> SourceOut(const TranslucentColor<Tcolor>& backdrop, const Tch& alpha_b, const TranslucentColor<Tcolor>& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			return SourceOut(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s);
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
		template<class Tcolor, class Tch = typename Tcolor::ValueType>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> DestinationOut(const TranslucentColor<Tcolor>& backdrop, const Tch& alpha_b, const TranslucentColor<Tcolor>& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			return DestinationOut(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s);
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
		template<class Tcolor, class Tch = typename Tcolor::ValueType>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> SourceAtop(const TranslucentColor<Tcolor>& backdrop, const Tch& alpha_b, const TranslucentColor<Tcolor>& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			return SourceAtop(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s);
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
		template<class Tcolor, class Tch = typename Tcolor::ValueType>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> DestinationAtop(const TranslucentColor<Tcolor>& backdrop, const Tch& alpha_b, const TranslucentColor<Tcolor>& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			return DestinationAtop(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s);
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
		template<class Tcolor, class Tch = typename Tcolor::ValueType>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> XOR(const TranslucentColor<Tcolor>& backdrop, const Tch& alpha_b, const TranslucentColor<Tcolor>& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			return XOR(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s);
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
		template<class Tcolor, class Tch = typename Tcolor::ValueType>
		[[nodiscard]] static constexpr TranslucentColor<Tcolor> Lighter(const TranslucentColor<Tcolor>& backdrop, const Tch& alpha_b, const TranslucentColor<Tcolor>& source, const Tch& alpha_s)
		{
			static_assert(ColorTraits::IsColorType<Tcolor>, "テンプレート引数 Tcolor は色型である必要があります。");
			return Lighter(backdrop.Color(), backdrop.Alpha().Data() * alpha_b, source.Color(), source.Alpha().Data() * alpha_s);
		}
	};
}
#endif // __stationaryorbit_graphics_core_colorcomposition__
