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
	StationaryOrbit::Graphics::BMPImage image = StationaryOrbit::Graphics::BMPImage(istream);
	StationaryOrbit::Graphics::BMPImageBitmap buffer = image.getBitmap();
	istream.close();

	const char* ofile = "output.bmp";
	std::fstream ostream = std::fstream(ofile, std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_bin);
	StationaryOrbit::Graphics::BMPImage::Export(ostream, buffer);

	return;
}