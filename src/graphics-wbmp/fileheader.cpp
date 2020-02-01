#include "stationaryorbit/graphics-wbmp/fileheader.hpp"
using namespace zawa_ch::StationaryOrbit;

const uint8_t Graphics::BMP::FileHeader::FileType_Signature[2] = { 'B', 'M' };

const size_t Graphics::BMP::FileHeader::Size = sizeof(FileHeader);

bool Graphics::BMP::FileHeader::CheckFileHeader() const
{
	for (size_t i = 0; i < (sizeof(FileType_Signature) / sizeof(uint8_t)); i++)
	{
		if (FileType_Signature[i] != FileType[i]) return false;
	}
	return true;
}
