#include "stationaryorbit/exception/invalidoperation.hpp"
using namespace zawa_ch::StationaryOrbit;

InvalidOperationException::InvalidOperationException(const std::string& what_arg) noexcept
	: std::logic_error(what_arg)
{}

InvalidOperationException::InvalidOperationException(const char* what_arg) noexcept
	: std::logic_error(what_arg)
{}
