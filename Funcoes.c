#include <stdio.h>
#include <stdlib.h>

#include "Cabecalho.h"

#pragma region Cria objetos
Baralho* pegaBaralhoNovo(){
    //Cria o baralho a ser modificado
    Baralho *esseBaralho = malloc(sizeof(Baralho));
    if(!esseBaralho) printf("Sem armazenamento suficiente!\n"), exit(1);

    esseBaralho->topo = NULL;
    return esseBaralho;
}

Descarte* criaDescarte(){
    //Cria o descarte
    Descarte *esseDescarte = malloc(sizeof(Descarte));
    if(!esseDescarte) printf("Sem armazenamento suficiente!\n"), exit(1);

    esseDescarte->topo = NULL;
    return esseDescarte;
}

Carta* criaCarta(char simbolo, char cor){
    //Cria a carta com o símbolo e cores especificados
    Carta *essaCarta = malloc(sizeof(Carta));
    if(!essaCarta) printf("Sem armazenamento suficiente!\n"), exit(1);

    essaCarta->cor = cor;
    essaCarta->simbolo = simbolo;
    essaCarta->prox = NULL; 

    return essaCarta;
}
#pragma endregion

#pragma region Push e Pop do Baralho e Descarte
void pushBaralho(Baralho *esseBaralho, Carta *essaCarta){
    if(esseBaralho->topo != NULL) essaCarta->prox = esseBaralho->topo;
    else essaCarta->prox = NULL;
    esseBaralho->topo = essaCarta;
}

Carta popBaralho(Baralho *esse){
    Carta *remover = esse->topo;
    Carta final = *remover;

    if(esse->topo->prox) esse->topo = esse->topo->prox;
    else esse->topo = NULL;

    free(remover);
    return final;
}

void pushDescarte(Descarte *oDescarte, Carta *essaCarta){
    if(oDescarte->topo != NULL) essaCarta->prox = oDescarte->topo;
    else essaCarta->prox = NULL;
    oDescarte->topo = essaCarta;
}

Carta popDescarte(Descarte *esse){
    Carta *remover = esse->topo;
    Carta final = *remover;

    if(esse->topo->prox) esse->topo = esse->topo->prox;
    else esse->topo = NULL;

    free(remover);
    return final;
}
#pragma endregion

void embaralharQuantasVezes(Baralho *b, int max, int vezes){
    if(b->topo){
        vezes *= max;

        for(int vez = 0; vez < vezes; vez++){
            Carta *carta1 = b->topo, *carta2 = b->topo;
            int rand1, rand2;

            do{//Impede de dois números sorteados serem iguais
                rand1 = rand() % max;
                rand2 = rand() % max;
            } while(rand1 == rand2);

            for(int qualCarta = 0; qualCarta < rand1 && carta1 != NULL; qualCarta++, carta1 = carta1->prox);
            for(int qualCarta = 0; qualCarta < rand2 && carta2 != NULL; qualCarta++, carta2 = carta2->prox);

            char cor1 = carta1->cor, simbolo1 = carta1->simbolo;
            carta1->cor = carta2->cor;
            carta1->simbolo = carta2->simbolo;

            carta2->cor = cor1;
            carta2->simbolo = simbolo1;
        }

        printf("Embaralhado!\n");
    }
    else printf("Nao eh possivel embaralhar! Baralho vazio!\n");
}

void criaEInsereCartaNoBaralho(Baralho *b, char simbolo, char cor){
    Carta *essaCarta = criaCarta(simbolo, cor);
    pushBaralho(b, essaCarta);
}

void inicializaBaralho(Baralho *b){
    printf("Inicializando baralho!\n");

    int qualCarta;
    char corAtual[4] = {'r', 'g', 'b', 'y'};

    b->topo = NULL;
    for(int qualCor = 0; qualCor < 4; qualCor++){
        //Só existe um '0' de cada cor no baralho de UNO
        criaEInsereCartaNoBaralho(b, '0', corAtual[qualCor]);

        for(int numero = 1; numero <= 9; numero++){
            for(int vez = 0; vez < 2; vez++) criaEInsereCartaNoBaralho(b, numero + '0', corAtual[qualCor]);
        }

        for(int vez = 0; vez < 2; vez++){
            criaEInsereCartaNoBaralho(b, 'b', corAtual[qualCor]);
            criaEInsereCartaNoBaralho(b, 'i', corAtual[qualCor]);
            criaEInsereCartaNoBaralho(b, 'd', corAtual[qualCor]);
        }
    }

    for(int vezes = 0; vezes < 4; vezes++){
        criaEInsereCartaNoBaralho(b, 'q', 'p');
        criaEInsereCartaNoBaralho(b, 't', 'p');
    }

    embaralharQuantasVezes(b, 108, 10);
}

void inicializaDescarte(Descarte *d, Baralho *b){
    Carta *essaCarta = b->topo;
    b->topo = b->topo->prox;

    pushDescarte(d, essaCarta);
}


// CODIGOS REFERENTES AOS JOGADORES // 
MaoDoJogador *criaMao(){
    MaoDoJogador *mao = (MaoDoJogador *) malloc (sizeof(MaoDoJogador));
    mao->prim = NULL;
    return mao;
}

void insereCartasNoJogador(Jogador *jogador, Carta *carta){
    MaoNo *novaCarta = malloc(sizeof(MaoNo));
    novaCarta->carta = carta;

    novaCarta->prox = jogador->mao->prim;
    jogador->mao->prim = novaCarta;
}

void imprimeMao(Jogador *jogador){
//    printf("O jogador: %s esta com\n", jogador->nome);

    MaoNo *maoNo;
    for(maoNo = jogador->mao->prim; maoNo != NULL; maoNo = maoNo->prox){
        printf("/ %c - %c  /  ", maoNo->carta->cor, maoNo->carta->simbolo);
    }
    printf("\n");
}

Jogador *registraJogador(){
    Jogador *jg = (Jogador *) malloc (sizeof(Jogador));
    scanf("%s", jg->nome);
    jg->mao = criaMao();
    jg->estaEmUno = 0;
    jg->qtasCartas = 0; 

    return jg;
}


// CODIGOS REFERENTES AS PESSOAS //

Pessoas *criaPessoa(){
    Pessoas *p = (Pessoas *) malloc (sizeof(Pessoas));
    p->prim = NULL;
    return p;
}

void inserePessoas(Pessoas *pessoa, Jogador *j){
    PessoasNo *novaPessoa = malloc(sizeof(PessoasNo));
    novaPessoa->jogador = j;

    if(pessoa->prim == NULL){
        novaPessoa->prox = novaPessoa;
        novaPessoa->ant = novaPessoa;
        pessoa->prim = novaPessoa;
    }
    else{
        PessoasNo *no = pessoa->prim;
        novaPessoa->prox = pessoa->prim;
        novaPessoa->ant =  pessoa->prim->ant;
        pessoa->prim->ant->prox = novaPessoa;
        pessoa->prim->ant = novaPessoa;
        pessoa->prim = novaPessoa;
    }
}

void inicializaPessoas(Pessoas *pessoas){
    int numJogadores;
    printf("Escolha a quantidade de jogadores: ");
    scanf("%d", &numJogadores);
    
    Jogador *jogador[numJogadores];
    for(int i = 0; i < numJogadores; i++){
        jogador[i] = registraJogador();
        inserePessoas(pessoas, jogador[i]);
    }
}

void reparteAsCartas(Baralho *baralho, Pessoas *pessoa){
    PessoasNo *p = pessoa->prim;
    Carta *carta = (Carta *) malloc (7 * sizeof(Carta));
    do {
        for(int i = 0; i < 7; i++){
            carta[i] = popBaralho(baralho);
            printf(" Carta %d: %c %c  /  ", i, carta[i].simbolo, carta[i].cor);
            insereCartasNoJogador(p->jogador, &carta[i]); // em todas as chamadas estao sendo registrados os valores para todos os jogadores do pessoas;
        }
        printf("\n");
    
        imprimeMao(p->jogador);
        printf("\n");
        p = p->prox;

    } while(p != pessoa->prim);

    printf("\n\n");    
}

// funcao auxiliar, a mesma nao ira ser implementada na versao final
void imprimePessoas(Pessoas *pessoas){
    PessoasNo *p = pessoas->prim;
//    printf("Jogadores:\n");
    do {
        imprimeMao(p->jogador);
        p = p->prox;
    } while(p != pessoas->prim);
    printf("\n");
}
