#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Funcoes.c"

int main(){
    srand(time(NULL)); //Concerta o bug do randômico ser sempre o mesmo
    Baralho *baralho = pegaBaralhoNovo();
    Descarte *descarte = criaDescarte();
    inicializaBaralho(baralho);
    inicializaDescarte(descarte, baralho);

    Pessoas *persons = criaPessoa();

    Jogador *jogador = registraJogador();

    Carta card1 = popBaralho(baralho);
    Carta card2 = popBaralho(baralho);
    insereCartasNoJogador(jogador, &card1);
    insereCartasNoJogador(jogador, &card2);

    Jogador *jogador2 = registraJogador();

    Carta card3 = popBaralho(baralho);
    Carta card4 = popBaralho(baralho);
    insereCartasNoJogador(jogador2, &card1);
    insereCartasNoJogador(jogador2, &card2);

    Jogador *jogador3 = registraJogador();

    Carta card5 = popBaralho(baralho);
    Carta card6 = popBaralho(baralho);
    insereCartasNoJogador(jogador3, &card1);
    insereCartasNoJogador(jogador3, &card2);

    inserePessoas(persons, jogador);
    inserePessoas(persons, jogador2);
    inserePessoas(persons, jogador3);

    imprimePessoas(persons);

    Pessoas *lixo = persons;
    persons = inverte(persons);
    free(lixo);

    imprimePessoas(persons);
}

   /*printf("Descarte:\n");
    Carta noDescarte = *descarte->topo;
    printf("1. Simbolo: %c, Cor: %c\n", noDescarte.simbolo, noDescarte.cor);

    printf("\nNo baralho:\n");
    for(int cartaAtual = 0; cartaAtual < 108; cartaAtual++){
        Carta essaCarta = popBaralho(baralho);
        printf("%d. Simbolo: %c, Cor: %c\n", cartaAtual + 1, essaCarta.simbolo, essaCarta.cor);
    }*/