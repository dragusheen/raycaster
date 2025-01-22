/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/*  ---- INCLUDES ---- */
#include "GradeDe/Window.hpp"
#include "GradeDe/Event.hpp"

namespace gd
{
    Window::~Window()
    {
        close();
    }

    void Window::create()
    {
        _videoMode = sf::VideoMode::getDesktopMode();
        _fullScreenVideoMode = sf::VideoMode(sf::VideoMode::getDesktopMode());
        _title = "GradeDe";
        _create(_fullScreenVideoMode, _title, sf::Style::Fullscreen);
    }

    void Window::create(int width, int height)
    {
        _videoMode = sf::VideoMode(width, height);
        _fullScreenVideoMode = sf::VideoMode(sf::VideoMode::getDesktopMode());
        _title = "GradeDe";
        _create(_videoMode, _title, sf::Style::Close | sf::Style::Titlebar);
    }

    void Window::create(int width, int height, const std::string &title)
    {
        _videoMode = sf::VideoMode(width, height);
        _fullScreenVideoMode = sf::VideoMode(sf::VideoMode::getDesktopMode());
        _title = title;
        _create(_videoMode, _title, sf::Style::Close | sf::Style::Titlebar);
    }

    void Window::close()
    {
        if (!_isOpen) return;
        _window.close();
        _isOpen = false;
    }

    bool Window::isOpen() const
    {
        return _isOpen;
    }

    void Window::setWidth(int width)
    {
        close();
        create(width, _videoMode.height, _title);
    }

    void Window::setHeight(int height)
    {
        close();
        create(_videoMode.width, height, _title);
    }

    void Window::setDimensions(int width, int height)
    {
        close();
        create(width, height, _title);
    }

    void Window::setDimensions(const gd::Vector<int> &dimensions)
    {
        close();
        create(dimensions.x, dimensions.y, _title);
    }

    void Window::setTitle(const std::string &title)
    {
        _window.setTitle(title);
    }

    void Window::setFullscreen(bool fullscreen)
    {
        close();
        if (fullscreen) {
            _create(_fullScreenVideoMode, _title, sf::Style::Fullscreen);
        } else {
            _create(_videoMode, _title, sf::Style::Close | sf::Style::Titlebar);
        }
        _fullscreen = fullscreen;
    }

    void Window::setFramerateLimit(int limit)
    {
        _window.setFramerateLimit(limit);
    }

    void Window::setPosition(const gd::Vector<int> &position)
    {
        _window.setPosition(sf::Vector2i(position.x, position.y));
    }

    void Window::setView(const gd::Vector<float> &center, const gd::Vector<float> &size)
    {
        _window.setView(sf::View(sf::Vector2f(center.x, center.y), sf::Vector2f(size.x, size.y)));
    }

    bool Window::isFullscreen() const
    {
        return _fullscreen;
    }

    void Window::pollEvent(gd::Event &event)
    {
        sf::Event sfEvent;
        while (_window.pollEvent(sfEvent))
            event.handleEvent((void *)&sfEvent);
    }

    void Window::clear(gd::Color color)
    {
        _window.clear(sf::Color(color.r, color.g, color.b, color.a));
    }

    void Window::display()
    {
        _window.display();
    }

    void Window::draw(gd::Shape &shape)
    {
        sf::ConvexShape *sh = (sf::ConvexShape *)shape.getShape();
        _window.draw(*sh);
    }

    void Window::draw(gd::CircleShape &shape)
    {
        sf::CircleShape *sh = (sf::CircleShape *)shape.getShape();
        _window.draw(*sh);
    }

    void Window::draw(gd::RectangleShape &shape)
    {
        sf::RectangleShape *sh = (sf::RectangleShape *)shape.getShape();
        _window.draw(*sh);
    }

    void Window::draw(std::vector<gd::Vertex> &vertices, gd::PrimitiveType primitiveType)
    {
        sf::VertexArray va;
        va.setPrimitiveType((sf::PrimitiveType)primitiveType);
        for (auto &vertex : vertices)
            va.append(*(sf::Vertex *)vertex.getVertex());
        _window.draw(va);
    }

    void Window::draw(gd::VertexArray &vertexArray)
    {
        sf::VertexArray *va = (sf::VertexArray *)vertexArray.getVertexArray();
        _window.draw(*va);
    }

    void Window::draw(gd::Text &text)
    {
        sf::Text *t = (sf::Text *)text.getText();
        _window.draw(*t);
    }

    void Window::_create(sf::VideoMode &videoMode, const std::string &title, sf::Uint32 style)
    {
        _window.create(videoMode, title, style);
        _isOpen = true;
    }

    int Window::getWidth() const
    {
        return _fullscreen ? (int)_fullScreenVideoMode.width : (int)_videoMode.width;
    }

    int Window::getHeight() const
    {
        return _fullscreen ? (int)_fullScreenVideoMode.height : (int)_videoMode.height;
    }

    gd::Vector<int> Window::getDimensions() const
    {
        return {getWidth(), getHeight()};
    }

    std::string Window::getTitle() const
    {
        return _title;
    }

    gd::Vector<unsigned int> Window::getDesktopSize()
    {
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        return gd::Vector<unsigned int>(desktop.width, desktop.height);
    }

    void *Window::getWindow()
    {
        return &_window;
    }
} // namespace gd
