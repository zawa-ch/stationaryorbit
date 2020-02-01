#include "stationaryorbit/exception/nullreference.hpp"
using namespace zawa_ch::StationaryOrbit;

NullReferenceException::NullReferenceException(const std::string& what_arg) noexcept
	: std::logic_error(what_arg)
{}

NullReferenceException::NullReferenceException(const char* what_arg) noexcept
	: std::logic_error(what_arg)
{}
