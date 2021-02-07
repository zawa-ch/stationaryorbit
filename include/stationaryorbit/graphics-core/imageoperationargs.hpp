//	stationaryorbit/graphics-core/imageoperationargs
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
#ifndef __stationaryorbit_graphics_core_imageoperationargs__
#define __stationaryorbit_graphics_core_imageoperationargs__
#include <type_traits>
#include "image.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	class ImageOperationArgs {};
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
}
#endif // __stationaryorbit_graphics_core_imageoperationargs__
