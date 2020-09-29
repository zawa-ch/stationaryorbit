#include "stationaryorbit/core/fixedpoint.hpp"
using namespace zawa_ch::StationaryOrbit;

template class zawa_ch::StationaryOrbit::FixedPoint<uint8_t, 7>;
template class zawa_ch::StationaryOrbit::FixedPoint<uint16_t, 8>;
template class zawa_ch::StationaryOrbit::FixedPoint<uint16_t, 15>;
template class zawa_ch::StationaryOrbit::FixedPoint<uint32_t, 16>;
template class zawa_ch::StationaryOrbit::FixedPoint<uint32_t, 31>;
template class zawa_ch::StationaryOrbit::FixedPoint<uint64_t, 32>;
template class zawa_ch::StationaryOrbit::FixedPoint<uint64_t, 63>;
