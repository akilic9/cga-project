#pragma once
#include <unordered_map>
/*
    This is specifically written in clockwise order,
    the difference between enums is used in sprite rotation calculations.
*/
enum class Direction {
    None = -1,
    Down,
    Left,
    Up,
    Right
};


static std::unordered_map<Direction, sf::Vector2f> m_directionsMap = { {Direction::Down,  sf::Vector2f(0.f,  1.f)},
                                                                       {Direction::Up,    sf::Vector2f(0.f, -1.f)},
                                                                       {Direction::Left,  sf::Vector2f(-1.f, 0.f)},
                                                                       {Direction::Right, sf::Vector2f(1.f,  0.f)} };