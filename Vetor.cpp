/*
CG - TRABALHO 2
JOSÉ AUGUSTO COMIOTTO ROTTINI - ENGENHARIA DE COMPUTACAO - UFSM

Implementacao da classe Vetor. Possibilita a obtencao de vetores atras da subtracao de pontos e funcao de normalizacao dos mesmos.

*/

#include "Vetor.h"
#include <cmath>
#include <iostream>

using namespace std;

Vetor::Vetor(const Ponto& a, const Ponto& b)
{
    x = b.x - a.x;
    y = b.y - a.y;
}

Vetor::Vetor ()
{
    x = 0;
    y = 0;
}

Vetor::~Vetor()
{
    //dtor
}

void Vetor:: normaliza() // normaliza o tamanho do vetor
{
    float modulo = sqrt(pow(x,2)+pow (y,2));
    x = x / modulo;
    y = y / modulo;
}


