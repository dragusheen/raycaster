/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

#ifndef GRADE_DE_MOUSE_SFML_HPP_
#define GRADE_DE_MOUSE_SFML_HPP_

/*  ---- INCLUDES ---- */
#include <tuple>
#include <unordered_map>
#include "GradeDe/Time.hpp"
#include "GradeDe/Vector.hpp"
#include "GradeDe/Window.hpp"

/*  ---- CLASS ---- */
namespace gd
{
    class Mouse
    {
        public:
            enum Button {
                Left = 0,
                Right,
                Middle,
                XButton1,
                XButton2,
                ButtonCount
            };

            enum State {
                Pressed,
                Released,
                None,
            };

            Mouse();
            ~Mouse() = default;

            void setButtonState(Button button, State state);
            State getButtonState(Button button);
            gd::Vector<float> getPosition(gd::Window &window);
            bool hasMove(gd::Window &window);

        private:
            std::unordered_map<Button, std::tuple<State, gd::Time>> _buttons;
            gd::Vector<float> _position = {0, 0};
    };
} // namespace gd

#endif /* !GRADE_DE_MOUSE_SFML_HPP_ */
