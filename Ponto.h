#ifndef PONTO_H
#define PONTO_H


class Ponto
{

    public:
        float ponto [3];
        float x,y;
        Ponto(float x1, float y1);
        virtual ~Ponto();
        //int getX();
        //int getY();
        Ponto operator+=(const Ponto& ponto);
        Ponto operator+(const Ponto& ponto);
        Ponto operator-(const Ponto& ponto);
        Ponto operator*(const Ponto& ponto);
        Ponto& operator=(const Ponto& ponto);
        Ponto operator*(float num);

    protected:
    private:
};

#endif // PONTO_H
