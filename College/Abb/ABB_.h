#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct eleitor ELEITOR;
typedef struct arvore ARVORE;
typedef struct votar VOTAR;

struct eleitor
{
   int titulo;
   ELEITOR *fesq;
   ELEITOR *fdir;
};

struct votar
{
   int candidato;
   int titulo;
   VOTAR *fesq;
   VOTAR *fdir;
};

struct arvore
{
   ELEITOR *raiz;
   VOTAR *rz;
};

ARVORE *criar_arvore();
ARVORE *cadastrar(ARVORE *arvore);
ARVORE *CadastrarVoto(ARVORE *arvore, int titulo);
ELEITOR *criar_raiz(ARVORE *arvore, int item);
ELEITOR *inserir_filho(int filho, ELEITOR *eleitor, int item);
ELEITOR *remover(ELEITOR *eleitor, int valor);
ELEITOR *RetornaEleitor(ELEITOR **T, int chave);
VOTAR *criar_raizVotar(ARVORE *arvore, int item, int titulo);
VOTAR *inserir_filhoVotar(int filho, VOTAR *eleitor, int titulo, int candidato);
VOTAR *removerV(VOTAR *eleitor, int valor);
int menu(ARVORE *arvore);
int inserir_aux(ELEITOR *raiz, int ItemNovo);
int inserir_auxVotar(VOTAR *raiz, int titulo, int candidato);
int inserir(ARVORE *arvore, int item);
int inserirVotar(ARVORE *arvore, int titulo, int candidato);
int busca_aux(ELEITOR *raiz, int chave);
int busca(ARVORE *arvore, int chave);
int validar(ARVORE *arvore);
int menorNo(VOTAR *raiz);
int maiorNo(VOTAR *raiz);
int contador(VOTAR *raiz, int candidato);
void emordem_aux(ELEITOR *raiz);
void emordem(ARVORE *arvore);
void emordem_auxVotar(VOTAR *raiz);
void emordemVotar(ARVORE *arvore);
void apagar_aux(ELEITOR *raiz);
void apagar_voto(VOTAR *raiz);
void encerrar(ARVORE *arvore);