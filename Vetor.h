#ifndef VETOR_H
#define VETOR_H
#include "Ponto.h"


class Vetor
{

    public:
        float x;
        float y;
        Vetor();
        Vetor (const Ponto& a, const Ponto& b);
        void normaliza();
        virtual ~Vetor();
    protected:
    private:
};

#endif // VETOR_H
