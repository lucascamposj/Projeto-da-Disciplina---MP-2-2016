#include <gtest/gtest.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

#define TRUE 1
#define FALSE 0


TEST(adiciona_usuario, Adicionar_usuario){
	p_grafo G;
	tp_user user;

	G = cria_grafo();
	ASSERT_EQ(TRUE,adiciona_usuario(G, user));

	
}

TEST(remove_usuario, Remover_usuario){
	p_grafo G;
	tp_user user, user2;
	char nome[] = "nome3";

	strcpy(user.nome,"nome");

	G = cria_grafo();
	ASSERT_EQ(TRUE,adiciona_usuario(G, user));
	ASSERT_EQ(TRUE,adiciona_usuario(G, user2));

	ASSERT_EQ(TRUE,adiciona_amizade(G, user2.nome, user.nome));

	ASSERT_EQ(TRUE,remove_usuario(G, user.nome));

	ASSERT_EQ(TRUE,remove_usuario(G, user2.nome));
		
	ASSERT_EQ(FALSE,remove_usuario(G, nome));

	
}

TEST(adiciona_amizade, Adiciona_amizade){
	p_grafo G;
	tp_user user1, user2;
	char nome[] = "nome3";

	strcpy(user1.nome,"nome1");
	strcpy(user2.nome,"nome2");


	G = cria_grafo();
	ASSERT_EQ(TRUE,adiciona_usuario(G, user1));
	ASSERT_EQ(TRUE,adiciona_usuario(G, user2));
	ASSERT_EQ(TRUE,adiciona_amizade(G, user2.nome, user1.nome));
	ASSERT_EQ(FALSE,adiciona_amizade(G, user2.nome, user1.nome));
	
	ASSERT_EQ(FALSE,adiciona_amizade(G, user2.nome, nome));

	
}

TEST(remove_amizade, Remove_amizade){
	p_grafo G;
	tp_user user1, user2;
	char nome[] = "nome3";

	strcpy(user1.nome,"nome1");
	strcpy(user2.nome,"nome2");

	G = cria_grafo();

	ASSERT_EQ(TRUE,adiciona_usuario(G, user1));
	ASSERT_EQ(TRUE,adiciona_usuario(G, user2));
	ASSERT_EQ(TRUE,adiciona_amizade(G, user2.nome, user1.nome));

	ASSERT_EQ(TRUE,remove_amizade(G, user2.nome, user1.nome));
	ASSERT_EQ(FALSE,remove_amizade(G, user2.nome, user1.nome));

	ASSERT_EQ(FALSE,remove_amizade(G, user2.nome, nome));

	
}

TEST(grafo_vazio, Grafo_vazio){
	p_grafo G;
	tp_user user;

	G = cria_grafo();

	ASSERT_EQ(TRUE,grafo_vazio(G));

	ASSERT_EQ(TRUE,adiciona_usuario(G, user));
	ASSERT_EQ(FALSE,grafo_vazio(G));

	
}

TEST(vertice_vazio, Vertice_vazio){
	p_grafo G;
	tp_user user1, user2;

	G = cria_grafo();


	ASSERT_EQ(TRUE,adiciona_usuario(G, user1));
	ASSERT_EQ(TRUE,vertice_vazio(G->head->prox));

	ASSERT_EQ(TRUE,adiciona_usuario(G, user2));
	ASSERT_EQ(TRUE,adiciona_amizade(G, user2.nome, user1.nome));
	ASSERT_EQ(FALSE,vertice_vazio(G->head->prox));

	
}

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

TEST(pesquisa_aresta, Pesquisa_aresta){
		p_grafo G;
	tp_user user1, user2;
	char nome[] = "nome3";

	strcpy(user1.nome,"nome1");
	strcpy(user2.nome,"nome2");

	G = cria_grafo();

	ASSERT_EQ(TRUE,adiciona_usuario(G, user1));

	EXPECT_EQ(NULL, pesquisa_aresta(G->head->prox, nome));

	ASSERT_EQ(TRUE,adiciona_usuario(G, user2));
	ASSERT_EQ(TRUE,adiciona_amizade(G, user2.nome, user1.nome));
	ASSERT_EQ(G->head->prox->head->prox,pesquisa_aresta(G->head->prox, user2.nome));

	EXPECT_EQ(NULL,pesquisa_aresta(G->head->prox, nome));

	
}


int main(int argc, char**argv)
{

	::testing::InitGoogleTest(&argc, argv);
	  int opcao = 0;
	  char string_1[100], string_2[100];
	  p_vertice vertice;
	  p_grafo G, G_teste;
	  tp_user x, y;

	  G = carrega_grafo();
	  while(opcao != -1){
	    printf("******************************************\n");
	    printf("*Qual teste deseja realizar?             *\n");
	    printf("*  (1)  - Cria Grafo                     *\n");
	    printf("*  (3)  - Destroi Grafo                  *\n");
	    printf("*  (4)  - Verifica adjacencia            *\n");
	    printf("*  (5)  - Lista de vizinhos              *\n");
	    printf("*  (6)  - Adiciona usuario               *\n");
	    printf("*  (7)  - Remove usuario                 *\n");
	    printf("*  (8)  - Adiciona amizade               *\n");
	    printf("*  (9)  - Remove amizade                 *\n");
	    printf("*  (10) - Imprime grafo                  *\n");
	    printf("*  (-1) - Sair                           *\n");
	    printf("******************************************\n");

	    printf("Digite a opcao: ");
	    scanf("%d", &opcao);
	    getchar();
	    printf("\n\n");
	    switch(opcao)
	    {
	      case 1:
	        printf("\n* Opcao - Cria Grafo *\n");

	        G_teste = cria_grafo();

	        /*Teste verifica se a alocação ocorreu de forma correta*/
	        if(G_teste != NULL)
	          printf("Passou no teste de alocacao - Alocacao efetivada\n");
	        else
	          printf("Falhou no teste de alocacao - Alocacao falhou\n");
	      break;
	      
	      case 3:  
	        destroi_grafo(G);
	      break;
	      case 4:  
	       
	      break;
	      case 5:  
	      break;
	      case 6:  
	        printf("\n* Opcao - Adiciona usuario *\n");
	        printf("Digite um nome para o usuario:\n");
	        scanf("%[^\n]s", x.nome);
	        getchar();
	        printf("Digite o genero do usuario:\n");
	        scanf("%c", &x.genero);
	        printf("Digite a idade do usuario:\n");
	        scanf("%d", &x.idade);
	        printf("Digite a escolaridade do usuario:\n");
	        scanf("%d", &x.escolaridade);
	        printf("Digite o cep do usuario:\n");
	        scanf("%d", &x.cep);

	        adiciona_usuario(G, x);

	        /*Procura vertice*/
	        vertice = G->head->prox;
	        while(vertice != NULL && strcmp(vertice->usuario.nome, x.nome))
	          vertice = vertice->prox;
	        if(!strcmp(vertice->usuario.nome, x.nome))
	          printf("Passou no teste de adicao de vertice\n");
	        else
	          printf("Falhou no teste de adicao de vertice\n");
	      break;
	      case 7:

	        printf("\n* Opcao - Remove usuario *\n");
	        printf("Digite um nome para o usuario:\n");
	        scanf("%[^\n]s", x.nome);
	        getchar();

	        remove_usuario(G, x.nome);
	        
	        vertice = G->head->prox;
	        while(vertice != NULL && (strcmp(vertice->usuario.nome, x.nome)))
	          vertice = vertice->prox;
	        if(vertice == NULL)
	          printf("Passou no teste de retirada de vertice\n");
	        else
	          printf("Falhou no teste de retirada de vertice\n");
	      break;
	      case 8:  

	        printf("\n* Opcao - Adiciona amizade *\n");
	        printf("Digite um nome para o usuario:\n");
	        scanf("%[^\n]s", x.nome);
	        getchar();

	        printf("Digite um nome para o usuario 2:\n");
	        scanf("%[^\n]s", y.nome);
	        getchar();
	        printf("\n");

	        adiciona_amizade(G, x.nome, y.nome);

	      break;
	      case 9:  

	        printf("\n* Opcao - Remove amizade *\n");
	        printf("Digite um nome para o usuario:\n");
	        scanf("%[^\n]s", x.nome);
	        getchar();
	        
	        printf("Digite um nome para o usuario 2:\n");
	        scanf("%[^\n]s", y.nome);
	        getchar();
	        printf("\n");

	        remove_amizade(G, x.nome, y.nome);
	      
	      break;

	     case 10:
	        imprime_grafo(G);

	    }
	  }
	  salva_grafo(G);
	  destroi_grafo(G);

	return  RUN_ALL_TESTS();
}