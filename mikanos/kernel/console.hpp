#pragma once

#include "graphics.hpp"

class Console {
public:
    static const int kRows = 25, kColumns = 80;

    Console(PixelWriter& writer, const PixelColor& fg_color, const PixelColor& bg_color);
    void PutString(const char* s);

private:
    void Newline();

    PixelWriter& m_writer;
    const PixelColor m_fgColor, m_bgColor;
    char m_buffer[kRows][kColumns + 1];
    int m_cursorRow, m_cursorColumn;
};