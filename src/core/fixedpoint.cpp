#include "stationaryorbit/core/fixedpoint.hpp"
using namespace zawa_ch::StationaryOrbit;

template class FixedPoint<uint8_t, 7>;
template class FixedPoint<uint16_t, 8>;
template class FixedPoint<uint16_t, 15>;
template class FixedPoint<uint32_t, 16>;
template class FixedPoint<uint32_t, 31>;
template class FixedPoint<uint64_t, 32>;
template class FixedPoint<uint64_t, 63>;
