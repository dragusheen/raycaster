/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

#ifndef GRADE_DE_JOYSTICK_SFML_HPP_
#define GRADE_DE_JOYSTICK_SFML_HPP_

/*  ---- INCLUDES ---- */
#include <SFML/Window/Joystick.hpp>
#include <tuple>
#include <unordered_map>
#include <vector>
#include "GradeDe/Time.hpp"

/*  ---- CLASS ---- */
namespace gd
{
    class JoyStick
    {
        public:
            enum Button {
                A = 0,
                B,
                X,
                Y,
                LB,
                RB,
                Select,
                Menu,
                Home,
                ButtonCount,
            };

            enum Axis {
                LeftJoyStickX = 0,
                LX = LeftJoyStickX,
                LeftJoyStickY,
                LY = LeftJoyStickY,
                LeftTrigger,
                LT = LeftTrigger,
                RightTrigger,
                RT = RightTrigger,
                RightJoyStickX,
                RX = RightJoyStickX,
                RightJoyStickY,
                RY = RightJoyStickY,
                CrossX,
                CX = CrossX,
                CrossY,
                CY = CrossY,
                AxisCount,
            };

            enum State {
                Pressed,
                Released,
                None,
            };

            JoyStick(unsigned int id);
            ~JoyStick() = default;

            void setConnected(bool connected);
            void setButtonState(Button button, State pressed);
            void setAxisMoved(Axis axis, float position);
            bool isConnected() const;
            State getButtonState(Button button);
            bool isJoyStickMoved() const;
            bool isJoyStickMoved(Axis axis) const;
            float getAxisPosition(Axis axis) const;
            float getXAxisPosition(bool highest) const;
            float getYAxisPosition(bool highest) const;

        private:
            std::unordered_map<Button, std::tuple<State, gd::Time>> _buttons;
            std::unordered_map<Axis, float> _axis;
            bool _isConnected;
            std::vector<Axis> _axisX;
            std::vector<Axis> _axisY;
    };
} // namespace gd

#endif /* !GRADE_DE_JOYSTICK_SFML_HPP_ */
