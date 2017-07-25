void inicializaVetorHash(strHash **tableHash) {
  *tableHash = (strHash*)calloc(26, sizeof(strHash));
  for(int i = 0; i < 26; i++) {
    (*tableHash+i)->group = NULL;
    (*tableHash+i)->quantidade = 0;
    (*tableHash+i)->nomeGrupo = 97+i;
  }
}

int hash(char group) {
  if(group < 97) {
    group += 32;
  }
  return group - 97;
}

int altura(treeContact *root) {
  int height = 0, heightLeft = 0, heightRight = 0;

  if(root != NULL) {

    height = 1;

    if(root->dir != NULL || root->esq != NULL) {
      heightLeft = altura(root->esq);
      heightRight = altura(root->dir);

      if(heightRight > heightLeft) {
        height += heightRight;
      } else {
        height += heightLeft;
      }
    }
  }

  return height;
}

void rotacionaEsquerda(treeContact **root) {
  printf("Rotacionou a esquerda.\n");
  treeContact *aux;

  if (*root != NULL) {
    aux = (*root)->dir;

    (*root)->dir = aux->esq;

    aux->esq = *root;

    (*root) = aux;
  }
}

void rotacionaDireita(treeContact **root) {
  printf("Rotacionou a direita.\n");
  treeContact *aux;

  if (*root != NULL) {
    aux = (*root)->esq;

    (*root)->esq = aux->dir;

    aux->dir = *root;

    (*root) = aux;
  }
}

void fatorialBalanceamento(treeContact **root) {
  (*root)->fatorBalanceamento = altura((*root)->esq) - altura((*root)->dir);
}

int balancing(treeContact **root) {
  printf("Balanceamento.\n");
  int flag = 0;
  if(root != NULL){
    fatorialBalanceamento(root);

    if((*root)->fatorBalanceamento >= 2) {
      if((*root)->esq != NULL) {
        fatorialBalanceamento(&((*root)->esq));

        if(((*root)->esq)->fatorBalanceamento == -1) {
          rotacionaEsquerda(&((*root)->esq));
        }
        else if(((*root)->esq)->fatorBalanceamento > 1 || ((*root)->esq)->fatorBalanceamento < -1) {
          return balancing(&((*root)->esq));
        }
      }

      rotacionaDireita(root);
      flag = 1;
    }
    else if((*root)->fatorBalanceamento <= -2) {

      if((*root)->dir != NULL) {
        fatorialBalanceamento(&((*root)->dir));

        if(((*root)->dir)->fatorBalanceamento == 1) {
          rotacionaDireita(&((*root)->dir));
        }
        else if(((*root)->dir)->fatorBalanceamento > 1 || ((*root)->dir)->fatorBalanceamento < -1) {
          return balancing(&((*root)->dir));
        }
      }

      rotacionaEsquerda(root);
      flag = 1;
    }

    if(!flag && (*root)->esq != NULL) {
      flag = balancing(&((*root)->esq));
    }

    if(!flag && (*root)->dir != NULL) {
      flag = balancing(&((*root)->dir));
    }

  }
  return flag;
}

void insertContact(treeContact **tree, treeContact *newContact) {
  if(*tree == NULL) {
    *tree = newContact;
  }
  else if(strcmp((*tree)->nome, newContact->nome) < 0) {
    insertContact(&((*tree)->dir), newContact);
  }
  else if(strcmp((*tree)->nome, newContact->nome) > 0) {
    insertContact(&((*tree)->esq), newContact);
  }
}

void promoveMaiorValorEsquerda(treeContact **root, treeContact *right) {
  if(right->dir == NULL) {
    treeContact *auxNode = right;
    auxNode->dir = (*root)->dir;

    *root = auxNode;
  }
  else if((right->dir)->dir == NULL) {
    treeContact *auxNode = right->dir;
    right->dir = auxNode->esq;

    auxNode->esq = (*root)->esq;
    auxNode->dir = (*root)->dir;

    *root = auxNode;
  } else {
    promoveMaiorValorEsquerda(root, right->dir);
  }
}

void removeRoot(treeContact **root){
  treeContact *auxRoot = *root;
  if(*root != NULL) {
    if((*root)->esq == NULL){
      *root = (*root)->dir;
    }
    else if((*root)->dir == NULL) {
      *root = (*root)->esq;
    } else {
      promoveMaiorValorEsquerda(root, (*root)->esq);
    }
    free(auxRoot);
    auxRoot = NULL;
  }
}

void remover(treeContact **root, char contact[]) {

  if(strcmp((*root)->nome, contact) == 0){
    removeRoot(root);
  }
  else if(strcmp((*root)->nome, contact) > 0) {
    remover(&((*root)->esq), contact);
  }
  else if(strcmp((*root)->nome, contact) < 0) {
    remover(&((*root)->dir), contact);
  }
}

void removerTodos(treeContact **root) {
  if(*root != NULL) {
    removerTodos(&((*root)->esq));
    removerTodos(&((*root)->dir));
    removeRoot(root);
  }
}

void insereTelefone(treeContact *root, telefone *fone) {
  telefone *aux = root->fones;

  if(aux != NULL){
    while(aux->prox != NULL){
      aux = aux->prox;
    }
    aux->prox = fone;
  } else {
    root->fones = fone;
  }

}

int contains(treeContact *root, char nome[]) {

  if(root != NULL && strcmp(root->nome, nome) == 0) {
    return 1;
  }
  else if(root != NULL && strcmp(root->nome, nome) > 0) {
    return contains(root->esq, nome);
  }
  else if(root != NULL && strcmp(root->nome, nome) < 0) {
    return contains(root->dir, nome);
  } else {
    return 0;
  }
}

int containsTelefone(telefone *fones, char numero[]) {

  if(fones != NULL) {
    if(strcmp(fones->tel, numero) == 0) {
      return 1;
    } else {
      return containsTelefone(fones->prox, numero);
    }
  }

  return 0;
}

treeContact* getContact(treeContact *root, char nome[]) {

  if(root != NULL && strcmp(root->nome, nome) == 0) {
    return root;
  }
  else if(root != NULL && strcmp(root->nome, nome) > 0) {
    return getContact(root->esq, nome);
  }
  else if(root != NULL && strcmp(root->nome, nome) < 0) {
    return getContact(root->dir, nome);
  } else {
    return NULL;
  }
}

void removeFone(telefone **fones, char numero[]) {
  telefone *aux = *fones, *auxWhile = *fones;

  if(*fones != NULL) {
    if(strcmp((*fones)->tel, numero) == 0) {
      *fones = (*fones)->prox;
      free(aux);
      aux = NULL;

    } else {
      while(auxWhile != NULL && auxWhile->prox != NULL && strcmp((auxWhile->prox)->tel, numero) != 0) {
        auxWhile = auxWhile->prox;
      }

      if(auxWhile != NULL && auxWhile->prox != NULL) {
          aux = auxWhile->prox;
          auxWhile->prox = aux->prox;

          free(aux);
          aux = NULL;
      }
    }
  }
}
