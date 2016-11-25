#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include <unistd.h>

int main(int argc, char const *argv[])
{
  int  menu = 1, sair = FALSE;
  char string_1[50], string_2[50], opcao, c;
  p_vertice user, amigo;
  p_grafo G, G_teste;
  tp_user new_user, y;
  p_aresta a_user;

  G = carrega_grafo();
  do
  { 
    sair = FALSE;
    printf("limpando tela...\n");
    sleep(1);
    system("clear");
    printf("******************************************\n");
    printf("*               BEM VINDO                *\n");
    printf("*(1)Ja sou usuario.                      *\n");
    printf("*(2)Cadastre-se.                         *\n");
    printf("Para sair digite x.                      *\n");
    printf("******************************************\n");
    scanf("%c", &opcao);
    getchar();
    
    switch(opcao)
    {
      case '1':
        printf("Digite o nome do usuario: ");
        scanf("%[^\n]s", string_1);
        getchar();
        printf("\n");
        user = pesquisa_vertice(G, string_1);// pesquisa o nome do usúário no grafo
        if(user)
        {
          printf("limpando tela...\n");
          sleep(1);
          system("clear"); // Mostra as informações deste usuário, assim como seus amigos
          printf("******************************************\n");
          puts(user->usuario.nome);
          a_user = user->head->prox;
          printf("\t%c\n", user->usuario.genero);
          printf("\t%d\n", user->usuario.idade);
          printf("\t%d\n", user->usuario.escolaridade);
          printf("\t%d\n", user->usuario.cep);
          // Opções para o usuário
          printf("***************OPCOES*********************\n");
          printf("*(1)Amigos.                              *\n");
          printf("*(2)Transferencias.                      *\n");
          printf("*(3)Apagar usuario.                      *\n");
          printf("Para voltar digite x.                     *\n");
          printf("******************************************\n");
          scanf("%c", &opcao);
          getchar();
          switch(opcao)
          {
            case '1':
              do
              {
                sair = FALSE;
                printf("limpando tela...\n");
                sleep(1);
                system("clear");
                printf("***************OPCOES DE AMIZADES*********************\n");
                printf("*(1)Ver amigos.                                      *\n");
                printf("*(2)Deletar amigo.                                   *\n");
                printf("*(3)Adicionar amigo.                                 *\n");
                printf("Para voltar digite x.                                *\n");
                printf("******************************************************\n");
                scanf("%c", &opcao);
                getchar();
                switch(opcao)
                {
                  case '1':
                    printf("limpando tela...\n");
                    sleep(1);
                    system("clear");
                    printf("*********************AMIGOS*********************\n");
                    a_user = user->head->prox;
                    if(!a_user)
                      printf("Sem amigos.\n");
                    else
                    {
                      while(a_user)
                      {
                        printf("\t%s\n",a_user->amigo->usuario.nome);
                        a_user = a_user->prox;
                      }
                    }
                    printf("************************************************\n");
                    printf("Digite qualquer tecla para voltar.\n");
                    scanf("%c", &c);
                    getchar();
                    break;
                  case '2':
                    printf("limpando tela...\n");
                    sleep(1);
                    system("clear");
                    printf("Digite o nome do amigo que deseja deletar:");
                    scanf("%[^\n]s", string_1);
                    getchar();  
                    remove_amizade(G,user->usuario.nome,string_1);
                    break;

                  case '3':
                    printf("limpando tela...\n");
                    sleep(1);
                    system("clear");
                    printf("Digite o nome do usuario que deseja adicionar aos seus amigos:");
                    scanf("%[^\n]s", string_1);
                    getchar();
                    adiciona_amizade(G,user->usuario.nome,string_1);
                    
                    break;

                  case 'x':
                    sair = TRUE;
                    break;

                  default:
                    printf("WAAATTT %c\n", opcao);
                    sleep(1);

                }

              }while(sair == FALSE);
              sair = FALSE;

              break;

            case '2':
              /*TRANSFERÊNCIAS*/
              break;
            
            case '3':
              if(remove_usuario(G, user->usuario.nome))
                printf("Usuario removido.\n");

              else
                printf("Falha ao remover o usuario.\n");

              sair = FALSE;
              break;

            case 'x':
              sair = TRUE;
              break;
          }
          sair = FALSE;
        }
        else
        {
          printf("limpando tela...\n");
          sleep(1);
          system("clear");
          printf("Usuario nao existe.\n");
          sleep(1);
          system("clear");
          sair = FALSE
          ;
        }
        break;

      case '2':
        printf("Digite um nome para o usuario:\n");
        scanf("%[^\n]s", new_user.nome);
        getchar();
        printf("Digite o genero do usuario:\n");
        scanf("%c", &new_user.genero);
        printf("Digite a idade do usuario:\n");
        scanf("%d", &new_user.idade);
        printf("Digite a escolaridade do usuario:\n");
        scanf("%d", &new_user.escolaridade);
        printf("Digite o cep do usuario:\n");
        scanf("%d", &new_user.cep);
        getchar();
        if(adiciona_usuario(G, new_user))
          printf("Usuário adicionado.\n");
        
        sleep(1);
        sair = FALSE;
        break;

      case 'x':

        sair = TRUE;
        break;

      default:
        printf("limpando tela... def: %c\n", opcao);
        sleep(1);
        system("clear");
        sair = FALSE;
    }

  }while(sair == FALSE);
 
  salva_grafo(G);
  destroi_grafo(G);
  return 0;
}