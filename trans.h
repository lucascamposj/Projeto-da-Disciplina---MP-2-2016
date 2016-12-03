typedef struct transacao* p_transacao;
typedef struct lista_trans* p_listatrans;

typedef struct transacao
{
	char trans[50];

	p_transacao ant;
	p_transacao prox;
} tp_transacao;

typedef struct lista_trans
{
	p_transacao head;
	p_transacao ultimo;
} tp_listatrans;

p_listatrans cria_lista_trans();

int cadastra_trans(p_listatrans, char *);

int remove_trans(p_listatrans, char *);

p_transacao pesquisa_trans(p_listatrans, char *);

p_listatrans carrega_trans();

int salva_trans(p_listatrans);

void destroi_trans(p_listatrans);

p_transacao pesquisa_trans(p_listatrans, char *);