#include "types.h"

char *nomeDoArquivo = "booklending.db";

// DATABASE
void inicializar() {
  FILE *f;

  f = fopen(nomeDoArquivo, "rb");
  if (f == 0)
    f = fopen(nomeDoArquivo, "wb");

  if (f != 0)
    fclose(f);
}
void carregarMemoria() {
  short tipo;
  int fr = 0;
  struct s_noh *tempA, *tempL, *tempE, *temp;
  FILE *f;

  listaA = (struct s_noh *)calloc(sizeof(struct s_noh), 1);
  listaL = (struct s_noh *)calloc(sizeof(struct s_noh), 1);
  listaE = (struct s_noh *)calloc(sizeof(struct s_noh), 1);
  listaAOrd = (struct s_noh_ord *)calloc(sizeof(struct s_noh_ord), 1);

  listaA->tipo = 0;
  listaA->modificado = 0;
  listaA->proximo = 0;
  listaA->anterior = 0;
  listaA->dado = 0;

  listaL->tipo = 0;
  listaL->modificado = 0;
  listaL->proximo = 0;
  listaL->anterior = 0;
  listaL->dado = 0;

  listaE->tipo = 0;
  listaE->modificado = 0;
  listaE->proximo = 0;
  listaE->anterior = 0;
  listaE->dado = 0;

  listaAOrd->proximo = 0;
  listaAOrd->endereco = 0;
  listaAOrd->nome = 0;

  tempA = listaA;
  tempL = listaL;
  tempE = listaE;

  f = fopen(nomeDoArquivo, "rb");

  if (f != 0) {
    while (!feof(f)) {
      if ((fr = fread(&tipo, sizeof(short), 1, f)) != 0) {
        if (tipo == _ASSOCIADO) {
          fseek(f, (-sizeof(short)), SEEK_CUR);

          tempA->tipo = _ASSOCIADO;
          tempA->modificado = 0;
          tempA->offset = ftell(f);

          struct s_associado *associado =
              (struct s_associado *)calloc(sizeof(struct s_associado), 1);
          fread(associado, sizeof(struct s_associado), 1, f);
          offset = ftell(f);
          tempA->dado = (struct s_associado *)associado;

          temp = tempA;
          tempA->proximo = (struct s_noh *)calloc(sizeof(struct s_noh), 1);
          tempA = tempA->proximo;
          tempA->anterior = temp;
          tempA->tipo = 0;
          tempA->modificado = 0;
          tempA->proximo = 0;
          tempA->dado = 0;
          // tempA->anterior=0;
        }
        if (tipo == _LIVRO) {
          fseek(f, (-sizeof(short)), SEEK_CUR);
          tempL->tipo = _LIVRO;
          tempL->modificado = 0;
          tempL->offset = ftell(f);
          struct s_livro *livro =
              (struct s_livro *)calloc(sizeof(struct s_livro), 1);
          fread(livro, sizeof(struct s_livro), 1, f);
          offset = ftell(f);
          tempL->dado = (struct s_livro *)livro;
          temp = tempL;
          tempL->proximo = (struct s_noh *)calloc(sizeof(struct s_noh), 1);
          tempL = tempL->proximo;
          tempL->anterior = temp;
          tempL->tipo = 0;
          tempL->modificado = 0;
          tempL->proximo = 0;
          tempL->dado = 0;
          // tempL->anterior=0;
        }
        if (tipo == _EMPRESTIMO) {
          fseek(f, (-sizeof(short)), SEEK_CUR);
          tempE->tipo = _EMPRESTIMO;
          tempE->modificado = 0;
          tempE->offset = ftell(f);
          struct s_emprestimo *emprestimo =
              (struct s_emprestimo *)calloc(sizeof(struct s_emprestimo), 1);
          fread(emprestimo, sizeof(struct s_emprestimo), 1, f);
          offset = ftell(f);
          tempE->dado = (struct s_emprestimo *)emprestimo;
          temp = tempE;
          tempE->proximo = (struct s_noh *)calloc(sizeof(struct s_noh), 1);
          tempE = tempE->proximo;
          tempE->anterior = temp;
          tempE->tipo = 0;
          tempE->modificado = 0;
          tempE->proximo = 0;
          tempE->dado = 0;
          // tempE->anterior=0;
        }
      }
    }
  }
  if (f != 0)
    fclose(f);
}
void adicionarNoh(struct s_associado *a, struct s_livro *l,
                  struct s_emprestimo *e) {
  struct s_noh *temp, *temp2;

  if (a != 0) {
    for (temp = listaA; temp->proximo != 0; temp = temp->proximo)
      ;
    temp->dado = a;
    temp->tipo = _ASSOCIADO;
    temp->modificado = 1;
    temp->offset = offset;
    offset += sizeof(struct s_associado);
    temp->proximo = (struct s_noh *)calloc(sizeof(struct s_noh), 1);
    temp2 = temp;
    temp = temp->proximo;
    temp->anterior = temp2;
    temp->tipo = 0;
    temp->modificado = 0;
    temp->proximo = 0;
    temp->dado = 0;
    temp->offset = 0;
    // temp->anterior=0;
  }
  if (l != 0) {
    for (temp = listaL; temp->proximo != 0; temp = temp->proximo)
      ;
    temp->dado = l;
    temp->tipo = _LIVRO;
    temp->modificado = 1;
    temp->offset = offset;
    offset += sizeof(struct s_livro);
    temp->proximo = (struct s_noh *)calloc(sizeof(struct s_noh), 1);
    temp2 = temp;
    temp = temp->proximo;
    temp->anterior = temp2;
    temp->tipo = 0;
    temp->modificado = 0;
    temp->proximo = 0;
    temp->dado = 0;
    temp->offset = 0;
    // temp->anterior=0;
  }
  if (e != 0) {
    for (temp = listaE; temp->proximo != 0; temp = temp->proximo)
      ;
    temp->dado = e;
    temp->tipo = _EMPRESTIMO;
    temp->modificado = 1;
    temp->offset = offset;
    offset += sizeof(struct s_emprestimo);
    temp->proximo = (struct s_noh *)calloc(sizeof(struct s_noh), 1);
    temp2 = temp;
    temp = temp->proximo;
    temp->anterior = temp2;
    temp->tipo = 0;
    temp->modificado = 0;
    temp->proximo = 0;
    temp->dado = 0;
    temp->offset = 0;
    // temp->anterior=0;
  }
  gravarDisco();
}
// FILE
void gravarDisco() {
  struct s_noh *temp;
  FILE *f;

  for (temp = listaA; temp->proximo != 0; temp = temp->proximo) {
    if (temp->modificado == 1) {
      f = fopen(nomeDoArquivo, "r+b");
      if (f != 0) {
        temp->modificado = 0;
        fseek(f, temp->offset, SEEK_SET);
        fwrite(temp->dado, sizeof(struct s_associado), 1, f);
        fclose(f);
      }
    }
  }
  for (temp = listaL; temp->proximo != 0; temp = temp->proximo) {
    if (temp->modificado == 1) {
      f = fopen(nomeDoArquivo, "r+b");
      if (f != 0) {
        temp->modificado = 0;
        fseek(f, temp->offset, SEEK_SET);
        fwrite(temp->dado, sizeof(struct s_livro), 1, f);
        fclose(f);
      }
    }
  }
  for (temp = listaE; temp->proximo != 0; temp = temp->proximo) {
    if (temp->modificado == 1) {
      f = fopen(nomeDoArquivo, "r+b");
      if (f != 0) {
        temp->modificado = 0;
        fseek(f, temp->offset, SEEK_SET);
        fwrite(temp->dado, sizeof(struct s_emprestimo), 1, f);
        fclose(f);
      }
    }
  }
}
int getTamanhoArquivo() {
  int tam = 0;
  FILE *f;

  f = fopen(nomeDoArquivo, "rb");
  if (f != 0) {
    fseek(f, 0, SEEK_END);
    tam = ftell(f);
    fclose(f);
  }

  return tam;
}