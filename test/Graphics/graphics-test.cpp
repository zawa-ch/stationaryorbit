#include <fstream>
#include "Graphics/General"
#include "Graphics/BMPImage"

void ReadBMP();

int main(int argc, char const *argv[])
{
	ReadBMP();
	return 0;
}

void ReadBMP()
{
	const char* ifile = "Jellyfish.bmp";
	std::fstream istream = std::fstream(ifile, std::ios_base::openmode::_S_in | std::ios_base::openmode::_S_bin);
	if (!istream.good()) throw std::logic_error("can't read file.");
	StationaryOrbit::Graphics::BMP::BMPImage image = StationaryOrbit::Graphics::BMP::BMPImage(istream);
	StationaryOrbit::Graphics::BMP::BMPImageBitmap buffer = image.getBitmap();
	istream.close();

	const char* ofile = "output.bmp";
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	if (!ostream.good()) throw std::logic_error("can't write file.");
	StationaryOrbit::Graphics::BMP::RGB24BMP::Export(ostream, buffer);

	return;
}