typedef struct TELEFONE telefone;
struct TELEFONE{
  char tel[16];
  telefone *prox;
};

typedef struct TREE_CONTACT treeContact;
struct TREE_CONTACT{
  char nome[70];
  telefone *fones;
  int fatorBalanceamento;
  treeContact *dir;
  treeContact *esq;
};

typedef struct STR_HASH strHash;
struct STR_HASH{
  treeContact *group;
  char nomeGrupo;
  int quantidade;
};
