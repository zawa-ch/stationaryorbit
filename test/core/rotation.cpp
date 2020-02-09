#include <iostream>
#include <cmath>
#include "stationaryorbit/core/numeral"
using namespace zawa_ch::StationaryOrbit;

int Test_Rotation()
{
    Rotation rot1 = Rotation(30, RotationUnit::Degree);
    Rotation rot2 = Rotation(0.5 * M_PI, RotationUnit::Radian);
    Rotation rot3 = Rotation(60, RotationUnit::Degree);

    std::cout << "rot1 = " << rot1.getRadian() << "rad" << std::endl;
    std::cout << "rot2 = " << rot2.getDegree() << "deg" << std::endl;
    std::cout << "rot1 + rot2 = " << (rot1 + rot2).getDegree() << "deg" << std::endl;
    std::cout << "rot1 - rot2 = " << (rot1 - rot2).getDegree() << "deg" << std::endl;
    std::cout << "rot2 * 2.0 = " << (rot2 * 2.0).getDegree() << "deg" << std::endl;
    std::cout << "rot1 / 2.0 = " << (rot1 * 2.0).getDegree() << "deg" << std::endl;

    return 0;
}