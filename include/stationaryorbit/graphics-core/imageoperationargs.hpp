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
	///	画像操作を行うための引数を保持する基本クラス。
	class ImageOperationArgs {};
	template<class operation, class = void>
	class ImageOperationArgsBinder;
	///	画像操作を行うクラスに引数をバインドします。
	///	@param operation
	///	画像操作を行うクラス。
	///	@a Image を継承し、 ( @a Image , @a operation::ArgsType ) を引数に取るコンストラクタをサポートする必要があります。
	template<class operation>
	class ImageOperationArgsBinder<operation, std::void_t< typename operation::ValueType, typename operation::ArgsType, std::enable_if_t< std::is_constructible_v<operation, const Image<typename operation::ValueType>&, const typename operation::ArgsType&>, void> > > final
	{
	public:
		///	画像操作を行うクラス。
		///	@a Image を継承し、 ( @a Image , @a ArgsType ) を引数に取るコンストラクタをサポートする必要があります。
		typedef operation OperationType;
		///	引数を保持するクラス。
		///	@a operation::ArgsType と同一です。
		typedef typename operation::ArgsType ArgsType;
		///	色を表現するために使用する型。
		///	@a operation::ValueType と同一です。
		typedef typename operation::ValueType ValueType;
	private:
		ArgsType _args;
	public:
		///	画像操作を行うクラスに引数をバインドします。
		///	@param	args
		///	バインドする引数。
		ImageOperationArgsBinder(const ArgsType args) : _args(args) {}

		///	バインドされている引数を取得します。
		[[nodiscard]] const ArgsType& Args() const { return _args; }
		///	ソースとなる画像を渡し、画像操作を行うクラスのインスタンスを作成します。
		[[nodiscard]] OperationType Get(const Image<ValueType>& source) const { return OperationType(source, _args); }
	};
}
#endif // __stationaryorbit_graphics_core_imageoperationargs__
