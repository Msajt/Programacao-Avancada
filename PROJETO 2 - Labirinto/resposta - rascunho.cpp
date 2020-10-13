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
