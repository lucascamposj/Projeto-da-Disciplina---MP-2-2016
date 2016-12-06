#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "user.h"

#define TRUE 1
#define FALSE 0

/************************************************************************************
* Função: Busca Requisitos
* Descrição
*	Busca e convida usuários que se encaixam em certos requisitos a realizar uma
* transação de acordo com a abrangência do convite.
* Parâmetros
*	G - ponteiro para a estrutura Grafo que armazena todos os usuários.
*	req_user - estrutura usuário base para comparação dos requisitos.
*	user - ponteiro para o usuário que requisitou a transação
*	abran - flag que determina a abrangência da análise
*		1 - Amigos
*		2 - Amigos de amigos
*		3 - Qualquer usuário
*	xp - flag que determina se há necessidade de se avaliar a experiência dos usuários
* com a transação em questão.
*	trans - String que armazena o tipo de transação a ser realizada.
* Assertiva de entrada
*	G necessita ser diferente de NULL e possuir uma estrutura grafo inicializada.
*	req_user necessita estar com valores padrões caso um dos requisitos não tenha 
*sido selecionado para análise.
*	user necessita ser diferente de NULL e possuir estrutura inicializada e contida
*no grafo G.
*	abran necessita armazenar um valor entre 1 e 3.
* 	xp necessista armazenar 0 ou 1.
*************************************************************************************/
/** @brief Busca e convida usuários que se encaixam em certos requisitos a realizar uma
 * transação de acordo com a abrangência do convite.
*	@param G Ponteiro para a estrutura Grafo que armazena todos os usuários.
*	@param req_user Estrutura usuário base para comparação dos requisitos.
*	@param user Ponteiro para o usuário que requisitou a transação
*	@param abran Flag que determina a abrangência da análise
*	@param xp Flag que determina se há necessidade de se avaliar a experiência dos usuários
* com a transação em questão.
*	@param trans String que armazena o tipo de transação a ser realizada.
*/

void buscarequisitos(p_grafo G,tp_user req_user,p_vertice user,int abran,int xp, char *trans)
{
	p_vertice v_aux = G->head->prox;
	p_aresta a_aux= user->head->prox, a_aux2;

	//caso abrangencia seja de qualquer usuário
	if(abran == 3)
	{
		while(v_aux) //percorre o grafo comparando os requisitos com todos os usuários
		{
			//verifica se o ponteiro não está apaontando para o usuário que pedir a transação
			if(v_aux != user)	
				if(verifica_requisitos(v_aux, req_user, xp, trans) == TRUE)
				{
					//adiciona na lista de transações requeridas do usuário
					adicionaNO((v_aux->usuario.listaT_req),trans, user->usuario.nome);
				}
			v_aux = v_aux->prox;
		}
	}
	else
	{	
		//percorre lista de amigos do user, comparando requesitos
		while(a_aux)
		{
			if(verifica_requisitos(a_aux->amigo, req_user, xp, trans) == TRUE)
			{
				adicionaNO((a_aux->amigo->usuario.listaT_req),trans, user->usuario.nome);
			}	
			//caso a abrangencia seja de amigos de amigos
			if(abran == 2)
			{
				//percorre lista de amigos de cada amigo
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

/************************************************************************************
* Função: Verifica Requisitos
* Descrição
* 	Verifica se usúario se qualifica de acordo com requesitos para uma transação
* Parâmetros
*	user - ponteiro para o usuário que requisitou a transação
*	req_user - estrutura usuário base para comparação dos requisitos.
*	xp - flag que determina se há necessidade de se avaliar a experiência dos usuários
* com a transação em questão.
*	trans - String que armazena o tipo de transação a ser realizada.
* Valor retornado
* 	Função retorna a macro TRUE caso o usuário seja qualificado com os requisitos
* e FALSE caso contrário.
* Assertiva de entrada
*	req_user necessita estar com valores padrões caso um dos requisitos não tenha 
*sido selecionado para análise.
*	user necessita ser diferente de NULL e possuir estrutura inicializada e contida
*no grafo G.
* 	xp necessista armazenar 0 ou 1.
* Assertiva de saída
*	Função deve retornar as macros FALSE ou TRUE.
*************************************************************************************/
/** @brief Busca e convida usuários que se encaixam em certos requisitos a realizar uma
* transação de acordo com a abrangência do convite.
*	@param req_user Estrutura usuário base para comparação dos requisitos.
*	@param user Ponteiro para o usuário a ser avaliado.
*	@param abran Flag que determina a abrangência da análise.
*	@param xp Flag que determina se há necessidade de se avaliar a experiência dos usuários
* com a transação em questão.
*	@param trans String que armazena o tipo de transação a ser realizada.
*	@return Retona TRUE caso o usuário seja qualificado com os requisitos, caso contrário retona FALSE. 
*/

int verifica_requisitos(p_vertice user, tp_user req_user, int xp, char *trans)
{
	p_noT T_aux = user->usuario.listaT_his->head->prox; //ponteiro auxiliar para verificar xp
	int i;

	/*Todas as comparações verificam se não há valores padrões no req_user,
	pois valores padrões indicam que o usuário não quer avaliar tal requesito*/

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
		/*Percorre vetor de interesses, verificando se usuário possui o interesse requerido*/
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
		/*Percorre lista de histórico verificando se o usúario já realizou a 
		transação em questão*/
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

/************************************************************************************
* Função: Finaliza Transação
* Descrição
*	Função que finaliza uma transação, retirando o convite de todos os usuários
*requisitados e armazenando no histórico dos envolvidos na transação.
* Parâmetros
*	G - ponteiro para a estrutura Grafo que armazena todos os usuários.
*	user - usuário que pediu uma transação.
*	nome - string que armazena o nome da pessoa escolhida.
*	trans - String que armazena o tipo de transação a ser realizada.
* Valor retornado
* 	Função retorna a macro TRUE caso os dados de entrada e o convite exista,
*FALSE caso contrário.
* Assertiva de entrada
*	G necessita ser diferente de NULL e possuir uma estrutura grafo inicializada.
*	user necessita ser diferente de NULL e possuir estrutura inicializada e contida
*no grafo G.
* Assertiva de saída
*	Função deve retornar as macros FALSE ou TRUE.
*************************************************************************************/

/** @brief Função que finaliza uma transação, retirando o convite de todos os usuários
*requisitados e armazenando no histórico dos envolvidos na transação.
*	@param G Ponteiro para a estrutura Grafo que armazena todos os usuários.
*	@param user Ponteiro para o usuário que requisitou a transação.
*	@param trans String que armazena o tipo de transação a ser realizada.
*	@param nome String que armazena o nome da pessoa escolhida.
*	@return Retorna a macro TRUE caso os dados de entrada e o convite exista,
*FALSE caso contrário. 
*/

int finalizar_trans(p_grafo G, p_vertice user,char *trans, char *nome)
{
	p_vertice v_aux, v_aux2;
	p_noT no;

	FILE *arq;

	//verificação e pesquisa do usuário escolhido
	if((v_aux = pesquisa_grafo_T(G, user->usuario.grafoT, trans, nome)))
	{
		//adiciciona na lista do histórico
		no = adicionaNO(v_aux->usuario.listaT_his, trans, user->usuario.nome);
		no->aval = 0; // não avaliou
		no = adicionaNO(user->usuario.listaT_his, trans, nome);
		no->aval = 0; // não avaliou

		//apaga convites dos outros usuários convidados
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
		remove_vertice_T(user->usuario.grafoT, trans); //Remove vértice e arestas a respeito da transação

		arq = fopen("historico.txt", "a");

		fprintf(arq, "%s/%s/%s\n", trans, user->usuario.nome, nome);

		fclose(arq);
	}
	else
		return FALSE;

	return TRUE;
}

/************************************************************************************
* Função: Pesquisa no Grafo T
* Descrição
*	Função que pesquisa no grafo de transações pendentes de um usuário uma transação com 
* outro usuário.
* Parâmetros
*	G - ponteiro para a estrutura Grafo que armazena todos os usuários.
*	grafoT - ponteiro para a estrutura GrafoTrans que armazena transações pendentes de
* usuário.
*	nome - string que armazena o nome da pessoa escolhida.
*	trans - String que armazena o tipo de transação a ser realizada.
* Valor retornado
* 	Função retorna o ponteiro para o vértice do usuário escolhido ou NULL caso não encontre.
* Assertiva de entrada
*	G necessita ser diferente de NULL e possuir uma estrutura grafo inicializada.
*	grafoT necessita ser diferente de NULL e possuir estrutura inicializada.
* Assertiva de saída
*	Função deve retornar um ponteiro da um usuário existente em G ou NULL.
*************************************************************************************/

/** @brief Função que pesquisa no grafo de transações pendentes de um usuário uma transação com 
* outro usuário.
*	@param G Ponteiro para a estrutura Grafo que armazena todos os usuários.
*	@param grafoT Ponteiro para a estrutura GrafoTrans que armazena transações pendentes de
* usuário.
*	@param trans String que armazena o tipo de transação a ser realizada.
*	@param nome String que armazena o nome da pessoa escolhida.
*	@return Retorna o ponteiro para o vértice do usuário escolhido ou NULL caso não encontre.
*/

p_vertice pesquisa_grafo_T(p_grafo G, p_grafo_trans grafoT, char *trans, char *nome)
{
	p_vertice v_aux = G->head->prox;
	p_verticeT vt_aux = grafoT->head->prox;
	p_arestaT at_aux;

	//Percorre vérices do Grafo T
	while(vt_aux)
	{
		//Busca transação
		if(!strcmp(vt_aux->trans, trans))
		{
			at_aux = vt_aux->head->prox;
			while(at_aux)
			{
				//Pesquisa o usuário escolhido no Grafo G
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

/************************************************************************************
* Função: Imprime Lista T
* Descrição
*	Imprime lista de requerimentos e de histórico.
* Parâmetros
*	T - ponteiro para uma estrutura lista T
*	flag - identifica se a lista é de requerimentos (flag = 0)
* ou de histórico (flag = 1).
* Assertiva de entrada
*	T necessita ser uma estrutura lista T inicializada.
*	flag necessita ser um valor 0 ou 1.
*************************************************************************************/

/** @brief Imprime lista de requerimentos e de histórico.
*	@param T Ponteiro para uma estrutura lista T
*	@param flag Identifica se a lista é de requerimentos (flag = 0)
* ou de histórico (flag = 1).
*/

void imprime_listaT(p_listaT T, int flag)
{
	p_noT no = T->head->prox;

	//percorre lista T
	while(no)
	{
		printf("%s: %s", no->trans, no->pessoa);
		
		//caso seja uma lista de histórico e a pessoa não tenha sido avaliada
		if(flag && !no->aval)
			printf("(Avalie o usuario.)");
		else if(flag && no->aval)
			printf("(Transacao ja avaliada.)\n");
		printf("\n");
		no = no->prox;
	}
}
