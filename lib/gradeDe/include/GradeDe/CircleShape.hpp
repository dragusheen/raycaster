/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

#ifndef GRADE_DE_CIRCLE_SHAPE_CIRCLE_SFML_HPP_
#define GRADE_DE_CIRCLE_SHAPE_CIRCLE_SFML_HPP_

/*  ---- INCLUDES ---- */
#include <SFML/Graphics.hpp>
#include <vector>
#include "GradeDe/Color.hpp"
#include "GradeDe/Texture.hpp"
#include "GradeDe/Vector.hpp"

/*  ---- CLASS ---- */
namespace gd
{
    class CircleShape
    {
        public:
            CircleShape() = default;
            ~CircleShape() = default;

            void create(float radius);
            void setFillColor(gd::Color color);
            void setOutlineColor(gd::Color color);
            void setOutlineThickness(float thickness);
            void setPosition(gd::Vector<float> position);
            void setTexture(gd::Texture &texture);
            void setOrigin(gd::Vector<float> origin);
            void setRotation(float angle);
            void setRadius(float radius);
            void move(gd::Vector<float> offset);
            void rotate(float angle);
            gd::Color getFillColor() const;
            gd::Color getOutlineColor() const;
            float getOutlineThickness() const;
            gd::Vector<float> getPosition() const;
            float getRotation() const;
            float getRadius() const;
            void *getShape();

        private:
            float _radius = 0;
            gd::Color _fillColor = gd::Color::White;
            gd::Color _outlineColor = gd::Color::Transparent;
            float _outlineThickness = 0;
            gd::Vector<float> _position = {0, 0};
            gd::Vector<float> _origin = {0, 0};
            float _rotation = 0;
            sf::CircleShape _shape;
    };
} // namespace gd

#endif /* !GRADE_DE_CIRCLE_SHAPE_CIRCLE_SFML_HPP_ */
