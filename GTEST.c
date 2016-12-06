#include <gtest/gtest.h>

#include <stdio.h>
#include <stdlib.h>

#include "trans.h"
#include "user.h"
#include "grafo.h"

TEST(cria_grafo, Criar_um_grafo)	
{
	p_grafo G;
	
	ASSERT_NE(NULL, G = cria_grafo());
	
	destroi_grafo(G);
}

TEST(adiciona_usuario, Adicionar_usuario){
	p_grafo G;
	tp_user user;

	ASSERT_NE(NULL,G = cria_grafo());
	ASSERT_EQ(TRUE,adiciona_usuario(G, user));

	destroi_grafo(G);
}

TEST(remove_usuario, Remover_usuário){
	p_grafo G;
	tp_user user;

	user.nome = "nome";

	ASSERT_NE(NULL,G = cria_grafo());
	ASSERT_EQ(TRUE,adiciona_usuario(G, user));
	ASSERT_EQ(TRUE,remove_usuario(G, user.nome));
	ASSERT_EQ(FALSE,remove_usuario(G, "nome_invalido"));

	destroi_grafo(G);
}

TEST(adiciona_amizade, Adiciona_amizade){
	p_grafo G;
	tp_user user1, user2;

	user1.nome = "nome1";
	user2.nome = "nome2";

	ASSERT_NE(NULL,G = cria_grafo());
	ASSERT_EQ(TRUE,adiciona_usuario(G, user1));
	ASSERT_EQ(TRUE,adiciona_usuario(G, user2));
	ASSERT_EQ(TRUE,adiciona_amizade(G, user2.nome, user1.nome));
	ASSERT_EQ(FALSE,adiciona_amizade(G, user2.nome, user1.nome));
	
	ASSERT_EQ(FALSE,adiciona_amizade(G, user2.nome, "nome3"));

	destroi_grafo(G);
}

TEST(remove_amizade, Remove_amizade){
	p_grafo G;
	tp_user user1, user2;

	user1.nome = "nome1";
	user2.nome = "nome2";

	ASSERT_NE(NULL,G = cria_grafo());
	ASSERT_EQ(TRUE,adiciona_usuario(G, user1));
	ASSERT_EQ(TRUE,adiciona_usuario(G, user2));
	ASSERT_EQ(TRUE,adiciona_amizade(G, user2.nome, user1.nome));

	ASSERT_EQ(TRUE,remove_amizade(G, user2.nome, user1.nome));
	ASSERT_EQ(FALSE,remove_amizade(G, user2.nome, user1.nome));

	ASSERT_EQ(FALSE,remove_amizade(G, user2.nome, "nome3"));

	destroi_grafo(G);
}

TEST(grafo_vazio, Grafo_vazio){
	p_grafo G;
	tp_user user;

	ASSERT_NE(NULL,G = cria_grafo());
	ASSERT_EQ(TRUE,grafo_vazio(G));

	ASSERT_EQ(TRUE,adiciona_usuario(G, user));
	ASSERT_EQ(FALSE,grafo_vazio(G));

	destroi_grafo(G);
}

TEST(vertice_vazio, Vertice_vazio){
	p_grafo G;
	tp_user user1, user2;

	ASSERT_NE(NULL,G = cria_grafo());

	ASSERT_EQ(TRUE,adiciona_usuario(G, user1));
	ASSERT_EQ(TRUE,vertice_vazio(G->head->prox));

	ASSERT_EQ(TRUE,adiciona_usuario(G, user2));
	ASSERT_EQ(TRUE,adiciona_amizade(G, user2.nome, user1.nome));
	ASSERT_EQ(FALSE,vertice_vazio(G->head->prox));

	destroi_grafo(G);
}

TEST(pesquisa_vertice, Pesquisa_vertice){
	p_grafo G;
	tp_user user;

	user.nome = "nome";

	ASSERT_NE(NULL,G = cria_grafo());

	//caso onde grafo está vazio
	ASSERT_EQ(NULL, pesquisa_vertice(G, "nome2"));

	//caso sucesso
	ASSERT_EQ(TRUE,adiciona_usuario(G, user));
	ASSERT_EQ(G->head->prox, pesquisa_vertice(G, user.nome));

	//caso nome não encontrado
	ASSERT_EQ(NULL, pesquisa_vertice(G, "nome2"));
}

TEST(pesquisa_aresta, Pesquisa_aresta){
		p_grafo G;
	tp_user user1, user2;

	user1.nome = "nome1";
	user2.nome = "nome2";

	ASSERT_NE(NULL,G = cria_grafo());

	ASSERT_EQ(TRUE,adiciona_usuario(G, user1));

	ASSERT_EQ(NULL, pesquisa_aresta(G->head->prox, "nome3"));

	ASSERT_EQ(TRUE,adiciona_usuario(G, user2));
	ASSERT_EQ(TRUE,adiciona_amizade(G, user2.nome, user1.nome));
	ASSERT_EQ(G->head->prox->head->prox,pesquisa_aresta(G->head->prox, user2.nome));

	ASSERT_EQ(NULL,pesquisa_aresta(G->head->prox, "nome3"));

	destroi_grafo(G);
}


int main(int argc, char const *argv[])
{
	::testing::InitGoogleTest(&arc,argv);

	return RUN_ALL_TESTS();
}