#include "General/Logic/InvalidOperationException.hpp"

StationaryOrbit::InvalidOperationException::InvalidOperationException(const std::string& what_arg) noexcept
	: std::logic_error(what_arg)
{}

StationaryOrbit::InvalidOperationException::InvalidOperationException(const char* what_arg) noexcept
	: std::logic_error(what_arg)
{}
