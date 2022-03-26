/**
 * @file main.cpp
 * 
 * カーネル本体
 */


#include <cstdint>
#include <cstddef>

#include "frame_buffer_config.hpp"

// #@@range_begin(write_pixel)
struct PixelColor {
    uint8_t r, g, b;
};

// #@@range_begin(pixel_writer)
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

    virtual void Write(int x, int y, const PixelColor& color) override {
        auto pixel = PixelAt(x, y);
        pixel[0] = color.r;
        pixel[1] = color.g;
        pixel[2] = color.b;
    }
};

class BGRResv8BitPerColorPixelWriter : public PixelWriter {
public:
    using PixelWriter::PixelWriter;

    virtual void Write(int x, int y, const PixelColor& color) override {
        auto pixel = PixelAt(x, y);
        pixel[0] = color.b;
        pixel[1] = color.g;
        pixel[2] = color.r;
    }
};
// #@@range_end(pixel_writer)

// #@@range_begin(placement_new)
void* operator new(size_t size, void* buf) {
    return buf;
}

void operator delete(void* obj) noexcept {
}
// #@@range_end(placement_new)

char pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
PixelWriter* pixel_writer;

// #@@range_begin(call_write_pixel)
extern "C" void KernelMain(const FrameBufferConfig& frame_buffer_config) {

    switch (frame_buffer_config.pixel_format) {
        case kPixelRGBResv8BitPerColor:
            pixel_writer = new(pixel_writer_buf) RGBResv8BitPerColorPixelWriter{frame_buffer_config};
            break;
        case kPixelBGRResv8BitPerColor:
            pixel_writer = new(pixel_writer_buf) BGRResv8BitPerColorPixelWriter{frame_buffer_config};
            break;
    }

    for (int x = 0; x < frame_buffer_config.horizontal_resolution; ++x) {
        for (int y = 0; y < frame_buffer_config.vertical_resolution; ++y) {
            pixel_writer->Write(x, y, {255, 255, 255});
        }
    }
    for (int x = 0; x < 200; ++ x) {
        for (int y = 0; y < 100; ++y) {
            pixel_writer->Write(x, y, {0, 255, 0});
        }
    }
    while (1) __asm__("hlt");
}
// #@@range_end(call_write_pixel)