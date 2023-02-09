#ifndef IMAGEMPPM_H
#define IMAGEMPPM_H

#include "imagem.hpp"

class PPM : public Imagem
{

public:
    int id = 1;

    string type;
    int height, width;
    int color_scale;

    Pixel **img_ppm;

public:
    PPM();
    void read_ppm(string myfile);
};

#endif