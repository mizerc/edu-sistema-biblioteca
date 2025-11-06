#ifndef TYPES_H
#define TYPES_H

#define _MACOS true

#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <malloc.h>
#include <conio.h>
#include <Windows.h>
#endif

#ifdef _MACOS
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#endif

// GLOBALS
extern int offset;
extern struct s_noh *listaA;
extern struct s_noh *listaL;
extern struct s_noh *listaE;
extern struct s_noh_ord *listaAOrd;

#define _VALORDAMULTA 3

#define NAO 0
#define SIM 1

#define _STRNOME 100
#define _STRCPF 30
#define _STREMAIL 100
#define _STREND 200
#define _STRTEL 15

#define _STRTIT 100
#define _STRSUBTIT 100
#define _STRAUT 100
#define _STRISBN 50
#define _STREDITORA 50
#define _STREDICAO 50

#define _F_LETRAESPACO 0
#define _F_NUMERO 1
#define _F_EMAIL 2
#define _F_ENDERECO 3

#define _ASSOCIADO 0
#define _LIVRO 1
#define _EMPRESTIMO 2

struct s_associado
{
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
};

struct s_livro
{
	short tipo;
	short deletado;
	int id_livro;
	char titulo[_STRTIT];
	char subtitulo[_STRSUBTIT];
	char autor[_STRAUT];
	char isbn[_STRISBN];
	char editora[_STREDITORA];
	char edicao[_STREDICAO];
	int exemplar;
	int qnt_livro_emprestado;
	int reservadoParaIdAssociado;
};

struct s_emprestimo
{
	short tipo;
	short deletado;
	int id_emprestimo;
	int id_associado;
	int id_livro;
	int dataEmprestado[3];
	int dataDevolvido[3];
};

struct s_noh
{
	short tipo;
	short modificado;
	int offset;
	void *dado;
	struct s_noh *proximo;
	struct s_noh *anterior;
};

struct s_noh_ord
{
	char *nome;
	struct s_noh *endereco;

	struct s_noh_ord *proximo;
	struct s_noh_ord *anterior;
};

enum e_tamanhoJanela
{
	LINHAS_12,
	LINHAS_60
};
typedef enum e_tamanhoJanela E_tamanhoJanela;

enum e_corJanela
{
	DEFAULT,
	VERDE,
	VERMELHO
};
typedef enum e_corJanela E_corJanela;

// API MENU
int getOpcao(char *titulo, char *texto);
int getSimNao();
char *getString(int tamanho, int filtro);
void printBorder(int n);

// API EMPRESTIMO
void janelaEmprestarLivro();
void janelaDevolverLivro();
void janelaListarEmprestimo();
int getNovaIdEmprestimo();
struct s_noh *getNohEmprestimoByIdAssociado(int);
struct s_noh *getNohEmprestimoByIdLivro(int);

// API LIVRO
void janelaCadastrarLivro();
void janelaEditarLivro();
void janelaRemoverLivro();
void janelaListarLivro();
int getNovaIdLivro();
struct s_noh *getNohLivroByIdLivro(int);
void janelaListarLivroOrdenado();
void QuickSortLivro();
struct s_noh *getNohLivroByIdLivro(int);
void exibirDadoLivro(struct s_livro *temp);
struct s_noh *getNohLivro();

// API ASSOCIADO
void janelaCadastrarAssociado();
void janelaEditarAssociado();
void janelaRemoverAssociado();
void janelaBuscarAssociado();
void janelaMulta();
void janelaZerarMulta();
void janelaListarAssociado();
void janelaListarAssociadoOrdenado();
void QuickSortAssociado();
int getNovaIdAssociado();
struct s_noh *getNohAssociado();
int cmpStructNohOrd(const void *, const void *);
int tamString(char *);
void janelaInfoAssociado();
struct s_noh *getNohAssociadoByIdAssociado(int);
void exibirDadosAssociado(struct s_associado *temp);

// GUI
void mostrarTituloPequeno(char *titulo);
void mostrarTituloGrande(char *titulo);
int showTextField(const char *title, char *buffer, size_t size);
int showPositiveIntegerField(const char *title, int *out);

// DATABASe
void inicializar();
void carregarMemoria();
void adicionarNoh(struct s_associado *, struct s_livro *, struct s_emprestimo *);
void gravarDisco();
int getTamanhoArquivo();

// OS
void os_setarTamanhoCorJanela(E_tamanhoJanela tamanho, E_corJanela cor);
void os_sleep(int ms);
void os_limparTela(void);
void os_system(const char *command);

// API DO SISTEMA
void splashScreen();
void inicializar();
void carregarMemoria();
void adicionarNoh(struct s_associado *, struct s_livro *, struct s_emprestimo *);
void gravarDisco();
int getTamanhoArquivo();
void os_limparTela();
void congelarTela();
int isLetra(char);
int isNumero(char);
char tirarAcento(unsigned char);
int getDia();
int getMes();
int getAno();
int diasEntreDuasDatas(int, int, int, int, int, int);

// API DO MENU
int getOpcao(char *, char *);
int getSimNao();
char *getString(int, int);
int getNumero();
void mostrarTituloPequeno(char *);
void mostrarTituloGrande(char *);

// API ASSOCIADO
void janelaCadastrarAssociado();
void janelaEditarAssociado();
void janelaRemoverAssociado();
void janelaBuscarAssociado();
void janelaMulta();
void janelaZerarMulta();
void janelaListarAssociado();
void janelaListarAssociadoOrdenado();
void QuickSortAssociado();
int getNovaIdAssociado();
struct s_noh *getNohAssociado();
int cmpStructNohOrd(const void *, const void *);
int tamString(char *);
void janelaInfoAssociado();
struct s_noh *getNohAssociadoByIdAssociado(int);

// API LIVRO
void janelaCadastrarLivro();
void janelaEditarLivro();
void janelaRemoverLivro();
void janelaListarLivro();
int getNovaIdLivro();
struct s_noh *getNohLivroByIdLivro(int);
void janelaListarLivroOrdenado();
void QuickSortLivro();
struct s_noh *getNohLivroByIdLivro(int);

void reservarLivro();
void tirarReserva();

// API EMPRESTIMO
void janelaEmprestarLivro();
void janelaDevolverLivro();
void janelaListarEmprestimo();
int getNovaIdEmprestimo();
struct s_noh *getNohEmprestimoByIdAssociado(int);
struct s_noh *getNohEmprestimoByIdLivro(int);


#endif // TYPES_H



