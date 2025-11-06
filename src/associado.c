#include "types.h"

void janelaCadastrarAssociado()
{
	/*
	short tipo;
	short deletado;
	int id_associado;
	char nome[_STRNOME];
	char cpf[_STRCPF];
	char email[_STREMAIL];
	char endereco[_STREND];
	char telefone[_STRTEL];
	int qnt_livro_emprestado;
	int multa;
	int dia_sem_livro;
	int qnt_de_multa;
	int bloqueado;
	int dia_do_bloqueio[3];
	*/

	struct s_noh *temp;
	struct s_associado *associado;
	associado = (struct s_associado *)calloc(sizeof(struct s_associado), 1);

	associado->tipo = _ASSOCIADO;
	associado->deletado = 0;
	associado->id_associado = getNovaIdAssociado();

	associado->qnt_livro_emprestado = 0;
	associado->multa = 0;
	associado->dia_sem_livro = 0;
	associado->qnt_de_multa = 0;
	associado->bloqueado = 0;
	associado->dia_do_bloqueio[0] = 0;
	associado->dia_do_bloqueio[1] = 1;
	associado->dia_do_bloqueio[2] = 2;

	// TOPO
	os_limparTela();
	printf("\n");
	mostrarTituloPequeno("Cadastro de associado");
	printf("\n");

	// PERGUNTAS
	printf("  ID: %d", associado->id_associado);
	printf("\n");

	printf("  Digite o CPF do associado:\n  > ");
	strcpy(associado->cpf, getString(_STRCPF, _F_NUMERO));
	printf("\n");

	for (temp = listaA; temp->proximo != 0; temp = temp->proximo)
	{
		if ((strcmp(associado->cpf, ((struct s_associado *)temp->dado)->cpf)) == 0)
		{
			printf("ASSOCIADO JA CADASTRADO\n\n");
			congelarTela();
			return;
		}
	}

	printf("  Digite o nome do associado:\n  > ");
	strcpy(associado->nome, getString(_STRNOME, _F_LETRAESPACO));
	printf("\n");

	printf("  Digite o e-mail do associado:\n  > ");
	strcpy(associado->email, getString(_STREMAIL, _F_EMAIL));
	printf("\n");

	printf("  Digite o endere�o do associado:\n  > ");
	strcpy(associado->endereco, getString(_STREND, _F_ENDERECO));
	printf("\n");
	printf("  Digite o telefone do associado:\n  > ");
	strcpy(associado->telefone, getString(_STRTEL, _F_NUMERO));
	printf("\n");

	// CONFIRMA��O
	while (1)
	{
		os_limparTela();
		printf("\n");
		mostrarTituloPequeno("Cadastro de associado");
		printf("\n");

		printf("   Nome......: %s\n", associado->nome);
		printf("   CPF.......: %s\n", associado->cpf);
		printf("   E-mail....: %s\n", associado->email);
		printf("   Endere�o..: %s\n", associado->endereco);
		printf("   Telefone..: %s\n", associado->telefone);
		printf("\n");
		printf(" [0=Cancelar] [1=Cadastrar]\n");

		switch (getNumero())
		{
		case 0:
			os_limparTela();
			printf("\n  Cancelado\n");
			congelarTela();
			return;
		case 1:
			adicionarNoh(associado, 0, 0);
			return;
		}
	}
}
void janelaEditarAssociado()
{
	struct s_noh *temp;

	int id_associado;

	struct s_associado *associado;
	associado = (struct s_associado *)calloc(sizeof(struct s_associado), 1);

	os_limparTela();
	printf("\n");
	mostrarTituloPequeno("Editar associado");
	printf("\n");

	printf("  Informe a identifica��o do associado:\n  > ");
	scanf("%d", &id_associado);
	printf("\n");

	temp = getNohAssociadoByIdAssociado(id_associado);

	if (temp == 0 || (((struct s_associado *)temp->dado)->deletado == 1))
	{
		os_limparTela();
		printf("\n  Associado n�o encontrado\n");
		congelarTela();
		return;
	}

	os_limparTela();
	printf("\n");
	mostrarTituloPequeno("Editar associado");
	printf("\n");

	printf("   Nome......: %s\n", ((struct s_associado *)temp->dado)->nome);
	printf("   CPF.......: %s\n", ((struct s_associado *)temp->dado)->cpf);
	printf("   E-mail....: %s\n", ((struct s_associado *)temp->dado)->email);
	printf("   Endere�o..: %s\n", ((struct s_associado *)temp->dado)->endereco);
	printf("   Telefone..: %s\n", ((struct s_associado *)temp->dado)->telefone);
	printf("\n");
	printf(" [0=Cancelar] [1=Continuar]\n");

	if (getNumero() == 0)
	{
		os_limparTela();
		printf("\n  Cancelado\n");
		congelarTela();
		return;
	}

	os_limparTela();
	printf("\n");
	mostrarTituloPequeno("Editar associado");
	printf("\n");

	printf("   Nome......: %s\n", ((struct s_associado *)temp->dado)->nome);
	printf("   CPF.......: %s\n", ((struct s_associado *)temp->dado)->cpf);
	printf("   E-mail....: %s\n", ((struct s_associado *)temp->dado)->email);
	printf("   Endere�o..: %s\n", ((struct s_associado *)temp->dado)->endereco);
	printf("   Telefone..: %s\n", ((struct s_associado *)temp->dado)->telefone);
	printf("\n");

	printf("  Digite o nome do associado:\n  > ");
	strcpy(associado->nome, getString(_STRNOME, _F_LETRAESPACO));
	if (strcmp(associado->nome, "") == 0)
	{
		strcpy(associado->nome, ((struct s_associado *)temp->dado)->nome);
		printf("  > %s\n", associado->nome);
	}
	printf("\n");

	printf("  Digite o CPF do associado:\n  > ");
	strcpy(associado->cpf, getString(_STRCPF, _F_NUMERO));
	if (strcmp(associado->cpf, "") == 0)
	{
		strcpy(associado->cpf, ((struct s_associado *)temp->dado)->cpf);
		printf("  > %s\n", associado->cpf);
	}
	printf("\n");

	printf("  Digite o e-mail do associado:\n  > ");
	strcpy(associado->email, getString(_STREMAIL, _F_EMAIL));
	if (strcmp(associado->email, "") == 0)
	{
		strcpy(associado->email, ((struct s_associado *)temp->dado)->email);
		printf("  > %s\n", associado->email);
	}
	printf("\n");

	printf("  Digite o endere�o do associado:\n  > ");
	strcpy(associado->endereco, getString(_STREND, _F_ENDERECO));
	if (strcmp(associado->endereco, "") == 0)
	{
		strcpy(associado->endereco, ((struct s_associado *)temp->dado)->endereco);
		printf("  > %s\n", associado->endereco);
	}
	printf("\n");

	printf("  Digite o telefone do associado:\n  > ");
	strcpy(associado->telefone, getString(_STRTEL, _F_NUMERO));
	if (strcmp(associado->telefone, "") == 0)
	{
		strcpy(associado->telefone, ((struct s_associado *)temp->dado)->telefone);
		printf("  > %s\n", associado->telefone);
	}
	printf("\n");

	while (1)
	{
		os_limparTela();
		printf("\n");
		mostrarTituloPequeno("Editar associado");
		printf("\n");

		printf("   Dados antigos:\n");
		printf("   Nome......: %s\n", ((struct s_associado *)temp->dado)->nome);
		printf("   CPF.......: %s\n", ((struct s_associado *)temp->dado)->cpf);
		printf("   E-mail....: %s\n", ((struct s_associado *)temp->dado)->email);
		printf("   Endere�o..: %s\n", ((struct s_associado *)temp->dado)->endereco);
		printf("   Telefone..: %s\n", ((struct s_associado *)temp->dado)->telefone);
		printf("\n");

		printf("   Dados modificados:\n");
		printf("   Nome......: %s\n", associado->nome);
		printf("   CPF.......: %s\n", associado->cpf);
		printf("   E-mail....: %s\n", associado->email);
		printf("   Endere�o..: %s\n", associado->endereco);
		printf("   Telefone..: %s\n", associado->telefone);
		printf("\n");
		printf(" [0=Cancelar] [1=Editar]\n");

		switch (getNumero())
		{
		case 0:
			os_limparTela();
			printf("\n  Cancelado\n");
			congelarTela();
			return;
		case 1:
			strcpy(((struct s_associado *)temp->dado)->nome, associado->nome);
			strcpy(((struct s_associado *)temp->dado)->cpf, associado->cpf);
			strcpy(((struct s_associado *)temp->dado)->email, associado->email);
			strcpy(((struct s_associado *)temp->dado)->endereco, associado->endereco);
			strcpy(((struct s_associado *)temp->dado)->telefone, associado->telefone);
			temp->modificado = 1;
			gravarDisco();
			return;
		}
	}
}
void janelaRemoverAssociado()
{
	struct s_noh *temp;

	int id_associado;

	struct s_associado *associado;
	associado = (struct s_associado *)calloc(sizeof(struct s_associado), 1);

	os_limparTela();
	printf("\n");
	mostrarTituloPequeno("Remover associado");
	printf("\n");

	printf("  Informe a identifica��o do associado:\n  > ");
	scanf("%d", &id_associado);
	printf("\n");

	temp = getNohAssociadoByIdAssociado(id_associado);

	if (temp == 0 || (((struct s_associado *)temp->dado)->deletado == 1))
	{
		os_limparTela();
		printf("\n  Associado n�o encontrado\n");
		congelarTela();
		return;
	}

	while (1)
	{
		os_limparTela();
		printf("\n");
		mostrarTituloPequeno("Remover associado");
		printf("\n");

		printf("   Nome......: %s\n", ((struct s_associado *)temp->dado)->nome);
		printf("   CPF.......: %s\n", ((struct s_associado *)temp->dado)->cpf);
		printf("   E-mail....: %s\n", ((struct s_associado *)temp->dado)->email);
		printf("   Endere�o..: %s\n", ((struct s_associado *)temp->dado)->endereco);
		printf("   Telefone..: %s\n", ((struct s_associado *)temp->dado)->telefone);
		printf("\n");
		printf(" [0=Cancelar] [1=Remover]\n");

		if (getNumero() == 0)
		{
			os_limparTela();
			printf("\n  Cancelado\n");
			congelarTela();
			return;
		}
		if (getNumero() == 1)
		{
			((struct s_associado *)temp->dado)->deletado = 1;
			temp->modificado = 1;
			gravarDisco();
			return;
		}
	}
}
void janelaListarAssociado()
{
	struct s_noh *temp;
	int itemTotal = 0, pagTotal = 0, pagAtual = 1, op = (-1), count, itemPorPagina = 40;

	temp = listaA;

	if (temp->proximo == 0)
	{
		os_limparTela();
		printf("N�o foram encontrados registros\n");
		congelarTela();
		return;
	}

	// Descobre quantos itens existem na lista encadeada (1 item = 1)
	for (temp = listaA, itemTotal = 0; temp->proximo != 0; temp = temp->proximo, itemTotal++)
		if (((struct s_associado *)temp->dado)->deletado == 1)
			itemTotal--;

	// Calcula o n�mero de p�ginas necess�rias
	pagTotal = itemTotal / itemPorPagina;
	if ((itemTotal % itemPorPagina) != 0)
		pagTotal++;

	// Ajusta a tela
#ifdef _WIN32
	os_os_system("mode con lines=54");
	os_os_system("mode con cols=160");
#endif

	// + ---------------------------------------------------------- +

	temp = listaA;
	while (op != 0)
	{
		printf("\n");
		mostrarTituloGrande("Lista de associados");
		printf("\n");

		// printTableHeader("ID", "NOME", "CPF", "E-MAIL", "ENDERECO", "TELEFONE");

		// +-------
		// +----------------
		// +------------------------

		printBorder(6);
		printBorder(30);
		printBorder(30);
		printBorder(30);
		printBorder(30);
		printBorder(30);
		printBorder(0);
		printf("\n");

		printf("| %-*s", 6, "ID");
		printf("| %-*s", 30, "NOME");
		printf("| %-*s", 30, "CPF");
		printf("| %-*s", 30, "E-MAIL");
		printf("| %-*s", 30, "ENDERECO");
		printf("| %-*s", 30, "TELEFONE");
		printf("|");
		printf("\n");

		printBorder(6);
		printBorder(30);
		printBorder(30);
		printBorder(30);
		printBorder(30);
		printBorder(30);
		printBorder(0);
		printf("\n");

		// printf("  +------+--------------------------------+-----------------+---------------------------------+-----------------------------------------------+--------------+\n");
		// printf("  | ID   | NOME                           | CPF             | E-MAIL                          | ENDERE�O                                      | TELEFONE     |\n");
		// printf("  +------+--------------------------------+-----------------+---------------------------------+-----------------------------------------------+--------------+\n");
		
		for (count = 1; count <= itemPorPagina; count++)
		{
			if (temp->proximo != 0)
			{
				if (((struct s_associado *)temp->dado)->deletado != 1)
				{
					printf("  | %-04d |", ((struct s_associado *)temp->dado)->id_associado);
					printf(" %-30s |", ((struct s_associado *)temp->dado)->nome);
					printf(" %-15s |", ((struct s_associado *)temp->dado)->cpf);
					printf(" %-31s |", ((struct s_associado *)temp->dado)->email);
					printf(" %-45s |", ((struct s_associado *)temp->dado)->endereco);
					printf(" %-12s |", ((struct s_associado *)temp->dado)->telefone);
					printf(" \n");
				}
				else
					count--;

				temp = temp->proximo;
			}
			else
				printf("  |      |                                |                 |                                 |                                               |              |\n");
		}
		printf("  +------+--------------------------------+-----------------+---------------------------------+-----------------------------------------------+--------------+\n");
		printf("\n");
		printf(" [0=Sair][1=P�gina anterior][2=Pr�xima p�gina]    [p�gina %d de %d]    [%d associado(s)]\n", pagAtual, pagTotal, itemTotal);

		// + ---------------------------------------------------------- +
		while (op != 0)
		{
			op = getNumero();
			if (op == 0)
				break;

			if (op == 1)
			{
				if (pagAtual > 1)
				{
					int aux, v;

					if ((pagAtual == pagTotal) && ((itemTotal % ((pagTotal - 1) * itemPorPagina)) != 0))
						v = itemPorPagina + (itemTotal - ((pagAtual - 1) * itemPorPagina));

					if ((pagAtual == pagTotal) && ((itemTotal % ((pagTotal - 1) * itemPorPagina)) == 0))
						v = (2 * itemPorPagina);

					if ((pagAtual < pagTotal))
						v = (2 * itemPorPagina);

					for (aux = 1; aux <= v; aux++)
						temp = temp->anterior;

					pagAtual--;
					os_limparTela();
					break;
				}
			}
			if (op == 2)
			{
				if (pagAtual < pagTotal)
				{
					pagAtual++;
					os_limparTela();
					break;
				}
			}
		}
		// + ---------------------------------------------------------- +
	}

#ifdef _WIN32
	os_system("mode con lines=60");
	os_system("mode con cols=62");
#endif
}
void janelaMulta()
{
	struct s_noh *temp;

	int id_associado;

	os_limparTela();
	printf("\n");
	mostrarTituloPequeno("Multa");
	printf("\n");

	printf("  Informe a identifica��o do associado:\n  > ");
	scanf("%d", &id_associado);
	printf("\n");

	temp = getNohAssociadoByIdAssociado(id_associado);

	if (temp == 0)
	{
		os_limparTela();
		printf("\n  Associado n�o encontrado\n");
		congelarTela();
		return;
	}

	while (1)
	{
		os_limparTela();
		printf("\n");
		mostrarTituloPequeno("Multa");
		printf("\n");

		printf("   O associado %s possui %f reais em multa.\n", ((struct s_associado *)temp->dado)->nome, ((struct s_associado *)temp->dado)->multa);
		printf("\n");
		printf(" [0=Sair]\n");
		if (getNumero() == 0)
			return;
	}
}
void janelaZerarMulta()
{
	struct s_noh *temp;
	int opcao;

	int id_associado;

	os_limparTela();
	printf("\n");
	mostrarTituloPequeno("Multa");
	printf("\n");

	printf("  Informe a identifica��o do associado:\n  > ");
	scanf("%d", &id_associado);
	printf("\n");

	temp = getNohAssociadoByIdAssociado(id_associado);

	if (temp == 0)
	{
		os_limparTela();
		printf("\n  Associado n�o encontrado\n");
		congelarTela();
		return;
	}

	while (1)
	{
		os_limparTela();
		printf("\n");
		mostrarTituloPequeno("Multa");
		printf("\n");

		printf("   O associado %s possui %f reais em multa.\n", ((struct s_associado *)temp->dado)->nome, ((struct s_associado *)temp->dado)->multa);
		printf("\n");
		printf(" [0=Sair] [1=Zerar multa]\n");
		opcao = getNumero();
		if (opcao == 0)
			return;
		if (opcao == 1)
		{
			((struct s_associado *)temp->dado)->multa;
			temp->modificado = 1;
			gravarDisco();
		}
	}
}
int getNovaIdAssociado()
{
	int id = 1;
	struct s_noh *temp;

	for (temp = listaA; temp->proximo != 0; temp = temp->proximo, id++)
		;

	for (temp = listaA; temp->proximo != 0; temp = temp->proximo)
		if (id == ((struct s_associado *)temp->dado)->id_associado)
		{
			id++;
			temp = listaA;
		}

	return id;
}
void janelaInfoAssociado()
{
	struct s_noh *temp;

	int id_associado;

	struct s_associado *associado;

	os_limparTela();
	printf("\n");
	mostrarTituloPequeno("Informa��es de associado");
	printf("\n");

	printf("  Informe a identifica��o do associado:\n  > ");
	scanf("%d", &id_associado);
	printf("\n");

	temp = getNohAssociadoByIdAssociado(id_associado);

	if (temp == 0 || (((struct s_associado *)temp->dado)->deletado == 1))
	{
		os_limparTela();
		printf("\n  Associado n�o encontrado\n");
		congelarTela();
		return;
	}

	while (1)
	{
		os_limparTela();
		printf("\n");
		mostrarTituloPequeno("Informa��es de associado");
		printf("\n");

		printf("   Nome......: %s\n", ((struct s_associado *)temp->dado)->nome);
		printf("   CPF.......: %s\n", ((struct s_associado *)temp->dado)->cpf);
		printf("   E-mail....: %s\n", ((struct s_associado *)temp->dado)->email);
		printf("   Endere�o..: %s\n", ((struct s_associado *)temp->dado)->endereco);
		printf("   Telefone..: %s\n", ((struct s_associado *)temp->dado)->telefone);
		printf("\n");
		if (((struct s_associado *)temp->dado)->bloqueado == 1)
		{
			int diasBloqueado = diasEntreDuasDatas(getDia(), getMes() - 1, getAno(), ((struct s_associado *)temp->dado)->dia_do_bloqueio[0], ((struct s_associado *)temp->dado)->dia_do_bloqueio[1] - 1, ((struct s_associado *)temp->dado)->dia_do_bloqueio[2]);
			printf("  Bloqueado: SIM\n");
			printf("  Dias bloqueado: %d\n", diasBloqueado);
			printf("  Dias restante: %d\n", 180 - diasBloqueado);
		}
		else
		{
			printf("  Bloqueado: N�O\n");
		}
		printf("\n");
		printf("   Multa: %d\n", ((struct s_associado *)temp->dado)->multa);
		printf("\n");
		printf("   Quantidade de multa: %d\n", ((struct s_associado *)temp->dado)->qnt_de_multa);
		printf("\n");
		printf(" [0=Cancelar]\n");

		if (getNumero() == 0)
		{
			os_limparTela();
			printf("\n  Cancelado\n");
			congelarTela();
			return;
		}
	}
}
// ************************************************ QUICKSORT & BUSCA BIN�RIA
int busca(struct s_noh_ord *vetor, int tam, char *elemento)
{
	int i;
	for (i = 0; i < tam; i++)
	{
		if (strcmp(vetor[i].nome, elemento) == 0)
			return i;
		else if (strcmp(vetor[i].nome, elemento) > 0)
			return -2;
	}
	return -1;
}
void janelaBuscarAssociado()
{
	int qnt, i;
	struct s_noh *temp;
	struct s_noh_ord *tempO, *tempO2;

	// vetor de ponteiros para noh
	struct s_noh_ord *vetor;

	// conta quantos nomes h�
	for (qnt = 0, temp = listaA; temp->proximo != 0; temp = temp->proximo)
		if (((struct s_associado *)temp->dado)->deletado != 1)
			qnt++;

	// aloca memoria para QNT noh's
	vetor = (struct s_noh_ord *)calloc(sizeof(struct s_noh_ord), qnt);

	// copia os nomes para os noh's
	for (i = 0, temp = listaA; temp->proximo != 0; temp = temp->proximo, i++)
	{
		if (((struct s_associado *)temp->dado)->deletado != 1)
		{
			vetor[i].endereco = temp;
			vetor[i].nome = (char *)calloc(tamString((char *)&((struct s_associado *)temp->dado)->nome), sizeof(char));
			strcpy(vetor[i].nome, ((struct s_associado *)temp->dado)->nome);
			vetor[i].proximo = 0;
		}
		else
			i--;
	}

	// qsort neles
	qsort(vetor, qnt, sizeof(struct s_noh_ord), cmpStructNohOrd);

	char termo[_STRNOME];
	char *result;
	printf("Digite o nome para procurar:\n");
	strcpy(termo, getString(_STRNOME, _F_LETRAESPACO));

	char *keey;
	char **key;
	keey = termo;
	key = &keey;
	/*result = (char*) bsearch(key,vetor,qnt,sizeof(struct s_noh_ord),cmpStructNohOrd);

	if(result>0)
	printf("Encontrado:  %s\n",vetor[result]);
	else
	printf("nao encontrado - %d\n",result);*/
	int ii = busca(vetor, qnt, termo);
	if (ii >= 0)
		printf("Encontrado:  %s \n", vetor[ii]);
	else
		printf("N�o encontrado\n");
	congelarTela();
}
void janelaListarAssociadoOrdenado()
{
	QuickSortAssociado();
	//*************************************************************************************************
	struct s_noh_ord *temp;
	int itemTotal = 0, pagTotal = 0, pagAtual = 1, op = (-1), count, itemPorPagina = 40;

	// Verifica se existe registros para mostrar
	//*************************************************************************************************
	temp = listaAOrd;
	if (temp->proximo == 0)
	{
		os_limparTela();
		printf("N�o foram encontrados registros\n");
		congelarTela();
		return;
	}

	// Descobre quantos itens existem na lista encadeada (1 item = 1)
	//*************************************************************************************************
	for (temp = listaAOrd, itemTotal = 0; temp->proximo != 0; temp = temp->proximo, itemTotal++)
		// if(((struct s_associado*)temp->dado)->deletado==1)
		//	itemTotal--;

		// Calcula o n�mero de p�ginas necess�rias
		pagTotal = itemTotal / itemPorPagina;
	if ((itemTotal % itemPorPagina) != 0)
		pagTotal++;

	// Ajusta a tela
	os_system("mode con lines=54");
	os_system("mode con cols=160");

	//*************************************************************************************************
	temp = listaAOrd;

	while (op != 0)
	{

		printf("\n");
		mostrarTituloGrande("Lista de associados");
		printf("\n");
		printf("  +------+---------------------------------------+------------------+----------------------+-------------------------------------------------+---------------+\n");
		printf("  | ID   | NOME                                  | CPF              | E-MAIL               | ENDERE�O                                        | TELEFONE      |\n");
		printf("  +------+---------------------------------------+------------------+----------------------+-------------------------------------------------+---------------+\n");
		for (count = 1; count <= itemPorPagina; count++)
		{
			if (temp->proximo != 0)
			{

				/*if(((struct s_associado*)temp->dado)->deletado!=1)
				{*/
				//*************************************************************************************************
				printf("  | %-04d |", ((struct s_associado *)((struct s_noh *)temp->endereco)->dado)->id_associado);
				printf(" %-37s |", ((struct s_associado *)((struct s_noh *)temp->endereco)->dado)->nome);
				printf(" %-16s |", ((struct s_associado *)((struct s_noh *)temp->endereco)->dado)->cpf);
				printf(" %-20s |", ((struct s_associado *)((struct s_noh *)temp->endereco)->dado)->email);
				printf(" %-47s |", ((struct s_associado *)((struct s_noh *)temp->endereco)->dado)->endereco);
				printf(" %-13s |", ((struct s_associado *)((struct s_noh *)temp->endereco)->dado)->telefone);
				printf(" \n");
				/*		} else
				count--;*/

				temp = temp->proximo;
			}
			else
				printf("  |      |                                       |                  |                      |                                                 |               |\n");
		}
		printf("  +------+---------------------------------------+------------------+----------------------+-------------------------------------------------+---------------+\n");
		printf("\n");
		printf(" [0=Sair][1=P�gina anterior][2=Pr�xima p�gina]    [p�gina %d de %d]    [%d associado(s)]\n", pagAtual, pagTotal, itemTotal);

		while (op != 0)
		{
			op = getNumero();
			if (op == 0)
				break;

			if (op == 1)
			{
				if (pagAtual > 1)
				{
					int aux, v;

					if ((pagAtual == pagTotal) && ((itemTotal % ((pagTotal - 1) * itemPorPagina)) != 0))
					{
						// printf("1");
						v = itemPorPagina + (itemTotal - ((pagAtual - 1) * itemPorPagina));
					}

					if ((pagAtual == pagTotal) && ((itemTotal % ((pagTotal - 1) * itemPorPagina)) == 0))
					{
						// printf("2");
						v = (2 * itemPorPagina);
					}

					if ((pagAtual < pagTotal))
					{
						// printf("3");
						v = (2 * itemPorPagina);
					}

					/// printf(" [%d]\n",v);
					// congelarTela();

					for (aux = 1; aux <= v; aux++)
					{
						temp = temp->anterior;
					}
					pagAtual--;
					os_limparTela();
					break;
				}
			}

			if (op == 2)
			{
				if (pagAtual < pagTotal)
				{
					pagAtual++;
					os_limparTela();
					break;
				}
			}
		}
	}

#ifdef _WIN32
	os_system("mode con lines=60");
	os_system("mode con cols=62");
#endif
}
int cmpStructNohOrd(const void *a, const void *b)
{
	struct s_noh_ord *ia = (struct s_noh_ord *)a;
	struct s_noh_ord *ib = (struct s_noh_ord *)b;
	return strcmp(ia->nome, ib->nome);
}
int tamString(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		;

	return i + 1;
}
void QuickSortAssociado()
{
	int qnt, i;
	struct s_noh *temp;
	struct s_noh_ord *tempO, *tempO2;

	// vetor de ponteiros para noh
	struct s_noh_ord *vetor;

	// conta quantos nomes
	for (qnt = 0, temp = listaA; temp->proximo != 0; temp = temp->proximo)
		if (((struct s_associado *)temp->dado)->deletado != 1)
			qnt++;

	// aloca memoria para QNT noh's
	vetor = (struct s_noh_ord *)calloc(sizeof(struct s_noh_ord), qnt);

	// copia os nomes para os noh's
	for (i = 0, temp = listaA; temp->proximo != 0; temp = temp->proximo, i++)
	{
		if (((struct s_associado *)temp->dado)->deletado != 1)
		{
			vetor[i].endereco = temp;
			vetor[i].nome = (char *)calloc(tamString((char *)&((struct s_associado *)temp->dado)->nome), sizeof(char));
			strcpy(vetor[i].nome, ((struct s_associado *)temp->dado)->nome);
			vetor[i].proximo = 0;
		}
		else
			i--;
	}

	// qsort neles
	qsort(vetor, qnt, sizeof(struct s_noh_ord), cmpStructNohOrd);

	// cria a lista encadeada
	for (tempO = listaAOrd, i = 0; i < qnt; i++)
	{
		tempO->nome = (char *)calloc(tamString(vetor[i].nome), sizeof(char));
		tempO->endereco = vetor[i].endereco;
		tempO->proximo = vetor[i].proximo;
		tempO->proximo = (struct s_noh_ord *)calloc(sizeof(struct s_noh_ord), 1);

		tempO2 = tempO;

		tempO = tempO->proximo;

		tempO->anterior = tempO2;
		tempO->proximo = 0;
		tempO->nome = 0;
		tempO->endereco = 0;
	}

	// libera a memoria
	// for(i=0;i<qnt;i++)
	// free((struct s_noh_ord *)&vetor[i]);
}
struct s_noh *getNohAssociado()
{
	struct s_noh *temp;

	int id_associado;

	showPositiveIntegerField("ID DO ASSOCIADO", &id_associado);

	// PROCURA O ASSOCIADO PELO ID
	for (temp = listaA; temp->proximo != 0; temp = temp->proximo)
		{
			if (id_associado == ((struct s_associado *)temp->dado)->id_associado)
{
	return temp;
}		}

	// REGRA DE NEGOCIO: O associado nao pode ser deletado
	if (temp == 0 || (((struct s_associado *)temp->dado)->deletado == 1))
	{
		os_limparTela();
		printf("\n  Associado n�o encontrado\n");
		congelarTela();
		return 0;
	}

	return 0;
}
void exibirDadosAssociado(struct s_associado *temp)
{
	printf("   Nome......: %s\n", ((struct s_associado *)temp)->nome);
	printf("   CPF.......: %s\n", ((struct s_associado *)temp)->cpf);
	printf("   E-mail....: %s\n", ((struct s_associado *)temp)->email);
	printf("   Endere�o..: %s\n", ((struct s_associado *)temp)->endereco);
	printf("   Telefone..: %s\n", ((struct s_associado *)temp)->telefone);
	printf("\n");
}