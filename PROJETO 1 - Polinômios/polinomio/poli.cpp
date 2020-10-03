#include <iostream>
#include <cmath>
#include "poli.h"

using namespace std;

/// ===== FUNÇÕES AUXILIARES =====
void Poly::Criar(unsigned grau){
    // Passando o tamanho
    tam = grau+1;
    // Alocando memória
    eq = (tam > 0 ? new double[tam] : nullptr);
}

void Poly::Copiar(const Poly& P){
    // Alocando memória para o array
    Criar(P.tam-1);
    // Passando os valores
    for(unsigned i=0; i<tam; i++){
        eq[i] = P.eq[i];
    }
}

void Poly::Limpar(){
    // Limpando a memoria
    if(eq != nullptr) delete[] eq;
    // Zerando as variaveis
    eq = nullptr;
    tam = 0;
}

/// ===== CONSTRUTOR ESPECÍFICO =====
Poly::Poly(unsigned grau){
    // Verifica se o grau é nulo, deve ter apenas um elemento
    if(grau == 0){
        Criar(0);
        for(unsigned i=0; i<tam; i++) eq[i] = 0.0;
    // Caso for maior, o elemento [0] deve ser igual a 1.0
    } else {
        Criar(grau);
        for(unsigned i=0; i<tam; i++) eq[i] = (i==0 ? 1.0 : 0.0);
    }
}

/// ===== SOBRECARGA DO OPERADOR ( = ) =====
void Poly::operator=(const Poly &P){
    // Evitar redundância (A=A)
    // Verificar se o 'this' (endereço) aponta pro mesmo endereço
    if(this != &P){
        // Verificar se caso seja o mesmo tamanho
        if(this->tam == P.tam){
            for(unsigned i=0; i<tam; i++) eq[i] = P.eq[i];
        } else{
            Limpar();
            Copiar(P);
        }
    }
}

/// ===== CONSULTA DE GRAU E CONSULTA DO VALOR =====
int Poly::GetGrau() const{
    int result = 0;
    result = tam-1;

    // Caso o resultado der negativo
    if(result < 0){
        cerr << "Polinomio invalido\n";
        return 0;
    }

    return result;
}

double Poly::GetElemento(unsigned elem) const{
    if(elem >= tam){
        cerr << "Indice invalido\n";
        return 0.0;
    }

    return eq[elem];
}

/// ===== /// SOBRECARGA DO OPERADOR ( [] ) -- UTILIZAR DO MÉTODO GetElemento() -- Saída =====
double Poly::operator[](unsigned elem) const{
    return GetElemento(elem);
}

/// ===== MÉTODO PARA ENCONTRAR O VALOR DO 'x' =====
double Poly::GetValor(double x) const{
    double result = 0.0;

    // Como o primeiro elemento não é seguido de 'x', então não é necessário coloca-lo no laço
    result += eq[0];
    for(unsigned i=1; i<tam; i++){
        // pow(base, expoente)
        result += eq[i] * pow(x, i);
    }

    return result;
}

/// ===== SOBRECARGA DO OPERADOR ( () ) -- UTILIZAR DO MÉTODO GetValor() -- Saída =====
double Poly::operator()(double x) const{
    return GetValor(x);
}

/// ===== MÉTODO PARA SETAR O GRAU E SETAR O VALOR =====
void Poly::SetGrau(unsigned grau){
    // Polinomio de grau = 2, tem 3 elementos

    if(tam != 0){
        // Criando um polinômio de grau 'x', que tem tamanho x+1
        Poly prov(grau);

        // Caso o polinomio for de grau nulo
        if(grau == 0){
            if(eq[0] == 0.0){
                for(unsigned i=0; i<prov.tam; i++){
                    prov.eq[i] = 0.0;
                }
            } else {
                for(unsigned i=0; i<prov.tam; i++){
                    prov.eq[i] = eq[i];
                }
            }
        } else {
            for(unsigned i=0; i<prov.tam; i++){
            // Passo os elementos que estão no polinomio original para o provisório
                if(i < tam){
                    prov.eq[i] = eq[i];
                } else {
                    prov.eq[i] = 0.0;
                }
            }
        }

        // Desalocar a memória do polinomio original
        Limpar();
        // Apontando a memória do polinomio, agora limpo, para o novo polinomio
        *this = prov;
    } else {
        Criar(grau);
    }
}

void Poly::SetElemento(unsigned elem, double valor){
    // Verificar se o elemento não ultrapassa o tamanho do polinômio
    if(elem >= tam){
        cerr << "Indice invalido\n";
    } else {
        eq[elem] = valor;
    }
}

/// ===== MÉTODOS DE ENTRADA E SAÍDA =====
istream &operator>>(istream &X, Poly &P){
    if(P.tam <= 0){
        cerr << "Polinomio invalido\n";
        //exit(0);
    } else{
        cout << "Digite os elementos do polinomio de grau " << P.GetGrau() << endl;
        for(int i=P.tam-1; i>=0; i--){
            cout << "Digite o elemento x^" << i << '\n';
            X >> P.eq[i];
        }
    }

    return X;
}

ostream &operator<<(ostream &X, const Poly &P){
    if(P.tam <= 0){
        cerr << "Polinomio invalido\n";
        exit(0);
    }
    else if(P.tam == 1){
        cout << "Polinomio de grau nulo\n";
        X << P.eq[0];
    }
    else{
        cout << "Imprimindo os elementos do polinomio de grau " << P.GetGrau() << endl;
            // O laço só pega os elementos que tem o 'x'
        for(int i=P.tam-1; i>=1; i--){
            if(P.eq[i] != 0.0){
                if(abs(P.eq[i]) == 1.0){
                    if(i == 1){
                        X << (P.eq[i] > 0.0 ? '+' : '-') << 'x';
                    } else {
                        X << (P.eq[i] > 0.0 ? '+' : '-') << "x^" << i;
                    }
                }
                else if(i == 1){
                    X << (P.eq[i] > 0.0 ? '+' : '-') << abs(P.eq[i]) << "x";
                } else {
                    X << (P.eq[i] > 0.0 ? '+' : '-') << abs(P.eq[i]) << "*x^" << i;
                }
            }
        }
            // Último elemento do polinomio
        if(P.eq[0] != 0.0) X << (P.eq[0] > 0.0 ? '+' : '-') << abs(P.eq[0]);
    }

    return X;
}

/// ===== SOBRECARGA DO OPERADOR '+' E '-' E '*' =====

Poly Poly::operator+(const Poly& P) const{
    cout << "Calculando o resultado da soma do polinomio\n";

    unsigned newGrau = (GetGrau() >= P.GetGrau() ? GetGrau() : P.GetGrau());
    Poly P1, P2, result(newGrau);

    P1 = *this;
    P2 = P;

    P1.SetGrau(newGrau);
    P2.SetGrau(newGrau);

    for(unsigned i=0; i<P1.tam; i++){
        result.eq[i] = P1.eq[i] + P2.eq[i];
    }

    cout << "=== RESULTADO DA OPERACAO - ADICAO ===" << endl;
    return result.VerificarGrau();
}

Poly Poly::operator-(const Poly& P) const{
    cout << "Calculando o resultado da subtracao do polinomio\n";

    // O grau da soma/subtração é dado pelo maior grau entre os operandos
    unsigned newGrau = (GetGrau() >= P.GetGrau() ? GetGrau() : P.GetGrau());
    Poly P1, P2, result(newGrau);

    // As variaveis auxiliares pegam os dados da entrada
    P1 = *this;
    P2 = P;

    // Aumenta o grau do polinomio para o maior grau
    P1.SetGrau(newGrau);
    P2.SetGrau(newGrau);

    for(unsigned i=0; i<P1.tam; i++){
        result.eq[i] = P1.eq[i] - P2.eq[i];
    }

    cout << "=== RESULTADO DA OPERACAO - SUBTRACAO ===" << endl;
    return result.VerificarGrau();
}

Poly Poly::operator*(const Poly& P) const{
    cout << "Calculando o resultado da multiplicacao do polinomio\n";

    // O grau máximo de uma multiplicação é dado pela soma dos grais do polinomio
    unsigned newGrau = GetGrau()+P.GetGrau();
    Poly result(newGrau);
    // Como o polinomio de grau maior que zero é terminado de 1, é feito isso para evitar problema
    result.eq[0] = 0.0;

    for(unsigned i=0; i<tam; i++){
        for(unsigned j=0; j<P.tam; j++){
            result.eq[i+j] += eq[i]*P.eq[j];
        }
    }

    cout << "=== RESULTADO DA OPERACAO - MULTIPLICACAO ===" << endl;
    return result.VerificarGrau();
}

/// ===== SOBRECARGA DO UNARIO '-' =====
Poly Poly::operator-() const{
    Poly prov(GetGrau());

    for(unsigned i=0; i<tam; i++){
        prov.eq[i] = -eq[i];
    }

    return prov;
}

/// ===== VERIFICA GRAU DO RESULTADO DAS OPERAÇÕES =====
Poly Poly::VerificarGrau(){
    // Proteção da função em caso de polinomio nulo ou polinomio de tamanho menor no resultado

    // Pegando tamanho atual do grau do polinomio
    unsigned resultGrau = GetGrau();
    // Verificando do maior grau até o ultimo se seu valor é 0, enquanto for o grau da função pode diminuir ou se manter
    while(eq[resultGrau] == 0.0){
        resultGrau--;
        // Caso o resultado dê 0 e também para evitar loop infinito da função
        if(resultGrau == 0 && eq[0] == 0.0){
            Limpar();
            *this = Poly(0);
            return *this;
        }
    }
    // Setando o novo grau se necessário
    SetGrau(resultGrau);

    return *this;
}
