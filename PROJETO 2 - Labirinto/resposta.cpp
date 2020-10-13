// Tipo de dado Noh
Noh:
    pos: célula atual (posição)
    ant: célula anterior (antecessor)
    g: custo passado
    h: custo futuro

// Cria os conjuntos de Noh inicialmente vazios
Container<Noh> Aberto
Container<Noh> Fechado

// Cria o noh inicial
Noh atual;
atual.pos ← origem
atual.ant ← void()
atual.g ← 0.0
atual.h ← heurística()

// Inicializa o conjunto Aberto
inserir(atual,Aberto)

// Iteração: repita enquanto houver nohs em Aberto e ainda não houver encontrado a solução
Repita
|
| // Remove o noh de menor custo
| // (o primeiro) de Aberto
| atual ← remove_primeiro(Aberto)
|
| // insere o noh em Fechado
| inserir(atual,Fechado)
|
| // Testa se é solução
| Se ( Não(é_destino(atual)) )
| |
| | // Gera sucessores de atual
| | Para dir.lin de -1 a 1
| | Para dir.col de -1 a 1
| | Se dir ≠ (0,0)
| | |
| | | dest ← atual.pos + dir
| | |
| | | // Testa se pode mover de
| | | // atual na direção dir
| | | Se ( movVálido(atual,dest) )
| | | |
| | | | // Gera novo sucessor:
| | | | suc.pos ← dest
| | | | suc.ant ← atual.pos
| | | | suc.g ← atual.g+custo(dir)
| | | | suc.h ← heurística()
| | | |
| | | | // Procura suc em Fechado
| | | | oldF ← procura(suc,Fechado)
| | | | Se (existe(oldF))
| | | | |
| | | | | // Testa qual o melhor
| | | | | Se (suc < oldF)
| | | | | | remove(oldF,Fechado)
| | | | | | oldF ← não_existe()
| | | | | Fim Se
| | | | |
| | | | Fim Se
| | | |
| | | | // Procura suc em Aberto
| | | | oldA ← procura(suc,Aberto)
| | | | Se (existe(oldA))
| | | | |
| | | | | // Testa qual o melhor
| | | | | Se (suc < oldA)
| | | | | |
| | | | | | remove(oldA,Aberto)
| | | | | | oldA ← não_existe()
| | | | | |
| | | | | Fim Se
| | | | |
| | | | Fim Se
| | | |
| | | | // Insere suc em Aberto se
| | | | // não existe nem em Aberto
| | | | // nem em Fechado, seja pq
| | | | // não existia mesmo, seja
| | | | // pq foi removido
| | | | Se ( Não(existe(oldF)) E
| | | | | Não(existe(oldA)) )
| | | | |
| | | | | inserir_ordem(suc,Aberto)
| | | | |
| | | | Fim Se
| | | |
| | | Fim Se
| | |
| | Fim Se,Para,Para
| |
| Fim Se
|
Enquanto ( Não(é_destino(atual)) E
Não(vazio(Aberto)) )
// Imprime estado final da busca
// quer encontre ou não o caminho
// Se não encontrou caminho,
// tamanho(Aberto) deve ser 0
exibir(tamanho(Fechado))
exibir(tamanho(Aberto))
// Pode ter terminado porque
// encontrou a solução ou porque
// não há mais nohs a testar
Se ( Não(é_destino(atual)) )
|
| exibir(“Não existe caminho”)
|
Caso contrário
|
| comprimento ← atual.g
| profundidade ← 1
| Enquanto (atual.ant != origem)
| |
| | incluir_caminho(atual.ant)
| | atual ← procura(atual.ant,
| | Fechado)
| | profundidade++
| |
| Fim Enquanto
|
| // Dados do caminho encontrado
| exibir(comprimento)
| exibir(profundidade)
|
Fim Se
