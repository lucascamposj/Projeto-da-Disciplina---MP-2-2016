#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

int main(int argc, char const *argv[])
{
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
        /*G = cria_grafo();
        printf("\n* Opcao - Verifica adjacencia *\n");
        printf("Digite um nome para cada vertice:\n");
        printf("Digite x(nome):");
        scanf("%[^\n]s", x.nome);
        printf("\nDigite y(nome):");
        scanf("%[^\n]s", y.nome);
        printf("\n");

        adiciona_usuario(G,x);
        adiciona_usuario(G,y);
        adiciona_amizade(G,x,y);

        if(adjacente(G, x, y) == TRUE)
          printf("Passou no teste de adjacencia verdadeira.\n");
        else
          printf("Falhou no teste de adjacencia verdadeira.\n");
        
        remove_aresta(G,x,y);

        if(adjacente(G, x, y) == FALSE)
          printf("Passou no teste de adjacencia falsa.\n");
        else
          printf("Falhou no teste de adjacencia falsa.\n");
        destroi_grafo(G);*/
      break;
      case 5:  
        /*G = cria_grafo();

        printf("\n* Opcao - Lista de vizinhos *\n");
        printf("Digite uma chave inteira para cada vertice:\n");
        printf("Digite x:");
        scanf("%d", &x);
        printf("\nDigite y:");
        scanf("%d", &y);
        printf("\n");

        adiciona_usuario(G,x);
        adiciona_usuario(G,y);
        adiciona_aresta(G,x,y);

        printf("Verificacao do teste de vizinhos ocorre na impressao, deve haver a chave y na seguinte lista\n");
        vizinhos(G, x);
        destroi_grafo(G);*/
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

        // PEDE O RESTO DA PORRA TODA
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
  return 0;
}