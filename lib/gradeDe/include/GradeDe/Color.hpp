/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

#ifndef GRADE_DE_COLOR_SFML_HPP_
#define GRADE_DE_COLOR_SFML_HPP_

/*  ---- INCLUDES ---- */
#include <iomanip>
#include <sstream>
#include <string>

/*  ---- CLASS ---- */
namespace gd
{
    class Color
    {
        public:
            Color(int r = 0, int g = 0, int b = 0, int a = 255);
            ~Color() = default;

            int r;
            int g;
            int b;
            int a;

            static const gd::Color Black;
            static const gd::Color White;
            static const gd::Color Red;
            static const gd::Color Green;
            static const gd::Color Blue;
            static const gd::Color Yellow;
            static const gd::Color Magenta;
            static const gd::Color Cyan;
            static const gd::Color Transparent;

            static const gd::Color fromHex(std::string hex);
            static const std::string toHex(const gd::Color &color);

            bool operator!=(const gd::Color &color) const;
            bool operator==(const gd::Color &color) const;
    };
} // namespace gd

#endif /* !GRADE_DE_COLOR_SFML_HPP_ */
