
typedef struct transacao* p_transacao;
typedef struct lista_trans* p_listatrans;
typedef struct grafo_trans* p_grafo_trans;
typedef struct verticeT* p_verticeT;
typedef struct arestaT* p_arestaT;
typedef struct noT* p_noT;
typedef struct listaT* p_listaT;


typedef struct transacao
{
	char trans[50];

	p_transacao ant;
	p_transacao prox;
} tp_transacao;

typedef struct lista_trans
{
	p_transacao head;
	p_transacao ultimo;
} tp_listatrans;

/*GRAFO*/
typedef struct verticeT
{
	char trans[50];

	p_verticeT prox;
	p_verticeT ant;

	p_arestaT head;
	p_arestaT ultimo;

}tp_verticeT;

typedef struct arestaT
{
	char pessoa[50];

	p_arestaT prox;
	p_arestaT ant;


}tp_arestaT;

typedef struct grafo_trans 
{	
	p_verticeT head;
	p_verticeT ultimo;

}tp_grafo_trans;


/*LISTA T*/

typedef struct noT
{
	char trans[50];
	char pessoa[50];
	int aval;//representa na lista de historico se o usuario ja foi avaliado ou nao

	p_noT prox;
	p_noT ant;

}tp_noT;


typedef struct listaT
{
	p_noT head;
	p_noT ultimo;
	
}tp_listaT;

/*CABEÇALHO DE FUNCOES*/

p_listatrans cria_lista_trans();

int cadastra_trans(p_listatrans, char *);

int remove_trans(p_listatrans, char *);

p_transacao pesquisa_trans(p_listatrans, char *);

p_listatrans carrega_trans();

int salva_trans(p_listatrans);

void destroi_trans(p_listatrans);

p_transacao pesquisa_trans(p_listatrans, char *);

void imprime_trans(p_listatrans);

/*GRAFO*/

p_grafo_trans cria_grafo_T();

void destroi_grafo_T(p_grafo_trans T);

p_verticeT pesquisa_verticeT(p_grafo_trans, char *);

p_verticeT adiciona_vertice_T(p_grafo_trans, char *);

void adiciona_aresta_T(p_grafo_trans, char *, char *);

void remove_vertice_T(p_grafo_trans, char *);

void imprime_grafoT(p_grafo_trans );

/*LISTA*/

p_noT adicionaNO(p_listaT, char *, char *);

void destroi_T(p_listaT );

int remove_T(p_listaT , p_noT);

p_noT pesquisa_T(p_listaT , char *s, int);

p_listaT cria_listaT();

void imprime_listaT(p_listaT, int);
