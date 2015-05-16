/*
CG - TRABALHO 2
JOSÉ AUGUSTO COMIOTTO ROTTINI - ENGENHARIA DE COMPUTACAO - UFSM

Cria a aplicacao e adiciona os widgets. Trata os eventos do teclado.

*/

#include "Application.h"
#include <iostream>

bool buttonAccelerate = false;
bool buttonBreak = false;

Application::Application(void) : Kernel() {
   setWindowSize(1300, 720);
   lockWindowSize(false);
   setFramesPerSecond(60);

   setWindowTitle("Trabalho 2 CG - Curvas: Bezier e B-Spline");
}

Application::~Application(void) {}
void Application::init(void) {
   _mainPanel = new scv::Panel(scv::Point(0, 0), scv::Point(1300, 720));

   addComponent(_mainPanel);

   CanvasPista *canvasPista = new CanvasPista(scv::Point(10, 10), scv::Point(1290, 600), scv::Color4f(.2f, .5f, .2f));
   addComponent(canvasPista);

   ButtonOk *buttonOk = new ButtonOk(scv::Point(200,620), scv::Point(250, 650), "OK");
   addComponent(buttonOk);

   ButtonClear *buttonClear = new ButtonClear(scv::Point(300, 620), scv::Point(380, 650), "Clear Road");
   addComponent(buttonClear);

   ButtonViewGraphs *buttonViewGraphs = new ButtonViewGraphs(scv::Point(410, 620), scv::Point(540, 650), "View Control Graphs");
   addComponent(buttonViewGraphs);
}

void Application::onKey(const scv::KeyEvent &evt) { // Trata os eventos do teclado
	if (evt.keycode == 265)
		buttonAccelerate = true;
	else if (evt.keycode == 264)
		buttonBreak = true;
}

void Application::onSizeChange(void) {
   _mainPanel->setSize(getWidth(), getHeight());
}

