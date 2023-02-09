#include "imagem.hpp"
#include "memlog.hpp"
#include "imagem_ppm.hpp"
#include "msgassert.h"

PPM::PPM()
{
}

void PPM::read_ppm(string text_file)
{
    erroAssert(text_file[0], "Arquivo de entrada não definido");
    ifstream myfile;
    string line;
    int r, g, b;
    int i, j, k;

    // abertura do arquivo
    myfile.open(text_file);
    erroAssert(myfile, "Erro na abertura do arquivo");

    // lê os dados da imagem -- tipo, proporções e escala de cor
    if (getline(myfile, line))
    {
        istringstream ss(line);
        type = line;
    }
    if (getline(myfile, line))
    {
        istringstream ss(line);
        i = 0;
        string token;
        string arr[2];

        // associa o tamanho da matriz a partir do arquivo
        while (getline(ss, token, ' '))
        {
            arr[i] = token;
            i++;
        }
        width = stoi(arr[0]);
        height = stoi(arr[1]);
        erroAssert(width > 0, "Largura inválida");
        erroAssert(height > 0, "Altura inválida");
    }
    if (getline(myfile, line))
    {
        color_scale = stoi(line);
    }

    // alocação dinâmica da matriz
    img_ppm = new Pixel *[height * width];
    for (i = 0; i < height; i++)
    {
        img_ppm[i] = new Pixel[width];
    }
    img_ppm = (Pixel **)malloc(sizeof(Pixel *) * height);
    erroAssert(img_ppm != NULL, "Malloc falhou");
    for (int i = 0; i < height; i++)
    {
        img_ppm[i] = (Pixel *)malloc(sizeof(Pixel) * width);
        ESCREVEMEMLOG((long int)(&(img_ppm[i])), sizeof(Pixel), 0);
        erroAssert(img_ppm[i] != NULL, "Malloc falhou");
    }

    // associando cada pixel a um rgb por um índice
    k = 0;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            img_ppm[i][j].index = k;
            k++;
        }
    }

    // associa cada pixel a um valor vermelho, verde ou azul de acordo com os dados do arquivo
    k = -1;
    while (myfile >> r >> g >> b)
    {
        k++;
        for (i = 0; i < height; i++)
        {
            for (j = 0; j < width; j++)
            {
                if (img_ppm[i][j].index == k)
                {
                    img_ppm[i][j].red = r;
                    img_ppm[i][j].green = g;
                    img_ppm[i][j].blue = b;
                    ESCREVEMEMLOG((long int)(&(img_ppm[i][j].red)), sizeof(int), 0);
                }
            }
        }
    }

    // fechamento do arquivo
    myfile.close();
    erroAssert(!myfile, "Erro no fechamento do arquivo");
}
