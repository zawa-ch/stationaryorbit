#include <fstream>
#include "Graphics/General"
#include "Graphics/Bitmap"
#include "Graphics/BMPImage"

using namespace StationaryOrbit::Graphics;

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
	Read();
	Write();
	FripV();
	FripH();
	Crop();
	Resize1();
	Resize2();
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
	const float resizefactor = 3.0f;
	newinfo.setSize(Point(PointF(newinfo.getSize()) * resizefactor));
	Bitmap out = BitmapSimpleConvert::Resize(bitmap, newinfo.getSize(), BitmapSimpleConvert::Nearest);
	const char* ofile = "output_resize2.bmp";
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	BMP::RGB24BMP::Export(ostream, out, newinfo);
    ostream.close();
}
