#include <iostream>
#include <cmath>
using namespace std;

class Poly{
private:
    /// VARIÁVEIS -- OK
    double *eq;
    unsigned tam;

    /// FUNÇÕES AUXILIARES (CRIAR E COPIAR) -- OK
    void Criar(unsigned grau);
    void Copiar(const Poly &P);

public:
    /// CONSTRUTORES -- OK
        // Default
        inline Poly(): eq(nullptr), tam(0) {}
        // Copia
        inline Poly(const Poly &P) { Copiar(P); }
        // Especifico
        explicit Poly(unsigned grau);

    /// FUNÇÃO AUXILIAR (LIMPAR) -- OK
    void Limpar();

    /// DESTRUTOR -- OK
        ~Poly() { Limpar(); }

    /// SOBRECARGA DO OPERADOR ( = ) -- OK
        void operator=(const Poly &P);

    /// CONSULTA DE GRAU E CONSULTA DO VALOR -- OK
        int GetGrau() const;
        double GetElemento(unsigned elem) const;

    /// SOBRECARGA DO OPERADOR ( [] ) -- UTILIZAR DO MÉTODO GetElemento() -- Saída -- OK
        double operator[](unsigned elem) const;

    /// MÉTODO PARA ENCONTRAR O VALOR DO 'x' -- OK
        double GetValor(double x) const;

    /// SOBRECARGA DO OPERADOR ( () ) -- UTILIZAR DO MÉTODO GetValor() -- Saída -- OK
        double operator()(double x) const;

    /// MÉTODO PARA SETAR O GRAU E SETAR O VALOR
        void SetGrau(unsigned grau);
        void SetElemento(unsigned elem, double valor);

    /// MÉTODOS DE ENTRADA E SAÍDA -- OK
        friend istream &operator>>(istream &X, Poly &P);
        friend ostream &operator<<(ostream &X, const Poly &P);

    /// SOBRECARGA DO OPERADOR '+' E '-' E '*'
        Poly operator+(const Poly &P) const;
        Poly operator-(const Poly &P) const;
        Poly operator*(const Poly &P) const;

    /// SOBRECARGA DO UNARIO '-'
        Poly operator-() const;

    /// VERIFICA GRAU
        Poly VerificarGrau();
};
