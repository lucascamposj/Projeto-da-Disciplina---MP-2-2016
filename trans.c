#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "trans.h"

#define TRUE 1
#define FALSE 0

/*GRAFO*/

/*******************************************************
*Função: Cria grafo de transação de um usuário
*Descrição
*	Cria um grafo que irá conter as transação(e pessoas) que aceitaram uma
*	uma transação que este usuário pediu(mas não aceitou ainda).
*
*Parâmetros
*	-
*Valor retornado
*	T - grafo de transações desse usuário.	
*
*Assertiva de entrada
*  Não digite o nome com asterisco(Apenas caracteres alfabéticos).
*
*Assertiva de saída
*	Deve retornar um grafo criado.
*********************************************************/

/** \brief  Função que cria um grafo que conterá as transações em que o usuário pediu e recebeu resposta.*/
p_grafo_trans cria_grafo_T()
{
	/** 
	\return Um ponteiro para o grafo de transação alocado.
	*/
	p_grafo_trans T; 

	T = (p_grafo_trans)malloc(sizeof(tp_grafo_trans));// aloca-se o grafo de transações
	assert(T); // checa se foi de fato alocado o espaço para o grafo


	T->head = (p_verticeT)malloc(sizeof(tp_verticeT)); //cria-se a célula cabeça
	assert(T->head);// checa se foi de fato alocado o espaço
	T->ultimo = T->head; // faz o ultimo apontar para a celula cabeça

	T->head->prox = NULL;
	T->head->ant = NULL;

	return T; // retorna o grafo alocado
}
/*******************************************************
*Função: Destroi grafo de transação de um usuário
*Descrição
*	Realiza a liberação de memória do grafo de transação desse usuário	
*
*Parâmetros
*	T - o grafo de transação desse usuário.
*
*Assertiva de entrada
*	O grafo deve existir e conter strings em formato alfabético.
*
*Assertiva de saída
*	Deve liberar todo o espaço reservado para esse grafo(tanto seus vértices quanto suas arestas) 
*********************************************************/

/** \brief  Função que libera a memória alocada para o grafo.*/
void destroi_grafo_T(p_grafo_trans T)
{
	/** 
	\details Libera tanto os vértices, quando a lista de arestas de cada vértice.
	\param T é o ponteiro para o grafo de transação.
	*/

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

/*******************************************************
*Função: Pesquisa Vértice no grafo T

*Descrição
*	Pesquisa um vértice(tipo de transação) no grafo de transação
*	desse usuário.	
*
*Parâmetros
*	T - o grafo de transação desse usuário.
*	s - a string que condiz à transação buscada.
*
*Valor retornado
*	NULL - Não encontrou o vértice(a transação buscada).
*	 p - o ponteiro para esse vértice(transação).
*
*Assertiva de entrada
*	O nome da transação não pode conter *, apenas caracteres alfabéticos.
*
*Assertiva de saída	
*	Deve retornar ou NULL ou um vértice do grafo que corresponda à string 's'.
*********************************************************/

/** \brief  Função que pesquisa um vértice(transação) no grafo de um determinado usuário.*/
p_verticeT pesquisa_verticeT(p_grafo_trans T, char *s)
{
	/**  
	\details Percorre a lista de vértices(transações) do grafo.
	\param T é o ponteiro para o grafo de transações do grafo de um determinado usuário.
	\param s é a string que, possivelmente, corresponde à transação que se está buscando.
	\return ponteiro para esse vértice(transação).
	*/   
	p_verticeT p = T->head->prox; // recebe a lista de vértices do grafo

	assert(T); // checa se o grafo foi alocado devidamente.
	while(p) // enquanto nao chegar no final do arquivo.
	{
		if(!strcmp(s, p->trans)) // se encontrou uma transação cujo nome corresponde a 's'
			return p; // retorna o ponteiro para essa transação
		p = p->prox;
	}
	return NULL; // não encontrou uma transação que correspondessse a 's'
}
/*******************************************************
*Função: Adiciona um Vértice no grafo T
*Descrição
*	Adiciona um vértice(tipo de transação) no grafo de transação
*	desse usuário.	
*
*Parâmetros
*	T - o grafo de transação desse usuário.
*	x - a string que condiz à transação que deseja-se adicionar.
*
*Valor retornado
*	NULL - Encontrou uma transação correspondente a essa string(a transação que desejava-se adicionar).
*	 p - o ponteiro para esse vértice(transação).
*
*Assertiva de entrada
*	O nome da transação não pode conter *, apenas caracteres alfabéticos.
*
*Assertiva de saída
*	Deve retornar NULL ou um ponteiro para vértice(tendo em mente que T é um grafo criado e 'x' uma string alfabética)
*********************************************************/

/** \brief  Função que adiciona um vértice(transação) no grafo de transações do usuário.*/
p_verticeT adiciona_vertice_T(p_grafo_trans T, char *x)
{
	p_verticeT p = T->head->prox;

	/**  
	\details Pesquisa se o a transação qeu deseja-se inserir já não existe.Caso não exista insere-se no final da lista de vértices do grafo.
	\param T é o ponteiro para o grafo de transações do grafo de um determinado usuário.
	\param x é a string que, possivelmente, corresponde à transação que deseja-se inserir.
	\return ponteiro para esse vértice(transação) criado.
	*/   
	
	assert(T);// checa se o grafo de fato existe
	if(pesquisa_verticeT(T, x) == NULL){ // caso essa transação ainda não exista(leva-se em consideração o nome fornecido)
		p = (p_verticeT)malloc(sizeof(tp_verticeT)); // aloca-se espaço para esse vértice
		assert(p); // checa se foi de fato alocado espaço

		T->ultimo->prox = p;
		p->ant = T->ultimo;
		T->ultimo = p;
		p->prox = NULL;

		strcpy(p->trans,x); // copia-se o nome correspondente 'x'

		p->head = (p_arestaT)malloc(sizeof(tp_arestaT)); // aloca-se a célula cabeça para a sua lista de arestas(pessoas)
		assert(p->head); // checa se foi de fato alocado espaço
		p->ultimo = p->head;
		p->head->ant = NULL;
		p->head->prox = NULL;

		return p; // retorna o ponteiro para esse novo vértice
	}
	else
		return NULL; // encontrou uma transação cujo nomo corresponde a 'x'
}

/*******************************************************
*Função: Adiciona uma aresta no grafo T
*Descrição
*	Adiciona uma aresta(pessoa) no grafo de transação
*	desse usuário.	
*
*Parâmetros
*	T - o grafo de transação desse usuário.
*	trans - a string que condiz à transação que deseja-se adicionar uma aresta.
*	nome - a string que condiz ao nome da pessoa que deseja-se adicionar a lista de aresta de 'trans'.
*
*Assertiva de entrada
*	o grafo deve ter sido criado previamente.
*	O nome da transação não pdoe conter *, apenas caracteres alfabéticos.
* 	O nome da pessoa não pode conter *, apenas caracteres alfabéticos.
*
*Assertiva de saída
*	Deve ser adicionada uma aresta no vértice trans.
*********************************************************/

/** \brief  Função que adiciona uma aresta(pessoa) no grafo de transações do usuário.*/
void adiciona_aresta_T(p_grafo_trans T, char *trans, char *nome)
{
	p_arestaT a_aux;
	p_verticeT v;

	/**  
	\details Insere na lista de arestas(pessoas cuja transação com o usuário ainda não foi finalizada) do vértice uma pessoa.
	\param T é o ponteiro para o grafo de transações do grafo de um determinado usuário.
	\param trans é a string que, possivelmente, corresponde à transação que deseja-se inserir uma aresta.
	\param nome é a string que corresponde ao nome da pessoa.
	*/  

	if(v = pesquisa_verticeT(T, trans)) // checa se a stirng correspondente a transação de fato existe na lista de vértices do grafo
	{
		a_aux = (p_arestaT)malloc(sizeof(tp_arestaT)); // aloca-se a aresta(pessoa)
		assert(a_aux); // checa se foi alocada.
		a_aux->ant = v->ultimo; // faz o encadeamento.
		v->ultimo->prox = a_aux;
		v->ultimo = a_aux;
		strcpy(a_aux->pessoa,nome); // copia-se o nome da pessoa à aresta.
		a_aux->prox = NULL;
	}
	else // cria-se um novo vértice cujo nome deve ser a transação.
	{
		adiciona_vertice_T(T, trans); //cria-se o novo vértice no grafo 
		adiciona_aresta_T(T, trans, nome); // adiciona-se a nova aresta nesse novo vértice criado

	}
}

/*******************************************************
*Função: Remove um vértice do grafo T
*Descrição
*	Remove um vértice(transação) do grafo de transação
*	desse usuário.	
*
*Parâmetros
*	T - o grafo de transação desse usuário.
*	trans - a string que condiz à transação que deseja-se remover do grafo(transação concluida).
*
*Assertiva de entrada
*	O grafo deve ser criado previamente.
*	O nome da transação não pode conter *, apenas caracteres alfabéticos.
*
*Assertiva de saída
*	O vértice correspondente a trans deve ser removido.
*********************************************************/

/** \brief  Função que remove um vértice(transação) do grafo de transações do usuário.*/
void remove_vertice_T(p_grafo_trans T, char *trans)
{
	p_verticeT V;
	p_arestaT A, A2;

	/**  
	\details Libere a memória reservada para essa transação(vértice), bem como todas as suas arestas(pessoas).
	\param T é o ponteiro para o grafo de transações do grafo de um determinado usuário.
	\param trans é a string que, possivelmente, corresponde à transação que deseja-se inserir uma aresta.
	*/  

	if(V = pesquisa_verticeT(T, trans)) // pesquisa se o nome da transação existe de fato
	{
		A = V->head; // recebe a célula cabeça desse vértice(transação)
		while(A)
		{
			A2 = A;
			A = A->prox;// salva-se o restante da lista.
			free(A2); // libera-se a aresta.
		}
		if(V == T->ultimo) // se for o último vértice do grafo
			T->ultimo = V->ant;
		else
			V->prox->ant = V->ant;
		V->ant->prox = V->prox;
		free(V); // libera-se o vértice
	}
}


/*LISTAS*/

/*******************************************************
*Função: Cria-se uma lista de transação
*
*Descrição
*	Cria-se uma lista de transação que contém todas as possíveis
*	transações(carona, viagem, aluguel etc) que podem ser realizadas.
*
*Valor retornado
*	T - a lista de transação criada.
*
*Assertiva de saída
*	Deve retornar um ponteiro para listatrans.
*********************************************************/


/** \brief  Função que cria uma lista(transações) que irá conter todas as transações cadastradas pelo administrador.*/
p_listatrans cria_lista_trans()
{
	p_listatrans T; 

	/**  
	\return um ponteiro para lista de transações.
	*/  

	T = (p_listatrans)malloc(sizeof(tp_listatrans));// aloca-se a lista de transação
	assert(T); // checa se foi de fato alocado o espaço para a lista


	T->head = (p_transacao)malloc(sizeof(tp_transacao)); //cria-se a célula cabeça
	assert(T->head);// checa se foi de fato alocado o espaço
	T->ultimo = T->head;

	T->head->prox = NULL;
	T->head->ant = NULL;

	return T; // retorno da lista criada e alocada devidamente
}

/*******************************************************
*Função: Carrega transação
*
*Descrição
*	Lê-se do arquivo de transação(trans) todas as ransferências(cadastradas pelo administrador) 
*	que pode ser realizadas pelos usuários.
*	
*Valor retornado
*	lista - a lista de transação criada e completa com todas as possíveis transações.
*
*Assertiva de entrada
*	O nome do arquivo de leitura não deve ser alterado.
*	O nome das transação não podem conter caracteres especiais(apenas alfabéticos).
*
*Assertiva de saída
*	Deve retornar NULL, caso o arquivo não contenha nada, ou uma lista contendo
*	todas as transações cadastradas pelo administrador.
*********************************************************/

/** \brief  Função que lê do arquivo "trans.txt" todas as transações previamente criadas pelo administrador e armazena na lista.*/
p_listatrans carrega_trans(){
	char s[50]; //string auxiliar
	p_listatrans lista;
	int size; //tamanho da string
	int i;
	FILE *arq;

	/**  
	\return um ponteiro para lista de transações.
	*/ 

	if(arq = fopen("trans.txt","r")) // abre o arquivo para leitura(se tiver, de fato, algo para ler)
	{
		lista = cria_lista_trans(); // aloca-se a célula cabeça
		while(!feof(arq)) // enquanto não chegar ao final do arquivo
		{
			fscanf(arq,"%d", &size); // lê-se o tamanho da string que irá corresponder ao nome da transação
			if(feof(arq)) return lista; // se chegou no final do arquivo nesse ponto
			fgets(s, size+1,arq); // armazena-se na string auxiliar
			fgetc(arq); //pegar o \n
			cadastra_trans(lista, s); // insere na lista de transação.
		}
		fclose(arq); // fecha-se o arquivo.
	}else
		return NULL; // não há nada para ler
	
	return lista; // retorna a lista
}

/*******************************************************
*Função: Cadastra transação
*
*Descrição
*	Insere na lista de transações uma possível transação com o nome 'x'.
*	
*Parâmentros
*	T - a lista de transação.
*	x - o possível nome da transação.
*
*Valor retornado
*	TRUE - foi possível inserir a transação.
*	FALSE - não foi possível inserir, visto que uma transação com esse nome já existe.
*
*Assertiva de entrada
*	a string 'x' deve ser inserida apenas com caracteres alfabéticos(padrões).
*
*Assertiva de saída
*	Deve retornar TRUE se a inserção do item foi feita bem sucedida, ou
*	retornar FALSE caso esse item('x') já exista na lista.
*********************************************************/

/** \brief  Função que insere(cadastra) na lista de transações uma transação que o administrador deseja.*/
int cadastra_trans(p_listatrans T ,char *x){
	p_transacao p = T->head->prox;

	/** 
	\param T lista de transações cadastradas. 
	\param x string que corresponde à transação que deseja-se cadastrar.
	\return TRUE se teve sucesso na hora de cadastrar, ou FALSE caso essa transação já esteja cadastrada.
	*/


	assert(T);// checa se a lista de fato existe
	if(pesquisa_trans(T, x) == NULL){ // caso a transacao não exista(leva-se em consideração o nome fornecido)
		p = (p_transacao)malloc(sizeof(tp_transacao)); // aloca-se espaço para esse no
		assert(p); // checa se foi de fato alocado espaço

		T->ultimo->prox = p;
		p->ant = T->ultimo;
		T->ultimo = p;
		p->prox = NULL;

		strcpy(p->trans,x); // copia-se o nome 'x' para esse novo item da lista

		return TRUE; // sucesso na inserção
	}
	else
		//transacao ja existe
		return FALSE;
}
/*******************************************************
*Função: Remove transação
*
*Descrição
*	Remove da lista de transações uma possível transação com o nome 's'.
*	
*Parâmentros
*	T - a lista de transação.
*	s - o possível nome da transação.
*
*Valor retornado
*	TRUE - foi possível remover a transação.
*	FALSE - não foi possível remover, visto que uma transação com esse nome não existe.
*
*Assertiva de entrada
*	a string 's' deve ser inserida apenas com caracteres alfabéticos(padrões).
*
*Assertiva de saída
*	Deve retornar TRUE se a remoção do item foi feita bem sucedida, ou
*	retornar FALSE caso esse item('x') não exista na lista.
*********************************************************/

/** \brief  Função que remove(descadastra) da lista de transações uma transação que o administrador deseja.*/
int remove_trans(p_listatrans T, char *s){
	p_transacao x;

	/** 
	\param T lista de transações cadastradas. 
	\param s string que corresponde à transação que deseja-se descadastrar.
	\return TRUE se teve sucesso na hora de descadastrar, ou FALSE caso essa transação não esteja cadastrada.
	*/

	assert(T); // checa se a lista já existe.

	if(x = pesquisa_trans(T, s)) // checa se existe uma transação cujo nome corresponde a 's'
	{
		if(x == T->ultimo) // checa se for o último item da lista de transação
			T->ultimo = x->ant;
		else
			x->prox->ant = x->ant;
		x->ant->prox = x->prox;
		
		free(x); // libera-se esse item

		return TRUE; // sucesso na remoçao
	}else
		return FALSE;// não existe a transacao

}
/*******************************************************
*Função: Pesquisa transação
*
*Descrição
*	Pesquisa na lista de transações uma possível transação com o nome 's'.
*	
*Parâmentros
*	T - a lista de transação.
*	s - o possível nome da transação.
*
*Valor retornado
*	NULL - não foi possível encoutrar uma transação cujo nome corresponde-se a 's'.
*	p -ponteiro para essa essa transação buscada.
*
*Assertiva de entrada
*	a string 's' deve ser inserida apenas com caracteres alfabéticos(padrões).
*
*Assertiva de saída
*	Deve retornar um ponteiro para um item da lista, ou NULL caso esse item('s') não exista
*********************************************************/

/** \brief  Função que pesquisa na lista de transações uma transação desejada.*/
p_transacao pesquisa_trans(p_listatrans T, char *s){
	p_transacao p = T->head->prox; // recebe o primeiro item da lista de transaçoes

	/** 
	\param T lista de transações cadastradas. 
	\param s string que corresponde à transação que deseja-se pesquisar.
	\return um ponteiro para esse item da transação ou NULL caso não tenha achado a transação buscada(não foi previamente cadastrada).
	*/

	assert(T); // checa se a lista, de fato, existe
	while(p) // enquanto não chegar ao fim da lista
	{
		if(!strcmp(s, p->trans)) // se esse item da lista possui o mesmo nome que a transação
			return p; // retorna o ponteiro para esse item da lista
		p = p->prox;
	}
	return NULL; // não foi possivel encontrar uma transação cujo nome fosse 's'
}
/*******************************************************
*Função: Salva Transações
*
*Descrição
*	Salva todas as transações cadastradas pelo administrador no arquivo "trans.txt"
*	
*Parâmentros
*	T - a lista de transação.
*
*Assertiva de entrada
*	O nome das transações deve ser inserido apenas com caracteres alfabéticos(padrões).
*
*Assertiva de saída
*	Deve salvar no arquivo "trans.txt" todas as informações contidas na lista.
*********************************************************/

/** \brief  Função que salva no arquivo "trans.txt" todas as transações cadastradas pelo administrador.*/
int salva_trans(p_listatrans T){
	FILE *arq;
	p_transacao p = T->head->prox;// recebe o primeiro item da lista de transação

	/** 
	\param T lista de transações cadastradas. 
	*/

	if(arq = fopen("trans.txt","w")) // abre o arquivo "trans.txt" para escrita
	{
		while(p) // enquanto não chegar ao final da lista de transações
		{
			fprintf(arq,"%d", (int)strlen(p->trans)); // escreve o tamanho da string que corresponde a transação
			fputs(p->trans,arq); // escreve a transação
			fprintf(arq,"\n");
			p = p->prox;
		}
	}
	fclose(arq); // fecha-se o arquivo
}

/*******************************************************
*Função: Destroi Transações
*
*Descrição
*	Libera a memória armazenada para a lista de transações.	
*	
*Parâmentros
*	T - a lista de transação.
*
*Assertiva de entrada
*	O nome das transações deve ser inserido apenas com caracteres alfabéticos(padrões).
*
*Assertiva de saída
*	Função deve liberar o espaço alocado para a lista.
*
*********************************************************/

/** \brief  Função que libera toda a lista de transações cadastradas.*/
void destroi_trans(p_listatrans T){
	p_transacao p = T->head, p2 = NULL;
	
	/** 
	\param T lista de transações cadastradas. 
	*/
	while(p) // enquanto não chegar ao final da lista
	{
		p2 = p; 
		p = p->prox; // salva-se o restante da lista
		free(p2); // elimina-se esse item
	}

	free(T); // elimina-se a estrutura listaT
}
/*******************************************************
*Função: Imprime Transações
*
*Descrição
*	Imprime todas as transações cadastradas pelo administrador.
*	
*Parâmentros
*	T - a lista de transação.
*
*Assertiva de entrada
*	O nome das transações deve ser inserido apenas com caracteres alfabéticos(padrões).
*
*********************************************************/

/** \brief  Função que imprime todas as transações cadastradas pelo administrador.*/
void imprime_trans(p_listatrans T)
{

	/** 
	\param T lista de transações cadastradas. 
	*/
	p_transacao p = T->head->prox; // recebe o primeiro item da lista de transação

	while(p) // enquanto não chegar ao final da lista de transação 
	{
		printf("%s.\n", p->trans); // imprime a transação

		p = p->prox;
	}
}


/*LISTA DE HISTÓRICO E REQUISITOS*/


/*******************************************************
*Função: Adiciona um nó a lista(REQUERIDO OU HISTÓRICO)
*
*Descrição
*	Adiciona um novo item ou na lista em que esse usuário foi requerido(seus dados correspondem aos pedidos por um outro usuário)
*	ou na lista que contém o seu histórico de transações efetivadas.
*	
*Parâmentros
*	lista - a lista(ou de requerido ou o historico de transações).
*	trans - o possível nome da transação que deseja-se adicionar à lista.
*	nome - o possivel nome da pessoa que pediu(lista de requerido) ou da outra pessoa
*		   que estava envolvida na transação que já foi realizada.	
*
*Valor retornado
*	Ponteiro para esse item da lista(no).
*
*Assertiva de entrada
*	O nome das transações deve ser inserido apenas com caracteres alfabéticos(padrões),
*	bem como o nome da pessoa.
*
*Assertiva de saída
*	Função deve retornar o ponteiro para esse novo item da lista.
*********************************************************/


/** \brief  Função que adiciona um nó na lista de transações(REQUERIDO OU HISTÓRICO) de um usuário.
A lista de requerido contém os convites que esse usuário recebe ao corresponder aos requerimentos de uma 
transação criada por outro usuário.
A lista de histórico contém todas as transações em que esse usuário participou.
*/
p_noT adicionaNO(p_listaT lista, char *trans, char *nome)
{
	/** 
	\param lista É a lista que pode ser tanto de requerido quanto o histórico.
	\param trans É a transação que deseja-se inserir.
	\param nome É o nome da pessoa com quem esse usuário está envolvido(lista de requerido) ou se envolveu(histórico).
	\return O nó que foi adicionado à lista.
	*/


	p_noT T_aux;
	T_aux = (p_noT)malloc(sizeof(tp_noT)); // aloca-se espaço para esse no
	assert(T_aux); // checa se foi de fato alocado espaço


	T_aux->ant = lista->ultimo;
	lista->ultimo->prox = T_aux;
	lista->ultimo = T_aux;
	T_aux->prox = NULL;

	strcpy(T_aux->trans,trans); // copia-se o nome da transaçao para esse no
	strcpy(T_aux->pessoa,nome); // copia-se o nome da pessoa para esse no


	return T_aux;
/*VERIFICAR SE PODE HAVER REPETIÇÃO DE PEDIDOS DO MESMO TIPO DE TRANSAÇÃO*/
}

/*******************************************************
*Função: Destroi a lista(REQUERIDO OU HISTÓRICO)
*
*Descrição
*	Libera a memória reservada para essa lista.
*	
*Parâmentros
*	T - ponteiro para a lista(ou de requerido ou de histórico).	
*
*Assertiva de saída
*	Função deve liberar todo espaço que foi reservado para essa lista(bem como todos os seus itens).
*********************************************************/


/** \brief  Função que libera a memória reservada para a lista de transações(REQUERIDO OU HISTÓRICO) de um usuário.
A lista de requerido contém os convites que esse usuário recebe ao corresponder aos requerimentos de uma 
transação criada por outro usuário.
A lista de histórico contém todas as transações em que esse usuário participou.
*/
void destroi_T(p_listaT T){
	p_noT p = T->head, p2 = NULL;

	/** 
	\param T É a lista que pode ser tanto de requerido quanto o histórico.
	*/

	while(p) // enqaunto nao for o final da lista
	{
		p2 = p;
		p = p->prox; // salva-se o restante da lista
		free(p2); // libera esse item
	}

	free(T); // libera a celula cabeça
}
/*******************************************************
*Função: Remove item da lista(REQUERIDO OU HISTÓRICO)
*
*Descrição
*	Libera a memória reservada para esse item da lista.
*	
*Parâmentros
*	T - ponteiro para a lista(ou de requerido ou de histórico).	
*	x - ponteiro para o item da lista(no).
*
*Valor retornado
*	TRUE - sucesso ao remover o item da lista.
*	FALSE - não foi possível remover, visto que o item não existe.
*
*Assertiva de saída
*	Função deve liberar todo espaço que foi reservado para esse item da lista.
*********************************************************/

/** \brief  Função que remove um item da lista de transações(REQUERIDO OU HISTÓRICO) de um usuário.
A lista de requerido contém os convites que esse usuário recebe ao corresponder aos requerimentos de uma 
transação criada por outro usuário.
A lista de histórico contém todas as transações em que esse usuário participou.
*/
int remove_T(p_listaT T, p_noT x){
	
	assert(T);

	/** 
	\param T É a lista que pode ser tanto de requerido quanto o histórico.
	\param x é o nó que deseja-se remover da lista.
	\return TRUE se a remoção foi bem sucedida, ou FALSE caso esse nó não exista.
	*/

	if(x) // se o nó existe
	{
		if(x == T->ultimo) // se ele for o ultimo item da lista de transação
			T->ultimo = x->ant;
		else
			x->prox->ant = x->ant;
		x->ant->prox = x->prox;
		
		free(x); // libera-se o nó

		return TRUE; // sucesso ao remover o nó
	}else
		return FALSE;// não existe a transacao
}

/*******************************************************
*Função: Pesquisa item da lista(REQUERIDO OU HISTÓRICO)
*
*Descrição
*	Realiza uma busca na lista para retornar o ponteiro para esse determinado item, 
*	levando em consideração o nome da transação.
*	
*Parâmentros
*	T - ponteiro para a lista(ou de requerido ou de histórico).	
*	s - string que corresponde ao nome da transação.
*	aval - flag que informa se a pesquisa deve levar em consideração o fato
*	da pessoa já ter avaliado, ou nao, uma transação.
*
*Valor retornado
*	NULL - Não foi possível encontrar essa transação.
*	p - a transação buscada foi encontrada.
*
*Assertiva de entrada
*	O nome da transação não pode conter caracteres especiais, apenas alfabéticos.
*
*Assertiva de saída
*	Dado que os paramêtros foram entrados de forma correta, a função deve retornar ou NULL ou p.
*********************************************************/

/** \brief  Função que busca por um item da lista de transações(REQUERIDO OU HISTÓRICO) de um usuário.
A lista de requerido contém os convites que esse usuário recebe ao corresponder aos requerimentos de uma 
transação criada por outro usuário.
A lista de histórico contém todas as transações em que esse usuário participou.
*/
p_noT pesquisa_T(p_listaT T, char *s, int aval){
	p_noT p = T->head->prox;

	/** 
	\param T É a lista que pode ser tanto de requerido quanto o histórico.
	\param s é a string que, possivelmente, corresponde à transação que se está buscando.
	\param aval É uma flag que informa se a busca deve levar em consideração se a transação que se está buscando já foi avaliada ou não.
	\return um ponteiro para um nó da lista(busca realizada com sucesso), ou NULL caso esse nó não exista.
	*/

	assert(T);
	if(!aval)
	{
		while(p){
			if(!strcmp(s, p->trans))
				return p;
			p = p->prox;
		}
	}
	else
	{
		while(p){
			if(!strcmp(s, p->trans) && !p->aval)
				return p;
			p = p->prox;
		}
	}

	return NULL;
}
/*******************************************************
*Função: Cria a lista(REQUERIDO OU HISTÓRICO)
*
*Descrição
*	Realiza a criação da lista(REQUERIDO OU HISTÓRICO).
*	
*Valor retornado
*	T - o ponteiro para a lista criada.
*
*Assertiva de saída
*	Deve retornar um ponteiro para lista.
*********************************************************/

/** \brief  Função que cria uma lista de transações(REQUERIDO OU HISTÓRICO) de um usuário.
A lista de requerido contém os convites que esse usuário recebe ao corresponder aos requerimentos de uma 
transação criada por outro usuário.
A lista de histórico contém todas as transações em que esse usuário participou.
*/
p_listaT cria_listaT()
{
	/** 
	\return um ponteiro para a lista criada(pode ser tanto de requerido quanto de histórico).
	*/
	p_listaT T; 

	T = (p_listaT)malloc(sizeof(tp_listaT));// aloca-se a lista
	assert(T); // checa se foi de fato alocado memória


	T->head = (p_noT)malloc(sizeof(tp_noT)); //cria-se a célula cabeça
	assert(T->head);// checa se foi de fato alocado o espaço
	T->ultimo = T->head;

	T->head->prox = NULL;
	T->head->ant = NULL;

	return T; // retorna-se o ponteiro para a lista
}

/*******************************************************
*Função: Imprime o grafo de transações
*
*Descrição
*	Percorre a o grafo imprimindo cada vértice e aresta(tanto a transação quanto as pessoas).
*	
*Paramêtros
*	T - ponteiro para o grafo de transações desse usuário.
*
*Assertiva de entrada
*	Os nomes das transações e das pessoas não deve conter caracteres especiais, apenas
*	alfabéticos.
*
*Assertiva de saída
*	Deve imprimir todo o grafo.
*********************************************************/

/** \brief Função que imprime todas as informações do grafo de transações criadas, mas não finalizadas, de um usuário
bem como seus vértices e arestas.
*/
void imprime_grafoT(p_grafo_trans T){
	p_verticeT v = T->head->prox; // recebe o primeiro vértice do grafo
	p_arestaT  a;
	
	/**
	\param T É o ponteiro para o grafo de transações de um usuário.
	*/

	while(v) // enquanto não chegar ao final da lista de vértices desse grafo
	{
		a = v->head->prox; // recebe a lista de arestas desse vértice
		printf("%s\n", v->trans); // imprime a transaçao
		while(a) // enquanto não chegar ao final da lista de arestas desse vértice
		{
			printf("\t%s\n", a->pessoa); // imprime a pessoa cuja transação está em andamento
			a = a->prox;
		}
		v = v->prox;
	}	
}

