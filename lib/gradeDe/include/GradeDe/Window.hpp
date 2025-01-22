/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

#ifndef GRADE_DE_WINDOW_SFML_HPP_
#define GRADE_DE_WINDOW_SFML_HPP_

/*  ---- INCLUDES ---- */
#include <SFML/Graphics.hpp>
#include <string>
#include "GradeDe/Color.hpp"
#include "GradeDe/PrimitiveType.hpp"
#include "GradeDe/RectangleShape.hpp"
#include "GradeDe/CircleShape.hpp"
#include "GradeDe/Shape.hpp"
#include "GradeDe/Text.hpp"
#include "GradeDe/Vector.hpp"
#include "GradeDe/VertexArray.hpp"

/*  ---- CLASS ---- */
namespace gd
{
    class Event;

    class Window
    {
        public:
            Window() = default;
            ~Window();

            void create();
            void create(int width, int height);
            void create(int width, int height, const std::string &title);
            void close();
            bool isOpen() const;
            void setWidth(int width);
            void setHeight(int height);
            void setDimensions(int width, int height);
            void setDimensions(const gd::Vector<int> &dimensions);
            void setTitle(const std::string &title);
            void setFullscreen(bool fullscreen);
            void setFramerateLimit(int limit);
            void setPosition(const gd::Vector<int> &position);
            void setView(const gd::Vector<float> &center, const gd::Vector<float> &size);
            bool isFullscreen() const;
            void pollEvent(gd::Event &event);
            void clear(gd::Color color = gd::Color::Black);
            void display();
            void draw(gd::Shape &shape);
            void draw(gd::RectangleShape &rectangleShape);
            void draw(gd::CircleShape &circleShape);
            void draw(std::vector<gd::Vertex> &vertices, gd::PrimitiveType primitiveType);
            void draw(gd::VertexArray &vertexArray);
            void draw(gd::Text &text);
            int getWidth() const;
            int getHeight() const;
            gd::Vector<int> getDimensions() const;
            std::string getTitle() const;
            static gd::Vector<unsigned int> getDesktopSize();
            void *getWindow();

        private:
            sf::RenderWindow _window;
            sf::VideoMode _videoMode;
            sf::VideoMode _fullScreenVideoMode;
            std::string _title;
            bool _isOpen = false;
            bool _fullscreen = false;
            void _create(sf::VideoMode &videoMode, const std::string &title, sf::Uint32 style);
    };
} // namespace gd

#endif /* !GRADE_DE_WINDOW_SFML_HPP_ */
