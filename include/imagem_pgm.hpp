#ifndef IMAGEMPGM_H
#define IMAGEMGPM_H

#include "imagem.hpp"
#include "imagem_ppm.hpp"

class PGM : public Imagem
{

public:
    int id = 0;

    string type;
    int height, width;
    int color_scale;

    Pixel **img_pgm;

public:
    PGM();
    void converter(PPM ppm);
    void write_pgm(Pixel **img, string myfile);
};

#endif