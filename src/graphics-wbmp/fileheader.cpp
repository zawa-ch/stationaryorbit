#include "Graphics/BMP/Structure/FileHeader.hpp"

const uint8_t StationaryOrbit::Graphics::BMP::FileHeader::FileType_Signature[2] = { 'B', 'M' };

const size_t StationaryOrbit::Graphics::BMP::FileHeader::Size = sizeof(FileHeader);

bool StationaryOrbit::Graphics::BMP::FileHeader::CheckFileHeader() const
{
	for (size_t i = 0; i < (sizeof(FileType_Signature) / sizeof(uint8_t)); i++)
	{
		if (FileType_Signature[i] != FileType[i]) return false;
	}
	return true;
}
