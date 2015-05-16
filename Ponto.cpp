/*
CG - TRABALHO 2
JOSÉ AUGUSTO COMIOTTO ROTTINI - ENGENHARIA DE COMPUTACAO - UFSM

Implementacao da classe Ponto, a qual trata o mesmo como ponto homogeneo e facilita as transformacoes 2D.	

*/

#include "Ponto.h"

Ponto::Ponto(float x1, float y1)
{
	// 3 coordenadas (x,y,h)
    ponto[0]=x1;
    ponto[1]=y1;
    ponto[2]=1;
    x= ponto[0];
    y=ponto[1];
}

Ponto::~Ponto()
{
    //dtor
}

Ponto Ponto::operator*(float num)
{
    Ponto pontoResultante(x * num, y * num);
    return pontoResultante;
}

Ponto Ponto::operator+=(const Ponto& ponto)
{
	x += ponto.x;
	y += ponto.y;
	return *this;
}

Ponto Ponto::operator+(const Ponto& ponto){
	Ponto pontoResultante(x + ponto.x, y + ponto.y);
	return pontoResultante;
}

Ponto Ponto::operator-(const Ponto& ponto){
	Ponto pontoResultante(x - ponto.x, y - ponto.y);
	return pontoResultante;
}

Ponto Ponto::operator*(const Ponto& ponto){
	Ponto pontoResultante(x * ponto.x, y * ponto.y);
	return pontoResultante;
}

Ponto& Ponto::operator=(const Ponto& ponto){
	x = ponto.x;
	y = ponto.y;
	return *this;
}
