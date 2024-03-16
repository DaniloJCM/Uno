#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "Funcoes.c"

int main(){
    limparTela();
    srand(time(NULL)); //Concerta o bug do randômico ser sempre o mesmo
    Baralho *baralho = pegaBaralhoNovo();
    Descarte *descarte = criaDescarte();
    inicializaBaralho(baralho);
    inicializaDescarte(descarte, baralho);

    delayNaTela(5);
    Pessoas *pessoas = criaPessoa();
    inicializaPessoas(pessoas);
    reparteAsCartas(baralho, pessoas);
 //   imprimePessoas(pessoas);

    PessoasNo *p = pessoas->prim;
    for(int cont = 0; cont < 4; cont++){
        jogadaDe(descarte, p->jogador);
        imprimeTopoDescarte(descarte);
        p = p->prox;
    }

}
