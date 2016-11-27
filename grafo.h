typedef struct vertice* p_vertice;
typedef struct aresta* p_aresta;
typedef struct grafo* p_grafo;
typedef struct transacao* p_transacao;

typedef struct user{
	char nome[50];
	char genero;
	unsigned int idade;
	unsigned int escolaridade;
	unsigned int cep;
	char *interesses[20];
	/*Transações*/
	int soma_aval;
	int quant_aval;
} tp_user;

typedef struct vertice
{
	tp_user usuario;

	p_vertice prox;
	p_vertice ant;

	p_aresta head;
	p_aresta ultimo;
} tp_vertice;

typedef struct aresta{
	p_vertice amigo;
	
	p_aresta ant;
	p_aresta prox;
} tp_aresta;

typedef struct grafo 
{	
	p_vertice head;
	p_vertice ultimo;

} tp_grafo;

typedef struct transacao
{
	char *trans;

	p_transacao ant;
	p_transacao prox;
} tp_transacao;

typedef struct lista_trans
{
	p_transacao head;
	p_transacao ultimo;
} tplista_transacao;

typedef enum {
	TRUE,FALSE
} boolean;

p_grafo cria_grafo();

/*destrói grafo g*/
void destroi_grafo(p_grafo G);

/*verifica se x e y sao adjacentes em G*/
boolean adjacente(p_grafo G, int x, int y);

/* retorna lista de todos os vértices que podem ser visitados a partir de x
(existe uma aresta que vai de x para este vértice)*/
void vizinhos(p_grafo G,int x);


/*adiciona vértice x no grafo G*/
boolean adiciona_usuario(p_grafo G, tp_user x);


/*remove vértice x do grafo G*/
boolean remove_usuario(p_grafo G,char *x);

/*no grafo G adiciona uma aresta de x para y*/
boolean adiciona_amizade(p_grafo G,char *x,char *y);

/*remove a aresta que vai de x para y*/
boolean remove_amizade(p_grafo G,char *x,char *y);

boolean imprime_grafo(p_grafo G);

boolean salva_grafo(p_grafo G);

p_grafo carrega_grafo();



/*
	FUNCOES EXTRAS
*/

boolean grafo_vazio(p_grafo G);

boolean vertice_vazio(p_vertice A);

p_vertice pesquisa_vertice (p_grafo G, char *x);

p_aresta pesquisa_aresta(p_vertice  V, char *x);

/*
	FUNCOES TRANSA
*/

p_transacao cria_lista_trans();



void imprime_transacoes();

boolean cadastra_transacao();

boolean remove_transacao();

p_transacao pesquisa_transacao();

p_transacao carrega_transacao();

boolean salva_transacao();

