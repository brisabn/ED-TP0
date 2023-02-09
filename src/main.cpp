#include "imagem.hpp"
#include "pixel.hpp"
#include "imagem_ppm.hpp"
#include "imagem_pgm.hpp"
#include <iostream>
#include "msgassert.h"
#include "memlog.hpp"
#include <cstring>

// variáveis globais
bool read_ppm, write_pgm, regmem;
char lognome[100];

string arquivo_ppm;
string arquivo_pgm;

void parse_args(int argc, char const *argv[])
{
    int ext = 0;
    lognome[0] = 0;

    for (int i = 0; i < argc; i++)
    {
        if (string(argv[i]) == "-i")
        {
            for (int j = 0; j < int(string(argv[i + 1]).length()); j++)
            {
                if ((string(argv[i + 1])[j] == '.'))
                {
                    ext++;
                }
            }
            avisoAssert(ext > 0, "Arquivo sem extensão");

            // pode ler o arquivo de entrada definido no argumento
            read_ppm = true;
            arquivo_ppm = argv[i + 1];
        }

        else if (string(argv[i]) == "-o")
        {
            for (int j = 0; j < int(string(argv[i + 1]).length()); j++)
            {
                if ((string(argv[i + 1])[j] == '.'))
                {
                    ext++;
                }
            }
            avisoAssert(ext > 0, "Arquivo sem extensão");

            // pode escrever o arquivo de saída definido no argumento
            write_pgm = true;
            arquivo_pgm = argv[i + 1];
        }

        else if (string(argv[i]) == "-p")
        {
            for (int j = 0; j < int(string(argv[i + 1]).length()); j++)
            {
                if ((string(argv[i + 1])[j] == '.'))
                {
                    ext++;
                }
            }
            avisoAssert(ext > 0, "Arquivo sem extensão");

            strcpy(lognome, argv[i + 1]);
            iniciaMemLog(lognome);
            erroAssert(string(lognome).length() > 0, "Arquivo não definido");
        }

        else if (string(argv[i]) == "-l")
        {
            regmem = true;
        }
    }
}

int main(int argc, char const *argv[])
{
    PPM imagem_ppm;
    PGM imagem_pgm;

    // leitura dos argumento
    parse_args(argc, argv);

    // indica se devem ser registrados os acessos à memória
    if (regmem)
        ativaMemLog();
    else
        desativaMemLog();

    // possibilita ler e converter o arquivo ppm
    if (read_ppm)
    {
        imagem_ppm.read_ppm(arquivo_ppm);
        imagem_pgm.converter(imagem_ppm);
    }
    // possibilita escrever o arquivo pgm e deletar as matrizes alocadas dinamicamente
    if (write_pgm)
    {
        imagem_pgm.write_pgm(imagem_pgm.img_pgm, arquivo_pgm);
    }

    finalizaMemLog();
    return 0;
}