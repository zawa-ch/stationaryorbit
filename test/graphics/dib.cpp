//	stationaryorbit.test.graphics:/dib
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
#include <iostream>
#include <fstream>
#include <chrono>
#include <memory>
#include "stationaryorbit/graphics-dib.bmpimage.hpp"
using namespace zawa_ch::StationaryOrbit;
using namespace zawa_ch::StationaryOrbit::Graphics;

DIB::DIBBitmap bitmap;

void Read();
void Write();
void Write16();
void FripV();
void FripH();
void Crop();
void Resize1();
void Resize2();
void Mono();

void Test_DIB()
{
	std::chrono::duration<double> elapsed;
	auto start = std::chrono::system_clock::now();
	Read();
	elapsed = std::chrono::system_clock::now() - start;
	std::cout << "File read: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::system_clock::now();
	Write();
	elapsed = std::chrono::system_clock::now() - start;
	std::cout << "File write: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::system_clock::now();
	Write16();
	elapsed = std::chrono::system_clock::now() - start;
	std::cout << "File write at 16bit: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::system_clock::now();
	FripV();
	elapsed = std::chrono::system_clock::now() - start;
	std::cout << "Vertical frip: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::system_clock::now();
	FripH();
	elapsed = std::chrono::system_clock::now() - start;
	std::cout << "Horizonal frip: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::system_clock::now();
	Crop();
	elapsed = std::chrono::system_clock::now() - start;
	std::cout << "Cropping: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::system_clock::now();
	Resize1();
	elapsed = std::chrono::system_clock::now() - start;
	std::cout << "Shrink: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::system_clock::now();
	Resize2();
	elapsed = std::chrono::system_clock::now() - start;
	std::cout << "Expand: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::system_clock::now();
	Mono();
	elapsed = std::chrono::system_clock::now() - start;
	std::cout << "Monotone: " << elapsed.count() << "sec." << std::endl;
}

void Read()
{
	///	読み込みを行うWindowsビットマップファイル。
	const char* ifile = "input.bmp";
	// ファイルを開く(ファイルオープンに失敗した場合は例外をスローする)
	std::fstream istream = std::fstream(ifile, std::ios_base::openmode::_S_in | std::ios_base::openmode::_S_bin);
	if (!istream.good()) throw std::logic_error("can't read file.");
	// ビットマップをロードする
	bitmap = DIB::DIBBitmap::FromStream(istream);
	// この段階で物理メモリにビットマップが格納されるためストリームは閉じても問題ない
	istream.close();
}

void Write()
{
	const char* ofile = "output.bmp";
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	bitmap.WriteTo(ostream);
	ostream.close();
}

void Write16()
{
	const char* ofile = "output16.bmp";
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	bitmap.WriteTo(ostream, DIB::BitDepth::Bit16);
	ostream.close();
}

void FripV()
{
	const char* ofile = "output_fripv.bmp";
	auto out = DIB::DIBBitmap::ReinterpretFrom(BitmapConverter<uint8_t>::FripVertical(bitmap));
	out.HorizonalResolution() = bitmap.HorizonalResolution();
	out.VerticalResolution() = bitmap.VerticalResolution();
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	out.WriteTo(ostream);
	ostream.close();
}

void FripH()
{
	const char* ofile = "output_friph.bmp";
	auto out = DIB::DIBBitmap::ReinterpretFrom(BitmapConverter<uint8_t>::FripHorizonal(bitmap));
	out.HorizonalResolution() = bitmap.HorizonalResolution();
	out.VerticalResolution() = bitmap.VerticalResolution();
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	out.WriteTo(ostream);
	ostream.close();
}

void Crop()
{
	const char* ofile = "output_crop.bmp";
	auto rec = DisplayRectangle(100, 100, bitmap.Width() - 200, bitmap.Height() - 200);
	auto out = DIB::DIBBitmap::ReinterpretFrom(BitmapConverter<uint8_t>::Crop(bitmap, rec));
	out.HorizonalResolution() = bitmap.HorizonalResolution();
	out.VerticalResolution() = bitmap.VerticalResolution();
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	out.WriteTo(ostream);
	ostream.close();
}

void Resize1()
{
	const char* ofile = "output_resize1.bmp";
	const float resizefactor = 0.5f;
	auto newsize = RectangleSizeF(bitmap.Width() * resizefactor, bitmap.Height() * resizefactor);
	auto out = DIB::DIBBitmap::ReinterpretFrom(BitmapConverter<uint8_t>::Resize(bitmap, RectangleSize(newsize), BitmapConverter<uint8_t>::Bilinear));
	out.HorizonalResolution() = bitmap.HorizonalResolution();
	out.VerticalResolution() = bitmap.VerticalResolution();
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	out.WriteTo(ostream);
	ostream.close();
}

void Resize2()
{
	const char* ofile = "output_resize2.bmp";
	const float resizefactor = 2.0f;
	auto newsize = RectangleSizeF(bitmap.Width() * resizefactor, bitmap.Height() * resizefactor);
	auto out = DIB::DIBBitmap::ReinterpretFrom(BitmapConverter<uint8_t>::Resize(bitmap, RectangleSize(newsize), BitmapConverter<uint8_t>::Bilinear));
	out.HorizonalResolution() = bitmap.HorizonalResolution();
	out.VerticalResolution() = bitmap.VerticalResolution();
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	out.WriteTo(ostream);
	ostream.close();
}

void Mono()
{
	const char* ofile = "output_mono.bmp";
	auto rgbbmp = ARGBBitmapImageBase<uint8_t>(bitmap);
	rgbbmp.Monotone();
	auto out = DIB::DIBBitmap(rgbbmp);
	out.HorizonalResolution() = bitmap.HorizonalResolution();
	out.VerticalResolution() = bitmap.VerticalResolution();
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	out.WriteTo(ostream);
	ostream.close();
}
