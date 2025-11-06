#include "types.h"

void janelaEmprestarLivro()
{
	// -*****************************************
	int id_associado = 0;
	int id_livro = 0;

	struct s_noh *nohAssociado;
	struct s_noh *nohLivro;

	// Declaracao da variavel da estrutura
	struct s_emprestimo *emprestimo;
	// Alocacao de memoria para a estrutura
	emprestimo = (struct s_emprestimo *)calloc(sizeof(struct s_emprestimo), 1);
	// Zeracao dos dados da estrutura
	emprestimo->tipo = _EMPRESTIMO;
	emprestimo->deletado = 0;
	emprestimo->id_emprestimo = getNovaIdEmprestimo();

	// TOPO
	os_limparTela();
	mostrarTituloPequeno("EMPRESTAR LIVRO");
	printf("  ID DESSE EMPRESTIMO: %d", emprestimo->id_emprestimo);
	printf("\n");

	// REGRA DE NEGOCIO: O associado nao pode ter mais de 3 exemplares emprestados
	nohAssociado = getNohAssociado();
	if (((struct s_associado *)nohAssociado->dado)->qnt_livro_emprestado >= 3)
	{
		os_limparTela();
		printf("\n  Associado j� possui 3 exemplares emprestados.\nCancelado.\n");
		congelarTela();
		return;
	}

	// REGRA DE NEGOCIO: O associado nao pode estar bloqueado
	if (((struct s_associado *)nohAssociado->dado)->bloqueado == 1)
	{
		int diasBloqueado = diasEntreDuasDatas(getDia(), getMes() - 1, getAno(), ((struct s_associado *)nohAssociado->dado)->dia_do_bloqueio[0], ((struct s_associado *)nohAssociado->dado)->dia_do_bloqueio[1] - 1, ((struct s_associado *)nohAssociado->dado)->dia_do_bloqueio[2]);
		if (diasBloqueado > 180)
		{
			printf("\n  Usu�rio foi desbloqueado!\n  J� se passou 180 dias desde o bloqueio!\n");
			((struct s_associado *)nohAssociado->dado)->bloqueado = 0;
			((struct s_associado *)nohAssociado->dado)->dia_do_bloqueio[0] = 0;
			((struct s_associado *)nohAssociado->dado)->dia_do_bloqueio[1] = 0;
			((struct s_associado *)nohAssociado->dado)->dia_do_bloqueio[2] = 0;
			((struct s_associado *)nohAssociado->dado)->qnt_de_multa = 0;
		}
		else
		{
			os_limparTela();
			printf("\n  Associado bloqueado!  Dias bloqueado: %d\n  Dias para acabar o bloqueio: %d\n  Cancelado.\n", diasBloqueado, 180 - diasBloqueado);
			congelarTela();
			return;
		}
	}

	exibirDadosAssociado(nohAssociado);

	nohLivro = getNohLivro();

	// REGRA DE NEGOCIO: O livro nao pode ter mais de 3 exemplares emprestados
	if (((struct s_livro *)nohLivro->dado)->qnt_livro_emprestado >= ((struct s_livro *)nohLivro->dado)->exemplar)
	{
		os_limparTela();
		printf("\n  N�o h� exemplares dispon�veis.\nCancelado.\n");
		congelarTela();
		return;
	}

	// REGRA DE NEGOCIO: O livro nao pode estar reservado para outro associado
	if (((struct s_livro *)nohLivro->dado)->reservadoParaIdAssociado != 0 && (((struct s_livro *)nohLivro->dado)->exemplar - ((struct s_livro *)nohLivro->dado)->qnt_livro_emprestado) < 2)
	{
		if (((struct s_livro *)nohLivro->dado)->reservadoParaIdAssociado != ((struct s_associado *)nohAssociado->dado)->id_associado)
		{
			os_limparTela();
			printf("%d  %d\n", ((struct s_livro *)nohLivro->dado)->reservadoParaIdAssociado, ((struct s_associado *)nohAssociado->dado)->id_associado);
			printf("\n  O livro est� reservado.\n");
			congelarTela();
			return;
		}
	}

	while (1)
	{
		mostrarTituloPequeno("Empr�stimo de livro");
		exibirDadosAssociado(nohAssociado);
		exibirDadoLivro(nohLivro);

		printf("\n");
		printf("   Data de empr�stimo: %d/%d/%d\n", getDia(), getMes(), getAno());
		printf("\n");

		printf(" [0=Cancelar] [1=Confirmar]\n");

		switch (getNumero())
		{
		case 0:
			os_limparTela();
			printf("\n  Cancelado\n");
			congelarTela();
			return;
		case 1:
			((struct s_associado *)nohAssociado->dado)->qnt_livro_emprestado += 1;
			((struct s_livro *)nohLivro->dado)->qnt_livro_emprestado += 1;
			((struct s_livro *)nohLivro->dado)->reservadoParaIdAssociado = 0;

			emprestimo->id_associado = id_associado;
			emprestimo->id_livro = id_livro;
			emprestimo->dataEmprestado[0] = getDia();
			emprestimo->dataEmprestado[1] = getMes();
			emprestimo->dataEmprestado[2] = getAno();
			nohAssociado->modificado = 1;
			nohLivro->modificado = 1;
			adicionarNoh(0, 0, emprestimo);
			return;
		default:
			os_limparTela();
			printf("\n  Op��o inv�lida.\n  Cancelado\n");
			congelarTela();
			return;
		}
	}
}
void janelaDevolverLivro()
{
	int id_associado = 0, id_livro = 0, id_livros[3] = {0, 0, 0}, i;
	struct s_noh *nohEmprestimo, *nohAssociado, *nohLivro, *nohEmprestimos[3] = {0, 0, 0};

	mostrarTituloPequeno("Devolu��o de livro");

	nohAssociado = getNohAssociado();

	for (nohEmprestimo = listaE, i = 0; nohEmprestimo->proximo != 0 && i <= 3; nohEmprestimo = nohEmprestimo->proximo)
		if (id_associado == ((struct s_emprestimo *)nohEmprestimo->dado)->id_associado)
		{
			id_livro = ((struct s_emprestimo *)nohEmprestimo->dado)->id_livro;
			printf(" [%d] %s\n", i, ((struct s_livro *)getNohLivroByIdLivro(id_livro)->dado)->titulo);
			id_livros[i] = id_livro;
			nohEmprestimos[i] = nohEmprestimo;
			i++;
		}

	printf("\n");
	printf("  Informe o livro a ser devolvido:\n  > ");
	i = getNumero();
	if (i != 0 && i != 1 && i != 2)
	{
		os_limparTela();
		printf("\n  Op��o inv�lida.\n  Cancelado\n");
		congelarTela();
		return;
	}
	id_livro = id_livros[i];
	printf("\n");
	nohLivro = getNohLivroByIdLivro(id_livro);
	if (nohLivro == 0)
	{
		os_limparTela();
		printf("\n  Livro n�o encontrado\n");
		congelarTela();
		return;
	}

	os_limparTela();
	printf("\n");
	mostrarTituloPequeno("Devolu��o de livro");
	printf("\n");

	nohAssociado = getNohAssociadoByIdAssociado(id_associado);

	int dia = getDia();
	int mes = getMes();
	int ano = getAno();

	int diaD = ((struct s_emprestimo *)nohEmprestimos[i]->dado)->dataEmprestado[0];
	int mesD = ((struct s_emprestimo *)nohEmprestimos[i]->dado)->dataEmprestado[1];
	int anoD = ((struct s_emprestimo *)nohEmprestimos[i]->dado)->dataEmprestado[2];

	((struct s_emprestimo *)nohEmprestimos[i]->dado)->dataDevolvido[0] = dia;
	((struct s_emprestimo *)nohEmprestimos[i]->dado)->dataDevolvido[1] = mes;
	((struct s_emprestimo *)nohEmprestimos[i]->dado)->dataDevolvido[2] = ano;

	int diasComLivro = diasEntreDuasDatas(diaD, mesD - 1, anoD, dia, mes - 1, ano);

	while (1)
	{
		os_limparTela();
		printf("\n");
		mostrarTituloPequeno("Devolu��o de livro");
		printf("\n");

		printf("   Dia emprestado: %d/%d/%d\n", diaD, mesD, anoD);
		printf("   Dia devolvido.: %d/%d/%d\n", dia, mes, ano);
		printf("   Dias com o livro: %d\n", diasComLivro);
		printf("\n");
		if (diasComLivro > 3)
		{
			printf("   Multa: SIM \n");
			printf("   Valor da multa: %d reais \n", (diasComLivro - 3) * _VALORDAMULTA);

			((struct s_associado *)nohAssociado->dado)->qnt_de_multa += 1;
			((struct s_associado *)nohAssociado->dado)->multa += ((diasComLivro - 3) * _VALORDAMULTA);

			if (((struct s_associado *)nohAssociado->dado)->qnt_de_multa > 10)
			{
				((struct s_associado *)nohAssociado->dado)->bloqueado = 1;
				((struct s_associado *)nohAssociado->dado)->dia_do_bloqueio[0] = dia;
				((struct s_associado *)nohAssociado->dado)->dia_do_bloqueio[1] = mes;
				((struct s_associado *)nohAssociado->dado)->dia_do_bloqueio[2] = ano;
			}
		}
		else
		{
			printf("   Multa: N�O \n");
		}
		printf("\n");
		printf("   Titulo......: %s\n", ((struct s_livro *)nohLivro->dado)->titulo);
		printf("   Subt�tulo.......: %s\n", ((struct s_livro *)nohLivro->dado)->subtitulo);
		printf("   Autor....: %s\n", ((struct s_livro *)nohLivro->dado)->autor);
		printf("   ISBN..: %s\n", ((struct s_livro *)nohLivro->dado)->isbn);
		printf("   Editora..: %s\n", ((struct s_livro *)nohLivro->dado)->editora);
		printf("   Edi��o..: %s\n", ((struct s_livro *)nohLivro->dado)->edicao);
		printf("   Exemplar(es)..: %d\n", ((struct s_livro *)nohLivro->dado)->exemplar);
		printf("\n");
		printf(" [0=Cancelar] [1=Confirmar]\n");

		switch (getNumero())
		{
		case 0:
			os_limparTela();
			printf("\n  Cancelado\n");
			congelarTela();
			return;
		case 1:
			((struct s_associado *)nohAssociado->dado)->qnt_livro_emprestado -= 1;
			((struct s_livro *)nohLivro->dado)->qnt_livro_emprestado -= 1;
			((struct s_emprestimo *)nohEmprestimos[i]->dado)->deletado = 1;
			nohEmprestimos[i]->modificado = 1;
			nohLivro->modificado = 1;
			nohAssociado->modificado = 1;
			gravarDisco();
			return;
		}
	}
}
void janelaListarEmprestimo()
{
	//*************************************************************************************************
	struct s_noh *temp, *nohAssociado, *nohLivro;
	int itemTotal = 0, pagTotal = 0, pagAtual = 1, op = (-1), count, itemPorPagina = 40;

	temp = listaE;
	if (temp->proximo == 0)
	{
		os_limparTela();
		printf("N�o foram encontrados registros\n");
		congelarTela();
		return;
	}

	for (temp = listaE, itemTotal = 0; temp->proximo != 0; temp = temp->proximo, itemTotal++)
		if (((struct s_emprestimo *)temp->dado)->deletado == 1)
			itemTotal--;

	pagTotal = itemTotal / itemPorPagina;
	if ((itemTotal % itemPorPagina) != 0)
		pagTotal++;

#ifdef _WIN32
	os_system("mode con lines=54");
	os_system("mode con cols=160");
#endif

	temp = listaE;

	while (op != 0)
	{

		printf("\n");
		mostrarTituloGrande("Lista de empr�stimos");
		printf("\n");
		printf("  +------+---------------------------------------+------------------+----------------------+-----------------------------------------------------------------+\n");
		printf("  | ID   | NOME                                  | CPF              | QTD EMPRESTADA       | TITULO DO LIVRO                                                 |\n");
		printf("  +------+---------------------------------------+------------------+----------------------+-----------------------------------------------------------------+\n");
		for (count = 1; count <= itemPorPagina; count++)
		{
			if (temp->proximo != 0)
			{
				if (((struct s_emprestimo *)temp->dado)->deletado != 1)
				{
					nohAssociado = getNohAssociadoByIdAssociado(((struct s_emprestimo *)temp->dado)->id_associado);
					nohLivro = getNohLivroByIdLivro(((struct s_emprestimo *)temp->dado)->id_livro);
					if (nohLivro == 0 || nohAssociado == 0)
						return;
					printf("  | %-04d |", ((struct s_emprestimo *)temp->dado)->id_emprestimo);
					printf(" %-37s |", ((struct s_associado *)nohAssociado->dado)->nome);
					printf(" %-16s |", ((struct s_associado *)nohAssociado->dado)->cpf);
					printf(" %-20d |", ((struct s_associado *)nohAssociado->dado)->qnt_livro_emprestado);
					printf(" %-63s |", ((struct s_livro *)nohLivro->dado)->titulo);
					printf(" \n");
				}
				else
					count--;

				temp = temp->proximo;
			}
			else
				printf("  |      |                                       |                  |                      |                                                                 |\n");
		}
		printf("  +------+---------------------------------------+------------------+----------------------+-----------------------------------------------------------------+\n");
		printf("\n");
		printf(" [0=Sair][1=P�gina anterior][2=Pr�xima p�gina]    [p�gina %d de %d]    [%d empr�stimo(s)]\n", pagAtual, pagTotal, itemTotal);

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
				if (pagAtual < pagTotal)
				{
					pagAtual++;
					os_limparTela();
					break;
				}
		}
	}
	os_system("mode con lines=60");
	os_system("mode con cols=62");
}

int getNovaIdEmprestimo()
{
	int id = 1;
	struct s_noh *temp;

	for (temp = listaE; temp->proximo != 0; temp = temp->proximo, id++)
		;

	for (temp = listaE; temp->proximo != 0; temp = temp->proximo)
		if (id == ((struct s_emprestimo *)temp->dado)->id_emprestimo)
		{
			id++;
			temp = listaE;
		}

	return id;
}
struct s_noh *getNohEmprestimoByIdAssociado(int id_associado)
{
	struct s_noh *temp;

	for (temp = listaE; temp->proximo != 0; temp = temp->proximo)
		if (id_associado == ((struct s_emprestimo *)temp->dado)->id_associado)
			return temp;

	return 0;
}
struct s_noh *getNohEmprestimoByIdLivro(int id_livro)
{
	struct s_noh *temp;

	for (temp = listaE; temp->proximo != 0; temp = temp->proximo)
		if (id_livro == ((struct s_emprestimo *)temp->dado)->id_livro)
		{
		}

	return 0;
}
struct s_noh *getNohAssociadoByIdAssociado(int id_associado)
{
	struct s_noh *ptemp;

	for (ptemp = listaA; ptemp->proximo != 0; ptemp = ptemp->proximo)
		if (id_associado == ((struct s_associado *)ptemp->dado)->id_associado)
		{
			return ptemp;
		}

	return 0;
};
struct s_noh *getNohLivroByIdLivro(int id_livro)
{
	struct s_noh *ptemp;

	for (ptemp = listaL; ptemp->proximo != 0; ptemp = ptemp->proximo)
		if (id_livro == ((struct s_livro *)ptemp->dado)->id_livro)
		{
			return ptemp;
		}

	return 0;
};
