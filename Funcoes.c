#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "Cabecalho.h"

#pragma region Leitura válida
int ehNumero(char *texto){
    int analisado = 0, ehNumero = 1, tamanhoTexto = strlen(texto);

    while(analisado < tamanhoTexto && analisado < 50 && ehNumero){
        if(!isdigit(texto[analisado]) && texto[analisado] != '\n') ehNumero = 0;
        analisado++;
    }
    if(strlen(texto) > 5) ehNumero = 0;

    return ehNumero;
}

int lerNumero(int valorMinimo, int valorMaximo){
    char texto[50];
    int numero = -1;

    do{
        scanf("%50s", texto);

        if(ehNumero(texto)){
            numero = 0;
            for(int casa = 0; casa < strlen(texto); casa++) numero = (numero * 10) + (texto[casa] - '0');

            if(numero < valorMinimo || numero > valorMaximo){
                printf("O numero %d nao eh valido! Tente novamente:\n", numero);
                numero = -1;
            }
        }
        else printf("Voce nao escreveu um numero! Tente novamente:\n");
    } while(numero < 0);

    return numero;
}
#pragma endregion

#pragma region Console
void limparTela(){
    system("cls||clear");
    printf("----------UNO----------\n");
}

void delayNaTela(int segundos){
    sleep(segundos);
    limparTela();
}
#pragma endregion

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

#pragma region Relacionados baraho
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
#pragma endregion

#pragma region Mao dos jogadores
MaoDoJogador *criaMao(){
    MaoDoJogador *mao = (MaoDoJogador *) malloc (sizeof(MaoDoJogador));
    mao->prim = NULL;
    return mao;
}

void insereCartasNaMao(MaoDoJogador *mao, Carta *carta){
    MaoNo *novaCarta = malloc(sizeof(MaoNo));
    novaCarta->carta = carta;

    novaCarta->prox = mao->prim;
    mao->prim = novaCarta;
}

void imprimeMao(Jogador *jogador){
    int carta = 1;
    printf("O jogador %s esta com:\n", jogador->nome);

    MaoNo *no;
    for(no = jogador->mao->prim; no != NULL; no = no->prox){
        printf("Carta %d. /%c - %c/\n", carta, no->carta->cor, no->carta->simbolo);
        carta++;
    }
    printf("\n");

}

Jogador *registraJogador(){
    Jogador *jg = (Jogador *) malloc (sizeof(Jogador));
    printf("Insira seu nome:\n");
    scanf("%30s", jg->nome);
    fflush(stdin);
    jg->mao = criaMao();
    jg->estaEmUno = 0;
    jg->qtasCartas = 0; 

    return jg;
}
#pragma endregion
