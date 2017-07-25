#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <locale.h>

typedef struct{
  unsigned char c :8;
}code_gen;

struct no1{
  char data;
  int f;
  struct no1 *esq;
  struct no1 *dir;
  struct no1 *p;
};

int len;
typedef struct no1 no;
char e[50][10];
void decode(char en[50], no * raiz,int u);
char conta_letra(char code[], no *raiz);
void encode(char data[], char en[],char codes[128][10]);
char convert_string_char(char code[]);
void emordem(no *);
no * extract_min( no **);
void lista_ordenada(no **);
no  * cria_no(char , int);
void sort(char *, int *, int );
void encontra(no *, char *, char[128][10]);


main()
{
setlocale(LC_ALL,"portuguese");
system ("color F3");

 printf("_______________________________________________________________________________\n");
       printf("\t|\tDesenvolvedores: Arthur de Melo e Cayo Cavalcante\t|\n");
       printf("\t|\tGraduandos do curso de Ciência da Computação - UFRR\t|\n");
       printf("\t|\tDisciplina: Estrutura de Dados II (2016.1)\t\t|\n");
       printf("\t|\tFerramenta Utilizada: Code::Blocks 16.01\t\t|\n");
       printf("\t|\tBoa Vista, RR - Julho/2016\t\t\t\t|\n");
       printf("\t\t\tTrabalho 6 - Algoritmo de Huffman\t\t\t\t\n");;
       printf("_______________________________________________________________________________\n");


  char data[50],ch,codes[128][10],code[10],en[50],dn[50];
  no *new;
  int temp,i,freq[128]={0},u=0;
  char a[128];// to hold unique letter
  int b[128];// to hold coressponding frequencies
  no *list[128],*x,*y;
  strcpy(code,"");
printf("\t\t\t[Funcionalidade 1]\n");
  printf("\t\tEntre com uma String para compressão: \n");
  gets(data);
  printf("\n");
  printf("-------------------------------------------------------------------------------\n");
  printf("\t\t\t[Funcionalidade 2]\n");
  printf("\t\tConjunto de Caracteres/Números não-repetidos (em ordem)\n");
  i=0;
  while(data[i]!='\0')
    {
      temp=data[i];
      freq[temp]++;
      i++;
    }
  for(i=0;i<128;i++)
    {
      if(freq[i]!=0)
	{
	  ch=i;
	  printf("%c \n",ch);
	  a[u]=ch;
	  b[u]=freq[i];
	  u++;
	  sort(a,b,u);
	  //new=make_no(ch,freq[i]);
	  //add_to_list(new);
	}
    }
  len=u;
    printf("-------------------------------------------------------------------------------\n");
   printf("\t\t\t[Funcionalidade 3]\n");
  printf("\t\tÁrvore Criada com Sucesso!\n\n");
   printf("-------------------------------------------------------------------------------\n");
   printf("\t\t\t[Funcionalidade 4]\n");
  printf("\t\tImpressão em Ordem com a Frequência\n");
  for(i=0;i<u;i++)
    {
      new=cria_no(a[i],b[i]);
      list[i]=new;
    }
  for(i=0;i<u;i++)
    {
      x=list[i];
      printf("%c %d\n",x->data,x->f);
    }
  for(i=0;i<u-1;i++)
    {
      x=extract_min(list);
      y=extract_min(list);
      new=cria_no('\0',0);
      new->esq=x;
      new->dir=y;
      new->f=x->f + y->f;
      x->p=new;
      y->p=new;
      list[len]=new;
      len++;
      lista_ordenada(list);
    }
  x=list[0];
  printf("%c\n Total: %d\n",x->data,x->f);

printf("-------------------------------------------------------------------------------\n");
printf("\t\t\t[Funcionalidade 6]\n");
printf("\t\t\tImpressão da Árvore\n");
  emordem(list[0]);

  printf("-------------------------------------------------------------------------------\n");
printf("\t\t\t[Funcionalidade 8]\n");
  encontra(list[0],code,codes);
  len=u;
  encode(data,en,codes);
printf("\n\n\n\t\tImpressão de dados codificados em formato comprimido\n");
  for(i=0;i<strlen(data);i++)
    printf("%d",en[i]);
  printf("\n\n\n\t\tImpressão de dados codificados em formato nao comprimido\n");
  for(i=0;i<strlen(data);i++)
    puts(e[i]);

printf("-------------------------------------------------------------------------------\n");
printf("\t\t\t[Funcionalidades 1,2 e 3]\n");
printf("\t\t\t     Decodificando...\n");
  decode(en,list[0],strlen(data));
  printf("\n\n-------------------------------------------------------------------------------\n");
  printf("\n\n\t\t\t\t Pronto!! \n\n\n");
}
void decode(char en[50], no * raiz,int u)
{
  char code[10],ch;
  int i=0;
  while(i<u)
    {
      strcpy(code,e[i]);
      ch=conta_letra(code,raiz);
      printf("%c",ch);
      i++;
    }
}
char conta_letra(char code[], no *raiz)
{
  int j=0;
  while(raiz->esq!=NULL || raiz->dir!=NULL)
    {
      if(code[j]=='0')
	raiz=raiz->esq;
      else
	raiz=raiz->dir;
      j++;
    }
  return raiz->data;

}
void encode(char data[], char en[],char codes[128][10])
{
  int i=0,temp;
  char code[10];
  while(i<strlen(data))
    {
      temp=data[i];
      strcpy(code,codes[temp]);
      strcpy(e[i],code);
      //fwrite(code,10*sizeof(char),1,
      en[i]=convert_string_char(code);
      i++;
    }
}
char convert_string_char(char code[10])
{
  int i=0;
  char c=0;
  while(code[i]!='\0')
    {
      if(code[i]=='1')
	{
	  c=c*2;
	  c=c+1;
	}
      else
	{
	  c=c*2;
	}
      i++;
    }
  return c;
}
void encontra(no *raiz,char code[],char codes[128][10])
{
  char temp[10];
  if(raiz->esq==NULL && raiz->dir==NULL)
    {
      strcpy(codes[(int)(raiz->data)],code);
      printf("\nO código de %c é %s",raiz->data,code);
    }
  if(raiz->dir!=NULL)
    {
      strcpy(temp,code);
      strcat(temp,"1");
      encontra(raiz->dir,temp,codes);
    }
  if(raiz->esq!=NULL)
    {
      strcpy(temp,code);
      strcat(temp,"0");
      encontra(raiz->esq,temp,codes);
    }
}
void emordem(no *raiz)
{
  if(raiz!=NULL)
    {
      emordem(raiz->esq);
      printf("%c %d\n",raiz->data,raiz->f);
      emordem(raiz->dir);
    }
}

no * extract_min(no **list)
{
  no *temp;
  temp = list[0];
  list[0]=list[len-1];
  //free(list[len-1]);
  list[len-1]=NULL;
  len--;
  lista_ordenada(list);
  return temp;
}
void lista_ordenada(no **list)
{
  int i,j;
  no *x,*y;
  for(i=0;i<len;i++)
    {
      for(j=0;j<len-1;j++)
	{
	  //printf("wtf\n");
	  x=list[j];
	  y=list[j+1];
	  if(x->f > y->f)
	    {
	      list[j]=y;
	      list[j+1]=x;
	    }
	}
    }

}
no * cria_no(char ch, int freq)
{
  no *new;
  new=(no *)malloc(sizeof(no));
  new->data=ch;
  new->f=freq;
  new->esq=NULL;
  new->dir=NULL;
  new->p=NULL;
}

void sort(char a[],int b[],int u)
{
  int i,j,temp;
  char ch;
  for(i=0;i<u;i++)
    {
      for(j=0;j<u-1;j++)
	{
	  if(b[j]>b[j+1])
	    {
	      temp=b[j+1];
	      ch=a[j+1];
	      b[j+1]=b[j];
	      a[j+1]=a[j];
	      b[j]=temp;
	      a[j]=ch;
	    }
	}
    }
}
