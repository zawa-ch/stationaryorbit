//	stationaryorbit/graphics-dib/dibinfobitmap
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
#ifndef __stationaryorbit_graphics_dib_dibinfobitmap__
#define __stationaryorbit_graphics_dib_dibinfobitmap__
#include <vector>
#include <variant>
#include "dibloader.hpp"
namespace zawa_ch::StationaryOrbit::Graphics::DIB
{
		class DIBBitmapRGBDecoder
	{
	public:
		typedef std::variant<DIBPixelData<DIBBitDepth::Bit1>, DIBPixelData<DIBBitDepth::Bit4>, DIBPixelData<DIBBitDepth::Bit8>, DIBPixelData<DIBBitDepth::Bit16>, DIBPixelData<DIBBitDepth::Bit24>, DIBPixelData<DIBBitDepth::Bit32>> ValueType;
	private:
		///	デコード時に読み込みを行う @a DIBLoader への参照。
		DIBLoader& loader;
		///	読み込み先のデータのオフセット。
		size_t offset;
		///	画像の大きさ。
		DisplayRectSize size;
		///	全体の要素数。
		int64_t length;
		///	現在の読み込み位置。
		int64_t current;
		///	現在の値。
		ValueType current_value;
		///	各ピクセルのデータ長。
		DIBBitDepth bitdepth;
	public:
		DIBBitmapRGBDecoder(DIBLoader& loader, size_t offset, DIBBitDepth bitdepth, const DisplayRectSize& size);
		virtual ~DIBBitmapRGBDecoder() = default;

		///	現在の位置を次に進めます。
		bool Next();
		///	現在の位置を指定された数だけ次に進めます。
		bool Next(const IteratorTraits::IteratorDiff_t& count);
		///	現在の位置を前に戻します。
		bool Previous();
		///	現在の位置を指定された数だけ前に戻します。
		bool Previous(const IteratorTraits::IteratorDiff_t& count);
		///	画像の任意の位置にジャンプします。
		void JumpTo(const DisplayPoint& pos);
		///	現在の位置を初期位置に戻します。
		void Reset();
		///	現在の位置を初期位置に戻します。
		void Reset(const IteratorOrigin& origin);
		///	現在の位置が値を持っているかを取得します。
		[[nodiscard]] bool HasValue() const;
		///	現在の位置が最初の要素よりも前にいるかを取得します。
		[[nodiscard]] bool IsBeforeBegin() const;
		///	現在の位置が最後の要素よりも後にいるかを取得します。
		[[nodiscard]] bool IsAfterEnd() const;
		///	現在の位置を画像上での位置で取得します。
		[[nodiscard]] DisplayPoint CurrentPos() const;
		///	現在の位置にあるオブジェクトを取得します。
		[[nodiscard]] ValueType Current() const;
		///	現在の位置にオブジェクトを書き込みます。
		void Write(const ValueType& value);
		///	指定されたオブジェクトとの距離を取得します。
		[[nodiscard]] IteratorTraits::IteratorDiff_t Distance(const DIBBitmapRGBDecoder& other) const;
		[[nodiscard]] bool Equals(const DIBBitmapRGBDecoder& other) const;
		[[nodiscard]] int Compare(const DIBBitmapRGBDecoder& other) const;
	private:
		[[nodiscard]] ValueType Get(const DisplayPoint& pos);
		[[nodiscard]] size_t ResolveIndex(const DisplayPoint& pos) const;
		[[nodiscard]] DisplayPoint ResolvePos(size_t index) const;
		[[nodiscard]] size_t ResolveOffset(const DisplayPoint& pos) const;
	};
}
#endif // __stationaryorbit_graphics_dib_dibinfobitmap__
