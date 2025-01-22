/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/*  ---- INCLUDES ---- */
#include "GradeDe/CircleShape.hpp"

namespace gd
{
    CircleShape::CircleShape(float radius)
    {
        _radius = radius;
        _shape.setRadius(radius);
    }

    void CircleShape::setFillColor(gd::Color color)
    {
        _fillColor = color;
        _shape.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
    }

    void CircleShape::setOutlineColor(gd::Color color)
    {
        _outlineColor = color;
        _shape.setOutlineColor(sf::Color(color.r, color.g, color.b, color.a));
    }

    void CircleShape::setOutlineThickness(float thickness)
    {
        _outlineThickness = thickness;
        _shape.setOutlineThickness(thickness);
    }

    void CircleShape::setPosition(gd::Vector<float> position)
    {
        _position = position;
        _shape.setPosition(position.x, position.y);
    }

    void CircleShape::setOrigin(gd::Vector<float> origin)
    {
        _origin = origin;
        _shape.setOrigin(origin.x, origin.y);
    }

    void CircleShape::setRotation(float angle)
    {
        _rotation = angle;
        _shape.setRotation(angle);
    }

    void CircleShape::setTexture(gd::Texture &texture)
    {
        _shape.setTexture((sf::Texture *)texture.getTexture());
    }

    void CircleShape::setRadius(float radius)
    {
        _radius = radius;
        _shape.setRadius(radius);
    }

    void CircleShape::move(gd::Vector<float> offset)
    {
        _position += offset;
        _shape.move(offset.x, offset.y);
    }

    void CircleShape::rotate(float angle)
    {
        _rotation += angle;
        _shape.setRotation(_rotation);
    }

    gd::Color CircleShape::getFillColor() const
    {
        return _fillColor;
    }

    gd::Color CircleShape::getOutlineColor() const
    {
        return _outlineColor;
    }

    float CircleShape::getOutlineThickness() const
    {
        return _outlineThickness;
    }

    gd::Vector<float> CircleShape::getPosition() const
    {
        return _position;
    }

    float CircleShape::getRadius() const
    {
        return _radius;
    }

    float CircleShape::getRotation() const
    {
        return _rotation;
    }

    void *CircleShape::getShape()
    {
        return &_shape;
    }
} // namespace gd
