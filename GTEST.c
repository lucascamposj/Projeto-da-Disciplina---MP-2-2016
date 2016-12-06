#include <gtest/gtest.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

#define TRUE 1
#define FALSE 0

/**
	\mainpage
	\author Lucas Campos Jorge 150154135
	\author João Victor de Souza Poletti 150132425
	\date 06/12/2016

*/

/** @brief Verifica a funcionalidade da função "adiciona_usuario".Caso a inserção for bem sucedida,
retorna-se TRUE, caso contrário, FALSE.
*/
TEST(adiciona_usuario, Adicionar_usuario)
{
	p_grafo G;
	tp_user user;

	G = cria_grafo();
	ASSERT_EQ(TRUE,adiciona_usuario(G, user)); // insere um novo usuario
	ASSERT_EQ(FALSE,adiciona_usuario(G, user)); // tenta-se inserir esse mesmo usuário de novo
	
}

/** @brief Verifica a funcionalidade da função "remove_usuario".Caso a remoção for bem sucedida,
retorna-se TRUE, caso contrário, FALSE.
*/
TEST(remove_usuario, Remover_usuario)
{
	p_grafo G;
	tp_user user, user2, user3;
	char nome[] = "nome3";

	strcpy(user.nome,"nome");
	strcpy(user2.nome,"nome2");
	strcpy(user3.nome,"nome3");


	G = cria_grafo();
	ASSERT_EQ(TRUE,adiciona_usuario(G, user)); // insere 3 usuários
	ASSERT_EQ(TRUE,adiciona_usuario(G, user2));
	ASSERT_EQ(TRUE,adiciona_usuario(G, user3));

	ASSERT_EQ(TRUE,adiciona_amizade(G, user2.nome, user.nome)); // adiciona amizades
	ASSERT_EQ(TRUE,adiciona_amizade(G, user2.nome, user3.nome));

	ASSERT_EQ(TRUE,remove_usuario(G, user2.nome)); // ao remover este usuário, deve-se remover também todas as suas amizades
	
	ASSERT_EQ(FALSE,remove_usuario(G, user2.nome)); // tenta remover um usuário que já foi removido.

	ASSERT_EQ(TRUE,remove_usuario(G, user.nome)); // ao remover este usuário, deve-se remover também todas as suas amizades

	ASSERT_EQ(TRUE,remove_usuario(G, user3.nome)); // ao remover este usuário, deve-se remover também todas as suas amizades
		
	ASSERT_EQ(FALSE,remove_usuario(G, nome)); // tenta-se remover um usuário que nao foi previamente inserido(nome invalido)

	
}
/** @brief Verifica a funcionalidade da função "adiciona_amizade".Caso a inserçao for bem sucedida,
retorna-se TRUE, caso contrário, FALSE.
*/
TEST(adiciona_amizade, Adiciona_amizade){
	p_grafo G;
	tp_user user1, user2;
	char nome[] = "nome3";

	strcpy(user1.nome,"nome1");
	strcpy(user2.nome,"nome2");


	G = cria_grafo();
	ASSERT_EQ(TRUE,adiciona_usuario(G, user1)); // adiciona-se 2 usuários
	ASSERT_EQ(TRUE,adiciona_usuario(G, user2));
	ASSERT_EQ(TRUE,adiciona_amizade(G, user2.nome, user1.nome)); // adiciona uma amizade entre eles
	ASSERT_EQ(FALSE,adiciona_amizade(G, user2.nome, user1.nome)); // tenta-se adicionar uma amizade que ja foi efetuada
	
	ASSERT_EQ(FALSE,adiciona_amizade(G, user2.nome, nome)); // tenta-se adicionar uma amizade com um usuaŕio que nao foi previamente criado(nome invalido)

	
}
/** @brief Verifica a funcionalidade da função "remove_amizade".Caso a remoção for bem sucedida,
retorna-se TRUE, caso contrário, FALSE.
*/TEST(remove_amizade, Remove_amizade){
	p_grafo G;
	tp_user user1, user2;
	char nome[] = "nome3";

	strcpy(user1.nome,"nome1");
	strcpy(user2.nome,"nome2");

	G = cria_grafo();

	ASSERT_EQ(TRUE,adiciona_usuario(G, user1));// adiciona-se 2 usuários
	ASSERT_EQ(TRUE,adiciona_usuario(G, user2));
	ASSERT_EQ(TRUE,adiciona_amizade(G, user2.nome, user1.nome));// adiciona uma amizade entre eles

	ASSERT_EQ(TRUE,remove_amizade(G, user2.nome, user1.nome)); // remove-se a amizade criada
	ASSERT_EQ(FALSE,remove_amizade(G, user2.nome, user1.nome)); // tenta-se remover essa mesma amizade de novo

	ASSERT_EQ(FALSE,remove_amizade(G, user2.nome, nome)); // tenta-se remover uma amizade com um usuário que nao foi previamente criado(nome invalido)

	
}
/** @brief Verifica a funcionalidade da função "grafo_vazio".Caso o ponteiro head aponte para o ultimo,
e vice-versa, retorna-se TRUE, caso contrário FALSE(existem vértices neste grafo).
*/
TEST(grafo_vazio, Grafo_vazio){
	p_grafo G;
	tp_user user;

	G = cria_grafo();

	ASSERT_EQ(TRUE,grafo_vazio(G)); // não possui vértices

	ASSERT_EQ(TRUE,adiciona_usuario(G, user)); // adiciona-se um vértice
	ASSERT_EQ(FALSE,grafo_vazio(G)); // possui vértice

	
}
/** @brief Verifica a funcionalidade da função "verifica_vazio".Caso o ponteiro head aponte para o ultimo,
e vice-versa, retorna-se TRUE, caso contrário FALSE(existem arestas neste vertice).
*/
TEST(vertice_vazio, Vertice_vazio){
	p_grafo G;
	tp_user user1, user2;

	G = cria_grafo();


	ASSERT_EQ(TRUE,adiciona_usuario(G, user1));// cria-se um usuario
	ASSERT_EQ(TRUE,vertice_vazio(G->head->prox)); // não foi criada nenhuma amizade, entao o retorna será TRUE

	ASSERT_EQ(TRUE,adiciona_usuario(G, user2)); // cria-se um novo usuario
	ASSERT_EQ(TRUE,adiciona_amizade(G, user2.nome, user1.nome)); // adiciona-se uma amizade
	ASSERT_EQ(FALSE,vertice_vazio(G->head->prox)); // foi criada uma amizade, então a lista de arestas não está vazia

	
}
/** @brief Verifica a funcionalidade da função "pesquisa_vertice".Caso retorne NULL, o vértice não existe no grafo,
caso retorne um ponteiro para vértice, a pesquisa foi bem sucedida ao encontrar o usuario desejado.
*/
TEST(pesquisa_vertice, Pesquisa_vertice){
	p_grafo G;
	tp_user user;
	char nome[] = "nome2";

	strcpy(user.nome,"nome1");

	G = cria_grafo();

	//caso onde grafo está vazio
	EXPECT_EQ(NULL, pesquisa_vertice(G, nome));

	//caso sucesso
	ASSERT_EQ(TRUE,adiciona_usuario(G, user));
	ASSERT_EQ(G->head->prox, pesquisa_vertice(G, user.nome));

	//caso nome não encontrado
	EXPECT_EQ(NULL, pesquisa_vertice(G, nome));
}

/** @brief Verifica a funcionalidade da função "pesquisa_aresta".Caso retorne NULL, a aresta não existe no vértice,
caso retorne um ponteiro para aresta, a pesquisa foi bem sucedida ao encontrar a amizade desejada.
*/
TEST(pesquisa_aresta, Pesquisa_aresta){
		p_grafo G;
	tp_user user1, user2;
	char nome[] = "nome3";

	strcpy(user1.nome,"nome1");
	strcpy(user2.nome,"nome2");

	G = cria_grafo();

	ASSERT_EQ(TRUE,adiciona_usuario(G, user1));// cria-se um usuario

	EXPECT_EQ(NULL, pesquisa_aresta(G->head->prox, nome)); // como nao possui amizades, retorna NULL

	ASSERT_EQ(TRUE,adiciona_usuario(G, user2)); // cria-se novo usuario
	ASSERT_EQ(TRUE,adiciona_amizade(G, user2.nome, user1.nome)); // cria-se uma amizade entre eles
	ASSERT_EQ(G->head->prox->head->prox,pesquisa_aresta(G->head->prox, user2.nome)); // retorna essa amizade(aresta), visto que ela havia sido criada

	EXPECT_EQ(NULL,pesquisa_aresta(G->head->prox, nome)); // retorna NULL, visto que o usuario inserido nao foi previamente criado(nome invalido)

	
}



/** @brief Contém os testes automatizados de algumas funções dos módulos grafo.c, user.c e trans.c.
*/
int main(int argc, char**argv)
{

	::testing::InitGoogleTest(&argc, argv);
	  int opcao = 0, i;
	  char aux_interesse[] = "Interesse do usuario";
	  char aux_nome[] = "nome";
	  char aux_nome_falso[] = "false";

	  char aux_venda[] = "venda";
	  char aux_aluguel[] = "aluguel";
	  char aux_carona[] = "carona";
	  char aux_viagem[] = "viagem";


	  p_vertice vertice;
	  p_grafo G, G_teste;
	  tp_user x[6];

	printf("TESTE DE CRIACAO DE GRAFO\n");	 

	G = cria_grafo();
	assert(G);
	printf("\tPassou no teste de criacao de grafo.\n");

	printf("TESTE DA FUNCAO IMPRIME USUARIO\n");

	strcpy(x[0].nome, "nome0");
	strcpy(x[1].nome, "nome1");
	strcpy(x[2].nome, "nome2");
	strcpy(x[3].nome, "nome3");
	strcpy(x[4].nome, "nome4");
	strcpy(x[5].nome, "nome5");

	//TESTES DO MÓDULO GRAFO.C

	/* cria-se 6 usuários, preenchendo tanto seus grafos de transações, quanto suas
		listas de requerimento e histórico, para em fim imprimir todas as informações.
	*/
	for(i=0;i<6;i++)
	{
		x[i].idade = -1;
		x[i].genero = 'x';
		x[i].escolaridade = i;
		x[i].cep = 0;
		x[i].n_interesses = 2;
		strcpy(x[i].interesses[0], aux_interesse);
		strcpy(x[i].interesses[1], aux_interesse);
		x[i].quant_aval = 0;
		x[i].soma_aval = 0;
		x[i].grafoT = NULL;
		x[i].listaT_req = NULL;
		x[i].listaT_his = NULL;

		adiciona_usuario(G, x[i]);
	}

	x[3].quant_aval = 1;
	x[3].soma_aval = 10;

	vertice = G->head->prox;


	while(vertice)
	{	
		// adiciona-se transações em todos os usuários
		adiciona_vertice_T(vertice->usuario.grafoT, aux_carona);
		adiciona_vertice_T(vertice->usuario.grafoT, aux_aluguel);
		adiciona_vertice_T(vertice->usuario.grafoT, aux_venda);
		adiciona_aresta_T(vertice->usuario.grafoT, aux_venda, aux_nome);
		adiciona_aresta_T(vertice->usuario.grafoT, aux_carona, aux_nome);
		adiciona_aresta_T(vertice->usuario.grafoT, aux_aluguel, aux_nome);
		// todos os usuários recebem convites para transações
		adicionaNO(vertice->usuario.listaT_req, aux_carona, aux_nome);
		adicionaNO(vertice->usuario.listaT_req, aux_aluguel, aux_nome);
		adicionaNO(vertice->usuario.listaT_req, aux_venda, aux_nome);
		// todos os usuários possuem histórico de transações
		adicionaNO(vertice->usuario.listaT_his, aux_carona, aux_nome);
		adicionaNO(vertice->usuario.listaT_his, aux_aluguel, aux_nome);
		adicionaNO(vertice->usuario.listaT_his, aux_venda, aux_nome);

		vertice = vertice->prox;
	}

	// adiciona-se algumas amizades 
	adiciona_amizade(G, x[0].nome, x[1].nome);
	adiciona_amizade(G, x[0].nome, x[2].nome);
	adiciona_amizade(G, x[0].nome, x[3].nome);
	adiciona_amizade(G, x[1].nome, x[2].nome);
	adiciona_amizade(G, x[1].nome, x[3].nome);
	adiciona_amizade(G, x[2].nome, x[3].nome);

	imprime_grafo(G);

	printf("\tPassou no teste.\n");

	// testa se o programa está salvando o grafo corretamente no arquivo "user.txt" 
	printf("TESTE DE SALVA GRAFO\n");

	i = salva_grafo(G);
	if(i == TRUE)
		printf("\tPassou no teste.\n");

	// testa se o programa está carregando de forma correta o grafo no arquivo "user.txt"
	printf("TESTE DE CARREGA GRAFO\n");

	destroi_grafo(G);

	G =  carrega_grafo();
	assert(G);
	printf("\tPassou no teste.\n");

	//testa a funcionalidade da função que imprime todas as informações de todos os usuários da rede social
	printf("TESTE DE IMPRIME REDE SOCIAL\n");

	imprime_rede_social(G);

	printf("\tPassou no teste.\n");


	//FUNCOES DE TESTE DO MÓDULO trans.c e user.c

	p_listatrans p;

	vertice = G->head->prox;

	// testa a funcionalidade da função remove_vertice_T(remove vertice do grafo de transações de um usuario)
	printf("TESTE DA FUNCAO REMOVE VERTICE T\n");

	// remove-se o vertice previamente inserido
	remove_vertice_T(vertice->usuario.grafoT, aux_carona);
	// checa se, ao tentar remover esse mesmo vértice, a função retorna NULL
	if(!pesquisa_verticeT(vertice->usuario.grafoT, aux_carona))
		printf("\tPassou no teste.\n");


	// testa a funcionalidade da função cria_lista_trans(cria uma lista que contém todas as possíveis transações cadastradas pelo administrador)
	printf("TESTE DA FUNCAO CRIA LISTA TRANS\n");

	p = cria_lista_trans();
	assert(p);
	printf("\tPassou no teste.\n");

	/* testa a funcionalidade da função cadastra_trans(ao inserir na lista um item que não foi previamente inserido, retorna TRUE)
	 caso contrário retorna FALSE.*/
	printf("TESTE DA FUNCAO CADASTRA TRANS\n");

	// cadastra nova transação
	if(cadastra_trans(p,aux_venda) == TRUE)
		printf("\tPassou no teste.\n");
	// cadastra nova transação
	if(cadastra_trans(p,aux_aluguel) == TRUE)
		printf("\tPassou no teste.\n");
	// cadastra nova transação
	if(cadastra_trans(p,aux_carona) == TRUE)
		printf("\tPassou no teste.\n");
	// tenta cadastrar uma transação já inserida na lista
	if(cadastra_trans(p,aux_carona) == FALSE)
		printf("\tPassou no teste.\n");

	// testa a funcionalidade da função remove_trans(remove uma transação da lista de transações cadastradas)
	printf("TESTE DA FUNCAO REMOVE TRANS\n");

	// retira a transação "carona"
	if(remove_trans(p, aux_carona) == TRUE)
		printf("\tPassou no teste.\n");
	// retornar FALSE porque "viagem" não é uma transação cadastrada
	if(remove_trans(p,aux_viagem) == FALSE)
		printf("\tPassou no teste.\n");


	printf("TESTE DA FUNCAO IMPRIME TRANS\n");
	imprime_trans(p);
	printf("\tPassou no teste\n");


	// testa a funcionalidade da função salva_trans(salva no arquivo "trans.txt" todas as transações cadastradas pelo administrador)
	printf("TESTE DA FUNCAO SALVA TRANS\n");

	if(salva_trans(p) == TRUE) // retornar TRUE se foi salva no arquivo
		printf("\tPassou no teste.\n");


	// teste da funcionalidade da função destroi_trans(libera a memória reservada para essa lista)
	printf("TESTE DA FUNCAO DESTROI TRANS\n");

	destroi_trans(p);
	printf("\tPassou no teste.\n");

	// testa a funcionalidade da função carrega_trans(lê do arquivo "trans.txt" todas as transações cadastradas pelo administrador na ultima execucao)
	printf("TESTE DA FUNCAO CARREGA TRANS\n");

	p = carrega_trans();
	assert(p);
	printf("\tPassou no teste.\n");

	//testa a funcionalidade da funçao remove T(remove um item da lista de requerido ou historico de um usuario)
	printf("TESTE DA FUNCAO REMOVE T\n");

	// remove o primeiro item 
	if(remove_T(vertice->usuario.listaT_req, vertice->usuario.listaT_req->head->prox)==TRUE)
		// retornar false, visto que não é um item
		if(remove_T(vertice->usuario.listaT_req, NULL) == FALSE)
			printf("\tPassou no teste.\n");

	// testa a funcionalidade da função imprime lista T(lista de requerido ou histórico)
	printf("TESTE DA FUNCAO IMPRIME LISTA T\n");
	imprime_listaT(vertice->prox->usuario.listaT_req, 0);
	imprime_listaT(vertice->prox->usuario.listaT_his, 1);// leva em consideração se a pessoa já foi avaliada ou nao
	printf("\tPassou no teste.\n");

	// testa a funcionalidade da função pesquisa grafo T(pesquisa por um vértice(transação) no grafo de transações de uma pessoa) 
	printf("TESTE DA FUNCAO PESQUISA GRAFO T\n");

	// se for pesquisar por uma transação que não foi iniciada, retorna NULL
	if(pesquisa_grafo_T(G,vertice->usuario.grafoT,aux_carona, aux_nome_falso) == NULL)
		printf("\tPassou no teste(1).\n");
	
	// inicializa-se uma transação(cria-se a transação com outro usuário)
	adiciona_vertice_T(vertice->usuario.grafoT, aux_carona);
	adiciona_aresta_T(vertice->usuario.grafoT, aux_carona, vertice->prox->usuario.nome);

	// se encontrar essa transação criada
	if(pesquisa_grafo_T(G,vertice->usuario.grafoT, aux_carona, vertice->prox->usuario.nome))
		printf("\tPassou no teste(2).\n");

	// testa a funcionalidade da função que finaliza transações 
	printf("TESTE DA FUNCA FINALIZAR TRANS\n");

	// finaliza uma transação existente
	if(finalizar_trans(G,vertice,aux_carona,vertice->prox->usuario.nome) == TRUE)
		printf("\tPassou no teste(1).\n");

	// retorna NULL visto que a transação não existe
	if(finalizar_trans(G,vertice,aux_venda,aux_nome_falso) == FALSE)
		printf("\tPassou no teste(2).\n");

	// testa a funcionalidade da função buscarequisitos tendo em mente o padrão de usuário que outro usuário deseja para realizar a transação
	printf("TESTE DA FUNCAO BUSCA REQUISITOS\n");

	buscarequisitos(G,x[1],vertice,2,0, aux_carona);// 2 == amigos de amigos 0 == não leva em consideração experiencia
	buscarequisitos(G,x[1],vertice,3,0, aux_carona);// 3 == qualquer um 0 == não leva em consideração experiencia
	buscarequisitos(G,x[1],vertice,3,1, aux_carona);// 3 == qualquer um 1 == leva em consideração experiencia 
	buscarequisitos(G,x[1],vertice,2,1, aux_carona);// 2 == amigos de amigos 1 == leva em consideração experiencia

	printf("Passou no teste.\n");



	destroi_grafo(G);
	return  RUN_ALL_TESTS();
}