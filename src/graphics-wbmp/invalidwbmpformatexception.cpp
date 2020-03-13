#include "stationaryorbit/graphics-wbmp/invalidwbmpformatexception.hpp"
using namespace zawa_ch::StationaryOrbit;

Graphics::WBMP::InvalidWbmpFormatException::InvalidWbmpFormatException(const std::string& what_arg)
	: InvalidOperationException(what_arg)
{}

Graphics::WBMP::InvalidWbmpFormatException::InvalidWbmpFormatException(const char* what_arg)
	: InvalidOperationException(what_arg)
{}
