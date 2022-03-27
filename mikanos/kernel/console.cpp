/**
 * @file console.cpp
 *
 * コンソール描画
 */

#include "console.hpp"

#include <cstring>
#include "font.hpp"

Console::Console(PixelWriter& writer, const PixelColor& fg_color, const PixelColor& bg_color)
    : m_writer{writer}
    , m_fgColor{fg_color}
    , m_bgColor{bg_color}
    , m_buffer{}
    , m_cursorRow{0}
    , m_cursorColumn{0} {

    }

void Console::PutString(const char* s) {
    while(*s) {
        if (*s == '\n') {
            Newline();
        } else if (m_cursorColumn < kColumns - 1) {
            WriteAscii(m_writer, 8 * m_cursorColumn, 16 * m_cursorRow, *s, m_fgColor);
            m_buffer[m_cursorRow][m_cursorColumn] = *s;
            ++m_cursorColumn;
        }
        ++s;
    }
}

void Console::Newline() {
    m_cursorColumn = 0;
    if (m_cursorRow < kRows - 1) {
        ++m_cursorRow;
    } else {
        for (int y = 0; y < 16 * kRows; ++y) {
            for (int x = 0; x < 8 * kColumns; ++x) {
                m_writer.Write(x, y, m_bgColor);
            }
        }
        for (int row = 0; row < kRows - 1; ++row) {
            memcpy(m_buffer[row], m_buffer[row + 1], kColumns + 1);
            WriteString(m_writer, 0, 16 * row, m_buffer[row], m_fgColor);
        }
        memset(m_buffer[kRows - 1], 0, kColumns + 1);
    }
}