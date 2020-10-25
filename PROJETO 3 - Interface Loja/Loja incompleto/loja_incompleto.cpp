#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include <limits>
#include "loja_heranca.h"

using namespace std;

void Produto::digitar()
{
  // Leh o nomr do produto
  do
  {
    cout << "Nome: ";
    getline(cin,nome);
  } while (nome=="");
  // Leh o preco do produto
  double Pr;
  do
  {
    cout << "Preco (##.##): ";
    cin >> Pr;
  } while (Pr <= 0.0);
  cin.ignore();
  preco = (unsigned)round(100.0*Pr);
}

bool Produto::ler(istream &I)
{
  // Formato da linha no arquivo-> "STRING_AUTOR";$FLOAT_PRECO
  double Pr;

  // Ignora ateh aspa inicial
  I.ignore(numeric_limits<streamsize>::max(),'"');
  // Leh ateh a aspa final do nome do produto
  getline(I,nome,'"');
  // Ignora o ";" e o "$"
  I.ignore(numeric_limits<streamsize>::max(),'$');
  // Leh o preco como numero real
  I >> Pr;
  // Converte o preco para centavos (inteiro)
  preco = (unsigned)round(100.0*Pr);
  // Testa a leitura
  if (nome=="" || preco==0)
  {
    nome = "";
    preco = 0;
    return false;
  }
  return true;
}

void Produto::salvar(ostream &O) const
{
  // Formato da linha-> "STRING_NOME";$FLOAT_PRECO;
  O << '"' << nome << '"' << ";$" << fixed << setprecision(2) << double(preco)/100.0;
}

//
// DEFINA A CLASSE LIVRO
//

//
// DEFINA A CLASSE CD
//

//
// DEFINA A CLASSE DVD
//



//
// COMPLETE A DEFINICAO DA CLASSE LOJA
//

bool Loja::excluirLivro(unsigned id)
{
  falta_fazer();
  return true;
}

bool Loja::excluirCD(unsigned id)
{
  falta_fazer();
  return true;
}

bool Loja::excluirDVD(unsigned id)
{
  falta_fazer();
  return true;
}

void Loja::imprimir() const
{
  cout << ">> LIVROS:" << endl;
  for (unsigned i=0; i<LL.size(); i++) cout << i << ") " << LL[i] << endl;

  cout << ">> CDS:" << endl;
  for (unsigned i=0; i<LC.size(); i++) cout << i << ") " << LC[i] << endl;

  cout << ">> DVDS:" << endl;
  for (unsigned i=0; i<LD.size(); i++) cout << i << ") " << LD[i] << endl;
}

bool Loja::ler(const string& arq)
{
  ifstream I(arq.c_str());
  if (!I.is_open()) return false;

  string pS;
  unsigned NN;
  Livro L;
  CD C;
  DVD D;

  // Leh os livros
  I >> pS >> NN;
  I.ignore();
  if (pS!="LISTALIVRO")
  {
    I.close();
    return false;
  }
  LL.clear();
  for (unsigned i=0; i<NN; i++)
  {
    if (!L.ler(I))
    {
      LL.clear();
      I.close();
      return false;
    }
    LL.push_back(L);
  }

  // Leh os CDs
  I >> pS >> NN;
  I.ignore();
  if (pS!="LISTACD")
  {
    I.close();
    return false;
  }
  LC.clear();
  for (unsigned i=0; i<NN; i++)
  {
    if (!C.ler(I))
    {
      LC.clear();
      I.close();
      return false;
    }
    LC.push_back(C);
  }

  // Leh os DVDs
  I >> pS >> NN;
  I.ignore();
  if (pS!="LISTADVD")
  {
    I.close();
    return false;
  }
  LD.clear();
  for (unsigned i=0; i<NN; i++)
  {
    if (!D.ler(I))
    {
      LD.clear();
      I.close();
      return false;
    }
    LD.push_back(D);
  }

  I.close();
  return true;
}

bool Loja::salvar(const string& arq) const
{
  ofstream O(arq.c_str());
  if (!O.is_open()) return false;

  O << "LISTALIVRO " << LL.size() << endl;
  for (unsigned i=0; i<LL.size(); i++) O << LL[i] << endl;

  O << "LISTACD " << LC.size() << endl;
  for (unsigned i=0; i<LC.size(); i++) O << LC[i] << endl;

  O << "LISTADVD " << LD.size() << endl;
  for (unsigned i=0; i<LD.size(); i++) O << LD[i] << endl;

  O.close();
  return true;
}
