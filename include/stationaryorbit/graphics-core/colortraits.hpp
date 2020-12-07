//	stationaryorbit/graphics-core/colortraits
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
#ifndef __stationaryorbit_graphics_core_colortraits__
#define __stationaryorbit_graphics_core_colortraits__
#include "stationaryorbit/core.traits.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	class ColorTraits final
	{
	private:
		ColorTraits() = delete;
		ColorTraits(const ColorTraits&) = delete;
		ColorTraits& operator=(const ColorTraits&) = delete;
		ColorTraits&& operator=(ColorTraits&&) = delete;
		ColorTraits(ColorTraits&&) = delete;
		~ColorTraits() = delete;

		template<class, class = std::void_t<>>
		struct IsColorTypeBase_t : std::false_type {};
		template<class T>
		struct IsColorTypeBase_t<T, std::void_t< typename T::ValueType >>
			: std::conjunction
			<
				std::bool_constant<Traits::IsValueType<T>>,
				std::true_type
			>
		{};

		template<class, class = std::void_t<>>
		struct IsColorType_t : std::false_type {};
		template<class T>
		struct IsColorType_t<T, std::void_t< typename T::DataType >>
			: std::conjunction
			<
				IsColorTypeBase_t<T>,
				std::bool_constant<Traits::HasArithmeticOperation<T>>,
				std::bool_constant<Traits::HasSaturateOperation<T>>,
				std::bool_constant<Traits::HasCheckedOperation<T>>,
				std::bool_constant<Traits::HasOperatorArithmeticNot<T>>,
				std::bool_constant<Traits::HasOperatorArithmeticOr<T>>,
				std::bool_constant<Traits::HasOperatorArithmeticAnd<T>>,
				std::bool_constant<Traits::HasOperatorArithmeticXor<T>>,
				std::true_type
			>
		{};

		template<class, class = std::void_t<>>
		struct IsTranslucentColorType_t : std::false_type {};
		template<class T>
		struct IsTranslucentColorType_t<T, std::void_t< typename T::ColorType, typename T::OpacityType, decltype(std::declval<T>().Color()), decltype(std::declval<T>().Alpha()) >>
			: std::conjunction
			<
				IsColorTypeBase_t<T>,
				std::is_convertible<decltype(std::declval<T>().Color()), typename T::ColorType>,
				std::is_convertible<decltype(std::declval<T>().Alpha()), typename T::OpacityType>,
				std::true_type
			>
		{};

	public:
		template<class T>
		static constexpr bool IsColorTypeBase = IsColorTypeBase_t<T>::value;
		template<class T>
		static constexpr bool IsColorType = IsColorType_t<T>::value;
		template<class T>
		static constexpr bool IsTranslucentColorType = IsTranslucentColorType_t<T>::value;
	};
}
#endif // __stationaryorbit_graphics_core_colortraits__
