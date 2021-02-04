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

RGB8Pixmap_t image;
DIB::DIBInfoHeader ihead;

void Read();
void Write();
void Write16();
void WriteCoreProfile();
void FripV();
void FripH();
void Crop();
void Resize1();
void Resize2();
void Mono();

void Test_DIB()
{
	std::chrono::duration<double> elapsed;
	auto start = std::chrono::steady_clock::now();
	Read();
	elapsed = std::chrono::steady_clock::now() - start;
	std::cout << "File read: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::steady_clock::now();
	Write();
	elapsed = std::chrono::steady_clock::now() - start;
	std::cout << "File write: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::steady_clock::now();
	Write16();
	elapsed = std::chrono::steady_clock::now() - start;
	std::cout << "File write at 16bit: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::steady_clock::now();
	WriteCoreProfile();
	elapsed = std::chrono::steady_clock::now() - start;
	std::cout << "File write with CoreHeader Profile: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::steady_clock::now();
	FripV();
	elapsed = std::chrono::steady_clock::now() - start;
	std::cout << "Vertical frip: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::steady_clock::now();
	FripH();
	elapsed = std::chrono::steady_clock::now() - start;
	std::cout << "Horizonal frip: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::steady_clock::now();
	Crop();
	elapsed = std::chrono::steady_clock::now() - start;
	std::cout << "Cropping: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::steady_clock::now();
	Resize1();
	elapsed = std::chrono::steady_clock::now() - start;
	std::cout << "Shrink: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::steady_clock::now();
	Resize2();
	elapsed = std::chrono::steady_clock::now() - start;
	std::cout << "Expand: " << elapsed.count() << "sec." << std::endl;

	start = std::chrono::steady_clock::now();
	Mono();
	elapsed = std::chrono::steady_clock::now() - start;
	std::cout << "Monotone: " << elapsed.count() << "sec." << std::endl;
}

void Read()
{
	///	読み込みを行うWindowsビットマップファイル。
	const char* ifile = "input.bmp";
	// ファイルを開く
	auto loader = DIB::DIBFileLoader(ifile, std::ios_base::in | std::ios_base::binary);
	// ビットマップをロードする
	switch(loader.HeaderSize())
	{
		case 40:
		{
			auto bitmap = DIB::DIBInfoBitmap(std::move(loader));
			ihead = bitmap.InfoHead();
			image = bitmap.ToPixmap();
			break;
		}
		default: { throw std::runtime_error("Can't read file."); }
	}
}

void Write()
{
	const char* ofile = "output.bmp";
	// ファイルを開く
	auto loader = DIB::DIBFileLoader(ofile, std::ios_base::out | std::ios_base::binary);
	// ビットマップを書き込む
	DIB::DIBInfoBitmap::Generate(std::move(loader), ihead, image);
}

void Write16()
{
	const char* ofile = "output16.bmp";
	// ヘッダの準備
	auto whead = ihead;
	whead.BitCount = DIB::DIBBitDepth::Bit16;
	whead.ImageSize = (((uint16_t(whead.BitCount) * whead.ImageWidth) + 31) / 32 * 4) * whead.ImageHeight;
	// ファイルを開く
	auto loader = DIB::DIBFileLoader(ofile, std::ios_base::out | std::ios_base::binary);
	// ビットマップを書き込む
	DIB::DIBInfoBitmap::Generate(std::move(loader), whead, image);
}

void WriteCoreProfile()
{
	const char* ofile = "output_core.bmp";
	// ヘッダの準備
	auto whead = DIB::DIBCoreHeader();
	whead.BitCount = ihead.BitCount;
	whead.ImageHeight = ihead.ImageHeight;
	whead.ImageWidth = ihead.ImageWidth;
	whead.PlaneCount = 1;
	// ファイルを開く
	auto loader = DIB::DIBFileLoader(ofile, std::ios_base::out | std::ios_base::binary);
	// ビットマップを書き込む
	DIB::DIBCoreBitmap::Generate(std::move(loader), whead, image);
}

void FripV()
{
	const char* ofile = "output_fripv.bmp";
	// 画像を上下フリップ
	auto flipedimage = ImageVerticalFlip(image);
	auto alignedimage = ImageAlign(flipedimage);
	// ファイルを開く
	auto loader = DIB::DIBFileLoader(ofile, std::ios_base::out | std::ios_base::binary);
	// ビットマップを書き込む
	DIB::DIBInfoBitmap::Generate(std::move(loader), ihead, alignedimage);
}

void FripH()
{
	const char* ofile = "output_friph.bmp";
	// 画像を左右フリップ
	auto flipedimage = ImageHorizonalFlip(image);
	auto alignedimage = ImageAlign(flipedimage);
	// ファイルを開く
	auto loader = DIB::DIBFileLoader(ofile, std::ios_base::out | std::ios_base::binary);
	// ビットマップを書き込む
	DIB::DIBInfoBitmap::Generate(std::move(loader), ihead, alignedimage);
}

void Crop()
{
	const char* ofile = "output_crop.bmp";
	auto rec = DisplayRectangle(100, 100, image.Size().Width() - 200, image.Size().Height() - 200);
	// 画像を切り抜き
	auto shiftimage = ImageShift(image, DisplayPoint(-rec.Left(), -rec.Top()));
	// ヘッダの準備
	auto whead = ihead;
	whead.ImageWidth = rec.Width();
	whead.ImageHeight = rec.Height();
	whead.ImageSize = (((uint16_t(whead.BitCount) * whead.ImageWidth) + 31) / 32 * 4) * whead.ImageHeight;
	// ファイルを開く
	auto loader = DIB::DIBFileLoader(ofile, std::ios_base::out | std::ios_base::binary);
	// ビットマップを書き込む
	DIB::DIBInfoBitmap::Generate(std::move(loader), whead, shiftimage);
}

void Resize1()
{
	const char* ofile = "output_resize1.bmp";
	const float resizefactor = 0.5f;
	auto newsize = DisplayRectSizeF(image.Size().Width() * resizefactor, image.Size().Height() * resizefactor);
	// 画像をリサイズ
	auto resizedimage = ImageScaling<RGB8_t>(image, ImageInterpolation::NearestNeighbor<RGB8_t>, resizefactor);
	// ヘッダの準備
	auto whead = ihead;
	whead.ImageWidth = newsize.Width();
	whead.ImageHeight = newsize.Height();
	whead.ImageSize = (((uint16_t(whead.BitCount) * whead.ImageWidth) + 31) / 32 * 4) * whead.ImageHeight;
	// ファイルを開く
	auto loader = DIB::DIBFileLoader(ofile, std::ios_base::out | std::ios_base::binary);
	// ビットマップを書き込む
	DIB::DIBInfoBitmap::Generate(std::move(loader), whead, resizedimage);
}

void Resize2()
{
	const char* ofile = "output_resize2.bmp";
	const float resizefactor = 2.0f;
	auto newsize = DisplayRectSizeF(image.Size().Width() * resizefactor, image.Size().Height() * resizefactor);
	// 画像をリサイズ
	auto resizedimage = ImageScaling<RGB8_t>(image, ImageInterpolation::Bilinear<RGB8_t>, resizefactor);
	// ヘッダの準備
	auto whead = ihead;
	whead.ImageWidth = newsize.Width();
	whead.ImageHeight = newsize.Height();
	whead.ImageSize = (((uint16_t(whead.BitCount) * whead.ImageWidth) + 31) / 32 * 4) * whead.ImageHeight;
	// ファイルを開く
	auto loader = DIB::DIBFileLoader(ofile, std::ios_base::out | std::ios_base::binary);
	// ビットマップを書き込む
	DIB::DIBInfoBitmap::Generate(std::move(loader), whead, resizedimage);
}

void Mono()
{
	const char* ofile = "output_mono.bmp";
	// 画像をモノトーン化
	auto monoimage = RGB8Pixmap_t::Convert<RGB8_t>(image, [](const RGB8_t from)-> RGB8_t { return ColorConvert::ToRgbFromLuminance(ColorConvert::ToLuminanceFromSrgb(from)); });
	// ファイルを開く
	auto loader = DIB::DIBFileLoader(ofile, std::ios_base::out | std::ios_base::binary);
	// ビットマップを書き込む
	DIB::DIBInfoBitmap::Generate(std::move(loader), ihead, monoimage);
}
