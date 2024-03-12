#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Funcoes.c"

int main(){
    limparTela();
    srand(time(NULL)); //Concerta o bug do randômico ser sempre o mesmo
    Baralho *baralho = pegaBaralhoNovo();
    Descarte *descarte = criaDescarte();
    inicializaBaralho(baralho);
    inicializaDescarte(descarte, baralho);

    Jogador *jogador = registraJogador();

    Carta card1 = popBaralho(baralho);
    Carta card2 = popBaralho(baralho);
    insereCartasNaMao(jogador->mao, &card1);
    insereCartasNaMao(jogador->mao, &card2);

    imprimeMao(jogador);
    delayNaTela(3);
    printf("Digite um numero de 1 a 10\n");
    int num = lerNumero(1, 10);
    printf("Numero recebido: %d\n", num);
}

   /*printf("Descarte:\n");
    Carta noDescarte = *descarte->topo;
    printf("1. Simbolo: %c, Cor: %c\n", noDescarte.simbolo, noDescarte.cor);

    printf("\nNo baralho:\n");
    for(int cartaAtual = 0; cartaAtual < 108; cartaAtual++){
        Carta essaCarta = popBaralho(baralho);
        printf("%d. Simbolo: %c, Cor: %c\n", cartaAtual + 1, essaCarta.simbolo, essaCarta.cor);
    }*/
