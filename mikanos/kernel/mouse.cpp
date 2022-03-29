#include "mouse.hpp"

#include "graphics.hpp"

namespace {

const int kMouseCursorWidth = 15;
const int kMouseCursorHeight = 24;
const char mouse_cursor_shape[kMouseCursorHeight][kMouseCursorWidth + 1] = {
    "@              ",
    "@@             ",
    "@.@            ",
    "@..@           ",
    "@...@          ",
    "@....@         ",
    "@.....@        ",
    "@......@       ",
    "@.......@      ",
    "@........@     ",
    "@.........@    ",
    "@..........@   ",
    "@...........@  ",
    "@............@ ",
    "@......@@@@@@@@",
    "@......@       ",
    "@....@@.@      ",
    "@...@ @.@      ",
    "@..@   @.@     ",
    "@.@    @.@     ",
    "@@      @.@    ",
    "@       @.@    ",
    "         @.@   ",
    "         @@@   ",
};

void DrawMouseCursor(PixelWriter* writer, Vector2D<int> position) {
    for (int dy = 0; dy < kMouseCursorHeight; ++dy) {
        for (int dx = 0; dx < kMouseCursorWidth; ++dx) {
            if (mouse_cursor_shape[dy][dx] == '@') {
                writer->Write(position.x + dx, position.y + dy, {0, 0, 0});
            } else if (mouse_cursor_shape[dy][dx] == '.') {
                writer->Write(position.x + dx, position.y + dy, {255, 255, 255});
            }
        }
    }
}

void EraseMouseCursor(PixelWriter* writer, Vector2D<int> position, PixelColor erase_color) {
    for (int dy = 0; dy < kMouseCursorHeight; ++dy) {
        for (int dx = 0; dx < kMouseCursorWidth; ++dx) {
            if (mouse_cursor_shape[dy][dx] != ' ') {
                writer->Write(position.x + dx, position.y + dy, erase_color);
            }
        }
    }
}
}

MouseCursor::MouseCursor(PixelWriter* writer, PixelColor erase_color, Vector2D<int> initial_position)
    : m_pixelWriter(writer)
    , m_eraseColor(erase_color)
    , m_position(initial_position)
    {
        DrawMouseCursor(m_pixelWriter, m_position);
    }

void MouseCursor::MoveRelative(Vector2D<int> displacement) {
    EraseMouseCursor(m_pixelWriter, m_position, m_eraseColor);
    m_position += displacement;
    DrawMouseCursor(m_pixelWriter, m_position);
}