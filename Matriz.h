#ifndef MATRIZ_H
#define MATRIZ_H


class Matriz
{
    public:
        float matriz[3][3];
        int linhas, colunas;

        Matriz();
       // void operator* (const Matriz& a);
        void rotacao(float ang);
        void translada(int tx, int ty);
        void escala(int sx, int sy);
        void print();
        virtual ~Matriz();
    protected:
    private:
        void multiplica(float matriz1[3][3], float matriz2[3][3]);
};

#endif // MATRIZ_H
