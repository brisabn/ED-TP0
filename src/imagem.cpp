#include "imagem.hpp"
#include "memlog.hpp"
#include "msgassert.h"

Imagem::Imagem() {}

// deleta memória utilizada dinamicamente
void Imagem::deletar(Pixel **img)
{
    free(img);
    delete[] img;
}