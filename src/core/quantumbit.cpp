#include <random>
#include "General/Structure/QuantumBit.hpp"

StationaryOrbit::QuantumBit::QuantumBit()
	: val(), rot(Rotation(45, RotationUnit::Degree))
{}

StationaryOrbit::QuantumBit::QuantumBit(const Rotation& rotation)
	: val(), rot(rotation)
{}

StationaryOrbit::QuantumBit& StationaryOrbit::QuantumBit::Observe()
{
	if (IsObserved()) { return *this; }
	std::mt19937_64 generator = std::mt19937_64();
	double propability = rot.Cos();
	propability *= propability;
	if (propability < std::generate_canonical<double, 64, std::mt19937_64>(generator)) { val = true; }
	else { val = false; }
	return *this;
}

bool StationaryOrbit::QuantumBit::IsObserved() const
{
	return val.HasValue();
}

bool StationaryOrbit::QuantumBit::getBool() const
{
	if (IsObserved()) { return val.getBoolean(); }
	else { throw InvalidOperationException("This object not observed"); }
}

//StationaryOrbit::QuantumBit StationaryOrbit::QuantumBit::operator~() const
//{}

//StationaryOrbit::QuantumBit StationaryOrbit::QuantumBit::operator|(QuantumBit& value) const
//{}

//StationaryOrbit::QuantumBit StationaryOrbit::QuantumBit::operator&(QuantumBit& value) const
//{}

//StationaryOrbit::QuantumBit StationaryOrbit::QuantumBit::operator^(QuantumBit& value) const
//{}
