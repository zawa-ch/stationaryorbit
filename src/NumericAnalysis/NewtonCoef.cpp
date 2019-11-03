#include "NumericAnalysis/Structure/CompensatedFloat.hpp"
#include "NumericAnalysis/Logic/NewtonCoef.hpp"

void StationaryOrbit::NumericAnalysis::NewtonCoef::Complete()
{
    if (x.size() != b.size()) throw InvalidOperationException("illegal-state");
    for (size_t i = 0; i < b.size()-1; i++)
    {
        b.back() = (b.back() - b[i])/(x.back() - x[i]);
    }
}

StationaryOrbit::NumericAnalysis::NewtonCoef::NewtonCoef(const std::vector<Vector2d>& list)
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

StationaryOrbit::NumericAnalysis::NewtonCoef::NewtonCoef(const IMathmaticFunction<double>& func, const std::vector<double> xlist)
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

double StationaryOrbit::NumericAnalysis::NewtonCoef::Calc(const double& value) const
{
    CompensatedDouble result = CompensatedDouble(b.back());
    for (size_t i = b.size() - 1; 0 < i; i--)
    {
        result = result * (value - x[i-1]) + b[i-1];
    }
    return double(result);
}
