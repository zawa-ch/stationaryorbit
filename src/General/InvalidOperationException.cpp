#include "LogicClass/InvalidOperationException.hpp"

StationaryOrbit::InvalidOperationException::InvalidOperationException(const std::string& what_arg)
	: std::logic_error(what_arg)
{}

StationaryOrbit::InvalidOperationException::InvalidOperationException(const char* what_arg)
	: std::logic_error(what_arg)
{}
