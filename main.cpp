/*
CG - TRABALHO 2
JOS� AUGUSTO COMIOTTO ROTTINI - ENGENHARIA DE COMPUTACAO - UFSM

REQUISITOS M�NIMOS: TODOS
- Implementa��o de curvas
- Continuidade C1
- Pista � um circuito fechado
- Usu�rio gera a pista utilizando o mouse
- Carro anda sobre a pista usando transforma��es
- Permitir que o usu�rio visualize os grafos de controle e vetor dire��o do carro

EXTRAS:
- Utiliza��o de curvas de Bezier
- Estrada com largura

*/

#include <SCV/SCV.h>
#include "Application.h"

int main(int argc, char* argv[]) {
   Application *kernel = new Application();
   scv::Kernel::setInstance(kernel);

   kernel->init();

   kernel->run();
   return 0;
}
