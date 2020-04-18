#include "stationaryorbit/graphics-dib/invaliddibformat.hpp"
using namespace zawa_ch::StationaryOrbit;

Graphics::DIB::InvalidDIBFormatException::InvalidDIBFormatException(const std::string& what_arg)
	: InvalidOperationException(what_arg)
{}

Graphics::DIB::InvalidDIBFormatException::InvalidDIBFormatException(const char* what_arg)
	: InvalidOperationException(what_arg)
{}