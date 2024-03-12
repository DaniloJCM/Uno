typedef struct carta Carta;
typedef struct baralho Baralho;
typedef struct descarte Descarte;
typedef struct maoNo MaoNo;
typedef struct mao MaoDoJogador;
typedef struct jogador Jogador;
typedef struct listaJogadores ListaJogadores;
typedef struct pessoas Pessoas;

struct carta{
    char cor;//pode receber -> 'r': (red)vermelho, 'g': (green)verde, 'b': (blue)azul, 'y': (yellow)amarelo, 'p': preta
    char simbolo;//pode receber -> 0 a 9: números, 'b': bloqueio, 'i': inverte, 'd': +2, 'q': +4, 't': trocar a cor
    Carta *prox;
};

//1ª Pilha
struct descarte{
    Carta *topo;
};

//2ª Pilha
struct baralho{
    Carta *topo;
};

struct maoNo{
    Carta *carta;
    MaoNo *prox;
};

struct mao{
    MaoNo *prim;
};


struct jogador{
    char nome[30];
    int qtasCartas;
    int estaEmUno;
    MaoDoJogador *mao;
}; 

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