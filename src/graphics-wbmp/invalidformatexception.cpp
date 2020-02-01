#include "Graphics/BMP/Logic/InvalidFormatException.hpp"

StationaryOrbit::Graphics::BMP::InvalidFormatException::InvalidFormatException(const std::string& what_arg)
	: std::logic_error(what_arg)
{}

StationaryOrbit::Graphics::BMP::InvalidFormatException::InvalidFormatException(const char* what_arg)
	: std::logic_error(what_arg)
{}
