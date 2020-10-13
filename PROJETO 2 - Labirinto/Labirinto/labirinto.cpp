#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>   /* srand, rand */
#include <string>
#include <time.h>
#include <cmath>
#include <list>
#include <algorithm>

#include "labirinto.h"

using namespace std;

/* ***************** */
/* CLASSE CELULA     */
/* ***************** */

string estadoCel2string(EstadoCel E)
{
  switch(E)
  {
  case EstadoCel::LIVRE:
    return "  ";
  case EstadoCel::OBSTACULO:
    return "##";
  case EstadoCel::ORIGEM:
    return "Or";
  case EstadoCel::DESTINO:
    return "De";
  case EstadoCel::CAMINHO:
    return "..";
  default:
    break;
  }
  return "??";
}

istream& operator>>(istream& I, Coord& C)
{
  I >> C.lin >> C.col;
  return I;
}

ostream& operator<<(ostream& O, const Coord& C)
{
  O << C.lin << ';' << C.col;
  return O;
}

/* ***************** */
/* CLASSE NOH        */
/* ***************** */

ostream& operator<<(ostream& O, const Noh& N)
{
  O << '[' << N.pos << '|' << N.ant << '|'
    << N.custoTotal() << ']';
  return O;
}

// Calcula o custo futuro de um Noh ateh o destino
void Noh::heuristica(const Coord& Dest)
{
  static double sqrt2 = sqrt(2.0); // Para calcular soh uma vez

  Coord delta = abs(Dest-pos);

  // Distancia diagonal
  h = sqrt2*min(delta.lin,delta.col) +
      abs(delta.lin-delta.col);
  /*
  // Distancia Euclidiana
  h = norm(Dest-pos);
  */
}

/* ***************** */
/* CLASSE LABIRINTO  */
/* ***************** */

/// Torna o mapa vazio
void Labirinto::clear()
{
  // Esvazia o mapa de qualquer conteudo anterior
  NL = NC = 0;
  mapa.clear();
  // Apaga a origem e destino do caminho
  orig = dest = Coord();
}

/// Limpa o caminho anterior
void Labirinto::limpaCaminho()
{
  if (!empty()) for (unsigned i=0; i<NL; i++) for (unsigned j=0; j<NC; j++)
  {
    if (at(i,j) == EstadoCel::CAMINHO)
    {
      set(i,j) = EstadoCel::LIVRE;
    }
  }
}

/// Leh um mapa do arquivo nome_arq
/// Caso nao consiga ler do arquivo, cria mapa vazio
/// Retorna true em caso de leitura bem sucedida
bool Labirinto::ler(const string& nome_arq)
{
  // Limpa o mapa
  clear();

  // Abre o arquivo
  ifstream arq(nome_arq.c_str());
  if (!arq.is_open())
  {
    return false;
  }

  string prov;
  int numL, numC;
  int valor;

  // Leh o cabecalho
  arq >> prov >> numL >> numC;
  if (prov != "LABIRINTO" ||
      numL<ALTURA_MIN_MAPA || numL>ALTURA_MAX_MAPA ||
      numC<LARGURA_MIN_MAPA || numC>LARGURA_MAX_MAPA)
  {
    arq.close();
    return false;
  }

  // Redimensiona o mapa
  NL = numL;
  NC = numC;
  mapa.resize(NL*NC);

  // Leh as celulas do arquivo
  for (unsigned i=0; i<NL; i++) for (unsigned j=0; j<NC; j++)
  {
    arq >> valor;
    set(i,j) = (valor==0 ?
                EstadoCel::OBSTACULO :
                EstadoCel::LIVRE);
  }
  arq.close();
  return true;
}

/// Salva um mapa no arquivo nome_arq
/// Retorna true em caso de escrita bem sucedida
bool Labirinto::salvar(const string& nome_arq) const
{
  // Testa o mapa
  if (empty()) return false;

  // Abre o arquivo
  ofstream arq(nome_arq.c_str());
  if (!arq.is_open())
  {
    return false;
  }

  // Salva o cabecalho
  arq << "LABIRINTO " << NL << ' ' << NC << endl;

  // Salva as celulas do mapa
  for (unsigned i=0; i<NL; i++)
  {
    for (unsigned j=0; j<NC; j++)
    {
      arq << (at(i,j) == EstadoCel::OBSTACULO ? 0 : 1 ) << ' ';
    }
    arq << endl;
  }

  arq.close();
  return true;
}

/// Gera um novo mapa aleatorio
/// numL e numC sao as dimensoes do labirinto
/// perc_obst eh o percentual de casas ocupadas no mapa. Se <=0, assume um valor aleatorio
/// entre PERC_MIN_OBST e PERC_MAX_OBST
/// Se os parametros forem incorretos, gera um mapa vazio
/// Retorna true em caso de geracao bem sucedida (parametros corretos)
bool Labirinto::gerar(unsigned numL, unsigned numC, double perc_obst)
{
  // Limpa o mapa
  clear();

  // Inicializa a semente de geracao de numeros aleatorios
  srand(time(NULL));

  // Calcula o percentual de obstaculos no mapa
  if (perc_obst <= 0.0)
  {
    perc_obst = PERC_MIN_OBST +
                (PERC_MAX_OBST-PERC_MIN_OBST)*(rand()/double(RAND_MAX));
  }

  // Testa os parametros
  if (numL<ALTURA_MIN_MAPA || numL>ALTURA_MAX_MAPA ||
      numC<LARGURA_MIN_MAPA || numC>LARGURA_MAX_MAPA ||
      perc_obst<PERC_MIN_OBST || perc_obst>PERC_MAX_OBST)
  {
    return false;
  }

  // Assume as dimensoes passadas como parametro
  NL = numL;
  NC = numC;

  // Redimensiona o mapa
  mapa.resize(NL*NC);

  // Preenche o mapa
  bool obstaculo;
  for (unsigned i=0; i<NL; i++) for (unsigned j=0; j<NC; j++)
  {
    obstaculo = (rand()/double(RAND_MAX) <= perc_obst);
    set(i,j) = (obstaculo ?
                EstadoCel::OBSTACULO :
                EstadoCel::LIVRE);
  }
  return true;
}

/// Testa se uma celula eh valida dentro de um mapa
bool Labirinto::coordValida(const Coord& C) const
{
  if (!C.valida()) return false;
  if (C.lin >= int(NL)) return false;
  if (C.col >= int(NC)) return false;
  return true;
}

/// Testa se uma celula estah livre (nao eh obstaculo) em um mapa
bool Labirinto::celulaLivre(const Coord& C) const
{
  if (!coordValida(C)) return false;
  if (at(C) == EstadoCel::OBSTACULO) return false;
  return true;
}

/// Testa se um movimento Orig->Dest eh valido
bool Labirinto::movimentoValido(const Coord& Orig, const Coord& Dest) const
{
  // Soh pode mover de e para celulas livres
  if (!celulaLivre(Orig)) return false;
  if (!celulaLivre(Dest)) return false;

  // Soh pode mover para celulas vizinhas
  Coord delta=abs(Dest-Orig);
  if (delta.lin>1 || delta.col>1) return false;

  // Nao pode mover em diagonal se colidir com alguma quina
  // Se o movimento nao for diagonal, esses testes sempre dao certo,
  // pois jah testou que Orig e Dest estao livres e ou a linha ou a
  // coluna de Orig e Dest sao iguais
  if (!celulaLivre(Coord(Orig.lin,Dest.col))) return false;
  if (!celulaLivre(Coord(Dest.lin,Orig.col))) return false;

  // Movimento valido
  return true;
}

/// Fixa a origem do caminho a ser encontrado
bool Labirinto::setOrigem(const Coord& C)
{
  if (!celulaLivre(C)) return false;
  // Se for a mesma origen nao faz nada
  if (C==orig) return true;

  limpaCaminho();

  // Apaga a origem anterior no mapa, caso esteja definida
  if (coordValida(orig)) set(orig) = EstadoCel::LIVRE;

  // Fixa a nova origem
  orig = C;
  // Marca a nova origem no mapa
  set(orig) = EstadoCel::ORIGEM;

  return true;
}

/// Fixa o destino do caminho a ser encontrado
bool Labirinto::setDestino(const Coord& C)
{
  if (!celulaLivre(C)) return false;
  // Se for o mesmo destino nao faz nada
  if (C==dest) return true;

  limpaCaminho();

  // Apaga o destino anterior no mapa, caso esteja definido
  if (coordValida(dest)) set(dest) = EstadoCel::LIVRE;

  // Fixa o novo destino
  dest = C;
  // Marca o novo destino no mapa
  set(dest) = EstadoCel::DESTINO;

  return true;
}

/// Imprime o mapa no console
void Labirinto::imprimir() const
{
  if (empty())
  {
    cout << "+------------+" << endl;
    cout << "| MAPA VAZIO |" << endl;
    cout << "+------------+" << endl;
    return;
  }

  unsigned i,j;

  // Impressao do cabecalho
  cout << "    ";
  for (j=0; j<NC; j++)
  {
    cout << setfill('0') << setw(2) << j << setfill(' ') << setw(0) << ' ' ;
  }
  cout << endl;

  cout << "   +";
  for (j=0; j<NC; j++) cout << "--+" ;
  cout << endl;

  // Imprime as linhas
  for (i=0; i<NL; i++)
  {
    cout << setfill('0') << setw(2) << i << setfill(' ') << setw(0) << " |" ;
    for (j=0; j<NC; j++)
    {
      cout << estadoCel2string(at(i,j)) << '|' ;
    }
    cout << endl;

    cout << "   +";
    for (j=0; j<NC; j++) cout << "--+" ;
    cout << endl;
  }
}

/// Calcula o caminho entre a origem e o destino do labirinto usando o algoritmo A*
///
/// Retorna o comprimento do caminho (<0 se nao existe)
///
/// O parametro NC retorna o numero de nos no caminho encontrado (profundidade da busca)
/// O parametro NA retorna o numero de nos em aberto ao termino do algoritmo A*
/// O parametro NF retorna o numero de nos em fechado ao termino do algoritmo A*
/// Os 3 parametros NA, NC e NF retornam <0 caso nao exista caminho
double Labirinto::calculaCaminho(int& NC, int& NA, int& NF)
{
  if (empty() || !origDestDefinidos())
  {
    // Nao hah caminho
    NC = NA = NF = -1;
    return -1.0;
  }

  // Apaga um eventual caminho anterior
  limpaCaminho();

  // Testa se origem igual a destino
  if (orig==dest)
  {
    // Caminho tem profundidade nula
    NC = 0;
    // Algoritmo de busca nao gerou nenhum noh
    NA = NF = 0;
    // Caminho tem comprimento nulo
    return 0.0;
  }

  ////////////////////////////
  //////// FALTA FAZER ///////
  ////////////////////////////

    list<Noh> Aberto;
    list<Noh> Fechado;

    // Nó inicial
    Noh atual;
    atual.pos = getOrig();
    atual.g = 0.0;
    atual.heuristica(getOrig());

    // Inicializa o conjunto Aberto
    // inserir(atual, Aberto)
    Aberto.push_front(atual);

    // Iteração: repita enquanto houver nohs em Aberto e ainda não houver encontrado a solução
    do{
        // Remove o noh de menor custo (o primeiro) de Aberto
        atual = *Aberto.begin();
        Aberto.pop_front();
        //atual = Aberto.pop_front();

        // Insere o Noh em Fechado
        Fechado.push_front(atual);

        // Testa se é solução
        if(!(dest == atual.pos)){
            // Gera sucessores de atual
            for(int i = -1; i <= 1; i++){
                for(int j = -1; j <= 1; j++){
                    Coord direcao(i,j);
                    if(direcao != Coord(0,0)){
                        Coord dest = atual.pos + direcao;

                        // Testa se pode mover de atual na direção dir
                        if(movimentoValido(atual.pos, dest)){
                            // Gera novo sucessor:
                            Noh suc;
                            suc.pos = dest;
                            suc.ant = atual.pos;
                            atual.heuristica(dest);
                            //suc.g = atual.custoPassado() + 'custo(direcao)';
                            suc.g = atual.custoTotal();
                            //suc.heuristica(direcao);
                            suc.h = atual.custoFuturo();

                            // Procura suc em Fechado
                            list<Noh>::iterator oldF;
                            oldF = find(Fechado.begin(), Fechado.end(), suc);
                            if(oldF != Fechado.end()){
                                // Testa qual o melhor
                                if(suc < *oldF){
                                    Fechado.remove(*oldF);
                                    //oldF = 'naoExiste()'
                                    oldF = Fechado.end();
                                }
                            }
                            // Procura suc em Aberto
                            list<Noh>::iterator oldA;
                            oldA = find(Aberto.begin(), Aberto.end(), suc);
                            if(oldA != Aberto.end()){
                                // Testa qual o melhor
                                if(suc < *oldA){
                                    Aberto.remove(*oldA);
                                    //oldA = 'naoExiste()';
                                    oldA = Aberto.end();
                                }
                            }
                            // Insere suc em Aberto se não existe nem em Aberto nem em Fechado, seja pq
                            // não existia mesmo, seja pq foi removido
                            if(oldF == Fechado.end() && oldA == Aberto.end()){
                                Aberto.push_front(suc);
                                Aberto.sort();
                            }
                        }
                    }
                }
            }
        }
    } while(!(getDest() == atual.pos) && !(Aberto.empty()));

    // Imprime estado final da busca quer encontre ou não o caminho
    // Se não encontrou caminho, tamanho(Aberto) deve ser 0

    //cout << Aberto.size();
    //cout << Fechado.size();
    NA = Aberto.size();
    NF = Fechado.size();

    // Pode ter terminado porque encontrou a solução ou porque não há mais nohs a testar
    if(!(getDest() == atual.pos)){
        cout << "Não existe caminho\n";
        NA = NF = NC = -1;
        return -1.0;
    } else{
        double comprimento(atual.g);
        int profundidade(1);

        while(atual.ant != getOrig()){
            set(atual.ant) = EstadoCel::CAMINHO;
            atual = *find(Fechado.begin(), Fechado.end(), atual.ant);
            profundidade++;
        }

        // Dados do caminho encontrado
        //cout << comprimento << '\n';
        //cout << profundidade << '\n';
        NC = profundidade;
        //NA = Aberto.size();
        //NF = Fechado.size();
        return comprimento;
    }
}
