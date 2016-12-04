#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "user.h"

#define TRUE 1
#define FALSE 0

void buscarequisitos(p_grafo G,tp_user req_user,p_vertice user,int abran,int xp, char *trans)
{
	p_vertice v_aux = G->head->prox;
	p_aresta a_aux= user->head->prox, a_aux2;

	if(abran == 3)
	{
		while(v_aux)
		{
			if(verifica_requisitos(v_aux, req_user, xp, trans) == TRUE)
			{
				adicionaNO(*(v_aux->usuario.listaT_req),user->usuario.nome, trans);
			}

			v_aux = v_aux->prox;
		}
	}
	else
	{
		while(a_aux)
		{
			if(verifica_requisitos(a_aux->amigo, req_user, xp, trans) == TRUE)
			{
				adicionaNO(*(a_aux->amigo->usuario.listaT_req),user->usuario.nome, trans);
			}	

			if(abran == 2)
			{
				a_aux2 = a_aux->amigo->head->prox;
				while(a_aux2)
				{
					if(verifica_requisitos(a_aux2->amigo, req_user, xp, trans) == TRUE)
					{
						adicionaNO(*(a_aux2->amigo->usuario.listaT_req), user->usuario.nome, trans);
					}		
				}
			}

			a_aux = a_aux->prox;
		}
	}
}


int verifica_requisitos(p_vertice user, tp_user req_user, int xp, char *trans)
{
	int flag, i;
	p_noT T_aux = user->usuario.listaT_his->head->prox;

	if(user->usuario.idade < req_user.idade && user->usuario.idade!=-1)
		return FALSE;
	if(user->usuario.genero != req_user.genero && user->usuario.genero!='x')
		return FALSE;
	if(user->usuario.escolaridade != req_user.escolaridade && user->usuario.escolaridade!=0)
		return FALSE;
	if(user->usuario.cep != req_user.cep && user->usuario.cep!=0)
		return FALSE;
	if(user->usuario.quant_aval < req_user.quant_aval && user->usuario.quant_aval!=0)
		return FALSE;

	if(user->usuario.n_interesses != 0)
	{	
		for(i=0;i<user->usuario.n_interesses;i++)
		{
			if(!strcmp(user->usuario.interesses[i], req_user.interesses[0]))	
				break;
		}

		if(i == user->usuario.n_interesses)
			return FALSE;
	}

	if(xp == 1)
	{
		while(T_aux)
		{
			if(!strcmp(trans, T_aux->trans))
				break;

			T_aux = T_aux->prox;
		}

		if(!T_aux)
			return FALSE;
	}


	return TRUE;
}

int finalizar_trans(p_grafo G, p_grafo_trans G_trans, char *trans, char *nome){
		
}