#include <iostream>
#include <fstream>
#include <chrono>
#include "stationaryorbit/graphics-core/bitmap"
#include "stationaryorbit/graphics-wbmp/bmpimage"
using namespace zawa_ch::StationaryOrbit::Graphics;

BMP::BMPImageBitmap bitmap;

void Read();
void Write();
void FripV();
void FripH();
void Crop();
void Resize1();
void Resize2();

void Test_BMP()
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
}

void Read()
{
	const char* ifile = "Jellyfish.bmp";
	std::fstream istream = std::fstream(ifile, std::ios_base::openmode::_S_in | std::ios_base::openmode::_S_bin);
	if (!istream.good()) throw std::logic_error("can't read file.");
	BMP::BMPImage image = BMP::BMPImage(istream);
	bitmap = image.getBitmap();
	istream.close();
}

void Write()
{
	const char* ofile = "output.bmp";
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	BMP::RGB24BMP::Export(ostream, bitmap);
    ostream.close();
}

void FripV()
{
	Bitmap out = BitmapSimpleConvert::FripVertical(bitmap);
	const char* ofile = "output_fripv.bmp";
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	BMP::RGB24BMP::Export(ostream, out, bitmap.getBMPInfomation());
    ostream.close();
}

void FripH()
{
	Bitmap out = BitmapSimpleConvert::FripHorizonal(bitmap);
	const char* ofile = "output_friph.bmp";
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	BMP::RGB24BMP::Export(ostream, out, bitmap.getBMPInfomation());
    ostream.close();
}

void Crop()
{
	BMP::BMPImageInfomation newinfo = bitmap.getBMPInfomation();
	const Rectangle croparea = Rectangle(Point(100, 100), bitmap.getInfomation().getSize() - Point(100, 100));
	newinfo.setSize(croparea.getSize());
	Bitmap out = BitmapSimpleConvert::Crop(bitmap, croparea);
	const char* ofile = "output_crop.bmp";
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	BMP::RGB24BMP::Export(ostream, out, newinfo);
    ostream.close();
}

void Resize1()
{
	BMP::BMPImageInfomation newinfo = bitmap.getBMPInfomation();
	const float resizefactor = 0.5f;
	newinfo.setSize(Point(PointF(newinfo.getSize()) * resizefactor));
	Bitmap out = BitmapSimpleConvert::Resize(bitmap, newinfo.getSize(), BitmapSimpleConvert::Nearest);
	const char* ofile = "output_resize1.bmp";
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	BMP::RGB24BMP::Export(ostream, out, newinfo);
    ostream.close();
}

void Resize2()
{
	BMP::BMPImageInfomation newinfo = bitmap.getBMPInfomation();
	const float resizefactor = 2.0f;
	newinfo.setSize(Point(PointF(newinfo.getSize()) * resizefactor));
	Bitmap out = BitmapSimpleConvert::Resize(bitmap, newinfo.getSize(), BitmapSimpleConvert::Nearest);
	const char* ofile = "output_resize2.bmp";
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	BMP::RGB24BMP::Export(ostream, out, newinfo);
    ostream.close();
}
