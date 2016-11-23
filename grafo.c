#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "grafo.h"

/*
	FUNCOES
*/
/*******************************************************
*Função: Cria Grafo
*Descrição
*	Inicializa uma estrutura de um Grafo.
*	Nomeia o grafo inicializado com a string de entrada.
*Parâmetros
*	nome - string referente ao nome do Grafo.
*Valor retornado
*	G - ponteiro para a estrutura Grafo inicializada.
*Assertiva de entrada
*	A variável nome não pode ter o valor NULL.
*Assertiva de saida
*	O ponteiro G não pode ter valor NULL.
*********************************************************/

p_grafo cria_grafo()
{
	p_grafo G;

	G = (p_grafo)malloc(sizeof(tp_grafo));
	assert(G);


	G->head = (p_vertice)malloc(sizeof(tp_vertice));
	assert(G->head);
	G->ultimo = G->head;

	G->head->prox = NULL;
	G->head->ant = NULL;

	return G;
}

/*******************************************************
*Função: Destroi Grafo
*Descrição
*	Realiza a liberação correta de memória de um Grafo.
*Parâmetros
*	G - Ponteiro para uma estrutura de grafo.
*Assertiva de entrada
*	A estrutura do grafo necessita estar inicializada. G não pode possuir o valor NULL.
*********************************************************/

void destroi_grafo(p_grafo G)
{
	p_vertice v_aux = G->head->prox, v_aux2;
	p_aresta a_aux, a_aux2;

	assert(G);
	/*verifica fim da lista de vertices*/
	while(v_aux != NULL)
	{
		a_aux = v_aux->head->prox;
		/*verifica fim da lista de arestas*/         
		while(a_aux != NULL){
			a_aux2 = a_aux;
			a_aux = a_aux->prox;
			free(a_aux2);
		}
		free(v_aux->head);
		v_aux2 = v_aux;
		v_aux = v_aux->prox;
		free(v_aux2);
	}
	free(G->head);
	free(G);
}

/*******************************************************
*Função: Adjacente
*Descrição
*	Verifica se dois vértices são adjacentes em um grafo.
*Parâmetros
*	G - Ponteiro para a estrutura de um grafo.
*	x - Identificador de um vértice.
*	y - Identificador de outro vértice.
*Valor retornado
*	Retorna um valor booleano que indica se os vértices de entrada são adjacentes ou não.
*	True - são adjacentes.
*	False -  não são adjacentes.
*Assertiva de entrada
*	O ponteiro G não pode ser NULL.
*	Os vértices x e y não podem possuir o mesmo valor.
*********************************************************/
/*boolean adjacente(p_grafo G, int x, int y)
{
	p_vertice v_aux = G->head;
	p_aresta a_aux;
	int i;

	assert(x != y);
	assert(G);
	/*Realiza duas vezes para conferir os dois casos x->y e y<-x */
	/*for (i = 0; i < 2; ++i)
	{
		while(v_aux != NULL && v_aux->ch_vertice != x && v_aux->ch_vertice != y)
			v_aux = v_aux->prox;
		/*caso nao exista nem x, nem y*/
		/*if(v_aux == NULL)
			return FALSE;
		else
		{
			a_aux = v_aux->primeiro;
			while(a_aux != NULL && a_aux->vizinho->ch_vertice != x && a_aux->vizinho->ch_vertice != y)
				a_aux = a_aux->prox;
			if(a_aux != NULL)
				return TRUE;
		}
		v_aux = v_aux->prox;
	}
	return FALSE;
} 
*/
/*******************************************************
*Função:
*Descrição
*	Imprime uma lista de todos os vértices que podem ser visitados a partir de x
*(existe uma aresta que vai de x para este vértice).
*Parâmetros
*	G - Ponteiro para a estrutura de um grafo.
*	x - Identificador de um vértice.
*Assertiva de entrada
*	A estrutura do grafo necessita estar inicializada. G não pode possuir o valor NULL.
*********************************************************/
/*void vizinhos(p_grafo G,int x)
{
	p_vertice v_aux = G->primeiro;
	p_aresta a_aux;

	assert(G);

	while(v_aux != NULL && v_aux->ch_vertice != x)
		v_aux = v_aux->prox;
	if(v_aux == NULL)
	{
		printf("Erro - Vertice nao encontrado\n");
		return;
	}
	printf("Vertice %d: ", x);

	a_aux = v_aux->primeiro;
	while(a_aux != NULL)
	{
		printf("%d ",a_aux->vizinho->ch_vertice);
		a_aux = a_aux->prox;
	}
}*/

/*******************************************************
*Função: Adiciona Vértice
*Descrição
*	Adiciona um vértice a um grafo.
*Parâmetros
*	G - Ponteiro para a estrutura de um grafo.
*	x - Indentificador de um vértice.
*Assertiva de entrada
*	A estrutura do grafo necessita estar inicializada. G não pode possuir o valor NULL.
*********************************************************/

boolean adiciona_usuario(p_grafo G, tp_user x)
{
	p_vertice p = G->head->prox;

	assert(G);
	if(pesquisa_vertice(G, x.nome) == NULL){
		p = (p_vertice)malloc(sizeof(tp_vertice));
		assert(p);

		G->ultimo->prox = p;
		p->ant = G->ultimo;
		G->ultimo = p;
		p->prox = NULL;

		p->usuario = x;

		p->head = (p_aresta)malloc(sizeof(tp_aresta));
		assert(p->head);
		p->ultimo = p->head;
		p->head->ant = NULL;
		p->head->prox = NULL;

		return TRUE;
	}
	else
		/*usuario ja existe*/
		return FALSE;
}

/*******************************************************
*Função: Remove Vértice 
*Descrição
*	Remove um vértice de um grafo. Além disso, realiza a liberação correta de memória.
*Parâmetros
*	G - Ponteiro para a estrutura de um grafo.
*	x - Indentificador de um vértice.
*Assertiva de entrada
*	A estrutura do grafo necessitar estar inicializada. G não pode possuir o valor NULL.
*********************************************************/

boolean remove_usuario(p_grafo G, char *x)
{
	p_vertice v_aux = G->head->prox;
	p_aresta a_aux = NULL, a_aux2 = NULL;

	assert(G);

	v_aux = pesquisa_vertice(G, x);

	if(v_aux == NULL)
	{
		return FALSE;
	}
	else
	{	// percorre o grafo removendo a amizade
		a_aux = v_aux->head->prox;
		while(a_aux)
		{
			a_aux2 = a_aux->amigo->head->prox;
			/*percorrendo amigo e elimando amizade com o usuario*/
			while(a_aux2)
			{
				if(a_aux2->amigo == v_aux)
				{
					if(a_aux2 == a_aux->amigo->ultimo)
						a_aux->amigo->ultimo = a_aux2->ant;
					else
						a_aux2->prox->ant = a_aux2->ant;
					a_aux2->ant->prox = a_aux2->prox;

					free(a_aux2);
					break;
				}
				a_aux2 = a_aux2->prox;
			}
			/*
			remove_amizade(G, a_aux->amigo->usuario.nome, v_aux->usuario.nome);
			*/
			//aproveitando o a_aux2, eliminando o amigo da lista do usuario
			if(a_aux == v_aux->ultimo)
				v_aux->ultimo = a_aux->ant;
			else
				a_aux->prox->ant = a_aux->ant;
			v_aux->ant->prox = v_aux->prox;

			a_aux2 = a_aux;
			a_aux = a_aux->prox;
			free(a_aux2);
		}
		// eliminando o vértice no grafo
		if(v_aux == G->ultimo)
			G->ultimo = v_aux->ant;
		else
			v_aux->prox->ant = v_aux->ant;
		
		v_aux->ant->prox = v_aux->prox;
		
		free(v_aux->head);
		free(v_aux);

		return TRUE;
	}
}

/*******************************************************
*Função: Adiciona Aresta
*Descrição
*	Adiciona uma aresta entre dois vértices.
*Parâmetros
*	G - Ponteiro para a estrutura de um grafo.
*	x - Indentificador de um vértice.
*Assertiva de entrada
*	A estrutura do grafo necessita estar inicializada. G não pode possuir o valor NULL.
*********************************************************/

boolean adiciona_amizade(p_grafo G,char *x,char *y)
{
	p_vertice v_x = G->head, v_y = NULL;
	p_aresta a_aux;

	assert(G);

	if((v_x = pesquisa_vertice(G, x)) != NULL && (v_y = pesquisa_vertice(G, y)) != NULL)
		if(pesquisa_aresta(v_x, y) == NULL){
			/*adicionando em x*/
			a_aux = (p_aresta)malloc(sizeof(tp_aresta));
			assert(a_aux);
			a_aux->ant = v_x->ultimo;
			v_x->ultimo->prox = a_aux;
			a_aux->prox = NULL;

			v_x->ultimo = a_aux;
			a_aux->amigo = v_y;

			/*adicionando em y*/
			a_aux = (p_aresta)malloc(sizeof(tp_aresta));
			assert(a_aux);
			a_aux->ant = v_y->ultimo;
			v_y->ultimo->prox = a_aux;
			a_aux->prox = NULL;

			v_y->ultimo = a_aux;
			a_aux->amigo = v_x;
			
			return TRUE;
		}
		else
			return FALSE;
	else
		return FALSE;
}

/*******************************************************
*Função: Remove Aresta
*Descrição
*	Remove aresta entre dois vértices.
*Parâmetros
*	G - Ponteiro para a estrutura de um grafo.
*	x - Identificador de um vértice.
*	y - Identificador de outro vértice.
*Assertiva de entrada
*	A estrutura do grafo necessita estar inicializada. G não pode possuir o valor NULL.
*********************************************************/

boolean remove_amizade(p_grafo G,char *x, char *y)
{
	p_vertice v_x = NULL, v_y = NULL;
	p_aresta a_aux;

	assert(G);

	if((v_x = pesquisa_vertice(G, x)) != NULL && (v_y = pesquisa_vertice(G, y)) != NULL){
		if((a_aux = pesquisa_aresta(v_x, y)) != NULL){
			if(a_aux == v_x->ultimo)
				v_x->ultimo = a_aux->ant;
			else
				a_aux->prox->ant = a_aux->ant;
			
			a_aux->ant->prox = a_aux->prox;

			free(a_aux);
		}else
			return FALSE;
		if((a_aux = pesquisa_aresta(v_y, x)) != NULL){
			if(a_aux == v_y->ultimo)
				v_y->ultimo = a_aux->ant;
			else
				a_aux->prox->ant = a_aux->ant;
			
			a_aux->ant->prox = a_aux->prox;

			free(a_aux);
		}
		return TRUE;
	}
	else
		return FALSE;
} 

/*
	FUNCOES EXTRAS
*/

/*******************************************************
*Função: Grafo vazio
*Descrição
*	Verifica se uma esturutra grafo está vazia.
*Parâmetros
*	G - Estrutura de um grafo.
*Valor retornado
*	Retorna um valor booleano que indica se o grafo está vazio ou não.
*	True - caso o grafo esteja vazio.
*	False - caso contrário.
*Assertiva de entrada
*	A estrutura do grafo necessita estar inicializada. G não pode possuir o valor NULL.
*********************************************************/
boolean grafo_vazio(p_grafo G)
{
	if(G->head == G->ultimo)
		return TRUE;
	else 
		return FALSE;
}

/*******************************************************
*Função: Vértice isolado
*Descrição
*	Verifica se um vértice não possui arestas.
*Parâmetros
*	A - Ponteiro para a estrutura de um vértice.
*Valor retornado
*	Retorna um valor booleano que indica se um vértice não possui arestas.
*	True - Caso o vértice não possua arestas.
*	False - Caso contrário.
*Assertiva de entrada
*	A estrutura do vértice necessita estar inicializada. A não pode possuir o valor NULL.
*********************************************************/
boolean vertice_vazio(p_vertice A)
{
	if(A->head == A->ultimo)
		return TRUE;
	else
		return FALSE;
}

p_vertice pesquisa_vertice (p_grafo G, char *x){
	p_vertice p = G->head->prox;

	assert(G);

	if(grafo_vazio(G) == FALSE){
		while(p != NULL){
			if(strcmp(x, p->usuario.nome) == 0)
				break;
			p = p->prox;
		}
		if(p != NULL)
			return p;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

p_aresta pesquisa_aresta(p_vertice  V, char *x){
	p_aresta p = V->head->prox;

	assert(V);

	if(vertice_vazio(V) == FALSE){
		while(p != NULL){
			if(strcmp(x, p->amigo->usuario.nome) == 0)
				break;
			p = p->prox;
		}
		if(p != NULL)
			return p;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

boolean imprime_grafo(p_grafo G)
{
	p_vertice v_aux = G->head->prox;
	p_aresta a_aux;

	printf("HEAD: %p | ant: %p | prox: %p\n", G->head,G->head->ant,G->head->prox);
	while(v_aux)
	{
		printf("%s: %p | ant: %p | prox: %p\n", v_aux->usuario.nome,v_aux,v_aux->ant,v_aux->prox);
		a_aux = v_aux->head->prox;
		printf("\t%c\n", v_aux->usuario.genero);
		printf("\t%d\n", v_aux->usuario.idade);
		printf("\t%d\n", v_aux->usuario.escolaridade);
		printf("\t%d\n", v_aux->usuario.cep);

		printf("\t\tHEAD: %p | ant: %p | prox: %p\n", v_aux->head,v_aux->head->ant,v_aux->head->prox);
		while(a_aux)
		{
			printf("\t\t%s: %p | ant: %p | prox: %p\n",a_aux->amigo->usuario.nome,a_aux,a_aux->ant,a_aux->prox);
			a_aux = a_aux->prox;
		}
		v_aux = v_aux->prox;
	}
}

boolean salva_grafo(p_grafo G)
{

}

p_grafo carrega_grafo(FILE *arq)
{

}