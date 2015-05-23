/*
	CG - TRABALHO 2
	JOSÉ AUGUSTO COMIOTTO ROTTINI - ENGENHARIA DE COMPUTACAO - UFSM

	Implementacao dos widgets, curvas de bezier e desenho no canvas.

*/

#include "widget.h"
#include "Ponto.h"
#include <vector>
#include "vetor.h"
#include "Matriz.h"
#include "Application.h"
#include <SCV\Point.h>


Ponto pontoInicial(0,0);

int posicaoAtual = 0;
bool buttonOk = false;
bool botaoClear = false;
bool buttonViewControlGraphs = false;
bool smooth = false;
bool first = false;
float tempo = 0;
float speed = 0;

std::vector <Ponto> pontosDeControle;
std::vector<Ponto> subPontosDeControle;
std::vector<Ponto> subPontosDeControle2;
std::vector<Ponto> pontosAdicionados;


/* CALCULA O FATORIAL PARA UM VALOR DE ENTRADA */
int fatorial(int valor)
 {
    int resultado = 1;

    if(valor <= 1)
    {
        return 1;
    }

    for(int i = 1; i <= valor; i++)
    {
        resultado *= i;
    }
    return resultado;
}

/* CALCULA AS FUNCOES DE BASE DE BEZIER */
int blendingFunction(int grau, int posicaoPonto )
{
    return fatorial(grau) / (fatorial(posicaoPonto ) * fatorial(grau - posicaoPonto ));
}

/* CALCULA O BEZIER PARA UM DADO VETOR DE PONTOS DE CONTROLE */
 Ponto bezier(std::vector<Ponto>& pontosDeControle, float t)
 {
    Ponto p(0,0);
    int numPontosDeControle = pontosDeControle.size();
    int grau = numPontosDeControle-1;

	for (int i = 0; i < numPontosDeControle; i++)
	{
		p += pontosDeControle[i] *(float)(blendingFunction(grau, i) * pow((1.0 - t), grau - i) * pow(t, i));
	}
	return p;
}

 /* CALCULA A DERIVADA DE UMA FUNCAO DE BEZIER PARA UM DADO VETOR DE PONTOS DE CONTROLE */
Ponto derivadaBezier(std::vector<Ponto>& pontosDeControle, float t)
 {
	 Ponto p(0,0);
    int numPontosDeControle = pontosDeControle.size();
    int grau = numPontosDeControle-1;

        for(int i = 0; i < numPontosDeControle-1; i++)
        {
			p += (pontosDeControle[i + 1] - pontosDeControle[i])* (float)(blendingFunction(grau - 1, i) * pow((1.0 - t), grau - 1 - i) * pow(t, i)) * (float)grau;
			
        }
    return p;
}

/* GARANTE CONTINUIDADE C1 NAS CURVAS */
void suavizaCurva()
{
	int posicaoPontoAdicionado = 0;

	if (smooth == false) // Se ainda não foi suavizada
	{
		for (int i = 0; i < pontosDeControle.size(); i++) // Adiciona pontos de controle extras de forma colinear para garantir continuidade C1
		{
			if (pontosDeControle.size()-i <3) // Ultimo segmento
			{
				Vetor vetorColinear(pontosDeControle[1], pontosDeControle[0]);
				vetorColinear.normaliza();
				Ponto novoPonto(pontosDeControle[0].x + vetorColinear.x * 40, pontosDeControle[0].y + vetorColinear.y * 40);

				pontosDeControle.push_back(novoPonto);
				pontosDeControle.push_back(pontoInicial);	// Garante que a pista seja um circuito fechado
				pontosAdicionados.push_back(novoPonto);
				i = pontosDeControle.size();   //termina
			}
			else if (i % 2 == 0 && i > 0 && posicaoPontoAdicionado == 0 && i + 1 < pontosDeControle.size()) // Para os demais segmentos, adiciona um ponto colinear ao endpoint do segmento
			{
				int xloc = (pontosDeControle[i].x + pontosDeControle[i + 1].x) / 2.0;
				int yloc = (pontosDeControle[i].y + pontosDeControle[i + 1].y) / 2.0;

				Ponto novoPonto(xloc, yloc);
				pontosDeControle.insert(pontosDeControle.begin() + i + 1, novoPonto);
				pontosAdicionados.push_back(novoPonto);
				posicaoPontoAdicionado = i + 1;
			}
			else if (i - posicaoPontoAdicionado > 1 && i + 1 < pontosDeControle.size())
			{
				int xloc = (pontosDeControle[i].x + pontosDeControle[i + 1].x) / 2.0;
				int yloc = (pontosDeControle[i].y + pontosDeControle[i + 1].y) / 2.0;

				Ponto novoPonto(xloc, yloc);
				pontosDeControle.insert(pontosDeControle.begin() + i + 1, novoPonto);
				pontosAdicionados.push_back(novoPonto);
				posicaoPontoAdicionado = i + 1;
			}
		}
		smooth = true;
	}
}

/* MULTIPLICA A MATRIZ DE TRANSFORMACAO POR UM PONTO */
Ponto multiplica(float matriz[3][3], const Ponto& ponto)
{
    float soma;
    float* resultado = new float[3];
    for (int x=0; x<3;x++)
    {
        soma=0;
        for (int y=0;y<3;y++)
        {
            soma += matriz[x][y]* ponto.ponto[y];

        }
        resultado[x] = (float)soma;
    }
    Ponto ponto_resultante(resultado[0], resultado[1]);
    return ponto_resultante;
}

CanvasPista::CanvasPista(scv::Point p1, scv::Point p2, scv::Color4f bg_color) : scv::Canvas(p1, p2) {}
void CanvasPista::onMouseClick(const scv::MouseEvent &evt) {
        Ponto pontoClique(evt.getPosition().x, evt.getPosition().y);
        if (pontosDeControle.size()==0) // Se for o primeiro ponto adicionado
        {
            pontoInicial = pontoClique;
        }
		if (buttonOk == false)
		{
			pontosDeControle.push_back(pontoClique);	 // Adiciona o clique aos pontos de controle
		}
}

void CanvasPista::render(void)
{
    clear(0.2,0.5,0.2);
	drawRoad();	// Desenha estrada

	if ((pontosDeControle.size() >0 && pontosDeControle.size() <4) || buttonViewControlGraphs == true) // Antes de formar a primeira curva cubica ou viewControlGraphs ligado
	{
		viewControlGraphs();	// Mostra os pontos de controle e vetor tangente do carro
	}

	if (buttonOk == true && smooth == true) 
	{
		startAutorama();	// Inicia autorama
	}
}

/* DESENHA A ESTRADA */
void CanvasPista::drawRoad()
{
	if (pontosDeControle.size()>3)	// Se ja tem pontos para formar curva cubica
	{
		if (buttonOk == false)
		{
			for (std::vector<Ponto>::iterator it = pontosDeControle.begin(); (it) != pontosDeControle.end(); it++)	// Desenha os pontos selecionados
			{
				color(0, 0, 1);
				circleFillf(it->x, it->y, 4, 19);
			}
		}

		// Separa os pontos de controle 4 em 4 para formar segmentos de curvas cubicas:
		int iFinal = pontosDeControle.size() - 3;
		for (int i = 0; i<iFinal; i += 3)
		{
			if ((iFinal - i) <= 3)	 // Se o ultimo segmento tiver mais pontos, podera ser ate grau 5
			{
				subPontosDeControle.assign(std::next(pontosDeControle.begin(), i),pontosDeControle.end());
				first = true;
			}
			else		// Separa as curvas cubicas
			{
				subPontosDeControle.assign(std::next(pontosDeControle.begin(), i), std::next(pontosDeControle.begin(), i+3+1));
				first = true;
			}

			for (float t = 0; t < 1; t += 0.005)		// Desenha cada segmento de curva
			{
				Ponto pontoBezier = bezier(subPontosDeControle, t);

				color(0.1, 0.1, 0.1);
				circleFill(scv::Point(pontoBezier.x, pontoBezier.y), 18, 20);	// Desenha a estrada
			}
		}
	}
}

/* MOSTRA OS GRAFOS DE CONTROLE DA PISTA E TANGENTE DO CARRO */
void CanvasPista::viewControlGraphs()
{
	for (std::vector<Ponto>::iterator it = pontosDeControle.begin(); it != pontosDeControle.end(); it++)
	{
		// Desenha os pontos de controle:
		color(0, 0, 1);
		circleFill(scv::Point(it->x, it->y), 4, 19);

		// Traca as linhas entre os pontos de controle
		if ((it + 1) != pontosDeControle.end())
		{
			color(1, 0, 0);
			line(scv::Point(it->x, it->y), scv::Point((it + 1)->x, (it + 1)->y));
		}
	}

	for (int i = 0; i<pontosAdicionados.size(); i++) // Desenha os pontos adicionados para suavizar as curvas
	{
		color(1, 1, 1);
		circleFillf(pontosAdicionados[i].x, pontosAdicionados[i].y, 4, 20);
	}
}

/* DESENHA O CARRO ANDANDO SOBRE A CURVA */
void CanvasPista::startAutorama(void) {
	int iFinal = pontosDeControle.size() - 3; // posicao do ultimo segmento de curva

	if (tempo > 1.0)	// Passa para o proximo segmento de curva
	{
		tempo = 0;
		posicaoAtual += 3;
		if (posicaoAtual >= iFinal)
		{
			posicaoAtual = 0;
		}
	}

	if ((iFinal - posicaoAtual) <= 3)	// Se nao formar mais dois segmentos, o ultimo segmento sera maior
	{
		subPontosDeControle2.assign(std::next(pontosDeControle.begin(), posicaoAtual), pontosDeControle.end());
		first = true;
	}
	else		// Forma os segmentos de curvas cubicas
	{
		subPontosDeControle2.assign(std::next(pontosDeControle.begin(), posicaoAtual), std::next(pontosDeControle.begin(), posicaoAtual + 3 + 1));
		first = true;
	}

	// Calcula o bezier e a tangente
	Ponto pontoBezier = bezier(subPontosDeControle2, tempo);
	Ponto tangente = derivadaBezier(subPontosDeControle2, tempo);
	float angulo = (float)(atan((float)tangente.y / (float)tangente.x) * 180) / 3.14;

	// Define as posicoes iniciais do carro
	Ponto inferiorEsquerdo(- 10, - 4);
	Ponto inferiorDireito(10,  - 4);
	Ponto superiorEsquerdo( - 10,  4);
	Ponto superiorDireito( 10,  4);

	// Realiza as transformacoes 2D (ordem inversa)
	Matriz matriz;							// Cria matriz de transformacao
	matriz.translada(pontoBezier.x, pontoBezier.y);		// Translada para o ponto de bezier
	matriz.rotacao(angulo);			// Faz a rotacao

	// Novos pontos do carro
	Ponto novoInferiorEsquerdo = multiplica(matriz.matriz, inferiorEsquerdo);
	Ponto novoInferiorDireito = multiplica(matriz.matriz, inferiorDireito);
	Ponto novoSuperiorEsquerdo = multiplica(matriz.matriz, superiorEsquerdo);
	Ponto novoSuperiorDireito = multiplica(matriz.matriz, superiorDireito);

	// Desenha o carro apos as transformacoes
	color(1, 0, 0);
	circleFillf(pontoBezier.x, pontoBezier.y, 4, 20);
	linef(novoInferiorEsquerdo.x, novoInferiorEsquerdo.y, novoInferiorDireito.x, novoInferiorDireito.y);
	linef(novoInferiorEsquerdo.x, novoInferiorEsquerdo.y, novoSuperiorEsquerdo.x, novoSuperiorEsquerdo.y);
	linef(novoInferiorDireito.x, novoInferiorDireito.y, novoSuperiorDireito.x, novoSuperiorDireito.y);
	linef(novoSuperiorEsquerdo.x, novoSuperiorEsquerdo.y, novoSuperiorDireito.x, novoSuperiorDireito.y);

	// Ajusta a velocidade do carro:
	setSpeed();
	tempo += 0.001*speed;

	if (buttonViewControlGraphs == true) // Se viewControlGraphs == true, mostra vetor de direcao do carro
	{
		color(1, 1, 0);
		float moduloTangente = sqrt(pow(tangente.x, 2) + pow(tangente.y, 2));
		tangente.x = (tangente.x / moduloTangente);
		tangente.y = (tangente.y / moduloTangente);
		linef(pontoBezier.x, pontoBezier.y, pontoBezier.x + tangente.x * 45, pontoBezier.y + tangente.y * 45);
	}
}

void CanvasPista::setSpeed(void) {
	if (buttonAccelerate == true) // Botao para cima, aumenta a velocidade
	{
		speed += 0.5;
		buttonAccelerate = false;
	}
	else if (buttonBreak == true) // Botao para baixo, reduz a velocidade
	{
		speed -= 1;
		buttonBreak = false;
	}
	else	// Nenhum botao apertado, a velocidade diminui ate o carro parar
	{
		speed -= 0.2;
	}
	if (speed < 0)
	{
		speed = 0;
	}

	if (speed > 50) // Define a velocidade maxima
	{
		speed = 50;
	}
}

//  BOTAO OK (desenho da pista concluido)
ButtonOk::ButtonOk(scv::Point p1, scv::Point p2, std::string str) : scv::Button(p1, p2, str) {}
void ButtonOk::onMouseClick(const scv::MouseEvent &evt) {

	if (buttonOk == false) // Se ainda não foi apertado, suaviza as curvas
	{
		suavizaCurva();
		speed = 0;
		buttonOk = true;
	}
}

// BOTAO PARA APAGAR A PISTA DESENHADA
ButtonClear::ButtonClear(scv::Point p1, scv::Point p2, std::string str) : scv::Button(p1, p2, str) {}
void ButtonClear::onMouseClick(const scv::MouseEvent &evt) {
	// Apaga a pista e reseta posicoes
	pontosDeControle.clear();
	pontosAdicionados.clear();
	smooth = false;
	buttonOk = false;
	botaoClear = true;
	speed = 0;
	tempo = 0;
	posicaoAtual = 0;
}

// BOTAO PARA HABILITAR A VISUALIZACAO DOS GRAFOS DE CONTROLE
ButtonViewGraphs::ButtonViewGraphs(scv::Point p1, scv::Point p2, std::string str) : scv::Button(p1, p2, str) {}
void ButtonViewGraphs::onMouseClick(const scv::MouseEvent &evt) {
	// Habilita a visualizacao de grafos de controle
	if (buttonViewControlGraphs == true)
		buttonViewControlGraphs = false;
	else
		buttonViewControlGraphs = true;
}