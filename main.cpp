/*
CG - TRABALHO 2
JOSÉ AUGUSTO COMIOTTO ROTTINI - ENGENHARIA DE COMPUTACAO - UFSM

REQUISITOS MÍNIMOS: TODOS
- Implementação de curvas
- Continuidade C1
- Pista é um circuito fechado
- Usuário gera a pista utilizando o mouse
- Carro anda sobre a pista usando transformações
- Permitir que o usuário visualize os grafos de controle e vetor direção do carro

EXTRAS:
- Utilização de curvas de Bezier
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
