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

/*  ---- VARIABLES ---- */
/*  ---- MATH ---- */
float PI = 3.1415926535;
float P2 = PI / 2;
float P3 = 3 * PI / 2;
float DR = 0.0174533;

/*  ---- WINDOW ---- */
float window_width = 0;
float window_height = 0;

/*  ---- PLAYER ---- */
float player_size = 4;
float player_speed = 4;
float player_rotation_speed = 0.05;
gd::Vector<float> player_position = gd::Vector<float>(0, 0);
float player_angle = 0;
gd::Vector<float> player_delta = gd::Vector<float>(0, 0);
int player_view_angle = 60;
int player_view_distance = 200;
gd::CircleShape player;
gd::RectangleShape player_direction;

/*  ---- MAP ---- */
float mapX = 8;
float mapY = 8;
float map_cell_size = 64;
std::vector<std::vector<int>> map = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
};
std::vector<gd::RectangleShape> map_rectangles;
std::vector<gd::RectangleShape> walls;

/*  ---- GRID ---- */
std::vector<gd::RectangleShape> map_grid;

/*  ---- RAYS ---- */
int ray_count = 1920;
std::vector<gd::VertexArray> rays;


/*  ---- FUNCTION ---- */
/*  ---- MATH ---- */
float dist(float x1, float y1, float x2, float y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

/*  ---- PLAYER ---- */
void setPlayerDelta(void)
{
    player_delta.x = cos(player_angle) * player_speed;
    player_delta.y = sin(player_angle) * player_speed;
}

void initPlayer(void)
{
    player.create(player_size);
    player.setOrigin(gd::Vector<float>(player_size, player_size));
    player.setFillColor(gd::Color::Yellow);

    player_position = gd::Vector<float>(map_cell_size * map[0].size() / 2, map_cell_size * map.size() / 2);
    player.setPosition(player_position);

    player_direction.create(gd::Vector<float>(player_size * 3, 2));
    player_direction.setOrigin(gd::Vector<float>(0, 1));
    player_direction.setFillColor(gd::Color::Yellow);
    player_direction.setPosition(player_position);
    player_direction.setRotation(player_angle * 180 / PI);
    setPlayerDelta();
}

void drawPlayer(gd::Window &window)
{
    window.draw(player);
    window.draw(player_direction);
}

void movePlayerForward(void)
{
    gd::Vector<float> new_position = gd::Vector<float>(player_position.x + player_delta.x, player_position.y + player_delta.y);
    if (map[(int)(new_position.y / map_cell_size)][(int)(new_position.x / map_cell_size)] == 1) return;
    player_position = new_position;
}

void movePlayerBackward(void)
{
    gd::Vector<float> new_position = gd::Vector<float>(player_position.x - player_delta.x, player_position.y - player_delta.y);
    if (map[(int)(new_position.y / map_cell_size)][(int)(new_position.x / map_cell_size)] == 1) return;
    player_position = new_position;
}

void movePlayerLeft(void)
{
    player_angle -= player_rotation_speed;
    if (player_angle < 0)
        player_angle += 2 * PI;
    setPlayerDelta();
}

void movePlayerRight(void)
{
    player_angle += player_rotation_speed;
    if (player_angle > 2 * PI)
        player_angle -= 2 * PI;
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
    player.setPosition(player_position);
    player_direction.setPosition(player_position);
    player_direction.setRotation(player_angle * 180 / PI);
}

/*  ---- MAP ---- */
void initMap(void)
{
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 0) continue;
            gd::RectangleShape rectangle;
            rectangle.create(gd::Vector<float>(map_cell_size, map_cell_size));
            rectangle.setPosition(gd::Vector<float>(j * map_cell_size, i * map_cell_size));
            rectangle.setFillColor(gd::Color::White);
            map_rectangles.push_back(rectangle);
        }
    }
}

void drawMap(gd::Window &window)
{
    for (auto &rectangle : map_rectangles) window.draw(rectangle);
}

void drawWalls(gd::Window &window)
{
    for (auto &wall : walls) window.draw(wall);
}

/*  ---- GRID ---- */
void initGrid(void)
{
    gd::Color gray(120, 120, 120);
    float size = 2;
    for (int i = 0; i < map.size(); i++) {
        gd::RectangleShape rectangle;
        rectangle.create(gd::Vector<float>(800, size));
        rectangle.setPosition(gd::Vector<float>(0, i * map_cell_size - size / 2));
        rectangle.setFillColor(gray);
        map_grid.push_back(rectangle);
    }
    for (int i = 0; i < map[0].size(); i++) {
        gd::RectangleShape rectangle;
        rectangle.create(gd::Vector<float>(size, 800));
        rectangle.setPosition(gd::Vector<float>(i * map_cell_size - size / 2, 0));
        rectangle.setFillColor(gray);
        map_grid.push_back(rectangle);
    }
}

void drawGrid(gd::Window &window)
{
    for (auto &line : map_grid) window.draw(line);
}

/*  ---- RAYS ---- */
void initRays(void)
{
    rays.clear();
    for (int i = 0; i < ray_count; i++) {
        gd::VertexArray ray(gd::Lines, 2);
        ray[0].position = player_position;
        ray[1].position = player_position;
        ray[0].color = gd::Color::Red;
        ray[1].color = gd::Color::Red;
        rays.push_back(ray);
    }
}

void updateRays(void)
{
    walls.clear();
    int r, mx, my, mp, dof;
    float rx, ry, ra, xo, yo, distT;
    ra = player_angle - (player_view_angle / 2) * DR;
    if (ra < 0) ra += 2 * PI;
    if (ra > 2 * PI) ra -= 2 * PI;

    for (int i = 0; i < (int)ray_count; i++) {
        float distH = 100000;
        float hx = player_position.x;
        float hy = player_position.y;
        dof = 0;

        float aTan = -1 / tan(ra);
        if (ra > PI) {
            ry = (((int)player_position.y>>6)<<6) - 0.0001;
            rx = (player_position.y - ry) * aTan + player_position.x;
            yo = -map_cell_size;
            xo = -yo * aTan;
        }
        if (ra < PI) {
            ry = (((int)player_position.y>>6)<<6) + map_cell_size;
            rx = (player_position.y - ry) * aTan + player_position.x;
            yo = map_cell_size;
            xo = -yo * aTan;
        }
        if (ra == 0 || ra == PI) {
            rx = player_position.x;
            ry = player_position.y;
            dof = 8;
        }
        while (dof < 8) {
            mx = (int)(rx)>>6;
            my = (int)(ry)>>6;
            if (mx < 0 || mx >= map[0].size() || my < 0 || my >= map.size()) {
                dof = 8;
                break;
            }
            mp = (int)map[my][mx];
            if (mp == 1) {
                hx = rx;
                hy = ry;
                distH = dist(player_position.x, player_position.y, hx, hy);
                dof = 8;
                break;
            } else {
                rx += xo;
                ry += yo;
                dof++;
            }
        }

        float distV = 100000;
        float vx = player_position.x;
        float vy = player_position.y;
        dof = 0;
        float nTan = -tan(ra);
        if (ra > P2 && ra < P3) {
            rx = (((int)player_position.x>>6)<<6) - 0.0001;
            ry = (player_position.x - rx) * nTan + player_position.y;
            xo = -map_cell_size;
            yo = -xo * nTan;
        }
        if (ra < P2 || ra > P3) {
            rx = (((int)player_position.x>>6)<<6) + map_cell_size;
            ry = (player_position.x - rx) * nTan + player_position.y;
            xo = map_cell_size;
            yo = -xo * nTan;
        }
        if (ra == 0 || ra == PI) {
            rx = player_position.x;
            ry = player_position.y;
            dof = 8;
        }
        while (dof < 8) {
            mx = (int)(rx)>>6;
            my = (int)(ry)>>6;
            if (mx < 0 || mx >= map[0].size() || my < 0 || my >= map.size()) {
                dof = 8;
                break;
            }
            mp = (int)map[my][mx];
            if (mp == 1) {
                vx = rx;
                vy = ry;
                distV = dist(player_position.x, player_position.y, vx, vy);
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

        rays[i][0].position = player_position;
        rays[i][1].position = gd::Vector<float>(rx, ry);

        float ca = player_angle - ra;
        if (ca < 0) ca += 2 * PI;
        if (ca > 2 * PI) ca -= 2 * PI;
        distT *= cos(ca);
        if (distT > player_view_distance) color.a = 255 - distT + player_view_distance;
        if (color.a < 0) color.a = 0;

        gd::RectangleShape rectangle;
        float wallH = (map_cell_size * window_height) / distT;
        wallH = (wallH > window_height) ? window_height : wallH;
        rectangle.setSize(gd::Vector<float>(window_width / ray_count, wallH));
        rectangle.setPosition(gd::Vector<float>(i * (window_width / ray_count), window_height / 2 - wallH / 2));
        rectangle.setFillColor(color);
        walls.push_back(rectangle);

        ra += (float)((float)(player_view_angle) / (float)(ray_count)) * DR;
        if (ra < 0) ra += 2 * PI;
        if (ra > 2 * PI) ra -= 2 * PI;
    }
}

void drawRays(gd::Window &window)
{
    for (auto &ray : rays) window.draw(ray);
}

/*  ---- MAIN ---- */
int main(void)
{
    gd::Vector<unsigned int> desktop_size = gd::Window::getDesktopSize();
    window_width = map_cell_size * map[0].size();
    window_height = map_cell_size * map.size();
    gd::Window twoD_window;
    twoD_window.create(window_width, window_height, "2D Raycaster");
    twoD_window.setFramerateLimit(24);
    twoD_window.setPosition(gd::Vector<int>(desktop_size.x / 4 - window_width / 2, desktop_size.y / 2 - window_height / 2));
    window_width = 800;
    window_height = 600;
    gd::Window threeD_window;
    threeD_window.create(window_width, window_height, "3D Raycaster");
    threeD_window.setFramerateLimit(24);
    threeD_window.setPosition(gd::Vector<int>(desktop_size.x / 4 * 3 - window_width / 2, desktop_size.y / 2 - window_height / 2));
    gd::Event event;

    initPlayer();
    initMap();
    initGrid();
    initRays();

    while (twoD_window.isOpen() && threeD_window.isOpen()) {
        twoD_window.pollEvent(event);
        if (event.close()) twoD_window.close();
        movePlayer(event);
        threeD_window.pollEvent(event);
        if (event.close()) threeD_window.close();
        movePlayer(event);

        updatePlayer();
        updateRays();

        twoD_window.clear(gd::Color(50, 50, 50));
        drawMap(twoD_window);
        drawGrid(twoD_window);
        drawRays(twoD_window);
        drawPlayer(twoD_window);
        twoD_window.display();

        threeD_window.clear(gd::Color(50, 50, 50));
        drawWalls(threeD_window);
        threeD_window.display();
    }
    return 0;
}