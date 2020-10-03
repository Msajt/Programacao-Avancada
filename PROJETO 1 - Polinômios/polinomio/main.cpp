#include <iostream>
#include <cmath>
#include <cstring>
#include "poli.h"
using namespace std;

int main(void){
  Poly P1(1), P2(0), result(P2);
  double x;
  unsigned grau;
  char opcao;

  cout << "CALCULADORA DE POLINOMIOS\n";
  do{
    do{
      cout << endl;
      cout << "P1: " << P1 << endl;
      cout << "P2: " << P2 << endl;
      cout << "Digite sua opcao:\n";
      cout << "< - Entrar um novo polinomio\n";
      cout << "+ - Somar os polinomios\n";
      cout << "- - Subtrair os polinomios\n";
      cout << "* - Multiplicar os polinomios\n";
      cout << "x - Calcular o ultimo polinomio para um valor de x\n";
      cout << "i - Inverter o sinal do ultimo polinomio\n";
      cout << "t - Trocar os polinomios\n";
      cout << "q - Terminar\n";
      cin >> opcao;
      opcao = tolower(opcao);
    } while (strchr("<+-*/%xitq",opcao)==NULL);

    switch(opcao){
    case '<':
      do{
        cout << "Grau do polinomio: "  ;
        cin >> grau;
      } while (grau<0);
      result = Poly(grau);
      cout << "Coeficientes do polinomio:\n";
      cin >> result;
      break;
    case '+':
      result = P1+P2;
      break;
    case '-':
      result = P1-P2;
      break;
    case '*':
      result = P1*P2;
      break;
    case 'x':
      cout << "Valor de x: ";
      cin >> x;
      cout << "P2(x) = " << P2(x) << endl;
      break;
    case 'i':
      P2 = -P2;
      break;
    case 't':
      result = P1;
      P1 = P2;
      P2 = result;
      break;
    case 'q':
      break;
    default:
      cerr << "Opcao desconhecida\n";
      result = Poly();
      break;
    }
    if (strchr("<+-*",opcao)!=NULL){
      cout << "Resultado: " << result << endl;
      P1 = P2;
      P2 = result;
    }
  } while (opcao != 'q');
}

