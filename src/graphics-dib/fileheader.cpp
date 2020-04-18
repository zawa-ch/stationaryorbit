#include "stationaryorbit/graphics-dib/fileheader.hpp"
using namespace zawa_ch::StationaryOrbit;

bool Graphics::DIB::FileHeader::CheckFileHeader() const
{
	for (size_t i = 0; i < (sizeof(FileType_Signature) / sizeof(uint8_t)); i++)
	{
		if (FileType_Signature[i] != FileType[i]) return false;
	}
	return true;
}