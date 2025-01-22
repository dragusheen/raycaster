/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

#ifndef GRADE_DE_KEYBOARD_SFML_HPP_
#define GRADE_DE_KEYBOARD_SFML_HPP_

/*  ---- INCLUDES ---- */
#include <tuple>
#include <unordered_map>
#include "GradeDe/Time.hpp"

/*  ---- CLASS ---- */
namespace gd
{
    class KeyBoard
    {
        public:
            enum Key {
                Unknown = -1,
                A = 0,
                B,
                C,
                D,
                E,
                F,
                G,
                H,
                I,
                J,
                K,
                L,
                M,
                N,
                O,
                P,
                Q,
                R,
                S,
                T,
                U,
                V,
                W,
                X,
                Y,
                Z,
                Num0,
                Num1,
                Num2,
                Num3,
                Num4,
                Num5,
                Num6,
                Num7,
                Num8,
                Num9,
                Escape,
                LControl,
                LShift,
                LAlt,
                LSystem,
                RControl,
                RShift,
                RAlt,
                RSystem,
                Menu,
                LBracket,
                RBracket,
                Semicolon,
                Comma,
                Period,
                Apostrophe,
                Slash,
                Backslash,
                Grave,
                Equal,
                Hyphen,
                Space,
                Enter,
                Backspace,
                Tab,
                PageUp,
                PageDown,
                End,
                Home,
                Insert,
                Delete,
                Add,
                Subtract,
                Multiply,
                Divide,
                Left,
                Right,
                Up,
                Down,
                Numpad0,
                Numpad1,
                Numpad2,
                Numpad3,
                Numpad4,
                Numpad5,
                Numpad6,
                Numpad7,
                Numpad8,
                Numpad9,
                F1,
                F2,
                F3,
                F4,
                F5,
                F6,
                F7,
                F8,
                F9,
                F10,
                F11,
                F12,
                F13,
                F14,
                F15,
                Pause,
                KeyCount,

                Tilde = Grave,
                Dash = Hyphen,
                BackSpace = Backspace,
                BackSlash = Backslash,
                SemiColon = Semicolon,
                Return = Enter,
                Quote = Apostrophe
            };

            enum State {
                Pressed,
                Released,
                None,
            };

            KeyBoard();
            ~KeyBoard() = default;

            void setKeyState(Key key, State state);
            State getKeyState(Key key);

        private:
            std::unordered_map<Key, std::tuple<State, gd::Time>> _keys;
    };
} // namespace gd

#endif /* !GRADE_DE_KEYBOARD_SFML_HPP_ */
