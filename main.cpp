/*
CG - TRABALHO 2
JOS� AUGUSTO COMIOTTO ROTTINI - ENGENHARIA DE COMPUTACAO - UFSM

Requisitos B�sicos:


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
