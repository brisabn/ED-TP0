#include "pixel.hpp"

Pixel::Pixel() : Pixel(0, 0, 0) {}

Pixel::Pixel(int red, int green, int blue)
    : red(red), green(green), blue(blue) {}

void Pixel::set_rgb(int _red, int _green, int _blue)
{
    this->red = _red;
    this->green = _green;
    this->blue = _blue;
}
