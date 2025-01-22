/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/*  ---- INCLUDES ---- */
#include <cmath>
#include <iostream>
#include "GradeDe/Vector.hpp"
#include "GradeDe/CircleShape.hpp"
#include "GradeDe/RectangleShape.hpp"
#include "GradeDe/VertexArray.hpp"
#include "GradeDe/Window.hpp"
#include "GradeDe/Event.hpp"
#include "Math/Math.hpp"

/*  ---- VARIABLES ---- */
namespace Window {
    gd::Vector<float> size = gd::Vector<float>(0, 0);
}

namespace Player {
    float _2D_size = 4;
    float speed = 3;
    gd::Vector<float> position = gd::Vector<float>(0, 0);
    gd::Vector<float> delta = gd::Vector<float>(0, 0);
    float angle = 0;
    float rotation_speed = 0.05;
    int view_angle = 60;
    int view_distance = 200;
    gd::CircleShape shape(_2D_size);
    gd::RectangleShape directionPointer(gd::Vector<float>(_2D_size * 3, 2));
}

namespace Map {
    gd::Vector<float> size = gd::Vector<float>(8, 8);
    float cell_size = 64;
    std::vector<std::vector<int>> map = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };
    std::vector<gd::RectangleShape> map_rectangles;
    std::vector<gd::RectangleShape> map_grid;
    std::vector<gd::RectangleShape> walls;
}

namespace Rays {
    int count = 1920;
    std::vector<gd::VertexArray> rays;
}


/*  ---- FUNCTION ---- */
namespace Player {
    void setPlayerDelta(void)
    {
        delta.x = cos(angle) * speed;
        delta.y = sin(angle) * speed;
    }

    void initPlayer(void)
    {
        shape.setOrigin(gd::Vector<float>(_2D_size, _2D_size));
        shape.setFillColor(gd::Color::Yellow);

        position = gd::Vector<float>(Map::cell_size * Map::size.x / 2, Map::cell_size * Map::size.y / 2);
        shape.setPosition(position);

        Player::directionPointer.setOrigin(gd::Vector<float>(0, 1));
        directionPointer.setFillColor(gd::Color::Yellow);
        directionPointer.setPosition(position);
        directionPointer.setRotation(angle * 180 / Raycaster::Math::PI);
        setPlayerDelta();
    }

    void drawPlayer(gd::Window &window)
    {
        window.draw(shape);
        window.draw(directionPointer);
    }

    void movePlayerForward(void)
    {
        gd::Vector<float> new_position = gd::Vector<float>(position.x + delta.x, position.y + delta.y);
        if (Map::map[(int)(new_position.y / Map::cell_size)][(int)(new_position.x / Map::cell_size)] == 1) return;
        position = new_position;
    }

    void movePlayerBackward(void)
    {
        gd::Vector<float> new_position = gd::Vector<float>(position.x - delta.x, position.y - delta.y);
        if (Map::map[(int)(new_position.y / Map::cell_size)][(int)(new_position.x / Map::cell_size)] == 1) return;
        position = new_position;
    }

    void movePlayerLeft(void)
    {
        angle -= rotation_speed;
        if (angle < 0)
            angle += 2 * Raycaster::Math::PI;
        setPlayerDelta();
    }

    void movePlayerRight(void)
    {
        angle += rotation_speed;
        if (angle > 2 * Raycaster::Math::PI)
            angle -= 2 * Raycaster::Math::PI;
        setPlayerDelta();
    }

    void movePlayer(gd::Event event)
    {
        if (event.keyBoard.getKeyState(gd::KeyBoard::Key::Q) == gd::KeyBoard::State::Pressed || event.keyBoard.getKeyState(gd::KeyBoard::Key::Left) == gd::KeyBoard::State::Pressed) movePlayerLeft();
        if (event.keyBoard.getKeyState(gd::KeyBoard::Key::D) == gd::KeyBoard::State::Pressed || event.keyBoard.getKeyState(gd::KeyBoard::Key::Right) == gd::KeyBoard::State::Pressed) movePlayerRight();
        if (event.keyBoard.getKeyState(gd::KeyBoard::Key::Z) == gd::KeyBoard::State::Pressed || event.keyBoard.getKeyState(gd::KeyBoard::Key::Up) == gd::KeyBoard::State::Pressed) movePlayerForward();
        if (event.keyBoard.getKeyState(gd::KeyBoard::Key::S) == gd::KeyBoard::State::Pressed || event.keyBoard.getKeyState(gd::KeyBoard::Key::Down) == gd::KeyBoard::State::Pressed) movePlayerBackward();
        if (event.joyStick.isConnected()) {
            if (event.joyStick.getXAxisPosition(true) > 50) movePlayerRight();
            if (event.joyStick.getXAxisPosition(false) < -50) movePlayerLeft();
            if (event.joyStick.getYAxisPosition(true) > 50) movePlayerBackward();
            if (event.joyStick.getYAxisPosition(false) < -50) movePlayerForward();
        }
    }

    void updatePlayer(void)
    {
        shape.setPosition(position);
        directionPointer.setPosition(position);
        directionPointer.setRotation(angle * 180 / Raycaster::Math::PI);
    }
}

namespace Map {
    void initMap(void)
    {
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map[i].size(); j++) {
                if (map[i][j] == 0) continue;
                gd::RectangleShape rectangle(gd::Vector<float>(cell_size, cell_size));
                rectangle.setPosition(gd::Vector<float>(j * cell_size, i * cell_size));
                rectangle.setFillColor(gd::Color::White);
                map_rectangles.push_back(rectangle);
            }
        }

        for (int i = 0; i < (int)Rays::count; i++) {
            gd::RectangleShape rectangle(gd::Vector<float>(Window::size.x / Rays::count, Window::size.y));
            rectangle.setPosition(gd::Vector<float>(i * (Window::size.x / Rays::count), 0));
            rectangle.setFillColor(gd::Color::Transparent);
            walls.push_back(rectangle);
        }

        gd::Color gray(120, 120, 120);
        float gridBarSize = 2;
        for (int i = 0; i < size.y; i++) {
            gd::RectangleShape rectangle(gd::Vector<float>(Window::size.x, gridBarSize));
            rectangle.setPosition(gd::Vector<float>(0, i * cell_size - gridBarSize / 2));
            rectangle.setFillColor(gray);
            map_grid.push_back(rectangle);
        }
        for (int i = 0; i < size.x; i++) {
            gd::RectangleShape rectangle(gd::Vector<float>(gridBarSize, Window::size.y));
            rectangle.setPosition(gd::Vector<float>(i * cell_size - gridBarSize / 2, 0));
            rectangle.setFillColor(gray);
            map_grid.push_back(rectangle);
        }
    }

    void drawMap(gd::Window &window)
    {
        for (auto &rectangle : map_rectangles) window.draw(rectangle);
        for (auto &rectangle : map_grid) window.draw(rectangle);
    }

    void drawWalls(gd::Window &window)
    {
        for (auto &wall : walls) window.draw(wall);
    }
}

namespace Rays {
    void initRays(void)
    {
        rays.clear();
        for (int i = 0; i < count; i++) {
            gd::VertexArray ray(gd::Lines, 2);
            ray[0].position = Player::position;
            ray[1].position = Player::position;
            ray[0].color = gd::Color::Red;
            ray[1].color = gd::Color::Red;
            rays.push_back(ray);
        }
    }

    void updateRays(void)
    {
        int r, mx, my, mp, dof;
        float rx, ry, ra, xo, yo, distT;
        ra = Player::angle - (Player::view_angle / 2) * Raycaster::Math::DEGREE_TO_RADIEN;
        if (ra < 0) ra += 2 * Raycaster::Math::PI;
        if (ra > 2 * Raycaster::Math::PI) ra -= 2 * Raycaster::Math::PI;

        for (int i = 0; i < (int)count; i++) {
            float distH = 100000;
            float hx = Player::position.x;
            float hy = Player::position.y;
            dof = 0;

            float aTan = -1 / tan(ra);
            if (ra > Raycaster::Math::PI) {
                ry = (((int)Player::position.y>>6)<<6) - 0.0001;
                rx = (Player::position.y - ry) * aTan + Player::position.x;
                yo = -Map::cell_size;
                xo = -yo * aTan;
            }
            if (ra < Raycaster::Math::PI) {
                ry = (((int)Player::position.y>>6)<<6) + Map::cell_size;
                rx = (Player::position.y - ry) * aTan + Player::position.x;
                yo = Map::cell_size;
                xo = -yo * aTan;
            }
            if (ra == 0 || ra == Raycaster::Math::PI) {
                rx = Player::position.x;
                ry = Player::position.y;
                dof = 8;
            }
            while (dof < 8) {
                mx = (int)(rx)>>6;
                my = (int)(ry)>>6;
                if (mx < 0 || mx >= Map::size.x || my < 0 || my >= Map::size.y) {
                    dof = 8;
                    break;
                }
                mp = (int)Map::map[my][mx];
                if (mp == 1) {
                    hx = rx;
                    hy = ry;
                    distH = Raycaster::Math::distance(gd::Vector<float>(Player::position.x, Player::position.y), gd::Vector<float>(hx, hy));
                    dof = 8;
                    break;
                } else {
                    rx += xo;
                    ry += yo;
                    dof++;
                }
            }

            float distV = 100000;
            float vx = Player::position.x;
            float vy = Player::position.y;
            dof = 0;
            float nTan = -tan(ra);
            if (ra > Raycaster::Math::PI / 2 && ra < 3 * Raycaster::Math::PI / 2) {
                rx = (((int)Player::position.x>>6)<<6) - 0.0001;
                ry = (Player::position.x - rx) * nTan + Player::position.y;
                xo = -Map::cell_size;
                yo = -xo * nTan;
            }
            if (ra < Raycaster::Math::PI / 2 || ra > 3 * Raycaster::Math::PI / 2) {
                rx = (((int)Player::position.x>>6)<<6) + Map::cell_size;
                ry = (Player::position.x - rx) * nTan + Player::position.y;
                xo = Map::cell_size;
                yo = -xo * nTan;
            }
            if (ra == 0 || ra == Raycaster::Math::PI) {
                rx = Player::position.x;
                ry = Player::position.y;
                dof = 8;
            }
            while (dof < 8) {
                mx = (int)(rx)>>6;
                my = (int)(ry)>>6;
                if (mx < 0 || mx >= Map::size.x || my < 0 || my >= Map::size.y) {
                    dof = 8;
                    break;
                }
                mp = (int)Map::map[my][mx];
                if (mp == 1) {
                    vx = rx;
                    vy = ry;
                    distV = Raycaster::Math::distance(gd::Vector<float>(Player::position.x, Player::position.y), gd::Vector<float>(vx, vy));
                    dof = 8;
                    break;
                } else {
                    rx += xo;
                    ry += yo;
                    dof++;
                }
            }

            gd::Color color = gd::Color::Red;
            if (distH < distV) {
                rx = hx;
                ry = hy;
                distT = distH;
            } else {
                rx = vx;
                ry = vy;
                distT = distV;
                color.r = 200;
            }

            rays[i][0].position = Player::position;
            rays[i][1].position = gd::Vector<float>(rx, ry);

            float ca = Player::angle - ra;
            if (ca < 0) ca += 2 * Raycaster::Math::PI;
            if (ca > 2 * Raycaster::Math::PI) ca -= 2 * Raycaster::Math::PI;
            distT *= cos(ca);
            if (distT > Player::view_distance) color.a = 255 - distT + Player::view_distance;
            if (color.a < 0) color.a = 0;

            float wallH = (Map::cell_size * Window::size.y) / distT;
            wallH = (wallH > Window::size.y) ? Window::size.y : wallH;
            Map::walls[i].setSize(gd::Vector<float>(Window::size.x / count, wallH));
            Map::walls[i].setPosition(gd::Vector<float>(i * (Window::size.x / count), Window::size.y / 2 - wallH / 2));
            Map::walls[i].setFillColor(color);

            ra += (float)((float)(Player::view_angle) / (float)(count)) * Raycaster::Math::DEGREE_TO_RADIEN;
            if (ra < 0) ra += 2 * Raycaster::Math::PI;
            if (ra > 2 * Raycaster::Math::PI) ra -= 2 * Raycaster::Math::PI;
        }
    }

    void drawRays(gd::Window &window)
    {
        for (auto &ray : rays) window.draw(ray);
    }
}

int main(void)
{
    gd::Vector<unsigned int> desktop_size = gd::Window::getDesktopSize();
    Window::size.x = Map::cell_size * Map::size.x;
    Window::size.y = Map::cell_size * Map::size.y;
    gd::Window twoD_window;
    twoD_window.create(Window::size.x, Window::size.y, "2D Raycaster");
    twoD_window.setFramerateLimit(24);
    twoD_window.setPosition(gd::Vector<int>(desktop_size.x / 4 - Window::size.x / 2, desktop_size.y / 2 - Window::size.y / 2));
    Window::size.x = 800;
    Window::size.y = 600;
    gd::Window threeD_window;
    threeD_window.create(Window::size.x, Window::size.y, "3D Raycaster");
    threeD_window.setFramerateLimit(24);
    threeD_window.setPosition(gd::Vector<int>(desktop_size.x / 4 * 3 - Window::size.x / 2, desktop_size.y / 2 - Window::size.y / 2));
    gd::Event event;

    Player::initPlayer();
    Map::initMap();
    Rays::initRays();

    while (twoD_window.isOpen() && threeD_window.isOpen()) {
        twoD_window.pollEvent(event);
        if (event.close()) twoD_window.close();
        Player::movePlayer(event);
        threeD_window.pollEvent(event);
        if (event.close()) threeD_window.close();
        Player::movePlayer(event);

        Player::updatePlayer();
        Rays::updateRays();

        twoD_window.clear(gd::Color(50, 50, 50));
        Map::drawMap(twoD_window);
        Rays::drawRays(twoD_window);
        Player::drawPlayer(twoD_window);
        twoD_window.display();

        threeD_window.clear(gd::Color(50, 50, 50));
        Map::drawWalls(threeD_window);
        threeD_window.display();
    }
    return 0;
}