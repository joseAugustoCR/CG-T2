/*
CG - TRABALHO 2
JOSÉ AUGUSTO COMIOTTO ROTTINI - ENGENHARIA DE COMPUTACAO - UFSM

Definicao dos widgets.

*/

#ifndef __WIDGET_H__
#define __WIDGET_H__

#include <SCV/SCV.h>

extern float speed;

class CanvasPista : public scv::Canvas {		// CANVAS
public:
	CanvasPista(scv::Point p1, scv::Point p2, scv::Color4f color);

   virtual void onMouseClick(const scv::MouseEvent &evt);
   void drawRoad();
   void viewControlGraphs();
   void startAutorama();
   void setSpeed();
   virtual void render(void);
   void setBackground(const scv::Color4f& color) { bg_color = color; }

private:
   scv::Color4f bg_color; // Cor do fundo
};

class ButtonOk : public scv::Button {				// BOTAO OK
private:
public:
	ButtonOk(scv::Point p1, scv::Point p2, std::string str);

	virtual void onMouseClick(const scv::MouseEvent &evt);
};

class ButtonClear : public scv::Button {		// BOTAO CLEAR
private:
public:
	ButtonClear(scv::Point p1, scv::Point p2, std::string str);

	virtual void onMouseClick(const scv::MouseEvent &evt);
};

class ButtonViewGraphs : public scv::Button {	// BOTAO VIEW GRAPHS
private:
public:
	ButtonViewGraphs(scv::Point p1, scv::Point p2, std::string str);

	virtual void onMouseClick(const scv::MouseEvent &evt);
};

#endif
