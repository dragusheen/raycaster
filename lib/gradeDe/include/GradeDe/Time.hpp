/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

#ifndef GRADE_DE_TIME_SFML_HPP_
#define GRADE_DE_TIME_SFML_HPP_

/*  ---- INCLUDES ---- */
#include <SFML/System.hpp>

/*  ---- CLASS ---- */
namespace gd
{
    class Time
    {
        public:
            Time();
            ~Time() = default;
            void reset();
            int getElapsedTime();

        private:
            sf::Clock _clock;
            sf::Time _time;
    };
} // namespace gd

#endif /* !GRADE_DE_TIME_SFML_HPP_ */
