#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include "Cabecalho.h"

#define leituraMaxima 50

#pragma region LeituraValida
int ehNumero(char *texto){
    int analisado = 0, ehNumero = 1, tamanhoTexto = strlen(texto);

    while(analisado < tamanhoTexto && analisado < leituraMaxima && ehNumero){
        if(!isdigit(texto[analisado])){
            if(texto[analisado] != '\n') ehNumero = 0;
        }
        analisado++;
    }

    if(strlen(texto) > 5) ehNumero = 0;

    return ehNumero;
}

int lerNumero(int valorMinimo, int valorMaximo){
    char texto[leituraMaxima];
    int numero = -1, ehValido = 0;

    do{
        scanf("%s", texto);

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
    system("cls || clear");
    printf(white"----------- "blue"U"yellow"N"red"O"white" -----------\n\n");
}

void delayNaTela(float segundos){
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

#pragma region Das Cartas
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
#pragma endregion

#pragma region Jogadores
MaoDoJogador *criaMao(){
    MaoDoJogador *mao = (MaoDoJogador *) malloc (sizeof(MaoDoJogador));
    mao->prim = NULL;
    return mao;
}

Jogador *registraJogador(){
    fflush(stdin);
    Jogador *jg = (Jogador *) malloc (sizeof(Jogador));
    printf("Digite o nome do novo jogador:\n");
    scanf("%[^\n]30s%\n", jg->nome);
    fflush(stdin);
    jg->mao = criaMao();
    jg->estaEmUno = 0;
    jg->qtasCartas = 0; 

    return jg;
}

void insereCartasNoJogador(Jogador *jogador, Carta *carta){
    MaoNo *novaCarta = malloc(sizeof(MaoNo));
    novaCarta->carta = carta;
    jogador->qtasCartas++;

    novaCarta->prox = jogador->mao->prim;
    jogador->mao->prim = novaCarta;
}

// nao terminei ainda :/  
/*Carta *retiraCartaDoJogador(Jogador *jogador, int posicao){
    
    // fazer o caso em que a lista possui 2, 1 e 0 elementos
    
    MaoNo *no = jogador->mao->prim;
    MaoNo *ant = NULL;
    int buscaPos = 0;
    while(no != NULL){

        if(buscaPos == posicao){
            
            Carta *card = no->carta;
            free(no);
            return card;

        }

        ant = no;
        no = no->prox;
        buscaPos++;
    }
    
    printf("A posicao %d nao esta disponivel...\n", posicao);
    return NULL;
}*/

void imprimeMaoDoJogador(Jogador *jogador){
    printf("Vez de %s... Numero de cartas: %d\n", jogador->nome, jogador->qtasCartas);  // retirar quando for criado jogadaDe

    MaoNo *maoNo;
    for(maoNo = jogador->mao->prim; maoNo != NULL; maoNo = maoNo->prox){

        char corAtual = maoNo->carta->cor;
        switch(corAtual){
            case 'r': printf(red); break;
            case 'g': printf(green); break;
            case 'b': printf(blue); break;
            case 'y': printf(yellow); break;
        }

        //Confere se não é uma carta especial e imprime valor
        char codigoDaCarta = maoNo->carta->simbolo;
        if(isdigit(codigoDaCarta)){ 
            printf("%c ", maoNo->carta->simbolo);
            printf(white);      // redefine para a cor padrao, branco
        }
        else{
            switch(codigoDaCarta){
                case 'b': printf("Bloqueio "); break;
                case 'i': printf("Inverter "); break;
                case 'd': printf("+2 "); break;
                case 'q': printf("+4 "); break;
                case 't': printf("Troca a Cor "); break;  
            }
            printf(white);      // redefine para a cor padrao, branco 
        }
        printf("\n");
    }
    printf("\n");
}
#pragma endregion

#pragma region Pessoas
// CODIGOS REFERENTES AS PESSOAS //
Pessoas *criaPessoa(){
    Pessoas *p = (Pessoas *) malloc (sizeof(Pessoas));
    p->prim = NULL;
    return p;
}

void inserePessoas(Pessoas *pessoas, Jogador *j){
    PessoasNo *novaPessoa = malloc(sizeof(PessoasNo));
    novaPessoa->jogador = j;

    if(pessoas->prim == NULL){
        novaPessoa->prox = novaPessoa;
        novaPessoa->ant = novaPessoa;
        pessoas->prim = novaPessoa;
    }
    else{
        PessoasNo *no = pessoas->prim;
        novaPessoa->prox = pessoas->prim;
        novaPessoa->ant =  pessoas->prim->ant;
        pessoas->prim->ant->prox = novaPessoa;
        pessoas->prim->ant = novaPessoa;
        pessoas->prim = novaPessoa;
    }
}

void inicializaPessoas(Pessoas *pessoas){
    int numJogadores;
    printf("Escolha a quantidade de jogadores (Minimo 2 e maximo 9):\n");
    numJogadores = lerNumero(2, 9);
    
    for(int i = 0; i < numJogadores; i++){
        Jogador *esseJogador = registraJogador();
        inserePessoas(pessoas, esseJogador);
    }
}

void reparteAsCartas(Baralho *baralho, Pessoas *pessoas){
    PessoasNo *p = pessoas->prim;
    do {
        for(int i = 0; i < 7; i++){
            Carta *essaCarta = malloc(sizeof(Carta));
            *essaCarta = popBaralho(baralho);
            printf(" Carta %d: %c %c  /  ", i, essaCarta->simbolo, essaCarta->cor);
            insereCartasNoJogador(p->jogador, essaCarta); // em todas as chamadas estao sendo registrados os valores para todos os jogadores do pessoas;
        }
        printf("\n");
    
        p = p->prox;
    } while(p != pessoas->prim);

    printf("\n\n");    
}

// funcao auxiliar, a mesma nao ira ser implementada na versao final
void imprimePessoas(Pessoas *pessoas){
    PessoasNo *p = pessoas->prim;
//    printf("Jogadores:\n");
    do {
        imprimeMaoDoJogador(p->jogador);
        p = p->prox;
    } while(p != pessoas->prim);
    printf("\n");
}
#pragma endregion
