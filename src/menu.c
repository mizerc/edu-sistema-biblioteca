#include "types.h"



int getOpcao(char *titulo, char *texto)
{
	os_limparTela();

	printf("\n");
	mostrarTituloPequeno("Sistema de controle de empr�stimo de livros");
	printf("\n");
	printf("    %d/%d/%d\n", getDia(), getMes(), getAno());
	printf("\n");
	printf(" +==========================================================+\n");
	printf(" |                                                          |\n");
	printf(" |   %-54s |\n", titulo);
	printf(" |                                                          |\n");

	char *pergunta;
	int pos, pos2, tam = 0, ini = 0;
	for (pos = 0; texto[pos] != '$'; pos++)
	{
		if (texto[pos] == '#')
		{
			pergunta = (char *)malloc(tam + 1);
			for (pos2 = 0; pos2 < tam; pos2++) {
				pergunta[pos2] = texto[ini + pos2];
			}
			pergunta[pos2] = '\0';
			printf(" |      %-51s |\n", pergunta);
			tam = 0;
			ini = pos + 1;
			free(pergunta);
		}
		else
		{
			tam++;
		}
	}
	printf(" |                                                          |\n");
	printf(" +==========================================================+\n");
	printf("\n");

	printf(" > ");
	int input = getNumero();

	return input;
}
int getSimNao()
{
	return 0;
}
char *getString(int tamanho, int filtro)
{
	/*
	USAGE:
	  printf("  Digite a edi��o do livro:\n  > ");
  strcpy(livro->edicao, getString(_STREDICAO, _F_LETRAESPACO));
  printf("\n");
  */
	char *bkp, *str;
	int i, j;

	bkp = (char *)calloc(sizeof(char), tamanho + 1);
	str = (char *)calloc(sizeof(char), tamanho + 1);

	fflush(stdin);
	fgets(bkp, tamanho, stdin);

	if (filtro == _F_LETRAESPACO)
	{
		for (i = 0, j = 0; i <= tamanho; i++, j++)
		{
			bkp[i] = tirarAcento(bkp[i]);
			if (isLetra(bkp[i]))
			{
				str[j] = toupper(bkp[i]);
			}
			else if (bkp[i] == ' ')
			{
				str[j] = bkp[i];
			}
			else if (bkp[i] == '\n' || bkp[i] == '\0' || bkp[i] == '\r')
			{
				str[j] = '\0';
				break;
			}
			else
				j--;
		}
	}
	if (filtro == _F_NUMERO)
	{
		for (i = 0, j = 0; i <= tamanho; i++, j++)
		{
			if (isNumero(bkp[i]))
				str[j] = bkp[i];
			else if (bkp[i] == '\n' || bkp[i] == '\0' || bkp[i] == '\r')
			{
				str[j] = '\0';
				break;
			}
			else
				j--;
		}
	}
	if (filtro == _F_EMAIL)
	{
		for (i = 0, j = 0; i <= tamanho; i++, j++)
		{
			bkp[i] = tirarAcento(bkp[i]);
			if (isLetra(bkp[i]))
			{
				str[j] = toupper(bkp[i]);
			}
			else if (isNumero(bkp[i]))
			{
				str[j] = bkp[i];
			}
			else if (bkp[i] == ' ')
			{
				str[j] = bkp[i];
			}
			else if (bkp[i] == '@')
			{
				str[j] = bkp[i];
			}
			else if (bkp[i] == '.')
			{
				str[j] = bkp[i];
			}
			else if (bkp[i] == '_')
			{
				str[j] = bkp[i];
			}
			else if (bkp[i] == '-')
			{
				str[j] = bkp[i];
			}
			else if (bkp[i] == '\n' || bkp[i] == '\0' || bkp[i] == '\r')
			{
				str[j] = '\0';
				break;
			}
			else
				j--;
		}
	}
	if (filtro == _F_ENDERECO)
	{
		for (i = 0, j = 0; i <= tamanho; i++, j++)
		{
			bkp[i] = tirarAcento(bkp[i]);
			if (isLetra(bkp[i]))
			{
				str[j] = toupper(bkp[i]);
			}
			else if (isNumero(bkp[i]))
			{
				str[j] = bkp[i];
			}
			else if (bkp[i] == ' ')
			{
				str[j] = bkp[i];
			}
			else if (bkp[i] == ',')
			{
				str[j] = bkp[i];
			}
			else if (bkp[i] == '.')
			{
				str[j] = bkp[i];
			}
			else if (bkp[i] == '\n' || bkp[i] == '\0' || bkp[i] == '\r')
			{
				str[j] = '\0';
				break;
			}
			else
				j--;
		}
	}

	return str;
}

