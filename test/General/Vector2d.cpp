#include <iostream>
#include <cmath>
#include "General/Vector2d"
using namespace StationaryOrbit;

int Test_Vector2d()
{
    Vector2d vec1 = Vector2d(3, 4);
    Vector2d vec2 = Vector2d(10, Rotation(-30, RotationUnit::Degree));

    std::cout << "vec1 = (" << vec1.getMagnitude() << "∠" << vec1.getRotation().getDegree() << "deg)" << std::endl;
    std::cout << "vec2 = (" << vec2.getX() << ", " << vec2.getY() << ")" << std::endl;
    std::cout << "vec1 + vec2 = (" << (vec1 + vec2).getX() << ", " << (vec1 + vec2).getY() << ")" << std::endl;
    std::cout << "vec1 - vec2 = (" << (vec1 - vec2).getX() << ", " << (vec1 - vec2).getY() << ")" << std::endl;
    std::cout << "vec1 ・ vec2 = " << Vector2d::DotProduct(vec1, vec2) << std::endl;

    if (vec1 < vec2)
    {
        std::cout << "vec1 < vec2" << std::endl;
    }
    else
    {
        return -1;
    }
    

    return 0;
}
