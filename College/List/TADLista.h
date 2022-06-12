//Ryan Guilherme  Okonski dos Santos RA: 124117 , Lucas Garcia dos Santos RA: 123851
#include<stdlib.h>
#include<stdio.h>
#include<locale.h>

typedef struct usuario Usuario;

struct usuario{
   char nome[20];
   int telefone;
   char endereco[100];
   struct Usuario *prox;
};

int menu(Usuario *lista);
Usuario* Criar_Lista();
Usuario* Inserir(Usuario *lista);
void Imprimir(Usuario *lista);
int Busca(Usuario* lista);
int Remover(Usuario* lista);
int Apagar(Usuario *lista);
