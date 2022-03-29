/**
 * @file mouse.hpp
 * 
 * マウス制御
 */

#pragma once

#include "graphics.hpp"

class MouseCursor {
public:
    MouseCursor(PixelWriter* writer, PixelColor erace_color, Vector2D<int> initial_position);

    void MoveRelative(Vector2D<int> displacement);

private:
    PixelWriter* m_pixelWriter = nullptr;
    PixelColor m_eraseColor;
    Vector2D<int> m_position;
};
