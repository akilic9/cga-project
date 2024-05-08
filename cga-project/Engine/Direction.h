#pragma once

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