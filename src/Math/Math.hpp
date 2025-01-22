/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

#ifndef RAYCASTER_MATH_HPP_
#define RAYCASTER_MATH_HPP_

/*  ---- INCLUDES ---- */
#include <cmath>
#include "GradeDe/Vector.hpp"

/*  ---- CLASS ---- */
namespace Raycaster
{
    class Math
    {
        public:
            static float distance(const gd::Vector<float> &point1, const gd::Vector<float> &point2);

            static const float PI;
            static const float DEGREE_TO_RADIEN;

        private:
    };
} // namespace Raycaster

#endif /* !RAYCASTER_MATH_HPP_ */
