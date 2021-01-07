//	stationaryorbit/graphics-dib/dibcolor
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
#ifndef __stationaryorbit_graphics_dib_dibcolor__
#define __stationaryorbit_graphics_dib_dibcolor__
#include "stationaryorbit/core.bitoperation.hpp"
#include "stationaryorbit/graphics-core.color.hpp"
#include "dibheaders.hpp"
namespace zawa_ch::StationaryOrbit::Graphics::DIB
{
	///	Windowsビットマップ画像のピクセルデータを表します。
	template<BitDepth Depth>
	struct DIBPixelData final
	{
	private:
		static constexpr size_t data_length = (size_t(Depth) / BitWidth<uint8_t>) + ((size_t(Depth) % BitWidth<uint8_t> != 0)?(1):(0));
	public:
		typedef std::array<uint8_t, data_length> ValueType;
		typedef EndianValueType<ValueType, Endians::big> DataType;
	private:
		DataType _data;
	public:
		DIBPixelData() = default;
		constexpr explicit DIBPixelData(const uint32_t& value) :
		_data
		(
			[](const uint32_t& v)
			{
				auto result = ValueType();
				for (auto i: Range<size_t>(0, data_length).GetStdIterator()) { result[i] = (v >> (i * BitWidth<uint8_t>)) & 0xFF; }
				return result;
			}(value)
		)
		{}

		constexpr const DataType& Data() const { return _data; }
		constexpr ValueType Value() const { return _data.Value(); }

		constexpr explicit operator uint32_t() const
		{
			auto result = uint32_t();
			auto v = _data.Value();
			for (auto i: Range<size_t>(0, data_length).GetStdIterator()) { result |= v[i] << (i * BitWidth<uint8_t>); }
			return result;
		}
	};
	static_assert(sizeof(DIBPixelData<BitDepth::Bit1>) == 1, "");
	static_assert(sizeof(DIBPixelData<BitDepth::Bit4>) == 1, "");
	static_assert(sizeof(DIBPixelData<BitDepth::Bit8>) == 1, "");
	static_assert(sizeof(DIBPixelData<BitDepth::Bit16>) == 2, "");
	static_assert(sizeof(DIBPixelData<BitDepth::Bit24>) == 3, "");
	static_assert(sizeof(DIBPixelData<BitDepth::Bit32>) == 4, "");
}
#endif // __stationaryorbit_graphics_dib_dibcolor__
