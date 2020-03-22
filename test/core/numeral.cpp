#include <iostream>
#include <stdexcept>
#include "stationaryorbit/core/numeral"
using namespace zawa_ch::StationaryOrbit;

void Test_Point()
{
    auto p1 = Point<>(3, 4);
    auto p2 = Point<>(2, 8);
    if ((p1 + p2) != Point<>(5, 12)) { throw std::exception(); }
    std::cout << "p1 + p2 = (" << (p1 + p2).X() << ", " << (p1 + p2).Y() << ")" << std::endl;
    if ((p1 - p2) != Point<>(1, -4)) { throw std::exception(); }
    std::cout << "p1 - p2 = (" << (p1 - p2).X() << ", " << (p1 - p2).Y() << ")" << std::endl;
    auto p3 = Point<Quadrants::DownRight>(p1);
    if (p3 != Point<Quadrants::DownRight>(3, -4)) { throw std::exception(); }
    auto fp1 = GeometricPointF(0.3, 1.8);
    auto fp2 = GeometricPointF(-3.1, 2.0);
    std::cout << "fp1 + fp2 = (" << (fp1 + fp2).X() << ", " << (fp1 + fp2).Y() << ")" << std::endl;
    std::cout << "fp1 - fp2 = (" << (fp1 - fp2).X() << ", " << (fp1 - fp2).Y() << ")" << std::endl;
    auto p4 = fp1.Round();
    std::cout << "p4 = (" << p4.X() << ", " << p4.Y() << ")" << std::endl;
}
