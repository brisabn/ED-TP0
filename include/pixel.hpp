#ifndef PIXEL_H
#define PIXEL_H

#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class Pixel
{
public:
    int id = 1;

    int index = 0;
    int red = 0;
    int green = 0;
    int blue = 0;

public:
    Pixel();
    Pixel(int red, int green, int blue);
    void set_rgb(int red, int green, int blue);
};

#endif