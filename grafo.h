#include "trans.h"

typedef struct vertice* p_vertice;
typedef struct aresta* p_aresta;
typedef struct grafo* p_grafo;
typedef struct user *p_user;

//Estrutura de informações de um usuário
typedef struct user{
	char nome[50];
	char genero;
	unsigned int idade;
	unsigned int escolaridade;
	unsigned int cep;
	unsigned int n_interesses;
	char interesses[20][200];
	int soma_aval;
	int quant_aval;
	p_grafo_trans grafoT; //Grafo de transações pendentes
	int n_req;
	p_listaT listaT_req; //Lista de requerimentos
	p_listaT listaT_his; //Lista de histórico de transações
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

}tp_grafo;

p_grafo cria_grafo();

/*destrói grafo g*/
void destroi_grafo(p_grafo G);

/*adiciona vértice x no grafo G*/
int adiciona_usuario(p_grafo G, tp_user x);

int edita_usuario(p_user user);

/*remove vértice x do grafo G*/
int remove_usuario(p_grafo G,char *x);

/*no grafo G adiciona uma aresta de x para y*/
int adiciona_amizade(p_grafo G,char *x,char *y);

/*remove a aresta que vai de x para y*/
int remove_amizade(p_grafo G,char *x,char *y);

void imprime_grafo(p_grafo G);

int salva_grafo(p_grafo G); //salva estrutura no arquivo user.txt

p_grafo carrega_grafo(); //carrega estrutura do arquivo user.txt



/*
	FUNCOES EXTRAS
*/

int grafo_vazio(p_grafo G);

int vertice_vazio(p_vertice A);

p_vertice pesquisa_vertice (p_grafo G, char *x);

p_aresta pesquisa_aresta(p_vertice  V, char *x);

void imprime_tudo(p_grafo);
