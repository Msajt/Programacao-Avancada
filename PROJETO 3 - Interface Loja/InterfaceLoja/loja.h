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

  /// Funcoes de consulta
  inline string getNome() const {return nome;}
  inline double getPreco() const {return preco/100.0;}

  /// Funcoes de entrada/saida
  bool ler(istream &I);
  void salvar(ostream &O) const;
  void digitar();
  inline void imprimir() const {salvar(cout);}
};

inline istream& operator>>(istream &I, Produto &P) {P.digitar(); return I;}
inline ostream& operator<<(ostream &O, const Produto &P) {P.salvar(O); return O;}

class Livro: public Produto
{
private:
  string autor;
public:
  inline Livro(const string& N="", unsigned P=0, const string &A=""): Produto(N,P), autor(A) {}

  /// Funcoes de consulta
  inline string getAutor() const {return autor;}

  /// Funcoes de entrada/saida
  bool ler(istream &I);
  void salvar(ostream &O) const;
  void digitar();
  inline void imprimir() const {return salvar(cout);}
};

inline istream& operator>>(istream &I, Livro &L) {L.digitar(); return I;}
inline ostream& operator<<(ostream &O, const Livro &L) {L.salvar(O); return O;}

class CD: public Produto
{
private:
  unsigned nfaixas;
public:
  inline CD(const string& N="", unsigned P=0, unsigned NF=0): Produto(N,P), nfaixas(NF) {}

  /// Funcoes de consulta
  inline unsigned getNumFaixas() const {return nfaixas;}

  /// Funcoes de entrada/saida
  bool ler(istream &I);
  void salvar(ostream &O) const;
  void digitar();
  inline void imprimir() const {salvar(cout);}
};

inline istream& operator>>(istream &I, CD &C) {C.digitar(); return I;}
inline ostream& operator<<(ostream &O, const CD &C) {C.salvar(O); return O;}

class DVD: public Produto
{
private:
  unsigned duracao;
public:
  inline DVD(const string& N="", unsigned P=0, unsigned D=0): Produto(N,P), duracao(D) {}

  /// Funcoes de consulta
  inline unsigned getDuracao() const {return duracao;}

  /// Funcoes de entrada/saida
  bool ler(istream &I);
  void salvar(ostream &O) const;
  void digitar();
  inline void imprimir() const {salvar(cout);}
};

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

  /// Funcoes de consulta
  inline unsigned getNumLivro() const {return LL.size();}
  inline unsigned getNumCD() const {return LC.size();}
  inline unsigned getNumDVD() const {return LD.size();}
  Livro getLivro(unsigned id) const;
  CD getCD(unsigned id) const;
  DVD getDVD(unsigned id) const;

  /// Funcoes de manipulacao (inclusao/exclusao) de itens do estoque
  inline void incluirLivro(const Livro &X) {LL.push_back(X);}
  bool excluirLivro(unsigned id);
  inline void incluirCD(const CD &X) {LC.push_back(X);}
  bool excluirCD(unsigned id);
  inline void incluirDVD(const DVD &X) {LD.push_back(X);}
  bool excluirDVD(unsigned id);

  /// Funcoes de entrada/saida
  bool ler(const string& arq);
  bool salvar(const string& arq) const;
  void imprimir() const;
};
#endif // _LOJA_H_
