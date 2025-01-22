/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

#include "Math.hpp"

namespace Raycaster
{
    const float Math::PI = 3.1415926535;
    const float Math::DEGREE_TO_RADIEN = 0.0174533;

    float Math::distance(const gd::Vector<float> &point1, const gd::Vector<float> &point2)
    {
        return sqrt((point2.x - point1.x) * (point2.x - point1.x) + (point2.y - point1.y) * (point2.y - point1.y));
    }
} // namespace Raycaster
