#include "stationaryorbit/analysis/compensatedfloat.hpp"
#include "stationaryorbit/analysis/newtoncoef.hpp"
using namespace zawa_ch::StationaryOrbit;

void Analysis::NewtonCoef::Complete()
{
    if (x.size() != b.size()) throw InvalidOperationException("illegal-state");
    for (size_t i = 0; i < b.size()-1; i++)
    {
        b.back() = (b.back() - b[i])/(x.back() - x[i]);
    }
}

Analysis::NewtonCoef::NewtonCoef(const std::vector<Vector2d>& list)
    : x(), b()
{
    x.reserve(list.size());
    b.reserve(list.size());
    for (const Vector2d& pt : list)
    {
        x.push_back(pt.getX());
        b.push_back(pt.getY());
        Complete();
    }
}

Analysis::NewtonCoef::NewtonCoef(const IMathematicFunction<double>& func, const std::vector<double> xlist)
    : x(), b()
{
    x.reserve(xlist.size());
    b.reserve(xlist.size());
    for (const double& ptx : xlist)
    {
        x.push_back(ptx);
        b.push_back(func.Calc(ptx));
        Complete();
    }
}

double Analysis::NewtonCoef::Calc(const double& value) const
{
    CompensatedDouble result = CompensatedDouble(b.back());
    for (size_t i = b.size() - 1; 0 < i; i--)
    {
        result = result * (value - x[i-1]) + b[i-1];
    }
    return double(result);
}
