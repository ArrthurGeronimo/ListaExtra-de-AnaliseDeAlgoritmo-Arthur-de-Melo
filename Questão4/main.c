/* Exemplo Utilizando uma Lista de Contatos */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "estrutura.h"
#include "operacoes.h"

#ifdef LINUX
void systemClean(){
  system("clear");
}
#else
void systemClean(){
  system("cls");
}
#endif

int leInt() {
  int in = 0;
  fflush(stdin);
  scanf("%d", &in);

  return in;
}

void leString(char string[]) {
  fflush(stdin);
  scanf(" %69[^\n]", string);
}

char leChar() {
  char caracter = ' ';
  fflush(stdin);
  scanf(" %c", &caracter);

  return caracter;
}

void inserirTelefones(treeContact *contact) {
  char numero[16];
  telefone *fone = NULL, *aux = NULL;
  do{
    systemClean();

    printf("Digite um telefone ou 'end' para parar de adicionar.\n");

    fflush(stdin);
    leString(numero);

    if(strcmp(numero, "end") != 0) {
      aux = (telefone*)malloc(sizeof(telefone));
      strcpy(aux->tel, numero);
      aux->prox = fone;
      fone = aux;
      aux = NULL;
    }

  }while(strcmp(numero, "end") != 0);

  insereTelefone(contact, fone);
}

void inserirContato(strHash **tableHash) {
  treeContact *newContact;
  char nome[70];

  systemClean();
  printf("Digite o nome do contato.\n");
  leString(nome);

  if (!contains((*tableHash + hash(nome[0]))->group, nome)) {
    newContact = (treeContact*)malloc(sizeof(treeContact));

    strcpy(newContact->nome, nome);
    newContact->dir = NULL;
    newContact->esq = NULL;
    newContact->fones = NULL;
    newContact->fatorBalanceamento = 0;

    inserirTelefones(newContact);

    insertContact(&((*tableHash + hash(newContact->nome[0]))->group), newContact);
    balancing(&((*tableHash + hash(newContact->nome[0]))->group));

    (*tableHash + hash(newContact->nome[0]))->quantidade++;
  } else {
    printf("Contato já cadastrado\n");
  }
}

void inserirTelefonesEmContato(strHash **tableHash) {
  treeContact *contact = NULL;
  char nome[70];

  systemClean();
  printf("Digite o nome do contato.\n");
  leString(nome);

  contact = getContact((*tableHash + hash(nome[0]))->group, nome);

  if(contact != NULL) {
    inserirTelefones(contact);
  } else {
    printf("Contato não cadastrado\n");
  }
}

void removerTelefoneDeContato(strHash **tableHash) {
  treeContact *contact = NULL;
  char nome[70], fone[16];

  systemClean();
  printf("Digite o nome do contato.\n");
  leString(nome);

  contact = getContact((*tableHash + hash(nome[0]))->group, nome);

  if(contact != NULL) {
    printf("Digite o telefone.\n");
    leString(fone);

    if(containsTelefone(contact->fones, fone)) {

      removeFone(&(contact->fones), fone);

    } else {
      printf("Telefone inexistente!\n");
    }

  } else {
    printf("Contato não cadastrado\n");
  }
}

void removeTodosTelefones(treeContact *contact, telefone *fone) {
  if(fone != NULL) {
    removeTodosTelefones(contact, fone->prox);
    removeFone(&(contact->fones), fone->tel);
  }
}

void removeContato(strHash **tableHash) {
  treeContact *contact = NULL;
  char nome[70];

  systemClean();
  printf("Digite o nome do contato.\n");
  leString(nome);

  contact = getContact((*tableHash + hash(nome[0]))->group, nome);

  if(contact != NULL) {

    removeTodosTelefones(contact, contact->fones);
    remover(&((*tableHash + hash(contact->nome[0]))->group), contact->nome);

  } else {
    printf("Contato não cadastrado\n");
  }
}

void buscaContato(strHash **tableHash) {
  treeContact *contact = NULL;
  telefone *aux = NULL;
  char nome[70];

  systemClean();

  printf("Digite o nome do contato.\n");
  leString(nome);

  contact = getContact((*tableHash + hash(nome[0]))->group, nome);

  if(contact != NULL) {
    systemClean();
    printf("Nome: %s\n", contact->nome);
    if(contact->fones != NULL){
      printf("  Telefone(s):\n");
      aux = contact->fones;

      while(aux != NULL){
        printf("    %s\n", aux->tel);
        aux = aux->prox;
      }

    }
  } else {
    printf("Contato não cadastrado\n");
  }
}

void exibeContatosGrupo(treeContact *root, int *count) {

  if(root != NULL) {

    exibeContatosGrupo(root->esq, count);
    printf("Nome: %s\n", root->nome);
    exibeContatosGrupo(root->dir, count);

    *count = (*count) + 1;
  }
}

void exibeTodosContatos(strHash **tableHash) {
  int count = 0;

  systemClean();

  for(int i = 0; i < 26; i++) {

    if((*tableHash+i)->group != NULL) {

      printf("Grupo: %c\n", (*tableHash+i)->nomeGrupo);

      exibeContatosGrupo((*tableHash+i)->group, &count);
    }
  }
  printf("O número total de contatos é: %d\n", count);
}

void exibeTodosContatosPorGrupo(strHash **tableHash) {
  char grupo = ' ';
  int count = 0;

  systemClean();

  printf("Informe o grupo desejado\n");
  grupo = leChar();

  exibeContatosGrupo((*tableHash + hash(grupo))->group, &count);

  printf("O número total de contatos é: %d\n", count);
}

void exibeContatosSemTelefoneGrupo(treeContact *root, int *count) {

  if(root != NULL) {

    exibeContatosSemTelefoneGrupo(root->esq, count);

    if(root->fones == NULL) {
      printf("Nome: %s\n", root->nome);
      *count = (*count) + 1;
    }

    exibeContatosSemTelefoneGrupo(root->dir, count);

  }
}

void exibeTodosContatosSemTelefone(strHash **tableHash) {
  int count = 0, auxCont = 0;

  systemClean();

  for(int i = 0; i < 26; i++) {

    if((*tableHash+i)->group != NULL) {

      printf("Grupo: %c\n", (*tableHash+i)->nomeGrupo);

      auxCont = count;

      exibeContatosSemTelefoneGrupo((*tableHash+i)->group, &count);

      if(count == auxCont) {
        printf("Nenhum contato neste grupo\n");
      }
    }
  }
  printf("O número total de contatos sem telefone é: %d\n", count);
}

void exibeTodosContatosSemTelefonePorGrupo(strHash **tableHash) {
  char grupo = ' ';
  int count = 0;

  systemClean();

  printf("Informe o grupo desejado\n");
  grupo = leChar();

  exibeContatosSemTelefoneGrupo((*tableHash + hash(grupo))->group, &count);

  printf("O número total de contatos é: %d", count);
}

void removeTodosContatosPorGrupo(strHash **tableHash) {
  char grupo = ' ';

  systemClean();

  printf("Informe o grupo desejado\n");
  grupo = leChar();

  removerTodos(&((*tableHash + hash(grupo))->group));

  (*tableHash + hash(grupo))->quantidade = 0;

  printf("Os contatos foram removidos com sucesso!\n");

}

void exibeGrupos(strHash **tableHash) {

  systemClean();

  for(int i = 0; i < 26; i++) {
    printf("Grupo %c\nQuantidade %d\n\n", (*tableHash + i)->nomeGrupo, (*tableHash + i)->quantidade);
  }

}

void chamaFuncao(int opc, strHash **tableHash) {
  switch (opc) {
    case 1:
      inserirContato(tableHash);
      break;

    case 2:
      inserirTelefonesEmContato(tableHash);
      break;

    case 3:
      removerTelefoneDeContato(tableHash);
      break;

    case 4:
      removeContato(tableHash);
      break;

    case 5:
      buscaContato(tableHash);
      break;

    case 6:
      exibeTodosContatos(tableHash);
      break;

    case 7:
      exibeTodosContatosPorGrupo(tableHash);
      break;

    case 8:
      exibeTodosContatosSemTelefone(tableHash);
      break;

    case 9:
      exibeTodosContatosSemTelefonePorGrupo(tableHash);
      break;

    case 10:
      removeTodosContatosPorGrupo(tableHash);
      break;

    case 11:
      exibeGrupos(tableHash);
      break;

  }
}

void menu(strHash **tableHash) {
  int opc = 0;

  do {
    printf("Digite:\n \
    1 - Para inserir um contato.\n \
    2 - Para inserir telefones a um contato.\n \
    3 - Para remover telefone de um contato\n \
    4 - Para remover um contato.\n \
    5 - Para pesquisar por um contato.\n \
    6 - Para exibir todos os contatos.\n \
    7 - Para exibir os contatos de determinado grupo.\n \
    8 - Para exibir contatos sem telefone.\n \
    9 - Para exibir contatos sem telefone de determinado grupo.\n \
    10 - Para remover todos contatos de determinado grupo.\n \
    11 - Para exibir os grupos existentes.\n \
    ou qualquer outra tecla para sair\n");

    opc = leInt();

    if(opc >= 1 && opc <= 11) {
      chamaFuncao(opc, tableHash);
    }
  }while(opc >= 1 && opc <= 11);
}

int main(){
  strHash *tableHash;
  inicializaVetorHash(&tableHash);

  printf("Seja bem vindo!\n");

  menu(&tableHash);
}
