/*
CG - TRABALHO 2
JOSÉ AUGUSTO COMIOTTO ROTTINI - ENGENHARIA DE COMPUTACAO - UFSM

Implementacao da classe Matriz. Possibilita as transformadas 2D: translacao, rotacao e escala.

*/

#include "Matriz.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>

Matriz::Matriz()
{
      colunas = 3;
      linhas = 3;

    for (int x=0;x<linhas;x++)  // Carrega a matriz identidade
    {
        for(int y=0;y<colunas;y++)
        {
            if (x==y)
            {
                matriz[x][y] = 1;
            }
            else
            {
                matriz[x][y] = 0;
            }
        }
    }
}

Matriz::~Matriz()
{
    //dtor
}

/* MULTIPLICA DUAS MATRIZES DE ENTRADA */
void Matriz::multiplica(float matriz1[3][3], float matriz2[3][3])
{
    float matrizResultante[3][3];
    float soma;
    int i = 0;

     for (int x=0;x<3;x++)
    {
        for(int y=0;y<3;y++)
        {
            matrizResultante[x][y]=0;
            for (int j=0;j<3;j++)
            {
                matrizResultante[x][y]+= matriz1[x][j] * matriz2[j][y];
            }
        }
    }
    for (int x=0;x<3;x++)
    {
        for(int y=0;y<3;y++)
        {
            matriz[x][y] = matrizResultante[x][y];
        }
    }
}

/* CONCATENA A MATRIZ DE ROTACAO A MATRIZ DE TRANSFORMACAO */
void Matriz:: rotacao(float ang)
{
    float rad=ang*((float)3.14/(float)180);
    float matrizRotacao[3][3] = {cos(rad), -sin(rad),0,sin(rad), cos(rad),0,0,0,1};

    multiplica(matriz, matrizRotacao);
}

/* CONCATENA A MATRIZ DE TRANSLACAO A MATRIZ DE TRANSFORMACAO */
void Matriz::translada(int tx, int ty)
{
    float matrizTranslacao[3][3] = {1,0,tx,0,1,ty,0,0,1};

    multiplica(matriz, matrizTranslacao);
}

/* CONCATENA A MATRIZ DE ESCALA A MATRIZ DE TRANSFORMACAO */
void Matriz::escala(int sx, int sy)
{
    float matrizEscala[3][3] = {sx,0,0,0,sy,0,0,0,1};

    multiplica(matriz, matrizEscala);
}

/* MOSTRA A MATRIZ NA TELA */
void Matriz:: print()
{
    std::cout<< "\n\nMATRIZ"<<std::endl;
    for (int x=0;x<3;x++)
    {
        for(int y=0;y<3;y++)
        {
            std::cout<< matriz[x][y]<<std::endl;
        }
    }

}
