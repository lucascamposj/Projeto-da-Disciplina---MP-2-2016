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
				adicionaNO((v_aux->usuario.listaT_req),trans, user->usuario.nome);
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
				adicionaNO((a_aux->amigo->usuario.listaT_req),trans, user->usuario.nome);
			}	

			if(abran == 2)
			{
				a_aux2 = a_aux->amigo->head->prox;
				while(a_aux2)
				{
					if(verifica_requisitos(a_aux2->amigo, req_user, xp, trans) == TRUE)
					{
						adicionaNO((a_aux2->amigo->usuario.listaT_req),trans, user->usuario.nome);
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

	if(user->usuario.idade < req_user.idade && req_user.idade!=-1)
		return FALSE;
	if(user->usuario.genero != req_user.genero && req_user.genero!='x')
		return FALSE;
	if(user->usuario.escolaridade != req_user.escolaridade && req_user.escolaridade!=0)
		return FALSE;
	if(user->usuario.cep != req_user.cep && req_user.cep!=0)
		return FALSE;
	if(user->usuario.quant_aval < req_user.quant_aval && req_user.quant_aval!=0)
		return FALSE;

	if(req_user.n_interesses != 0)
	{	
		for(i = 0;i < user->usuario.n_interesses; i++)
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

int finalizar_trans(p_grafo G, p_vertice user,char *trans, char *nome)
{
	p_vertice v_aux, v_aux2;
	p_noT no;

	FILE *arq;

	if((v_aux = pesquisa_grafo_T(G, user->usuario.grafoT, trans, nome)))
	{
		no = adicionaNO(v_aux->usuario.listaT_his, trans, user->usuario.nome);
		no->aval = 0; // não avaliou
		no = adicionaNO(user->usuario.listaT_his, trans, nome);
		no->aval = 0; // não avaliou

		v_aux2 = G->head->prox; // recebe a lista de vértices do grafo(rede social)

		while(v_aux2) // percorre a lista de vértices
		{
			if((no = pesquisa_T(v_aux2->usuario.listaT_req, trans, 0))) // checa se, na lista de requerimentos desse usuário, existia essa transação como pendente
			{
				if(!strcmp(no->pessoa, user->usuario.nome)) // checa se o nome é o mesmo
					remove_T(v_aux2->usuario.listaT_req , no);
			}

			v_aux2 = v_aux2->prox;
		}

		remove_vertice_T(user->usuario.grafoT, trans);

		arq = fopen("historico.txt", "a");

		fprintf(arq, "%s/%s/%s\n", trans, user->usuario.nome, nome);

		fclose(arq);

	}
	else
		return FALSE;

	return TRUE;
}

p_vertice pesquisa_grafo_T(p_grafo G, p_grafo_trans grafoT, char *trans, char *nome)
{
	p_vertice v_aux = G->head->prox;
	p_verticeT vt_aux = grafoT->head->prox;
	p_arestaT at_aux;

	while(vt_aux)
	{
		if(!strcmp(vt_aux->trans, trans))
		{
			at_aux = vt_aux->head->prox;
			
			while(at_aux)
			{
				if(!strcmp(at_aux->pessoa, nome))
				{
					return pesquisa_vertice(G, nome);
				}

				at_aux = at_aux->prox;
			}
		}

		vt_aux = vt_aux->prox;
	}

	return NULL;

}

void imprime_listaT(p_listaT T, int flag)
{
	p_noT no = T->head->prox;

	while(no)
	{
		printf("%s: %s", no->trans, no->pessoa);
		if(flag && !no->aval)
			printf("(Avalie o usuario.)");
		else if(flag && no->aval)
			printf("(Transacao ja avaliada.)\n");
		printf("\n");
		no = no->prox;
	}
}
