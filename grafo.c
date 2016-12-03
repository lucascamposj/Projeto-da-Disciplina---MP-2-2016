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
*Parâmetros
*Valor retornado
*	G - ponteiro para a estrutura Grafo inicializada.
*Assertiva de entrada
* --------------------
*Assertiva de saida
*	O ponteiro G não pode ter valor NULL.
*********************************************************/

p_grafo cria_grafo()
{
	p_grafo G; 

	G = (p_grafo)malloc(sizeof(tp_grafo));// aloca-se o grafo(rede social)
	assert(G); // checa se foi de fato alocado o espaço para o grafo


	G->head = (p_vertice)malloc(sizeof(tp_vertice)); //cria-se a célula cabeça
	assert(G->head);// checa se foi de fato alocado o espaço
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

	assert(G); // checa se o grafo de fato existe
	/*verifica fim da lista de vertices*/
	while(v_aux != NULL) // percorre todos os vértices(usuários) até terminar a lista de vértices
	{
		a_aux = v_aux->head->prox; // recebe a lista de arestas desse vértice(lista de amigos desse usuário)
		/*verifica fim da lista de arestas*/         
		while(a_aux != NULL){
			a_aux2 = a_aux;
			a_aux = a_aux->prox;
			free(a_aux2); // libera essa aresta(amizade)
		}
		free(v_aux->head); // libera a célula cabeça desse vértice(usuário)
		v_aux2 = v_aux;
		v_aux = v_aux->prox;
		free(v_aux2); // libere o véritce(usuário)
	}
	free(G->head); // libera a célula cabeça do grafo
	free(G); // libera o grafo
}

/*******************************************************
*Função: Adiciona usuário
*Descrição
*	Adiciona um usuário a Rede Social.
*
*Parâmetros
*	G - Ponteiro para a estrutura de um grafo.
*	x - As informações do usuário(tipo estrutura user).
*
*Assertiva de entrada
*	A estrutura do grafo necessita estar inicializada. G não pode possuir o valor NULL.
*	Nenhum campo de informação do usuário deve conter o caracter '*'.
*
*Assertiva de saída
*	O usuário será inserido na rede social, caso ele ainda não esteja(checa se o nome já existe).
*********************************************************/

boolean adiciona_usuario(p_grafo G, tp_user x)
{
	p_vertice p = G->head->prox;

	assert(G);// checa se o grafo de fato existe
	if(pesquisa_vertice(G, x.nome) == NULL){ // caso esse usuário não exista(leva-se em consideração o nome fornecido)
		p = (p_vertice)malloc(sizeof(tp_vertice)); // aloca-se espaço para esse vértice(usuário)
		assert(p); // checa se foi de fato alocado espaço

		G->ultimo->prox = p;
		p->ant = G->ultimo;
		G->ultimo = p;
		p->prox = NULL;

		p->usuario = x;

		p->head = (p_aresta)malloc(sizeof(tp_aresta)); // aloca-se a célula cabeça para a sua lista de arestas(amizades)
		assert(p->head); // checa se foi de fato alocado espaço
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
*Função: Edita usuário
*Descrição
*	Edita um usuário da Rede Social.
*Parâmetros
*	user - ponteiro para o usuário que deseja-se editar
*
*Assertiva de entrada
*	o usuário deve existir no grafo.
*	Nenhum campo de informação do usuário deve conter o caracter '*'.
*
*Assertiva de saída
*	O usuário será inserido na rede social, caso ele ainda não esteja(checa se o nome já existe).
*********************************************************/

boolean edita_usuario(p_user user)
{
	char opcao, interesse[200];
	boolean sair = FALSE;
	int i, j;
	do
	{
		/*Menu para a edição do usuário*/
		sair = FALSE;
		system("clear");
	    printf("***************OPCOES DE EDICAO***********************\n");
	    printf("*(1)Editar nome.                                     *\n");
	    printf("*(2)Editar genero.                                   *\n");
	    printf("*(3)Editar idade.                                    *\n");
	    printf("*(4)Editar escolaridade.                             *\n");
	    printf("*(5)Editar cep.                                      *\n");
	    printf("*(6)Adicionar interesse.                             *\n");
	    printf("*(7)Remover interesse.                               *\n");
	    printf("*Para voltar digite x.                               *\n");
	    printf("******************************************************\n");
	    scanf("%c", &opcao);
	    getchar();

	    switch(opcao)
	    {
	    	case '1':
	    		printf("Digite o novo nome: ");
	    		scanf("%[^\n]s", user->nome);
	    		getchar();
	    		break;
			
			case '2':
				printf("Digite o novo gênero: ");
	    		scanf("%c", &user->genero);
	    		getchar();
				break;
			
			case '3':
				printf("Digite a nova idade: ");
	    		scanf("%d", &user->idade);

				break;
			
			case '4':
				printf("Digite a nova escolaridade: ");
	    		scanf("%d", &user->escolaridade);

				break;
			
			case '5':
				printf("Digite o novo cep: ");
	    		scanf("%d", &user->cep);

				break;
			
			case '6':
				if(user->n_interesses < 20) // se não atingiu o máximo de interesses possíveis
				{
					printf("Digite um interesse: ");
					scanf("%[^\n]s", user->interesses[user->n_interesses]);
					getchar();
					user->n_interesses++;
				}
				else
				{
					printf("Máximo de interesses atingido.\nDigite qualquer tecla para continuar edicao.");
				}
				break;
			
			case '7':
				if(user->n_interesses > 0) // ele possui algum interesse previamente inserido
				{
					printf("Digite o interesse que deseja remover: ");
					scanf("%[^\n]s", interesse);
					getchar();
					for(i=0;i < user->n_interesses;i++)
					{
						if(!strcmp(user->interesses[i], interesse))
						{
							for(j=i;j<user->n_interesses-1;j++)
							{
								strcpy(user->interesses[j], user->interesses[j+1]);
							}
							user->n_interesses--;
							break;
						}
					}
				}	
				else
					printf("Nao possui nenhum interesse.\nDigite qualquer tecla para continuar edicao.\n");
				break;

			case 'x':
				sair = TRUE;
				break;

	    }
	}while(sair == FALSE);
}

/*******************************************************
*Função: Remove Usuário 
*Descrição
*	Remove um usuário da rede social. Além disso, realiza a liberação correta de memória.
*Parâmetros
*	G - Ponteiro para a estrutura de um grafo.
*	x - nome do usuário a ser removido.
*Assertiva de entrada
*	A estrutura do grafo necessitar estar inicializada. G não pode possuir o valor NULL.
*Assertiva de saída
*	Remove o usuário da rede social, caso ele exista(checa se o nome existe no grafo).
*********************************************************/

boolean remove_usuario(p_grafo G, char *x)
{
	p_vertice v_aux = G->head->prox;
	p_aresta a_aux = NULL, a_aux2 = NULL;

	assert(G); // checa se o grafo já existe

	v_aux = pesquisa_vertice(G, x); // recebe o ponteiro para o vértice(usuário) que possui esse nome

	if(v_aux == NULL) // usuário não existe
	{
		return FALSE;
	}
	else
	{	// percorre o grafo removendo a amizade
		a_aux = v_aux->head->prox; // recebe a lista de amizades(arestas) desse usuário
		while(a_aux)
		{
			a_aux2 = a_aux->amigo->head->prox; // recebe a lista de amizades desse amigo do usuário
			/*percorrendo amigo e elimando amizade com o usuario*/
			while(a_aux2)
			{
				if(a_aux2->amigo == v_aux) // se a amizade foi encontrada
				{
					if(a_aux2 == a_aux->amigo->ultimo)
						a_aux->amigo->ultimo = a_aux2->ant;
					else
						a_aux2->prox->ant = a_aux2->ant;
					a_aux2->ant->prox = a_aux2->prox;

					free(a_aux2); // libera a aresta(amizade)
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
*Função: Adiciona Amizade
*Descrição
*	Adiciona amizade entre dois usuários.
*Parâmetros
*	G - Ponteiro para a estrutura de um grafo.
*	x - Nome de um dos usuários.
*	Y - Nome do outro usuário.
*Assertiva de entrada
*	A estrutura do grafo necessita estar inicializada. G não pode possuir o valor NULL.
*Assertiva de saída
*	Adiciona amizade, tanto de x com y, quanto de y com x. Isso só é feito de x e y existem na rede social.
*********************************************************/

boolean adiciona_amizade(p_grafo G,char *x,char *y)
{
	p_vertice v_x = G->head, v_y = NULL;
	p_aresta a_aux;

	assert(G); // checa se o grafo já existe

	/*Checa se os dois usuários, com os nomes fornecidos, existem*/
	if((v_x = pesquisa_vertice(G, x)) != NULL && (v_y = pesquisa_vertice(G, y)) != NULL)
		if(pesquisa_aresta(v_x, y) == NULL){
			/*adicionando a amizade em x*/
			a_aux = (p_aresta)malloc(sizeof(tp_aresta)); // aloca-se a aresta(amizade)
			assert(a_aux); // checa se foi alocada
			a_aux->ant = v_x->ultimo; // faz o encadeamento
			v_x->ultimo->prox = a_aux;
			a_aux->prox = NULL;

			v_x->ultimo = a_aux; // insere no final da lista de amizades
			a_aux->amigo = v_y;

			/*adicionando em y*/
			a_aux = (p_aresta)malloc(sizeof(tp_aresta));// aloca-se a aresta(amizade)
			assert(a_aux);// checa se foi alocada
			a_aux->ant = v_y->ultimo;// faz o encadeamento
			v_y->ultimo->prox = a_aux;
			a_aux->prox = NULL;

			v_y->ultimo = a_aux;// insere no final da lista de amizades
			a_aux->amigo = v_x;
			
			return TRUE;
		}
		else // não existe amizade entre os 2 usuários
			return FALSE;
	else// algum usuário inserido não existe
		return FALSE;
}

/*******************************************************
*Função: Remove Amizade
*Descrição
*	Remove amizade entre dois usuários.
*Parâmetros
*	G - Ponteiro para a estrutura de um grafo.
*	x - Nome de um usuário.
*	y - Nome de um usuário.
*Assertiva de entrada
*	A estrutura do grafo necessita estar inicializada. G não pode possuir o valor NULL.
*Assertiva de saída
*	Remove a amizade entre o usuário x e y, caso os 2 nomes existam na rede social.
*********************************************************/

boolean remove_amizade(p_grafo G,char *x, char *y)
{
	p_vertice v_x = NULL, v_y = NULL;
	p_aresta a_aux;

	assert(G); // checa se o grafo já existe

	/*Checa se os dois usuários, com os nomes fornecidos, existem*/
	if((v_x = pesquisa_vertice(G, x)) != NULL && (v_y = pesquisa_vertice(G, y)) != NULL){
		/*Checa se existe amizade entre esses 2 usuários*/
		if((a_aux = pesquisa_aresta(v_x, y)) != NULL){
			if(a_aux == v_x->ultimo)
				v_x->ultimo = a_aux->ant;
			else
				a_aux->prox->ant = a_aux->ant;
			
			a_aux->ant->prox = a_aux->prox;

			free(a_aux);
		}else
			return FALSE;// não existe amizade
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
	else // algum dos 2 usuários inseridos não existe
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
*	Retorna um valor booleano que indica se a rede socil está vazia ou não.
*	True - caso a rede esteja vazia.
*	False - caso contrário.
*Assertiva de entrada
*	A estrutura do grafo necessita estar inicializada. G não pode possuir o valor NULL.
*********************************************************/
boolean grafo_vazio(p_grafo G)
{
	if(G->head == G->ultimo) // se a célula cabeça é o fim do grafo
		return TRUE;
	else 
		return FALSE;
}

/*******************************************************
*Função: Vértice isolado
*Descrição
*	Verifica se um usuário não possui amizades.
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
	if(A->head == A->ultimo) // se a célula cabeça é o fim do grafo
		return TRUE;
	else
		return FALSE;
}
/*******************************************************
*Função: Pesquisa Vertice
*Descrição
*	Usada em outras funções, esta realiza uma busca na rede para verificar se, dado um nome, 
*	existe um usuário com este nome.
*Parâmetros
*	G - Ponteiro para a estrutura de um grafo.
*	x - Nome de um usuário.
*
*Valor retornado
*	p - Ponteiro para o usuário com este nome(foi encontrado).
*	NULL - Este nome não existe na rede social(não foi encontrado).
*
Assertiva de entrada
*	A estrutura do grafo necessita estar inicializada. G não pode possuir o valor NULL.
*********************************************************/
p_vertice pesquisa_vertice (p_grafo G, char *x){
	p_vertice p = G->head->prox;

	assert(G);

	/*Se o grafo não está vazio*/
	if(grafo_vazio(G) == FALSE){
		while(p != NULL){ // enquanto não chegar no final da lista de usuários
			if(strcmp(x, p->usuario.nome) == 0) // compara o nome, se for igual ao do inserido via terminal
				break;
			p = p->prox;
		}
		if(p != NULL)
			return p; // retorna o ponteiro para esse usuário
		else
			return NULL;
	}
	else // grafo não possui vértices(usuários)
	{
		return NULL;
	}
}
/*******************************************************
*Função: Pesquisa aresta
*Descrição
*	Realiza uma busca na lista de amizades de um dado usuário(caso ele exista), em busca de
*	uma determinada amizade.
*
*Parâmetros
*	V - Ponteiro para o usuário.
*	x - Nome de um usuário(suposta amizade).
*
*Valor retornado
*	p - Ponteiro para o usuário com este nome(foi encontrada a amizade).
*	NULL - Este nome não existe na lista de amizades deste usuário(não foi encontrado).
*
*Assertiva de entrada
*	V não pode ser NULL; deve estar inicializado.
*	x deve ser diferente de NULL.			
*********************************************************/
p_aresta pesquisa_aresta(p_vertice  V, char *x){
	p_aresta p = V->head->prox;

	assert(V);// checa se o vértice existe(foi alocado da forma correta)
	assert(x);

	if(vertice_vazio(V) == FALSE){ // se o usuário possuir amizades
		while(p != NULL){
			if(strcmp(x, p->amigo->usuario.nome) == 0) // percorre sua lista de amizades até encontrar
				break;
			p = p->prox;
		}
		if(p != NULL) // se encontrou
			return p; // retorna ponteiro para esse amigo
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}
/*******************************************************
*Função: Imprime grafo
*Descrição
*	Imprime todas as informações da rede social, bem como:
*	Usuários, amizades e transações.
*
*Parâmetros
*	G - ponteiro para estrutura grafo.	
*
*Assertiva de entrada
*	o grafo deve estar inicializado.		
*********************************************************/
boolean imprime_grafo(p_grafo G)
{
	p_vertice v_aux = G->head->prox;
	p_aresta a_aux;
	int i;

	while(v_aux) // enquanto não chegar no final da lista de usuários
	{
		// imprime o nome e o endereço desse usuário, bem como o endereço do usuário anteror e posterior
		printf("%s: %p | ant: %p | prox: %p\n", v_aux->usuario.nome,v_aux,v_aux->ant,v_aux->prox); 
		a_aux = v_aux->head->prox;
		// imprime as informações deste usuário(genero, idade, escolaridade, cep, interesses)
		printf("\t%c\n", v_aux->usuario.genero);
		printf("\t%d\n", v_aux->usuario.idade);
		printf("\t%d\n", v_aux->usuario.escolaridade);
		printf("\t%d\n", v_aux->usuario.cep);
		printf("\tInteresses:\n");
		for(i=0;i<v->aux->usuario.n_interesses;i++)
		{
			printf("\t");
			puts(user->usuario.interesses[i]);
		}
		// imprime o endereço da lista de amizades 
		printf("\t\tHEAD: %p | ant: %p | prox: %p\n", v_aux->head,v_aux->head->ant,v_aux->head->prox);
		while(a_aux)
		{
			printf("\t\t%s: %p | ant: %p | prox: %p\n",a_aux->amigo->usuario.nome,a_aux,a_aux->ant,a_aux->prox);
			a_aux = a_aux->prox;
		}
		v_aux = v_aux->prox;
	}
}
/*******************************************************
*Função: Salva grafo
*Descrição
*	Salva as informações da rede social(usuários e amizades) num arquivo(user.txt)
*
*Parâmetros
*	G - ponteiro para estrutura grafo.	
*
*Assertiva de entrada
*	o grafo deve estar inicializado.		
*********************************************************/
boolean salva_grafo(p_grafo G)
{
	FILE *arq;
	p_vertice v = G->head->prox;
	p_aresta a = NULL;
	int i,j;


	arq = fopen("user.txt", "w");
	while(v)
	{
		fprintf(arq, ".");
		fprintf(arq, "%ld", strlen(v->usuario.nome));
		for(int i=0;i<strlen(v->usuario.nome); i++)
			fprintf(arq, "%c", v->usuario.nome[i]);
		fprintf(arq,"\n");
		fprintf(arq, "%c %d %d %d \n", v->usuario.genero, v->usuario.idade, v->usuario.escolaridade,v->usuario.cep);
		
		fprintf(arq, "%d\n", v->usuario.n_interesses);
		
		for(j=0;j<v->usuario.n_interesses;j++)
		{	
			fprintf(arq,"%ld", strlen(v->usuario.interesses[j]));
			for(i=0;i<strlen(v->usuario.interesses[j]); i++)
				fprintf(arq, "%c", v->usuario.interesses[j][i]);
			fprintf(arq, "\n");
		}	

		fprintf(arq, "*\n");
		a = v->head->prox;
		while(a)
		{
			fprintf(arq, "%ld", strlen(a->amigo->usuario.nome));
			fprintf(arq, "%s\n", a->amigo->usuario.nome);
			a = a->prox;
		}
		fprintf(arq, "*\n");
		v = v->prox;
	}

	fclose(arq);
	return TRUE;
}
/*******************************************************
*Função: Carrega grafo
*Descrição
*	Lê o arquivo "user.txt" e armazena suas informações no grafo(rede social)
*
*Valor retornado
*	G - Retorna o grafo contendo as informações do user.txt(rede social)		
*********************************************************/
p_grafo carrega_grafo()
{
	FILE *arq;
	p_grafo G = NULL;
	tp_user user;
	char nome[50], amigo[50];
	p_aresta a = NULL;
	int size,i,j;
	G = cria_grafo();
	if (!(arq = fopen("user.txt","r")))
	{
		printf("Arquivo não pode ser aberto\n");
		return G;
	}
	else
	{
		if(fgetc(arq) != '.')
			return G;
		else
		{
			do{
				fscanf(arq, "%d", &size);
				fgets(user.nome, size+1, arq);
				fgetc(arq);
				fscanf(arq,"%c", &user.genero);
				fgetc(arq);
				fscanf(arq,"%d", &user.idade);
				fgetc(arq);
				fscanf(arq,"%d", &user.escolaridade);
				fgetc(arq);
				fscanf(arq,"%d", &user.cep);
				fgetc(arq);
				fscanf(arq, "%d", &user.n_interesses);
				fgetc(arq);
				for(i=0;i<user.n_interesses;i++)
				{
					fscanf(arq, "%d", &size);
					fgets(user.interesses[i], size+1, arq);
					fgetc(arq);
				}
				if(fgetc(arq) == '*');
					while(fgetc(arq) != '.'){
						if(feof(arq))
							break;
					}
				adiciona_usuario(G, user);
			}while(!feof(arq));

			fseek(arq, 0, SEEK_SET);
			do{
				if(fgetc(arq) == '.'){
					fscanf(arq, "%d", &size);
					fgets(nome, size+1, arq);
					
					while(fgetc(arq) != '*')
					{
						if(feof(arq))
							break;
					}
					fgetc(arq);
					do{
						fscanf(arq, "%d", &size);
						fgets(amigo, size+1, arq);
						if(strcmp(amigo,"*"))
							adiciona_amizade(G, nome, amigo);
						else{ 
							break;
							fgetc(arq);
						}
						fgetc(arq);
					}while(!feof(arq));
				}
			}while(!feof(arq));
		}
	}
	fclose(arq);
	return G;
}