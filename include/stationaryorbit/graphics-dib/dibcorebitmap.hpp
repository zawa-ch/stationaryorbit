//	stationaryorbit/graphics-dib/dibcorebitmap
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
#ifndef __stationaryorbit_graphics_dib_dibcorebitmap__
#define __stationaryorbit_graphics_dib_dibcorebitmap__
#include <vector>
#include <variant>
#include "dibloader.hpp"
namespace zawa_ch::StationaryOrbit::Graphics::DIB
{
	class DIBCoreBitmapDecoder
	{
	public:
		typedef std::variant<DIBPixelData<DIBBitDepth::Bit1>, DIBPixelData<DIBBitDepth::Bit4>, DIBPixelData<DIBBitDepth::Bit8>, DIBPixelData<DIBBitDepth::Bit24>> ValueType;
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
		DIBCoreBitmapDecoder(DIBLoader& loader, size_t offset, DIBBitDepth bitdepth, const DisplayRectSize& size);
		virtual ~DIBCoreBitmapDecoder() = default;

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
		void Write(const DIBPixelData<DIBBitDepth::Bit1>& value);
		///	現在の位置にオブジェクトを書き込みます。
		void Write(const DIBPixelData<DIBBitDepth::Bit4>& value);
		///	現在の位置にオブジェクトを書き込みます。
		void Write(const DIBPixelData<DIBBitDepth::Bit8>& value);
		///	現在の位置にオブジェクトを書き込みます。
		void Write(const DIBPixelData<DIBBitDepth::Bit24>& value);
		///	指定されたオブジェクトとの距離を取得します。
		[[nodiscard]] IteratorTraits::IteratorDiff_t Distance(const DIBCoreBitmapDecoder& other) const;
		[[nodiscard]] bool Equals(const DIBCoreBitmapDecoder& other) const;
		[[nodiscard]] int Compare(const DIBCoreBitmapDecoder& other) const;
	private:
		[[nodiscard]] ValueType Get(const DisplayPoint& pos);
		[[nodiscard]] size_t ResolveIndex(const DisplayPoint& pos) const;
		[[nodiscard]] DisplayPoint ResolvePos(size_t index) const;
		[[nodiscard]] size_t ResolveOffset(const DisplayPoint& pos) const;
	};
	///	@a DIBLoader を使用してCoreHeaderを持つWindows bitmap 画像を読み込みます。
	class DIBCoreBitmap
	{
	public:
		typedef RGB8_t ValueType;
		typedef RGB8Pixmap_t Pixmap;
	private:
		DIBLoader&& loader;
		DIBCoreHeader ihead;
		std::vector<RGB8_t> palette;
	public:
		///	@a DIBFileLoader を使用して @a DIBCoreBitmap を初期化します。
		///	@param	loader
		///	読み込みに使用する @a DIBFileLoader 。
		///	このオブジェクトで「消費」されるため、右辺値参照である必要があります。
		DIBCoreBitmap(DIBLoader&& loader);

		///	このオブジェクトの情報ヘッダを取得します。
		[[nodiscard]] const DIBCoreHeader& InfoHead() const { return ihead; }

		///	画像の指定された位置にある1ピクセルの色を取得します。
		///	@param	pos
		///	取得する画像上の座標位置。
		[[nodiscard]] ValueType GetPixel(const DisplayPoint& pos);
		///	画像の指定された位置から連続したピクセルの色を取得します。
		///	@param	pos
		///	取得する画像上の座標位置。
		///	@param	count
		///	取得する要素数。
		[[nodiscard]] std::vector<ValueType> GetPixel(const DisplayPoint& pos, size_t count);
		///	画像の指定された位置にある1ピクセルの色を設定します。
		///	@param	pos
		///	設定する画像上の座標位置。
		///	@param	value
		///	設定する値。
		void SetPixel(const DisplayPoint& pos, const ValueType& value);
		///	画像の指定された位置から連続したピクセルの色を設定します。
		///	@param	pos
		///	取得する画像上の座標位置。
		///	@param	value
		///	設定する値の配列。
		void SetPixel(const DisplayPoint& pos, const std::vector<ValueType>& value);
		///	画像の指定された位置にある1ピクセルの生データを取得します。
		///	@param	pos
		///	取得する画像上の座標位置。
		[[nodiscard]] uint32_t GetPixelRaw(const DisplayPoint& pos);
		///	画像の指定された位置から連続したピクセルの生データを取得します。
		///	@param	pos
		///	取得する画像上の座標位置。
		///	@param	count
		///	取得する要素数。
		[[nodiscard]] std::vector<uint32_t> GetPixelRaw(const DisplayPoint& pos, size_t count);
		///	画像の指定された位置にある1ピクセルの生データを設定します。
		///	@param	pos
		///	設定する画像上の座標位置。
		///	@param	value
		///	設定する値。
		void SetPixelRaw(const DisplayPoint& pos, const uint32_t& value);
		///	画像の指定された位置から連続したピクセルの生データを設定します。
		///	@param	pos
		///	取得する画像上の座標位置。
		///	@param	value
		///	設定する値の配列。
		void SetPixelRaw(const DisplayPoint& pos, const std::vector<uint32_t>& value);

		///	画像を @a WritableImage にコピーします。
		///	@param	dest
		///	コピー先の画像バッファ。
		void CopyTo(WritableImage<ValueType>& dest);
		///	画像の指定された領域を @a WritableImage にコピーします。
		///	@param	dest
		///	コピー先の画像バッファ。
		///	@param	area
		///	コピー元の切り抜き範囲。
		///	@param	destorigin
		///	コピー先の貼り付け基準位置。
		void CopyTo(WritableImage<ValueType>& dest, const DisplayRectangle& area, const DisplayPoint& destorigin = DisplayPoint(0, 0));
		///	画像を @a Pixmap として出力します。
		Pixmap ToPixmap();
		///	画像の指定された領域を @a Pixmap として出力します。
		///	@param	area
		///	画像の切り抜き範囲。
		Pixmap ToPixmap(const DisplayRectangle& area);
	};
}
#endif // __stationaryorbit_graphics_dib_dibcorebitmap__