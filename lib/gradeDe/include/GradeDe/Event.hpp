/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

#ifndef GRADE_DE_EVENT_SFML_HPP_
#define GRADE_DE_EVENT_SFML_HPP_

/*  ---- INCLUDES ---- */
#include <SFML/Window/Event.hpp>
#include <vector>
#include "GradeDe/JoyStick.hpp"
#include "GradeDe/KeyBoard.hpp"
#include "GradeDe/Mouse.hpp"

/*  ---- CLASS ---- */
namespace gd
{
    class Event
    {
        public:
            Event();
            ~Event() = default;
            void handleEvent(void *event);
            bool close() const;

            gd::JoyStick joyStick = gd::JoyStick(0);
            gd::KeyBoard keyBoard;
            gd::Mouse mouse;

        private:
            sf::Event _event;
            bool _close = false;
    };
} // namespace gd

#endif /* !GRADE_DE_EVENT_SFML_HPP_ */
