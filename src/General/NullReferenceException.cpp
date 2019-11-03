#include "General/Logic/NullReferenceException.hpp"

StationaryOrbit::NullReferenceException::NullReferenceException(const std::string& what_arg)
	: std::logic_error(what_arg)
{}

StationaryOrbit::NullReferenceException::NullReferenceException(const char* what_arg)
	: std::logic_error(what_arg)
{}
