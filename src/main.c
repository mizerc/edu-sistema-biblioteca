#include "types.h"

void menuAssociado(void) {
	os_limparTela();
	int opcao = 0;
	do {
		opcao = getOpcao("CONTROLE ASSOCIADOS", "0. Voltar#1. Cadastrar associado#2. Editar associado#3. Remover associado#4. Buscar associado por nome#5. Ver multa de associado#6. Zerar multa de associado#7. Listar associados#8. Listar associados por ordem de nome#9. Informa��es de associado#$");
		os_limparTela();
		if(opcao == 0) {
			opcao = (-1);
		}
		if(opcao == 1) {
			janelaCadastrarAssociado();
		}
		if(opcao == 2) {
			janelaEditarAssociado();
		}
		if(opcao == 3) {
			janelaRemoverAssociado();
		}
		if(opcao == 4) {
			janelaBuscarAssociado();
		}
		if(opcao == 5) {
			janelaMulta();
		}
		if(opcao == 6) {
			janelaZerarMulta();
		}
		if(opcao == 7) {
			janelaListarAssociado();
		}
		if(opcao == 8) {
			janelaListarAssociadoOrdenado();
		}
		if(opcao == 9) {
			janelaInfoAssociado();
		}
	} while (opcao != -1);
}

void menuLivro(void) {
	os_limparTela();
	int opcao = 0;
	do {
		opcao = getOpcao("CONTROLE LIVROS", "0. Voltar#1. Cadastrar livro#2. Editar livro#3. Remover livro#4. Buscar livro#5. Listar livros#6. Listar livro ordenado#7. Reservar livro#8. Tirar reserva#$");
		os_limparTela();
		switch (opcao) {
			case 0:
				opcao = (-1);
				break;
			case 1:
				janelaCadastrarLivro();
				break;
			case 2:
				janelaEditarLivro();
				break;
			case 3:
				janelaRemoverLivro();
				break;
			case 4:
				// janelaBuscarLivro();
				break;
			case 5:
				janelaListarLivro();
				break;
			case 6:
				// janelaListarLivroOrdenado();
				break;
			case 7:
				reservarLivro();
				break;
			case 8:
				tirarReserva();
				break;
		}
	} while (opcao != -1);
}

void menuEmprestimo(void) {
	os_limparTela();
	int opcao = 0;
	do {
		opcao = getOpcao("CONTROLE EMPRESTIMOS", "0. Voltar#1. Emprestar livro#2. Devolver livro#3. Listar emprestimos#$");
		os_limparTela();
		switch (opcao) {
			case 0:
				opcao = (-1);
				break;
			case 1:
				janelaEmprestarLivro();
				break;
			case 2:
				janelaDevolverLivro();
			break;
			case 3:
				janelaListarEmprestimo();
			break;
		}
	} while (opcao != -1);
}
int main()
{
	setlocale(LC_ALL, "");
	// os_system("TITLE BookLending");
	splashScreen();
	inicializar();
	carregarMemoria();

	int opcao = 0;
	do
	{
		opcao = getOpcao("Janela Principal", 
			"0. Sair#1. ASSOCIADOS#2. LIVROS#3. EMPRESTIMOS#$");
		os_limparTela();

		switch (opcao)
		{
		case 0:
			break;
		case 1:
			menuAssociado();
			break;
		case 2:
			menuLivro();
			break;
		case 3:
			menuEmprestimo();
			break;
		}
	} while (opcao != 0);
	printf("Saindo...\n");
	os_sleep(1000);
}
