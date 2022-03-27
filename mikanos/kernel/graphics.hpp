#pragma once

#include "frame_buffer_config.hpp"

struct PixelColor {
    uint8_t r, g, b;
};

class PixelWriter {
public:
    PixelWriter(const FrameBufferConfig& config) : m_config(config) {}
    virtual ~PixelWriter() = default;
    virtual void Write(int x, int y, const PixelColor& color) = 0;

protected:
    uint8_t* PixelAt(int x, int y) {
        return m_config.frame_buffer + 4 * (m_config.pixels_per_scan_line * y + x);
    }

private:
    const FrameBufferConfig& m_config;
};

class RGBResv8BitPerColorPixelWriter : public PixelWriter {
public:
    using PixelWriter::PixelWriter;
    virtual void Write(int x, int y, const PixelColor& c) override;
};

class BGRResv8BitPerColorPixelWriter : public PixelWriter {
public:
    using PixelWriter::PixelWriter;
    virtual void Write(int x, int y, const PixelColor& c) override;
};