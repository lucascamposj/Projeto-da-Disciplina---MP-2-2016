#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include <unistd.h>
#include <string.h>
#include <ctype.h>
int main(int argc, char const *argv[])
{
	int  menu = 1, sair = FALSE, i, j;
	char string_1[50], string_2[50], opcao, c;
	p_vertice user, amigo;
	p_grafo G, G_teste;
  	tp_user new_user, y;
	p_aresta a_user;

	G = carrega_grafo();
	if(argc == 2)
	{
		if(!strcmp(argv[1], "admin"))
		{
			do
			{
				system("clear");
				sair = FALSE;
				printf("*****************************************\n");
				printf("*              BEM VINDO (Admin)        *\n");
				printf("*(1)Visualizar Rede Social              *\n");
				printf("*(2)Transações                          *\n");
				printf("Para sair digite x.                     *\n");
				printf("*****************************************\n");
				scanf("%c", &opcao);
				getchar();
				switch(opcao)
				{
					case '1':
						system("clear");
						printf("************Rede Social**********\n");
						imprime_grafo(G);
						printf("\nPara sair digite qualquer tecla\n");

						scanf("%c", &c);
						sair = FALSE;
						break;
					case '2':
						/*jon snow*/
						do{
							sair = FALSE;
							system("clear");
							printf("***************Transações******************\n");
							printf("*(1)Ver Transações Efetivadas             *\n");
							printf("*(2)Cadastrar Transação                   *\n");
							printf("*(3)Descadastrar Transação                *\n");
							printf("Para sair digite x.                       *\n");
							printf("*******************************************\n");
							scanf("%c", &opcao);
							getchar();
							switch(opcao)
							{
								case '1':
									
									break;
								case '2':
									break;
								case '3':
									break;
								case 'x':
									sair = TRUE;
									break;
							}
						}while(sair == FALSE);
						sair = FALSE;
						break;
					case 'x':
						sair = TRUE;
						break;
				}
			}while(sair == FALSE);
		}
	}
	else
	{
		do
		{
			sair = FALSE;
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
			          
						system("clear"); // Mostra as informações deste usuário, assim como seus amigos
						printf("******************************************\n");
						printf("Nome:");
						puts(user->usuario.nome);
						a_user = user->head->prox;
						switch(user->usuario.genero)
						{
							case 'M':
								printf("\tGenero: Masculino.\n");
								break;

							case 'F':
								printf("\tGenero: Feminino.\n");
								break;
							
							case 'O':
								printf("\tGenero: Outros.\n");
						}
						printf("\tIdade:%d.\n", user->usuario.idade);
						printf("\tEscolaridade:%d.\n", user->usuario.escolaridade);
						printf("\tCEP:%d.\n", user->usuario.cep);
						printf("Interesses:\n");
						for(i=0;i<user->usuario.n_interesses;i++)
						{
							printf("\t");
							puts(user->usuario.interesses[i]);
						}
						// Opções para o usuário
						printf("***************OPCOES*********************\n");
						printf("*(1)Amigos.                              *\n");
						printf("*(2)Transações.                          *\n");
						printf("*(3)Apagar usuario.                      *\n");
						printf("*(4)Editar usuario.                      *\n");
						printf("Para voltar digite x.                    *\n");
						printf("******************************************\n");
						scanf("%c", &opcao);
						getchar();
						switch(opcao)
						{
						case '1':
							do
			              	{
				                sair = FALSE;
				                
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
						                system("clear");
						                printf("Digite o nome do amigo que deseja deletar:");
						                scanf("%[^\n]s", string_1);
						                getchar();  
						                remove_amizade(G,user->usuario.nome,string_1);
						                break;

				                	case '3':
					                    system("clear");
					                    printf("Digite o nome do usuario que deseja adicionar aos seus amigos:");
					                    scanf("%[^\n]s", string_1);
					                    getchar();
					                    adiciona_amizade(G,user->usuario.nome,string_1);
				                    
				                    break;

				                	case 'x':
				                    	sair = TRUE;
				                    	break;
				                }
			            	}while(sair == FALSE);
			            	sair = FALSE;

			            	break;

			            case '2':
			            	/*TRANSAÇÕES*/
			            	break;
			            
			            case '3':
			            	if(remove_usuario(G, user->usuario.nome))
			                	printf("Usuario removido.\n");
							else
			                	printf("Falha ao remover o usuario.\n");
			            	sair = FALSE;
			            	break;

			            case '4':
			            	edita_usuario(&(user->usuario));
			            	break;

			            case 'x':
			            	sair = TRUE;
			            	break;
			        	}
			          	sair = FALSE;
			        }
			        else
			        {
			        	system("clear");
			        	printf("Usuario nao existe.\n");
			        	sleep(1);
			        	system("clear");
			        	sair = FALSE;
			        }
			        break;

			    case '2':

			        printf("Digite um nome para o usuario:\n");
			        scanf("%[^\n]s", new_user.nome);
			        getchar();
			        printf("**********************************\n");
			        printf("*(M)Masculino.                   *\n");
			        printf("*(F)Feminino.                    *\n");
			        printf("*(O)Outros.                      *\n");
			        printf("**********************************\n");
			        do
			        {
			        	printf("Digite o genero do usuario:\n");
			        	scanf("%c", &new_user.genero);
			        
			        }while(new_user.genero != 'M' && new_user.genero != 'F' && new_user.genero != 'O');
			        printf("Digite a idade do usuario:\n");
			        scanf("%d", &new_user.idade);
			        printf("**********************************\n");
			        printf("*(1)Primeiro grau incompleto.    *\n");
			        printf("*(2)Primeiro grau completo.      *\n");
			        printf("*(3)Segundo grau incompleto.     *\n");
			        printf("*(4)Segundo grau completo.       *\n");
			        printf("*(5)Superior incompleto.         *\n");
			        printf("*(6)Pos-graduacao.               *\n");
			        printf("**********************************\n");
			        do
			        {
			        	printf("Digite a escolaridade do usuario:\n");
			        	scanf("%d", &new_user.escolaridade);

			        }while(new_user.escolaridade > 6 || new_user.escolaridade < 1);

			        printf("Digite o cep do usuario:\n");
			        scanf("%d", &new_user.cep);
			        getchar();
			        printf("Quantos interesses você deseja colocar: ");
			        scanf("%d", &new_user.n_interesses);
			        getchar();
			        for(i=0;i<new_user.n_interesses;i++)
			        {
			        	printf("Digite o %d interesse: ", i+1);
			        	scanf("%[^\n]s", new_user.interesses[i]);
			        	getchar();
			        }
			        printf("\n");
			        if(adiciona_usuario(G, new_user))
			        	printf("Usuário adicionado.\n");

			        sleep(1);
			        
			        sair = FALSE;
			        break;

			    case 'x':

			        sair = TRUE;
			        break;
		    }

		}while(sair == FALSE);
	}
	salva_grafo(G);
	destroi_grafo(G);
	return 0;
}