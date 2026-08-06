#include <iostream> // debugging
#include <cmath>
#include <ctime>

#include "tgaimage.hpp"


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

    int y = y1;
    int ierror = 0;

    for (int x {x1}; x <= x2; x++) {
        if (steep) {
            framebuffer.set(y, x, color);
        }
        else {
            framebuffer.set(x, y, color);  
        }

        ierror += 2 * std::abs(y2 - y1);
        
        if (ierror > (x2 - x1)) {
            y += y2 > y1 ? 1 : -1;
            ierror -= 2 * (x2 - x1);
        }
    }   
}

int main()
{
    constexpr int width = 64;
    constexpr int height = 64;
    TGAImage framebuffer(width, height, TGAImage::RGB);

    std::srand(std::time(0));

    for (int i {}; i < (1<<24); ++i) {
        int ax = rand() % width;
        int ay = rand() % height;
        int bx = rand() % width;
        int by = rand() & height;

        drawLine(ax, ay, bx, by, framebuffer, {
            static_cast<std::uint8_t>(rand() % 256),
            static_cast<std::uint8_t>(rand() % 256),
            static_cast<std::uint8_t>(rand() % 256),
            static_cast<std::uint8_t>(rand() % 255),
        });
    }

    framebuffer.write_tga_file("framebuffer.tga");

    return 0;
}