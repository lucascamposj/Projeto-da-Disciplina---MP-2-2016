#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "trans.h"

#define TRUE 1
#define FALSE 0

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