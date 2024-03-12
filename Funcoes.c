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


// CODIGOS REFERENTES A MAO DOS JOGADORES // 
MaoDoJogador *criaMao(){
    MaoDoJogador *mao = (MaoDoJogador *) malloc (sizeof(MaoDoJogador));
    mao->prim = NULL;
    return mao;
}

void insereCartasNaMao(MaoDoJogador *mao, Carta *carta){
    MaoNo *novaCarta = malloc(sizeof(MaoNo));
    novaCarta->carta = carta;
   // printf("%c - %c\n", carta->simbolo, carta->cor);

    novaCarta->prox = mao->prim;
    mao->prim = novaCarta;
}

void imprimeMao(MaoDoJogador *mao){
    MaoNo *no;
    for(no = mao->prim; no != NULL; no = no->prox){
        printf("/ %c - %c  /  ", no->carta->cor, no->carta->simbolo);
    }
    printf("\n");
}

/*Jogador* registraJogador(){

}*/