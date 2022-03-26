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

int WritePixel(const FrameBufferConfig& config, int x, int y, const PixelColor& color) {
    const int pixle_position = config.pixels_per_scan_line * y + x;
    uint8_t* pixel = &config.frame_buffer[4 * pixle_position];
    if (config.pixel_format == kPixelRGBResv8BitPerColor) {
        pixel[0] = color.r;
        pixel[1] = color.g;
        pixel[2] = color.b;
    } else if (config.pixel_format == kPixelBGRResv8BitPerColor) {
        pixel[0] = color.b;
        pixel[1] = color.g;
        pixel[2] = color.r;
    } else {
        return -1;
    }

    return 0;
}
// #@@range_end(write_pixel)

// #@@range_begin(call_write_pixel)
extern "C" void KernelMain(const FrameBufferConfig& frame_buffer_config) {
    for (int x = 0; x < frame_buffer_config.horizontal_resolution; ++x) {
        for (int y = 0; y < frame_buffer_config.vertical_resolution; ++y) {
            WritePixel(frame_buffer_config, x, y, {255, 255, 255});
        }
    }
    for (int x = 0; x < 200; ++x) {
        for (int y = 0; y < 100; ++y) {
            WritePixel(frame_buffer_config, 100 + x, 100 + y, {0, 255, 0});
        }
    }   
    while (1) __asm__("hlt");
}
// #@@range_end(call_write_pixel)