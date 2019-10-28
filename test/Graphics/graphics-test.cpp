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
	const char* file = "Jellyfish.bmp";
	std::fstream stream = std::fstream(file, std::ios_base::openmode::_S_in | std::ios_base::openmode::_S_bin);
	if (!stream.good()) throw std::logic_error("can't read file.");
	StationaryOrbit::Graphics::BMPImage image = StationaryOrbit::Graphics::BMPImage(stream);
	StationaryOrbit::Graphics::BMPImageBitmap buffer = image.getBitmap();

	return;
}