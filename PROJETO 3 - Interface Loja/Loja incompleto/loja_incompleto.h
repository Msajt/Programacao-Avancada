#ifndef _LOJA_H_
#define _LOJA_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Produto
{
private:
  string nome;
  unsigned preco;
public:
  inline Produto(const string& N="", unsigned P=0): nome(N), preco(P) {}

  bool ler(istream &I);
  void salvar(ostream &O) const;
  void digitar();
  /// Define a funcao imprimir como sendo salvar em cout
  inline void imprimir() const {salvar(cout);}
};

inline istream& operator>>(istream &I, Produto &P) {P.digitar(); return I;}
inline ostream& operator<<(ostream &O, const Produto &P) {P.salvar(O); return O;}

//
// DECLARE A CLASSE LIVRO
//

inline istream& operator>>(istream &I, Livro &L) {L.digitar(); return I;}
inline ostream& operator<<(ostream &O, const Livro &L) {L.salvar(O); return O;}

//
// DECLARE A CLASSE CD
//

inline istream& operator>>(istream &I, CD &C) {C.digitar(); return I;}
inline ostream& operator<<(ostream &O, const CD &C) {C.salvar(O); return O;}

//
// DECLARE A CLASSE DVD
//

inline istream& operator>>(istream &I, DVD &D) {D.digitar(); return I;}
inline ostream& operator<<(ostream &O, const DVD &D) {D.salvar(O); return O;}

class Loja
{
private:
  vector<Livro> LL;
  vector<CD>    LC;
  vector<DVD>   LD;
public:
  inline Loja(): LL(), LC(), LD() {}

  inline void incluirLivro(const Livro &X) {LL.push_back(X);}
  bool excluirLivro(unsigned id);
  inline void incluirCD(const CD &X) {LC.push_back(X);}
  bool excluirCD(unsigned id);
  inline void incluirDVD(const DVD &X) {LD.push_back(X);}
  bool excluirDVD(unsigned id);

  bool ler(const string& arq);
  bool salvar(const string& arq) const;
  void imprimir() const;
};
#endif // _LOJA_H_
