#include <fstream>
#include "Graphics/General"
#include "Graphics/Bitmap"
#include "Graphics/BMPImage"

void Test_BMP()
{
	const char* ifile = "Jellyfish.bmp";
	std::fstream istream = std::fstream(ifile, std::ios_base::openmode::_S_in | std::ios_base::openmode::_S_bin);
	if (!istream.good()) throw std::logic_error("can't read file.");
	StationaryOrbit::Graphics::BMP::BMPImage image = StationaryOrbit::Graphics::BMP::BMPImage(istream);
	StationaryOrbit::Graphics::BMP::BMPImageBitmap buffer = image.getBitmap();
	istream.close();

	const char* ofile1 = "output.bmp";
	std::fstream ostream1 = std::fstream(ofile1, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream1.good()) throw std::logic_error("can't write file.");
	StationaryOrbit::Graphics::BMP::RGB24BMP::Export(ostream1, buffer);
    ostream1.close();

	StationaryOrbit::Graphics::Bitmap out = StationaryOrbit::Graphics::BitmapSimpleConvert::FripVertical(buffer);
	const char* ofile2 = "output_fripv.bmp";
	std::fstream ostream2 = std::fstream(ofile2, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream2.good()) throw std::logic_error("can't write file.");
	StationaryOrbit::Graphics::BMP::RGB24BMP::Export(ostream2, out, buffer.getBMPInfomation());
    ostream2.close();
}
