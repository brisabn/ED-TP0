#include "imagem.hpp"
#include "memlog.hpp"
#include "imagem_pgm.hpp"
#include "msgassert.h"

PGM::PGM()
{
}

// converter valores rgb para cinza
void PGM::converter(PPM ppm)
{
    int i, j;

    // aloca uma nova matriz dinamicamente para valores de cinza
    img_pgm = new Pixel *[ppm.height * ppm.width];
    for (i = 0; i < ppm.height; i++)
    {
        img_pgm[i] = new Pixel[ppm.width];
    }
    img_pgm = (Pixel **)malloc(sizeof(Pixel *) * ppm.height);
    erroAssert(img_pgm != NULL, "Malloc falhou");
    for (int i = 0; i < ppm.height; i++)
    {
        img_pgm[i] = (Pixel *)malloc(sizeof(Pixel) * ppm.width);
        erroAssert(img_pgm[i] != NULL, "Malloc falhou");
    }

    // converte os dados da imagem -- tipo, proporções e escala de cor
    type = "P2";
    color_scale = 49;
    height = ppm.height;
    width = ppm.width;

    // converte os valores dos pixels da imagem
    for (i = 0; i < ppm.height; i++)
    {
        for (j = 0; j < ppm.width; j++)
        {
            float Y = (49.0f / 255.0f) *
                      (0.30f * ppm.img_ppm[i][j].red + 0.59f * ppm.img_ppm[i][j].green +
                       0.11f * ppm.img_ppm[i][j].blue);
            img_pgm[i][j].red = static_cast<int>(Y);
        }
    }
}

// escrever arquivo pgm
void PGM::write_pgm(Pixel **img_pgm, string text_file)
{
    erroAssert(text_file[0], "Arquivo de saída não definido");

    // abertura do arquivo
    ofstream myfile;
    myfile.open(text_file);
    erroAssert(myfile, "Erro na abertura do arquivo");

    // escreve os dados da imagem -- tipo, proporções e escala de cor
    myfile << type << endl;
    erroAssert(type[0], "Tipo de imagem inválido");
    myfile << width << ' ' << height << endl;
    erroAssert(width > 0, "Largura inválida");
    erroAssert(height > 0, "Altura inválida");
    myfile << color_scale << endl;
    erroAssert(color_scale > 0, "Escala de cor inválida");

    // escreve os pixels na matriz cinza
    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            myfile << img_pgm[i][j].red << ' ';
            ESCREVEMEMLOG((long int)(&(img_pgm[i][j].red)), sizeof(int), 1);
            erroAssert(img_pgm[i][j].red >= 0, "Erro na escrita do pixel no arquivo de saída");
        }
        myfile << endl;
    }

    // fechamento do arquivo
    myfile.close();
}