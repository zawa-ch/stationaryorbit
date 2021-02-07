//	stationaryorbit/graphics-core/imageoperationlist
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
#ifndef __stationaryorbit_graphics_core_imageoperationlist__
#define __stationaryorbit_graphics_core_imageoperationlist__
#include <tuple>
#include "image.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	template<class operation, class = void>
	class ImageOperationArgsBinder;
	template<class operation> 
	class ImageOperationArgsBinder<operation, std::void_t< typename operation::ValueType, typename operation::ArgsType, std::enable_if_t< std::is_constructible_v<operation, const Image<typename operation::ValueType>&, const typename operation::ArgsType&>, void> > > final
	{
	public:
		typedef operation OperationType;
		typedef typename operation::ArgsType ArgsType;
		typedef typename operation::ValueType ValueType;
	private:
		ArgsType _args;
	public:
		ImageOperationArgsBinder(const ArgsType args) : _args(args) {}

		[[nodiscard]] const ArgsType& Args() const { return _args; }
		[[nodiscard]] OperationType Get(const Image<ValueType>& source) const { return OperationType(source, _args); }
	};
	template<class Tcolor, class... operations>
	class ImageOperationList
	{
	public:
		typedef Tcolor ValueType;
		typedef std::tuple<operations...> OperationsType;
		typedef std::tuple<typename operations::ArgsType ...> ArgsType;
	private:
		OperationsType _op;
	public:
		ImageOperationList(const Image<Tcolor>& source, const typename operations::ArgsType& ... args) : _op(Build(source, BindArgs(args...))) {}

	private:
		[[nodiscard]] static std::tuple<ImageOperationArgsBinder<operations> ...> BindArgs(const typename operations::ArgsType& ... args)
		{
			return std::make_tuple(ImageOperationArgsBinder<operations>(args) ...);
		}
		template<std::size_t I, class... input_element>
		[[nodiscard]] static auto Concat(std::tuple<input_element...>&& base, const std::tuple<ImageOperationArgsBinder<operations>...>& binder)
		{
			return std::tuple_cat(std::forward<std::tuple<input_element...>>(base), std::make_tuple(std::get<I>(binder).Get(std::get<I - 1>(base))));
		}
		template<std::size_t I = std::tuple_size_v<std::tuple<ImageOperationArgsBinder<operations>...>> - 1>
		[[nodiscard]] static auto Build(const Image<ValueType>& source, const std::tuple<ImageOperationArgsBinder<operations>...>& binder)
		{
			return Concat<I>(Build<I-1>(source, binder), binder);
		}
		template<>
		[[nodiscard]] static auto Build<0>(const Image<ValueType>& source, const std::tuple<ImageOperationArgsBinder<operations>...>& binder)
		{
			return std::make_tuple(std::get<0>(binder).Get(source));
		}
	};
}
#endif // __stationaryorbit_graphics_core_imageoperationlist__
