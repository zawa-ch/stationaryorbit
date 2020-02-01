#include <random>
#include "stationaryorbit/core/quantumbit.hpp"
using namespace zawa_ch::StationaryOrbit;

QuantumBit::QuantumBit()
	: val(), rot(Rotation(45, RotationUnit::Degree))
{}

QuantumBit::QuantumBit(const Rotation& rotation)
	: val(), rot(rotation)
{}

QuantumBit& QuantumBit::Observe()
{
	if (IsObserved()) { return *this; }
	std::mt19937_64 generator = std::mt19937_64();
	double propability = rot.Cos();
	propability *= propability;
	if (propability < std::generate_canonical<double, 64, std::mt19937_64>(generator)) { val = true; }
	else { val = false; }
	return *this;
}

bool QuantumBit::IsObserved() const
{
	return val.HasValue();
}

bool QuantumBit::getBool() const
{
	if (IsObserved()) { return val.getBoolean(); }
	else { throw InvalidOperationException("This object not observed"); }
}

//QuantumBit QuantumBit::operator~() const
//{}

//QuantumBit QuantumBit::operator|(QuantumBit& value) const
//{}

//QuantumBit QuantumBit::operator&(QuantumBit& value) const
//{}

//QuantumBit QuantumBit::operator^(QuantumBit& value) const
//{}
