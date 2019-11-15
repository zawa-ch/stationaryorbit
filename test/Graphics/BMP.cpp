#include <fstream>
#include "Graphics/General"
#include "Graphics/Bitmap"
#include "Graphics/BMPImage"

StationaryOrbit::Graphics::BMP::BMPImageBitmap bitmap;

void Read();
void Write();
void FripV();
void FripH();
void Crop();

void Test_BMP()
{
	Read();
	Write();
	FripV();
	FripH();
	Crop();
}

void Read()
{
	const char* ifile = "Jellyfish.bmp";
	std::fstream istream = std::fstream(ifile, std::ios_base::openmode::_S_in | std::ios_base::openmode::_S_bin);
	if (!istream.good()) throw std::logic_error("can't read file.");
	StationaryOrbit::Graphics::BMP::BMPImage image = StationaryOrbit::Graphics::BMP::BMPImage(istream);
	bitmap = image.getBitmap();
	istream.close();
}

void Write()
{
	const char* ofile = "output.bmp";
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	StationaryOrbit::Graphics::BMP::RGB24BMP::Export(ostream, bitmap);
    ostream.close();
}

void FripV()
{
	StationaryOrbit::Graphics::Bitmap out = StationaryOrbit::Graphics::BitmapSimpleConvert::FripVertical(bitmap);
	const char* ofile = "output_fripv.bmp";
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	StationaryOrbit::Graphics::BMP::RGB24BMP::Export(ostream, out, bitmap.getBMPInfomation());
    ostream.close();
}

void FripH()
{
	StationaryOrbit::Graphics::Bitmap out = StationaryOrbit::Graphics::BitmapSimpleConvert::FripHorizonal(bitmap);
	const char* ofile = "output_friph.bmp";
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	StationaryOrbit::Graphics::BMP::RGB24BMP::Export(ostream, out, bitmap.getBMPInfomation());
    ostream.close();
}

void Crop()
{
	StationaryOrbit::Graphics::BMP::BMPImageInfomation newinfo = bitmap.getBMPInfomation();
	const StationaryOrbit::Graphics::Rectangle croparea = StationaryOrbit::Graphics::Rectangle(StationaryOrbit::Graphics::Point(100, 100), bitmap.getInfomation().getSize() - StationaryOrbit::Graphics::Point(100, 100));
	newinfo.setSize(croparea.getSize());
	StationaryOrbit::Graphics::Bitmap out = StationaryOrbit::Graphics::BitmapSimpleConvert::Crop(bitmap, croparea);
	const char* ofile = "output_crop.bmp";
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	StationaryOrbit::Graphics::BMP::RGB24BMP::Export(ostream, out, newinfo);
    ostream.close();
}
