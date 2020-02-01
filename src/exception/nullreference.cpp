#include "General/Logic/NullReferenceException.hpp"

StationaryOrbit::NullReferenceException::NullReferenceException(const std::string& what_arg) noexcept
	: std::logic_error(what_arg)
{}

StationaryOrbit::NullReferenceException::NullReferenceException(const char* what_arg) noexcept
	: std::logic_error(what_arg)
{}
