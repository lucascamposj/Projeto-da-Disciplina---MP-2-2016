#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "trans.h"

#define TRUE 1
#define FALSE 0

/*GRAFO*/

p_grafo_trans cria_grafo_T()
{
	p_grafo_trans T; 

	T = (p_grafo_trans)malloc(sizeof(tp_grafo_trans));// aloca-se o grafo(rede social)
	assert(T); // checa se foi de fato alocado o espaço para o grafo


	T->head = (p_verticeT)malloc(sizeof(tp_verticeT)); //cria-se a célula cabeça
	assert(T->head);// checa se foi de fato alocado o espaço
	T->ultimo = T->head;

	T->head->prox = NULL;
	T->head->ant = NULL;

	return T;
}

void destroi_grafo_T(p_grafo_trans T)
{
	p_verticeT v_aux = T->head->prox, v_aux2;
	p_arestaT a_aux, a_aux2;

	assert(T); // checa se o grafo de fato existe
	/*verifica fim da lista de vertices*/
	while(v_aux != NULL) // percorre todos os vértices até terminar a lista de vértices
	{
		a_aux = v_aux->head->prox; // recebe a lista de arestas desse vértice
		/*verifica fim da lista de arestas*/         
		while(a_aux != NULL){
			a_aux2 = a_aux;
			a_aux = a_aux->prox;
			free(a_aux2); // libera essa aresta
		}
		free(v_aux->head); // libera a célula cabeça desse vértice
		v_aux2 = v_aux;
		v_aux = v_aux->prox;
		free(v_aux2); // libere o véritce
	}
	free(T->head); // libera a célula cabeça do grafo
	free(T); // libera o grafo
}

p_verticeT pesquisa_verticeT(p_grafo_trans T, char *s)
{
	p_verticeT p = T->head->prox;

	assert(T);
	while(p){
		if(!strcmp(s, p->trans))
			return p;
		p = p->prox;
	}
	return NULL;
}

p_verticeT adiciona_vertice_T(p_grafo_trans T, char *x)
{
	p_verticeT p = T->head->prox;

	assert(T);// checa se o grafo de fato existe
	if(pesquisa_verticeT(T, x) == NULL){ // caso esse usuário não exista(leva-se em consideração o nome fornecido)
		p = (p_verticeT)malloc(sizeof(tp_verticeT)); // aloca-se espaço para esse vértice
		assert(p); // checa se foi de fato alocado espaço

		T->ultimo->prox = p;
		p->ant = T->ultimo;
		T->ultimo = p;
		p->prox = NULL;

		strcpy(p->trans,x);

		p->head = (p_arestaT)malloc(sizeof(tp_arestaT)); // aloca-se a célula cabeça para a sua lista de arestas
		assert(p->head); // checa se foi de fato alocado espaço
		p->ultimo = p->head;
		p->head->ant = NULL;
		p->head->prox = NULL;

		return p;
	}
	else
		return NULL;
}

void adiciona_aresta_T(p_grafo_trans T, char *trans, char *nome)
{
	p_arestaT a_aux;
	p_verticeT v;

	if(v = pesquisa_verticeT(T, trans))
	{
		a_aux = (p_arestaT)malloc(sizeof(tp_arestaT)); // aloca-se a aresta(amizade)
		assert(a_aux); // checa se foi alocada
		a_aux->ant = v->ultimo; // faz o encadeamento
		v->ultimo->prox = a_aux;
		v->ultimo = a_aux;
		strcpy(a_aux->pessoa,nome);
		a_aux->prox = NULL;
	}
	else
	{
		adiciona_vertice_T(T, trans);
		adiciona_aresta_T(T, trans, nome);

	}
}

void remove_vertice_T(p_grafo_trans T, char *trans)
{
	p_verticeT V;
	p_arestaT A, A2;

	if(V = pesquisa_verticeT(T, trans)){
		A = V->head;
		while(A){
			A2 = A;
			A = A->prox;
			free(A2);
		}
		if(V == T->ultimo)
			T->ultimo = V->ant;
		else
			V->prox->ant = V->ant;
		V->ant->prox = V->prox;
		free(V);
	}
}


/*LISTAS*/

p_listatrans cria_lista_trans(){
	p_listatrans T; 

	T = (p_listatrans)malloc(sizeof(tp_listatrans));// aloca-se o grafo(rede social)
	assert(T); // checa se foi de fato alocado o espaço para o grafo


	T->head = (p_transacao)malloc(sizeof(tp_transacao)); //cria-se a célula cabeça
	assert(T->head);// checa se foi de fato alocado o espaço
	T->ultimo = T->head;

	T->head->prox = NULL;
	T->head->ant = NULL;

	return T;
}

p_listatrans carrega_trans(){
	char s[50]; //string auxiliar
	p_listatrans lista;
	int size; //tamanho da string
	int i;
	FILE *arq;

	if(arq = fopen("trans.txt","r"))
	{
		lista = cria_lista_trans();
		while(!feof(arq))
		{
			fscanf(arq,"%d", &size);
			if(feof(arq)) return lista;
			fgets(s, size+1,arq);
			fgetc(arq); //pegar o \n
			cadastra_trans(lista, s);
		}
		fclose(arq);
	}else
		return NULL;
	
	return lista;
}

int cadastra_trans(p_listatrans T ,char *x){
	p_transacao p = T->head->prox;

	assert(T);// checa se a lista de fato existe
	if(pesquisa_trans(T, x) == NULL){ // caso a transacao não exista(leva-se em consideração o nome fornecido)
		p = (p_transacao)malloc(sizeof(tp_transacao)); // aloca-se espaço para esse no
		assert(p); // checa se foi de fato alocado espaço

		T->ultimo->prox = p;
		p->ant = T->ultimo;
		T->ultimo = p;
		p->prox = NULL;

		strcpy(p->trans,x);

		return TRUE;
	}
	else
		/*transacao ja existe*/
		return FALSE;
}

int remove_trans(p_listatrans T, char *s){
	p_transacao x;

	assert(T); // checa se o grafo já existe

	/*Checa se os dois usuários, com os nomes fornecidos, existem*/
	if(x = pesquisa_trans(T, s)){
		/*Checa se existe amizade entre esses 2 usuários*/
		if(x == T->ultimo)
			T->ultimo = x->ant;
		else
			x->prox->ant = x->ant;
		x->ant->prox = x->prox;
		
		free(x);

		return TRUE;
	}else
		return FALSE;// não existe a transacao

}

p_transacao pesquisa_trans(p_listatrans T, char *s){
	p_transacao p = T->head->prox;

	assert(T);
	while(p){
		if(!strcmp(s, p->trans))
			return p;
		p = p->prox;
	}
	return NULL;
}

int salva_trans(p_listatrans T){
	FILE *arq;
	p_transacao p = T->head->prox;

	if(arq = fopen("trans.txt","w")){
		while(p){
			fprintf(arq,"%d", (int)strlen(p->trans));
			fputs(p->trans,arq);
			fprintf(arq,"\n");
			p = p->prox;
		}
	}
	fclose(arq);
}

void destroi_trans(p_listatrans T){
	p_transacao p = T->head, p2 = NULL;
	while(p){
		p2 = p;
		p = p->prox;
		free(p2);
	}

	free(T);
}

void imprime_trans(p_listatrans T)
{
	p_transacao p = T->head->prox;

	while(p)
	{
		printf("%s.\n", p->trans);

		p = p->prox;
	}
}


/*LISTA*/

p_noT adicionaNO(p_listaT lista_req, char *trans, char *nome)
{
	p_noT T_aux;
	T_aux = (p_noT)malloc(sizeof(tp_noT)); // aloca-se espaço para esse no
	assert(T_aux); // checa se foi de fato alocado espaço


	T_aux->ant = lista_req->ultimo;
	lista_req->ultimo->prox = T_aux;
	lista_req->ultimo = T_aux;
	T_aux->prox = NULL;

	strcpy(T_aux->trans,trans);
	strcpy(T_aux->pessoa,nome);


	return T_aux;
/*VERIFICAR SE PODE HAVER REPETIÇÃO DE PEDIDOS DO MESMO TIPO DE TRANSAÇÃO*/
}

void destroi_T(p_listaT T){
	p_noT p = T->head, p2 = NULL;
	while(p){
		p2 = p;
		p = p->prox;
		free(p2);
	}

	free(T);
}

int remove_T(p_listaT T, p_noT x){
	
	assert(T);

	if(x){
		if(x == T->ultimo)
			T->ultimo = x->ant;
		else
			x->prox->ant = x->ant;
		x->ant->prox = x->prox;
		
		free(x);

		return TRUE;
	}else
		return FALSE;// não existe a transacao
}

p_noT pesquisa_T(p_listaT T, char *s){
	p_noT p = T->head->prox;

	assert(T);
	while(p){
		if(!strcmp(s, p->trans))
			return p;
		p = p->prox;
	}
	return NULL;
}

p_listaT cria_listaT(){
	p_listaT T; 

	T = (p_listaT)malloc(sizeof(tp_listaT));// aloca-se o grafo(rede social)
	assert(T); // checa se foi de fato alocado o espaço para o grafo


	T->head = (p_noT)malloc(sizeof(tp_noT)); //cria-se a célula cabeça
	assert(T->head);// checa se foi de fato alocado o espaço
	T->ultimo = T->head;

	T->head->prox = NULL;
	T->head->ant = NULL;

	return T;
}

void imprime_grafoT(p_grafo_trans T){
	p_verticeT v = T->head->prox;
	p_arestaT  a;

	while(v){
		a = v->head->prox;
		printf("%s\n", v->trans);
		while(a){
			printf("\t%s\n", a->pessoa);
			a = a->prox;
		}
		v = v->prox;
	}	
}

