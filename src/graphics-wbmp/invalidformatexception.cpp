#include "stationaryorbit/graphics-wbmp/invalidformatexception.hpp"
using namespace zawa_ch::StationaryOrbit;

Graphics::BMP::InvalidFormatException::InvalidFormatException(const std::string& what_arg)
	: std::logic_error(what_arg)
{}

Graphics::BMP::InvalidFormatException::InvalidFormatException(const char* what_arg)
	: std::logic_error(what_arg)
{}
