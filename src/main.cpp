#include "tgaimage.hpp"
#include <iostream> // debugging
#include <cmath>

// define multiple colors BGRA order
constexpr TGAColor white = {255, 255, 255, 255};
constexpr TGAColor green = {0, 255, 0, 255};
constexpr TGAColor red = {0, 0, 255, 255};
constexpr TGAColor blue = {255, 128, 64, 255};
constexpr TGAColor yellow = {0, 200, 255, 255};

// Draw line between two points using Bresenham's Line Algorithm
void drawLine(int x1, int y1, int x2, int y2, TGAImage &framebuffer, TGAColor color)
{
    bool steep = std::abs(y1 - y2) > std::abs(x2 - x1);

    // transapose image if line is steep
    if (steep) {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }

    // make sure we can iterate over distance between x1 and x2
    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    for (int x {x1}; x <= x2; x++) {
        float t = (x - x1) / static_cast<float> (x2 - x1);
        int y = std::round(y1 + t * (y2 - y1));

        if (steep) {
            framebuffer.set(y, x, color);
        }
        else {
            framebuffer.set(x, y, color);  
        }
    }   
}

int main()
{
    constexpr int width = 64;
    constexpr int height = 64;
    TGAImage framebuffer(width, height, TGAImage::RGB);

    int ax = 7, ay = 3;
    int bx = 12, by = 37;
    int cx = 62, cy = 53;

    drawLine(ax, ay, bx, by, framebuffer, blue);
    drawLine(cx, cy, bx, by, framebuffer, green);
    drawLine(cx, cy, ax, ay, framebuffer, yellow);
    drawLine(ax, ay, cx, cy, framebuffer, red);

    framebuffer.write_tga_file("framebuffer.tga");

    return 0;
}