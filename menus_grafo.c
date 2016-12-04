#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0

int main(int argc, char const *argv[])
{
	int  menu = 1, sair = FALSE, i, j, op, ex;
	char string_1[50], string_2[50], opcao, c;
	p_vertice user, amigo;
	p_grafo G, G_teste;
  	tp_user new_user, y;
	p_aresta a_user;
	tp_user req_user;
	p_listatrans transacoes;
	FILE *arq;

	G = carrega_grafo();
	transacoes = carrega_trans();
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

						do{
							sair = FALSE;
							system("clear");
							printf("***************Transacoes******************\n");
							printf("*(1)Ver Transacoes Efetivadas             *\n");
							printf("*(2)Cadastrar Transação                   *\n");
							printf("*(3)Descadastrar Transação                *\n");
							printf("Para sair digite x.                       *\n");
							printf("*******************************************\n");
							scanf("%c", &opcao);
							getchar();
							switch(opcao)
							{
								case '1':
										assert(arq = fopen("historico.txt","r"));
										
										printf("Transacoes:\n");
										while(!feof(arq)){
											if(c = fgetc(arq) != '/')
												printf("%c", c);
											else
												printf(" ");
										}
										fclose(arq);
									printf("Digite qualquer tecla para voltar.\n");
									getchar();
									break;
								case '2':
									printf("Digite a transação que deseja inserir: ");
									scanf("%[^\n]s",string_1);
									getchar();
									if(cadastra_trans(transacoes, string_1) == TRUE)
										printf("Transacoes inserida com sucesso\n");
									else
										printf("Falha ao inserir transacao. Verifique se a transacao ja nao existe\n");
									printf("Digite qualquer tecla para voltar.\n");
									getchar();
									break;
								case '3':
									printf("Digite a transação que deseja descadastrar: ");
									scanf("%[^\n]s",string_1);
									getchar();
									if(remove_trans(transacoes, string_1) == TRUE)
										printf("Transacoes retirada com sucesso\n");
									else
										printf("Falha ao retirar transacao. Verifique se a transacao existe\n");
									printf("Digite qualquer tecla para voltar.\n");
									getchar();
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
				            do{	
				            	sair = FALSE;
				            	system("clear");
				            	printf("********************TRANSACOES************************\n");
					            printf("*(1)Ver transacoes pedidas                           *\n");
					            printf("*(2)Ver convites de transacoes                       *\n");
					            printf("*(3)Realizar uma transacao.                          *\n");
					            printf("Para voltar digite x.                                *\n");
					            printf("******************************************************\n");
				            	scanf("%c", &opcao);
				                getchar();
				                switch(opcao)
				                {
				                	case '1':
				            			imprime_grafoT(user->grafoT);
				            			printf("*****************************************************\n");
				            			printf("Deseja aceitar alguma transacao? (Digite S para sim ou qualquer outra tecla para voltar)\n");
				            			scanf("%c", &opcao);
				            			switch(opcao){
				            				case 'S':
				            					printf("Digite o a transacao que deseja realizar\n");
				            					scanf("%[^\n]s", string_1);
				            					printf("Digite o nome do usuario\n");
				            					scanf("%[^\n]s", string_2);
				            					if(finalizar_trans(G, user->grafoT,string_1,string_2)){
				            						printf("Transacao realizada.\n");
				            						sleep(2);
				            					}else{
				            						printf("Erro ao realizar transacao\n");
				            						sleep(2);
				            					}
				            				break;
				            			}
				            			printf("\n");
				                		break;
				                	case '2':

				                		break;
				                	case '3':
				                		system("clear");

				                		do
				                		{
				                			system("clear");
					                		printf("\n**********************************\n");
					                		imprime_trans(transacoes);
					                		printf("Digite x para sair.\n");
					                		printf("\n**********************************\n");
					                		printf("Digite o nome da transacao: ");
					                		scanf("%[^\n]s", string_1);
					                		getchar();
				                		}while(!pesquisa_trans(transacoes, string_1) && strcmp(string_1,"x"));

					            		do{	

					            			if(!strcmp(string_1, "x"))
					            				break;

					            			system("clear");

					            			req_user.idade = -1;
					            			req_user.genero = 'x';
					            			req_user.escolaridade = 0;
					            			req_user.cep = 0;
					            			req_user.n_interesses = 0;
					            			req_user.quant_aval = 0;

					            			printf("********************Requisitos************************\n");
						            		printf("*(1)Idade                                            *\n");
						           			printf("*(2)Genero                                           *\n");
						           			printf("*(3)Nivel educacional                                *\n");
						           			printf("*(4)CEP                                              *\n");
						           			printf("*(5)Interesses                                       *\n");
						           			printf("*(6)Avaliacao                                        *\n");
						           			printf("*(7)Experiencia                                      *\n");
						           			printf("*(8)Abrangencia                                      *\n");
						            		printf("Para concluir digite x                               *\n");
						            		printf("******************************************************\n");
				                			printf("Digite uma opcao valida: ");
				                			scanf("%c", &opcao);
				               				getchar();

				               				switch(opcao){
				               					case'1':
				               						printf("Digite a idade mínima: ");
				               						scanf("%d", &req_user.idade);
					                    			getchar();

				               						break;
				               					case'2':
				               						printf("\n**********************************\n");
			        								printf("*(M)Masculino.                   *\n");
			        								printf("*(F)Feminino.                    *\n");
			        								printf("*(O)Outros.                      *\n");
			       									printf("**********************************\n");
				               						printf("Digite o genero requerido: ");
				               						scanf("%c", &req_user.genero);
					                    			getchar();

				               						break;
				               					case'3':
				               						printf("\n**********************************\n");
			       									printf("*(1)Primeiro grau incompleto.    *\n");
			        								printf("*(2)Primeiro grau completo.      *\n");
			        								printf("*(3)Segundo grau incompleto.     *\n");
			        								printf("*(4)Segundo grau completo.       *\n");
			       									printf("*(5)Superior incompleto.         *\n");
			       									printf("*(6)Pos-graduacao.               *\n");
			       									printf("**********************************\n");
				               						printf("Digite o nivel educacional requerido: ");
				               						scanf("%d", &req_user.escolaridade);
					                    			getchar();

				               						break;
				               					case'4':
				               						printf("Digite o CEP requerido: ");
				               						scanf("%d", &req_user.cep);
					                    			getchar();

				               						break;
				               					case'5':
				               						printf("Digite o interesse requerido: ");
				               						req_user.n_interesses = 1;
				               						scanf("%[^\n]s", req_user.interesses[0]);
					                    			getchar();

				               						break;
				               					case'6':
				               						printf("Digite o grau de avaliação mínima (0 a 10): ");
				               						req_user.quant_aval++;
				               						scanf("%d", &req_user.soma_aval);
					                    			getchar();

				               						break;
				               					case'7':
				               						printf("\n**********************************\n");
				               						printf("*(1)Sim.                          *\n");
				               						printf("*(2)Nao.                          *\n");
				               						printf("\n**********************************\n");
			       									do
			       									{
			       										printf("Digite se deseja experiencia: ");
			       										scanf("%d", &ex);
					                    				getchar();

			       										
			       									}while(op < 1 && op > 2);

				               						break;
				               					case'8':
				               						printf("\n**********************************\n");
			       									printf("*(1)Apenas amigos.               *\n");
			        								printf("*(2)Amigos de amigos.            *\n");
			        								printf("*(3)Qualquer um.                 *\n");
			       									printf("**********************************\n");
			       									do
			       									{
			       										printf("Digite o nivel de abrangencia: ");
			       										scanf("%d", &op);
					                    				getchar();

			       										
			       									}while(op < 1 && op > 3);

				               						break;
				               					case'x':
				               						buscarequisitos(G,req_user,user,op,ex,string_1);
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
					        sair = FALSE;
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
	salva_trans(transacoes);
	destroi_trans(transacoes);
	destroi_grafo(G);
	return 0;
}