typedef struct listaJogadores ListaJogadores;
typedef struct pessoas Pessoas;

typedef struct carta{
    char cor;//pode receber -> 'r': (red)vermelho, 'g': (green)verde, 'b': (blue)azul, 'y': (yellow)amarelo, 'p': preta
    char simbolo;//pode receber -> 0 a 9: números, 'b': bloqueio, 'i': inverte, 'd': +2, 'q': +4, 't': trocar a cor
    struct carta *prox;
} Carta;

//1ª Pilha
typedef struct descarte{
    Carta *topo;
} Descarte;

//2ª Pilha
typedef struct baralho{
    Carta *topo;
} Baralho;

typedef struct maoNo{
    Carta *carta;
    struct maoNo *prox;
} MaoNo;

typedef struct mao{
    MaoNo *prim;
} MaoDoJogador;


typedef struct jogador{
    char nome[30];
    int qtasCartas;
    int estaEmUno;
    MaoDoJogador *mao;
} Jogador; 

//Protótipos funções
Baralho* pegaBaralhoNovo();

Descarte* criaDescarte();

void inserirCartaNoBaralho(Baralho *b, Carta *c);

void inicializaBaralho(Baralho *b);

Carta popBaralho(Baralho *esse);

void inicializaDescarte(Descarte *d, Baralho *b);

void insereCartasNaMao(MaoDoJogador *mao, Carta *carta);

void imprimeMao(Jogador *jogador);

Jogador* registraJogador();
