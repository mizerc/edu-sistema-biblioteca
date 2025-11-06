#include "types.h"

// *************************************************************************************************************************************
// *
// * LIVRO
// *
// *************************************************************************************************************************************
void janelaCadastrarLivro() {
  /*
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
  reservadoParaIdAssociado;
  */

  struct s_noh *temp;
  struct s_livro *livro;
  livro = (struct s_livro *)calloc(sizeof(struct s_livro), 1);

  livro->tipo = _LIVRO;
  livro->deletado = 0;
  livro->id_livro = getNovaIdLivro();
  livro->qnt_livro_emprestado = 0;
  livro->reservadoParaIdAssociado = 0;

  // TOPO
  os_limparTela();
  printf("\n");
  mostrarTituloPequeno("Cadastro de livro");
  printf("\n");

  // PERGUNTAS

  // printf("  Digite o ISBN do livro:\n  > ");
  // strcpy(livro->isbn, getString(_STRISBN, _F_NUMERO));
  // printf("\n");

  showPositiveIntegerField("ID", &livro->id_livro);
  showTextField("ISBN", livro->isbn, sizeof(livro->isbn));

  // REGRA DE NEGÓCIO: VERIFICA SE O ISBN JÁ ESTÁ CADASTRADO
  for (temp = listaL; temp->proximo != 0; temp = temp->proximo) {
    if ((strcmp(livro->isbn, ((struct s_livro *)temp->dado)->isbn)) == 0) {
      printf("LIVRO JA CADASTRADO\n\n");
      congelarTela();
      return;
    }
  }

 showTextField("Título", livro->titulo, sizeof(livro->titulo));
 showTextField("Subtítulo", livro->subtitulo, sizeof(livro->subtitulo));
 showTextField("Autor", livro->autor, sizeof(livro->autor));
 showTextField("Editora", livro->editora, sizeof(livro->editora));
 showTextField("Edição", livro->edicao, sizeof(livro->edicao));
showPositiveIntegerField("Quantidade de exemplares", &livro->exemplar);

  // CONFIRMACAO DE CADASTRO
  while (1) {
    os_limparTela();

    printf("\n");
    mostrarTituloPequeno("Cadastro de livro");
    printf("\n");
    printf("   Titulo......: %s\n", livro->titulo);
    printf("   Subt�tulo.......: %s\n", livro->subtitulo);
    printf("   Autor....: %s\n", livro->autor);
    printf("   ISBN..: %s\n", livro->isbn);
    printf("   Editora..: %s\n", livro->editora);
    printf("   Edi��o..: %s\n", livro->edicao);
    printf("   Exemplar(es)..: %d\n", livro->exemplar);
    printf("\n");

    printf(" [0=Cancelar] [1=Cadastrar]\n");
    switch (getNumero()) {
    case 0:
      os_limparTela();
      printf("\n  Cancelado\n");
      congelarTela();
      return;
    case 1:
      adicionarNoh(0, livro, 0);
      return;
    }
  }
}
void janelaEditarLivro() {
  struct s_noh *temp;

  int id_livro;

  struct s_livro *livro;
  livro = (struct s_livro *)calloc(sizeof(struct s_livro), 1);

  os_limparTela();
  printf("\n");
  mostrarTituloPequeno("Editar livro");
  printf("\n");

  printf("  Informe a identifica��o do livro:\n  > ");
  scanf("%d", &id_livro);
  printf("\n");

  temp = getNohLivroByIdLivro(id_livro);

  if (temp == 0 || (((struct s_livro *)temp->dado)->deletado == 1)) {
    os_limparTela();
    printf("\n  Livro n�o encontrado\n");
    congelarTela();
    return;
  }

  os_limparTela();
  printf("\n");
  mostrarTituloPequeno("Editar livro");
  printf("\n");

  printf("   Titulo......: %s\n", ((struct s_livro *)temp->dado)->titulo);
  printf("   Subt�tulo.......: %s\n",
         ((struct s_livro *)temp->dado)->subtitulo);
  printf("   Autor....: %s\n", ((struct s_livro *)temp->dado)->autor);
  printf("   ISBN..: %s\n", ((struct s_livro *)temp->dado)->isbn);
  printf("   Editora..: %s\n", ((struct s_livro *)temp->dado)->editora);
  printf("   Edi��o..: %s\n", ((struct s_livro *)temp->dado)->edicao);
  printf("   Exemplar(es)..: %d\n", ((struct s_livro *)temp->dado)->exemplar);
  printf("\n");
  printf(" [0=Cancelar] [1=Continuar]\n");

  if (getNumero() == 0) {
    os_limparTela();
    printf("\n  Cancelado\n");
    congelarTela();
    return;
  }

  os_limparTela();
  printf("\n");
  mostrarTituloPequeno("Editar livro");
  printf("\n");

  printf("   Titulo......: %s\n", ((struct s_livro *)temp->dado)->titulo);
  printf("   Subt�tulo.......: %s\n",
         ((struct s_livro *)temp->dado)->subtitulo);
  printf("   Autor....: %s\n", ((struct s_livro *)temp->dado)->autor);
  printf("   ISBN..: %s\n", ((struct s_livro *)temp->dado)->isbn);
  printf("   Editora..: %s\n", ((struct s_livro *)temp->dado)->editora);
  printf("   Edi��o..: %s\n", ((struct s_livro *)temp->dado)->edicao);
  printf("   Exemplar(es)..: %d\n", ((struct s_livro *)temp->dado)->exemplar);
  printf("\n");

  printf("  ID: %d", livro->id_livro);
  printf("\n");

  printf("  Digite o titulo do livro:\n  > ");
  strcpy(livro->titulo, getString(_STRTIT, _F_LETRAESPACO));
  if (strcmp(livro->titulo, "") == 0) {
    strcpy(livro->titulo, ((struct s_livro *)temp->dado)->titulo);
    printf("  > %s\n", livro->titulo);
  }
  printf("\n");

  printf("  Digite o subt�tulo do livro:\n  > ");
  strcpy(livro->subtitulo, getString(_STRSUBTIT, _F_LETRAESPACO));
  if (strcmp(livro->subtitulo, "") == 0) {
    strcpy(livro->subtitulo, ((struct s_livro *)temp->dado)->subtitulo);
    printf("  > %s\n", livro->subtitulo);
  }
  printf("\n");

  printf("  Digite o autor do livro:\n  > ");
  strcpy(livro->autor, getString(_STRAUT, _F_LETRAESPACO));
  if (strcmp(livro->autor, "") == 0) {
    strcpy(livro->autor, ((struct s_livro *)temp->dado)->autor);
    printf("  > %s\n", livro->autor);
  }
  printf("\n");

  printf("  Digite o ISBN do livro:\n  > ");
  strcpy(livro->isbn, getString(_STRISBN, _F_LETRAESPACO));
  if (strcmp(livro->isbn, "") == 0) {
    strcpy(livro->isbn, ((struct s_livro *)temp->dado)->isbn);
    printf("  > %s\n", livro->isbn);
  }
  printf("\n");

  printf("  Digite a editora do livro:\n  > ");
  strcpy(livro->editora, getString(_STREDITORA, _F_LETRAESPACO));
  if (strcmp(livro->editora, "") == 0) {
    strcpy(livro->editora, ((struct s_livro *)temp->dado)->editora);
    printf("  > %s\n", livro->editora);
  }
  printf("\n");

  printf("  Digite a edi��o do livro:\n  > ");
  strcpy(livro->edicao, getString(_STREDICAO, _F_LETRAESPACO));
  if (strcmp(livro->edicao, "") == 0) {
    strcpy(livro->edicao, ((struct s_livro *)temp->dado)->edicao);
    printf("  > %s\n", livro->edicao);
  }
  printf("\n");

  printf("  Digite a quantidade de exemplares do livro:\n  > ");
  scanf("%d", &livro->exemplar);
  printf("\n");

  while (1) {
    os_limparTela();
    printf("\n");
    mostrarTituloPequeno("Editar livro");
    printf("\n");

    printf("   Dados antigos:\n");
    printf("   Titulo......: %s\n", ((struct s_livro *)temp->dado)->titulo);
    printf("   Subt�tulo.......: %s\n",
           ((struct s_livro *)temp->dado)->subtitulo);
    printf("   Autor....: %s\n", ((struct s_livro *)temp->dado)->autor);
    printf("   ISBN..: %s\n", ((struct s_livro *)temp->dado)->isbn);
    printf("   Editora..: %s\n", ((struct s_livro *)temp->dado)->editora);
    printf("   Edi��o..: %s\n", ((struct s_livro *)temp->dado)->edicao);
    printf("   Exemplar(es)..: %d\n", ((struct s_livro *)temp->dado)->exemplar);
    printf("\n");

    printf("   Dados modificados:\n");
    printf("   Titulo......: %s\n", livro->titulo);
    printf("   Subt�tulo.......: %s\n", livro->subtitulo);
    printf("   Autor....: %s\n", livro->autor);
    printf("   ISBN..: %s\n", livro->isbn);
    printf("   Editora..: %s\n", livro->editora);
    printf("   Edi��o..: %s\n", livro->edicao);
    printf("   Exemplar(es)..: %d\n", livro->exemplar);
    printf("\n");
    printf(" [0=Cancelar] [1=Editar]\n");

    switch (getNumero()) {
    case 0:
      os_limparTela();
      printf("\n  Cancelado\n");
      congelarTela();
      return;
    case 1:
      strcpy(((struct s_livro *)temp->dado)->titulo, livro->titulo);
      strcpy(((struct s_livro *)temp->dado)->subtitulo, livro->subtitulo);
      strcpy(((struct s_livro *)temp->dado)->autor, livro->autor);
      strcpy(((struct s_livro *)temp->dado)->isbn, livro->isbn);
      strcpy(((struct s_livro *)temp->dado)->editora, livro->editora);
      strcpy(((struct s_livro *)temp->dado)->edicao, livro->edicao);
      ((struct s_livro *)temp->dado)->exemplar = livro->exemplar;
      temp->modificado = 1;
      gravarDisco();
      return;
    }
  }
}
void janelaRemoverLivro() {
  struct s_noh *temp;

  int id_livro;

  struct s_livro *livro;
  livro = (struct s_livro *)calloc(sizeof(struct s_livro), 1);

  os_limparTela();
  printf("\n");
  mostrarTituloPequeno("Remover livro");
  printf("\n");

  printf("  Informe a identifica��o do livro:\n  > ");
  scanf("%d", &id_livro);
  printf("\n");

  temp = getNohLivroByIdLivro(id_livro);

  if (temp == 0 || (((struct s_livro *)temp->dado)->deletado == 1)) {
    os_limparTela();
    printf("\n  Livro n�o encontrado\n");
    congelarTela();
    return;
  }

  while (1) {
    os_limparTela();
    printf("\n");
    mostrarTituloPequeno("Remover livro");
    printf("\n");

    printf("   Titulo......: %s\n", ((struct s_livro *)temp->dado)->titulo);
    printf("   Subt�tulo.......: %s\n",
           ((struct s_livro *)temp->dado)->subtitulo);
    printf("   Autor....: %s\n", ((struct s_livro *)temp->dado)->autor);
    printf("   ISBN..: %s\n", ((struct s_livro *)temp->dado)->isbn);
    printf("   Editora..: %s\n", ((struct s_livro *)temp->dado)->editora);
    printf("   Edi��o..: %s\n", ((struct s_livro *)temp->dado)->edicao);
    printf("   Exemplar(es)..: %d\n", ((struct s_livro *)temp->dado)->exemplar);
    printf("\n");
    printf(" [0=Cancelar] [1=Remover]\n");

    if (getNumero() == 0) {
      os_limparTela();
      printf("\n  Cancelado\n");
      congelarTela();
      return;
    }
    if (getNumero() == 1) {
      ((struct s_livro *)temp->dado)->deletado = 1;
      temp->modificado = 1;
      gravarDisco();
      return;
    }
  }
}
void janelaListarLivro() {
  struct s_noh *temp;

  int itemTotal = 0, pagTotal = 0, pagAtual = 1, op = (-1), count,
      itemPorPagina = 40;

  // Verifica se existe registros para mostrar
  temp = listaL;
  if (temp->proximo == 0) {
    os_limparTela();
    printf("N�o foram encontrados registros\n");
    congelarTela();
    return;
  }

  // Descobre quantos itens existem na lista encadeada (1 item = 1)
  for (temp = listaL, itemTotal = 0; temp->proximo != 0;
       temp = temp->proximo, itemTotal++)
    if (((struct s_livro *)temp->dado)->deletado == 1)
      itemTotal--;

  // Calcula o n�mero de p�ginas necess�rias
  pagTotal = itemTotal / itemPorPagina;
  if ((itemTotal % itemPorPagina) != 0)
    pagTotal++;

  // Ajusta a tela
#ifdef _WIN32
  os_system("mode con lines=54");
  os_system("mode con cols=160");
#endif

  temp = listaL;

  while (op != 0) {

    printf("\n");
    mostrarTituloGrande("Lista de livros");
    printf("\n");
    printf("  "
           "+------+-----------------------------------------------------------"
           "-------------------------------------------------------------------"
           "---------------------+\n");
    printf("  | ID   | TITULO                                | SUBTITULO       "
           "          | AUTOR                         | EDITORA             | "
           "EXP  | ISBN             |\n");
    printf("  "
           "+------+-----------------------------------------------------------"
           "-------------------------------------------------------------------"
           "---------------------+\n");
    for (count = 1; count <= itemPorPagina; count++) {
      if (temp->proximo != 0) {

        if (((struct s_livro *)temp->dado)->deletado != 1) {
          printf("  | %-04d |", ((struct s_livro *)temp->dado)->id_livro);
          printf(" %-37s |", ((struct s_livro *)temp->dado)->titulo);
          printf(" %-25s |", ((struct s_livro *)temp->dado)->subtitulo);
          printf(" %-29s |", ((struct s_livro *)temp->dado)->autor);
          printf(" %-19s |", ((struct s_livro *)temp->dado)->editora);
          printf(" %-4d |", ((struct s_livro *)temp->dado)->exemplar);
          printf(" %-16s |", ((struct s_livro *)temp->dado)->isbn);
          printf(" \n");
        } else
          count--;

        temp = temp->proximo;
      } else
        printf("  |      |                                       |             "
               "              |                               |                "
               "     |      |                  |\n");
    }
    printf("  "
           "+------------------------------------------------------------------"
           "-------------------------------------------------------------------"
           "---------------------+\n");
    printf("\n");
    printf(" [0=Sair][1=P�gina anterior][2=Pr�xima p�gina]    [p�gina %d de "
           "%d]    [%d livro(s)]\n",
           pagAtual, pagTotal, itemTotal);

    while (op != 0) {
      op = getNumero();
      if (op == 0)
        break;

      if (op == 1) {
        if (pagAtual > 1) {
          int aux, v;

          if ((pagAtual == pagTotal) &&
              ((itemTotal % ((pagTotal - 1) * itemPorPagina)) != 0)) {
            // printf("1");
            v = itemPorPagina + (itemTotal - ((pagAtual - 1) * itemPorPagina));
          }

          if ((pagAtual == pagTotal) &&
              ((itemTotal % ((pagTotal - 1) * itemPorPagina)) == 0)) {
            // printf("2");
            v = (2 * itemPorPagina);
          }

          if ((pagAtual < pagTotal)) {
            // printf("3");
            v = (2 * itemPorPagina);
          }

          /// printf(" [%d]\n",v);
          // congelarTela();

          for (aux = 1; aux <= v; aux++) {
            temp = temp->anterior;
          }
          pagAtual--;
          os_limparTela();
          break;
        }
      }

      if (op == 2) {
        if (pagAtual < pagTotal) {
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
void janelaBuscarLivro() {}
int getNovaIdLivro() {
  int id = 1;
  struct s_noh *temp;

  for (temp = listaL; temp->proximo != 0; temp = temp->proximo, id++)
    ;

  for (temp = listaL; temp->proximo != 0; temp = temp->proximo)
    if (id == ((struct s_livro *)temp->dado)->id_livro) {
      id++;
      temp = listaL;
    }

  return id;
}
struct s_noh *getNohLivro() {
  struct s_noh *temp;
  int id_livro;

  printf("  Informe a identifica��o do livro:\n  > ");
  scanf("%d", &id_livro);
  printf("\n");

  for (temp = listaL; temp->proximo != 0; temp = temp->proximo)
    if (id_livro == ((struct s_livro *)temp->dado)->id_livro)
      return temp;

  if (temp == 0 || (((struct s_associado *)temp->dado)->deletado == 1)) {
    os_limparTela();
    printf("\n  Livro n�o encontrado\n");
    congelarTela();
    return 0;
  }

  return 0;
}
void reservarLivro() {
  int id_associado, id_livro;
  struct s_noh *nohAssociado, *nohLivro;

  // TOPO
  os_limparTela();
  printf("\n");
  mostrarTituloPequeno("Reservar de livro");
  printf("\n");

  printf("  Informe a identifica��o do associado:\n  > ");
  scanf("%d", &id_associado);
  printf("\n");
  nohAssociado = getNohAssociadoByIdAssociado(id_associado);
  if (nohAssociado == 0 ||
      (((struct s_associado *)nohAssociado->dado)->deletado == 1)) {
    os_limparTela();
    printf("\n  Associado n�o encontrado\n");
    congelarTela();
    return;
  }

  printf("   Nome......: %s\n",
         ((struct s_associado *)nohAssociado->dado)->nome);
  printf("   CPF.......: %s\n",
         ((struct s_associado *)nohAssociado->dado)->cpf);
  printf("   E-mail....: %s\n",
         ((struct s_associado *)nohAssociado->dado)->email);
  printf("   Endere�o..: %s\n",
         ((struct s_associado *)nohAssociado->dado)->endereco);
  printf("   Telefone..: %s\n",
         ((struct s_associado *)nohAssociado->dado)->telefone);
  printf("\n");

  printf("  Informe a identifica��o do livro:\n  > ");
  scanf("%d", &id_livro);
  printf("\n");
  nohLivro = getNohLivroByIdLivro(id_livro);
  if (nohLivro == 0 ||
      (((struct s_associado *)nohLivro->dado)->deletado == 1)) {
    os_limparTela();
    printf("\n  Livro n�o encontrado\n");
    congelarTela();
    return;
  }

  if (((struct s_livro *)nohLivro->dado)->qnt_livro_emprestado >=
      ((struct s_livro *)nohLivro->dado)->exemplar) {
    os_limparTela();
    printf("\n  N�o h� exemplares dispon�veis.\nCancelado.\n");
    congelarTela();
    return;
  }

  if (((struct s_livro *)nohLivro->dado)->reservadoParaIdAssociado != 0 &&
      (((struct s_livro *)nohLivro->dado)->exemplar -
       ((struct s_livro *)nohLivro->dado)->qnt_livro_emprestado) < 2) {
    if (((struct s_livro *)nohLivro->dado)->reservadoParaIdAssociado !=
        ((struct s_associado *)nohAssociado)->id_associado) {
      os_limparTela();
      printf("\n  O livro est� reservado.\n");
      congelarTela();
      return;
    }
  }

  os_limparTela();
  printf("\n");
  mostrarTituloPequeno("Reserva de livro");
  printf("\n");

  while (1) {
    os_limparTela();
    printf("\n");
    mostrarTituloPequeno("Empr�stimo de livro");
    printf("\n");
    printf("   Nome......: %s\n",
           ((struct s_associado *)nohAssociado->dado)->nome);
    printf("   CPF.......: %s\n",
           ((struct s_associado *)nohAssociado->dado)->cpf);
    printf("   E-mail....: %s\n",
           ((struct s_associado *)nohAssociado->dado)->email);
    printf("   Endere�o..: %s\n",
           ((struct s_associado *)nohAssociado->dado)->endereco);
    printf("   Telefone..: %s\n",
           ((struct s_associado *)nohAssociado->dado)->telefone);
    printf("\n");

    printf("   Titulo..........: %s\n",
           ((struct s_livro *)nohLivro->dado)->titulo);
    printf("   Subt�tulo.......: %s\n",
           ((struct s_livro *)nohLivro->dado)->subtitulo);
    printf("   Autor...........: %s\n",
           ((struct s_livro *)nohLivro->dado)->autor);
    printf("   ISBN............: %s\n",
           ((struct s_livro *)nohLivro->dado)->isbn);
    printf("   Editora.........: %s\n",
           ((struct s_livro *)nohLivro->dado)->editora);
    printf("   Edi��o..........: %s\n",
           ((struct s_livro *)nohLivro->dado)->edicao);
    printf("   Exemplar(es)....: %d\n",
           ((struct s_livro *)nohLivro->dado)->exemplar);
    printf("\n");
    printf("   Data de empr�stimo: %d/%d/%d\n", getDia(), getMes(), getAno());
    printf("\n");
    printf(" [0=Cancelar] [1=Reservar]\n");

    switch (getNumero()) {
    case 0:
      os_limparTela();
      printf("\n  Cancelado\n");
      congelarTela();
      return;
    case 1:
      ((struct s_livro *)nohLivro->dado)->reservadoParaIdAssociado =
          ((struct s_associado *)nohAssociado->dado)->id_associado;

      nohLivro->modificado = 1;
      gravarDisco();
      return;
    }
  }
}
void tirarReserva() {

  int id_associado, id_livro;
  struct s_noh *nohAssociado, *nohLivro;

  // TOPO
  os_limparTela();
  printf("\n");
  mostrarTituloPequeno("Tirar reserva de livro");
  printf("\n");

  printf("  Informe a identifica��o do livro:\n  > ");
  scanf("%d", &id_livro);
  printf("\n");
  nohLivro = getNohLivroByIdLivro(id_livro);
  if (nohLivro == 0 ||
      (((struct s_associado *)nohLivro->dado)->deletado == 1)) {
    os_limparTela();
    printf("\n  Livro n�o encontrado\n");
    congelarTela();
    return;
  }

  if (((struct s_livro *)nohLivro->dado)->reservadoParaIdAssociado != 0) {
    ((struct s_livro *)nohLivro->dado)->reservadoParaIdAssociado = 0;
  } else {
    os_limparTela();
    printf("\n  Livro nao tem reserva\n");
    congelarTela();
    return;
  }

  os_limparTela();
  printf("\n");
  mostrarTituloPequeno("Tirar Reserva de livro");
  printf("\n");

  while (1) {
    os_limparTela();
    printf("\n");
    mostrarTituloPequeno("Tirar reserva de livro");
    printf("\n");

    printf("   Titulo..........: %s\n",
           ((struct s_livro *)nohLivro->dado)->titulo);
    printf("   Subt�tulo.......: %s\n",
           ((struct s_livro *)nohLivro->dado)->subtitulo);
    printf("   Autor...........: %s\n",
           ((struct s_livro *)nohLivro->dado)->autor);
    printf("   ISBN............: %s\n",
           ((struct s_livro *)nohLivro->dado)->isbn);
    printf("   Editora.........: %s\n",
           ((struct s_livro *)nohLivro->dado)->editora);
    printf("   Edi��o..........: %s\n",
           ((struct s_livro *)nohLivro->dado)->edicao);
    printf("   Exemplar(es)....: %d\n",
           ((struct s_livro *)nohLivro->dado)->exemplar);
    printf("\n");
    printf(" [0=Cancelar] [1=Tirar reserva]\n");

    switch (getNumero()) {
    case 0:
      os_limparTela();
      printf("\n  Cancelado\n");
      congelarTela();
      return;
    case 1:
      nohLivro->modificado = 1;
      gravarDisco();
      return;
    }
  }
}
void exibirDadoLivro(struct s_livro *temp) {
  printf("   Titulo..........: %s\n", ((struct s_livro *)temp)->titulo);
  printf("   Subt�tulo.......: %s\n", ((struct s_livro *)temp)->subtitulo);
  printf("   Autor...........: %s\n", ((struct s_livro *)temp)->autor);
  printf("   ISBN............: %s\n", ((struct s_livro *)temp)->isbn);
  printf("   Editora.........: %s\n", ((struct s_livro *)temp)->editora);
  printf("   Edi��o..........: %s\n", ((struct s_livro *)temp)->edicao);
  printf("   Exemplar(es)....: %d\n", ((struct s_livro *)temp)->exemplar);
}
