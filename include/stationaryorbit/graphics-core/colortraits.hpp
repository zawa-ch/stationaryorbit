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
				std::bool_constant<Traits::IsArithmeticType<T>>,
				std::true_type
			>
		{};

		template<class, class = std::void_t<>>
		struct IsGrayScaleColorType_t : std::false_type {};
		template<class T>
		struct IsGrayScaleColorType_t<T, std::void_t< typename T::ValueType, decltype(std::declval<T>().Luminance()) >>
			: std::conjunction
			<
				IsColorType_t<T>,
				std::is_convertible<decltype(std::declval<T>().Luminance()), typename T::ValueType>,
				std::true_type
			>
		{};

		template<class, class = std::void_t<>>
		struct IsRGBColorType_t : std::false_type {};
		template<class T>
		struct IsRGBColorType_t<T, std::void_t< typename T::ValueType, decltype(std::declval<T>().R()), decltype(std::declval<T>().G()), decltype(std::declval<T>().B()) >>
			: std::conjunction
			<
				IsColorType_t<T>,
				std::is_convertible<decltype(std::declval<T>().R()), typename T::ValueType>,
				std::is_convertible<decltype(std::declval<T>().G()), typename T::ValueType>,
				std::is_convertible<decltype(std::declval<T>().B()), typename T::ValueType>,
				std::true_type
			>
		{};

		template<class, class = std::void_t<>>
		struct IsCMYColorType_t : std::false_type {};
		template<class T>
		struct IsCMYColorType_t<T, std::void_t< typename T::ValueType, decltype(std::declval<T>().C()), decltype(std::declval<T>().M()), decltype(std::declval<T>().Y()) >>
			: std::conjunction
			<
				IsColorType_t<T>,
				std::is_convertible<decltype(std::declval<T>().C()), typename T::ValueType>,
				std::is_convertible<decltype(std::declval<T>().M()), typename T::ValueType>,
				std::is_convertible<decltype(std::declval<T>().Y()), typename T::ValueType>,
				std::true_type
			>
		{};

		template<class, class = std::void_t<>>
		struct IsCMYKColorType_t : std::false_type {};
		template<class T>
		struct IsCMYKColorType_t<T, std::void_t< typename T::ValueType, decltype(std::declval<T>().C()), decltype(std::declval<T>().M()), decltype(std::declval<T>().Y()), decltype(std::declval<T>().K()) >>
			: std::conjunction
			<
				IsColorType_t<T>,
				std::is_convertible<decltype(std::declval<T>().C()), typename T::ValueType>,
				std::is_convertible<decltype(std::declval<T>().M()), typename T::ValueType>,
				std::is_convertible<decltype(std::declval<T>().Y()), typename T::ValueType>,
				std::is_convertible<decltype(std::declval<T>().K()), typename T::ValueType>,
				std::true_type
			>
		{};

		template<class, class = std::void_t<>>
		struct IsTranslucentColorType_t : std::false_type {};
		template<class T>
		struct IsTranslucentColorType_t
		<
			T,
			std::void_t
			<
				typename T::ColorType,
				typename T::OpacityType,
				decltype(std::declval<T>().Color()),
				decltype(std::declval<T>().Alpha()),
				decltype(T(std::declval<typename T::ColorType>())),
				decltype(T(std::declval<typename T::ColorType>(), std::declval<typename T::OpacityType>()))
			>
		>
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
		static constexpr bool IsGrayScaleColorType = IsGrayScaleColorType_t<T>::value;
		template<class T>
		static constexpr bool IsRGBColorType = IsRGBColorType_t<T>::value;
		template<class T>
		static constexpr bool IsCMYColorType = IsCMYColorType_t<T>::value;
		template<class T>
		static constexpr bool IsCMYKColorType = IsCMYKColorType_t<T>::value;
		template<class T>
		static constexpr bool IsTranslucentColorType = IsTranslucentColorType_t<T>::value;
	};
}
#endif // __stationaryorbit_graphics_core_colortraits__
