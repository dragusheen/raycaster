/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/*  ---- INCLUDES ---- */
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>

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
float player_speed = 5;
float player_rotation_speed = 0.1;
sf::Vector2f player_position = sf::Vector2f(0, 0);
float player_angle = 0;
sf::Vector2f player_delta = sf::Vector2f(0, 0);
sf::CircleShape player;
sf::RectangleShape player_direction;

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
std::vector<sf::RectangleShape> map_rectangles;
std::vector<sf::RectangleShape> walls;

/*  ---- GRID ---- */
std::vector<sf::RectangleShape> map_grid;

/*  ---- RAYS ---- */
int ray_count = 60;
std::vector<sf::VertexArray> rays;

/*  ---- FUNCTION ---- */
/*  ---- PLAYER ---- */
void setPlayerDelta(void)
{
    player_delta.x = cos(player_angle) * player_speed;
    player_delta.y = sin(player_angle) * player_speed;
}
void initPlayer(void)
{
    player.setRadius(player_size);
    player.setOrigin(player_size, player_size);
    player.setFillColor(sf::Color::Yellow);

    player_position = sf::Vector2f(map_cell_size * map[0].size() / 2, map_cell_size * map.size() / 2);
    player.setPosition(player_position);

    player_direction.setSize(sf::Vector2f(player_size * 3, 2));
    player_direction.setOrigin(0, 1);
    player_direction.setFillColor(sf::Color::Yellow);
    player_direction.setPosition(player_position);
    player_direction.setRotation(player_angle * 180 / PI);
    setPlayerDelta();
}

void drawPlayer(sf::RenderWindow &window)
{
    window.draw(player);
    window.draw(player_direction);
}

void movePlayer(sf::Event event)
{
    if (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::Left)  {
        player_angle -= player_rotation_speed;
        if (player_angle < 0)
            player_angle += 2 * PI;
        setPlayerDelta();
    }
    if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
        player_angle += player_rotation_speed;
        if (player_angle > 2 * PI)
            player_angle -= 2 * PI;
        setPlayerDelta();
    }
    if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::Up) {
        sf::Vector2f new_position = sf::Vector2f(player_position.x + player_delta.x, player_position.y + player_delta.y);
        if (map[(int)(new_position.y / map_cell_size)][(int)(new_position.x / map_cell_size)] == 1) return;
        player_position.x += player_delta.x;
        player_position.y += player_delta.y;
    }
    if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
        sf::Vector2f new_position = sf::Vector2f(player_position.x - player_delta.x, player_position.y - player_delta.y);
        if (map[(int)(new_position.y / map_cell_size)][(int)(new_position.x / map_cell_size)] == 1) return;
        player_position.x -= player_delta.x;
        player_position.y -= player_delta.y;
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
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(map_cell_size, map_cell_size));
            rectangle.setPosition(sf::Vector2f(j * map_cell_size, i * map_cell_size));
            rectangle.setFillColor(sf::Color::White);
            map_rectangles.push_back(rectangle);
        }
    }
}

void drawMap(sf::RenderWindow &window)
{
    for(auto &rectangle : map_rectangles) window.draw(rectangle);
}

void drawWalls(sf::RenderWindow &window)
{
    for (auto &wall : walls) window.draw(wall);
}

/*  ---- GRID ---- */
void initGrid(void)
{
    sf::Color gray(120, 120, 120);
    float size = 2;
    for (int i = 0; i < map.size(); i++) {
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(800, size));
        rectangle.setPosition(sf::Vector2f(0, i * map_cell_size - size / 2));
        rectangle.setFillColor(gray);
        map_grid.push_back(rectangle);
    }
    for (int i = 0; i < map[0].size(); i++) {
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(size, 800));
        rectangle.setPosition(sf::Vector2f(i * map_cell_size - size / 2, 0));
        rectangle.setFillColor(gray);
        map_grid.push_back(rectangle);
    }
}

void drawGrid(sf::RenderWindow &window)
{
    for (auto &line : map_grid) window.draw(line);
}

/*  ---- RAYS ---- */
float dist(float x1, float y1, float x2, float y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void updateRays(void)
{
    walls.clear();
    int r, mx, my, mp, dof;
    float rx, ry, ra, xo, yo, distT;
    ra = player_angle - DR * (int)(ray_count / 2);
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

        if (distH < distV) {
            rx = hx;
            ry = hy;
            distT = distH;
        } else {
            rx = vx;
            ry = vy;
            distT = distV;
        }

        rays[i][0].position = player_position;
        rays[i][1].position = sf::Vector2f(rx, ry);

        float ca = player_angle - ra;
        if (ca < 0) ca += 2 * PI;
        if (ca > 2 * PI) ca -= 2 * PI;
        distT *= cos(ca);

        float wallH = (map_cell_size * window_height) / distT;
        wallH = (wallH > window_height) ? window_height : wallH;
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(window_width / ray_count, wallH));
        rectangle.setPosition(sf::Vector2f(i * (window_width / ray_count), window_height / 2 - wallH / 2));
        rectangle.setFillColor(sf::Color::Red);
        walls.push_back(rectangle);

        ra += DR;
        if (ra < 0) ra += 2 * PI;
        if (ra > 2 * PI) ra -= 2 * PI;
    }
}

void initRays(void)
{
    for (int i = 0; i < ray_count; i++) {
        sf::VertexArray ray(sf::Lines, 2);
        ray[0].position = player_position;
        ray[1].position = player_position;
        ray[0].color = sf::Color::Red;
        ray[1].color = sf::Color::Red;
        rays.push_back(ray);
    }
    updateRays();
}

void drawRays(sf::RenderWindow &window)
{
    for (auto &ray : rays) window.draw(ray);
}

/*  ---- MAIN ---- */
int main(void)
{
    window_width = map_cell_size * map[0].size();
    window_height = map_cell_size * map.size();
    sf::RenderWindow twoD_window(sf::VideoMode(window_width, window_height), "2D Raycaster");
    sf::RenderWindow threeD_window(sf::VideoMode(window_width, window_height), "3D Raycaster");
    twoD_window.setFramerateLimit(60);
    threeD_window.setFramerateLimit(60);

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    twoD_window.setPosition(sf::Vector2i(desktop.width / 3 - twoD_window.getSize().x / 2, desktop.height / 2 - twoD_window.getSize().y / 2));
    threeD_window.setPosition(sf::Vector2i(desktop.width / 3 * 2 - threeD_window.getSize().x / 2, desktop.height / 2 - threeD_window.getSize().y / 2));

    initPlayer();
    initMap();
    initGrid();
    initRays();
    while (twoD_window.isOpen() && threeD_window.isOpen()) {
        sf::Event event;
        while (twoD_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) twoD_window.close();
            if (event.type == sf::Event::KeyPressed) movePlayer(event);
        }
        while (threeD_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) threeD_window.close();
            if (event.type == sf::Event::KeyPressed) movePlayer(event);
        }

        updatePlayer();
        updateRays();

        twoD_window.clear(sf::Color(50, 50, 50));
        drawMap(twoD_window);
        drawGrid(twoD_window);
        drawRays(twoD_window);
        drawPlayer(twoD_window);
        twoD_window.display();

        threeD_window.clear(sf::Color(50, 50, 50));
        drawWalls(threeD_window);
        threeD_window.display();
    }
    return 0;
}
