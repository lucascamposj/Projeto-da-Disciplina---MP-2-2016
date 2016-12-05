#include "grafo.h"

void buscarequisitos(p_grafo G,tp_user req_user,p_vertice user,int abran,int xp, char *trans);

int verifica_requisitos(p_vertice user, tp_user req_user, int xp, char *trans);

int finalizar_trans(p_grafo , p_vertice ,char *,char *);

p_vertice pesquisa_grafo_T(p_grafo, p_grafo_trans, char *, char*);

void imprime_listaT(p_listaT , int);
