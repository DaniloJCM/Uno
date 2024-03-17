#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include "Cabecalho.h"

#define leituraMaxima 50


int corTrocada = 0;

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

void imprimeCarta(Carta *carta){
    char corAtual = carta->cor;
    switch(corAtual){
        case 'r': printf(red); break;
        case 'g': printf(green); break;
        case 'b': printf(blue); break;
        case 'y': printf(yellow); break;
    }

    //Confere se não é uma carta especial e imprime valor
    char codigoDaCarta = carta->simbolo;
    if(isdigit(codigoDaCarta)){ 
        printf("%c ", carta->simbolo);
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


Carta *olharCartaDoJogador(Jogador *jog, int posicao){
    MaoNo *no = jog->mao->prim;
    int buscaPos = 1;
    while(buscaPos != posicao && no != NULL){
        no = no->prox;
        buscaPos++;
    }
    return no->carta;
}

Carta *retiraCartaDoJogador(Jogador *jogador, int posicao){
    if(posicao > 0 && posicao <= jogador->qtasCartas){  // retirar quando for criada a funcao posicaoValida
        if(jogador->mao->prim == NULL){
            printf("iiihh nao pra essa mensagem ser mostrada hein, parece que o jogador nao posssui nenhuma carta\n");
            exit(1);
        }
        else if(jogador->mao->prim->prox == NULL){
            if(posicao != 1){  // retirar quando for criada a funcao posicaoValida
                printf("Posicao nao disponivel, digite novamente\n");
                return NULL;
            }
            else{ 
                jogador->qtasCartas--;
                printf("---- Numero de cartas %d ----\n", jogador->qtasCartas);  // converter o a mensagem de ganhou numa funcao
                printf("%s ganhou !!!\n", jogador->nome);
                Carta *card = jogador->mao->prim->carta;
                free(jogador->mao->prim);
                return card;
            }
        }
        else{ 
            MaoNo *no = jogador->mao->prim;

            if(posicao == 1){
                jogador->mao->prim = no->prox;
                Carta *card = no->carta;
                jogador->qtasCartas--;
                free(no); 
                return card;
            }
            else{
                MaoNo *ant = NULL;
                int buscaPos = 1;
                while(no != NULL){
                    if(buscaPos == posicao){
                        ant->prox = no->prox;
                        Carta *card = no->carta;
                        jogador->qtasCartas--;
                        free(no);
                        return card;

                    }
                    ant = no;
                    no = no->prox;
                    buscaPos++;
                }
            }
        }
    }
    else{ 
        printf("A posicao %d nao esta disponivel...\n", posicao);
        return jogador->mao->prim->carta;
    }
}

void imprimeMaoDoJogador(Jogador *jogador){
    MaoNo *maoNo;
    int posicao = 1;
    for(maoNo = jogador->mao->prim; maoNo != NULL; maoNo = maoNo->prox){
        printf("%d - ", posicao);
        imprimeCarta(maoNo->carta);
        posicao++;
    }
    printf("%d - Comprar uma carta\n",jogador->qtasCartas + 1);
    printf("%d - Dizer Uno!", jogador->qtasCartas + 2);
    printf("\n\n");
}
#pragma endregion

#pragma region Pessoas
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
            insereCartasNoJogador(p->jogador, essaCarta); // em todas as chamadas estao sendo registrados os valores para todos os jogadores do pessoas;
        }
        printf("\n");
    
        p = p->prox;
    } while(p != pessoas->prim);

    printf("\n\n");    
}


// Jogo
void jogadaDe(Descarte *descarte, Jogador *jog){

    printf("Vez de %s... Numero de cartas: %d\n", jog->nome, jog->qtasCartas);
    imprimeMaoDoJogador(jog);
    imprimeTopoDescarte(descarte);  
    /*if(corTrocada == 1){    // caso seja usado um trocaCor, o descarte vai ser impresso com a cor definida na funcao  
        printf(white);      // por isso a cor depois da impressao eh redefinida para branca
//        corTrocada = 0;
    }*/
    printf("\nSelecione a posicao da acao que voce quer fazer:\n(NAO ESCREVA O NUMERO DA CARTA, ESCREVA O NUMERO DA POSICAO)\n");
   

    int posicao = lerNumero(1, jog->qtasCartas);
    Carta *card = olharCartaDoJogador(jog, posicao);

    while(!cartaPodeSerJogada(card, descarte)){ 
        printf("Carta nao compativel com o descarte...\nEscolha outra carta ou compre uma no descarte\n");
        posicao = lerNumero(1, jog->qtasCartas);
        card = olharCartaDoJogador(jog, posicao); 
    }


    Carta *cartaDescartada = retiraCartaDoJogador(jog, posicao);
    pushDescarte(descarte, cartaDescartada);

    printf("A mao do jogador %s ficou assim:\n", jog->nome);
    imprimeMaoDoJogador(jog);
}


int cartaPodeSerJogada(Carta *c, Descarte *descarte){
    int podeJogar;
//    if(descarte->topo->simbolo == 'p'){
//        trocaCor(c);
//    }
    if((c->simbolo == descarte->topo->simbolo || c->cor == descarte->topo->cor) || (c->cor == 'p')){
        podeJogar = 1;
    }
    else{
        podeJogar = 0;
    }
    return podeJogar;
}

void imprimeTopoDescarte(Descarte *d){
    printf("Este eh o descarte atual:\n");
    imprimeCarta(d->topo);
    printf("\n\n");
}

/*void trocaCor(Carta *c){
    int qualEscolhida;
    printf("\nPara qual cor voce deseja trocar?\n");
    printf(red  "1 - Vermelho\n" green "2 - Verde\n" blue "3 - Azul\n" yellow "4 - Amarelo\n");
    printf (white);
    printf("\nQual dessas cores voce ira escolher?\n");

    qualEscolhida = lerNumero(1, 4);

    printf("\nA cor escolhida foi a cor ");
    if(qualEscolhida == 1) printf(red "Vermelha!");
    else if(qualEscolhida == 2) printf(green "Verde!");
    else if(qualEscolhida == 3) printf(blue "Azul!");
    else printf(yellow "Amarela!");

    corTrocada = 1;

    printf("\n");

}*/


// funcao auxiliar, a mesma nao ira ser implementada na versao final
void imprimePessoas(Pessoas *pessoas){
    PessoasNo *p = pessoas->prim;
    do {
        imprimeMaoDoJogador(p->jogador);
        p = p->prox;
    } while(p != pessoas->prim);
    printf("\n");
}
#pragma endregion
