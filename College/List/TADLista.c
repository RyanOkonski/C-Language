#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"TADLista.h"
#include<locale.h>

int menu(Usuario *lista){
   setlocale(LC_ALL, "Portuguese");
   int op;
   char opcao;
   while (op != 8){
      printf("\n---Menu da Agenda---\n");
      printf("1 - Criar uma agenda\n");
      printf("2 - Inserir um usuario na agenda\n");
      printf("3 - Remover um usuario da agenda\n");
      printf("4 - Buscar um usuario na agenda\n");
      printf("5 - Imprimir agenda\n");
      printf("6 - Apagar agenda\n");
      printf("7 - Sair do programa\n");
      printf("\nOpcao: ");
      scanf("%d", &op);
      fflush(stdin);
      printf("\n");

      switch(op){

         case 1:
            lista = Criar_Lista();
            break;

         case 2:
            do{
               lista = Inserir(lista);
               printf("\nDeseja inserir mais um usuario? (s/n): ");
               scanf("%c", &opcao);
               fflush(stdin);
            }while(opcao != 'n');
            break;

         case 3:
            lista = Remover(lista);
            break;

         case 4:
            Busca(lista);
            break;

         case 5:
            Imprimir(lista);
            break;

         case 6:
            lista = Apagar(lista);
            break;

         case 7:
            printf("O programa foi encerrado!\n");
            return 0;

         default:
            printf("Este comando nao existe!\n");
            break;
      }
   }
}

Usuario* Criar_Lista(){
   printf("A agenda foi criada com sucesso!\n");
   return NULL;
}

Usuario* Inserir(Usuario *lista){
   Usuario *novo, *aux1, *aux2;

   if (lista == NULL){
      lista = (Usuario*) malloc(sizeof(struct usuario));
      printf("Digite o nome do unico usuario: ");
      gets(lista->nome);
      fflush(stdin);
      printf("Digite o telefone do unico usuario: ");
      scanf("%d", &lista->telefone);
      fflush(stdin);
      printf("Digite o endereço do unico usuario: ");
      gets(lista->endereco);
      fflush(stdin);
      lista->prox = NULL;
      fflush(stdin);
   }
   else{
      novo = (Usuario*) malloc(sizeof(struct usuario));
      printf("Digite o nome do novo usuario: ");
      gets(novo->nome);
      fflush(stdin);
      printf("Digite o telefone do novo usuario: ");
      scanf("%d", &novo->telefone);
      fflush(stdin);
      printf("Digite o endereço do novo usuario: ");
      gets(novo->endereco);
      fflush(stdin);
      novo->prox = NULL;
      fflush(stdin);

      if (strcmp(novo->nome,lista->nome) < 0){
         novo->prox = lista;
         lista = novo;
         novo = NULL;
      }
      else{
         aux1 = lista;
         while ((aux1 != NULL) && strcmp(novo->nome,aux1->nome) > 0 ){
            aux2 = aux1;
            aux1 = aux1->prox;
      }
      if (aux1 == NULL){
            aux2->prox = novo;
            novo = NULL;
            aux2 = NULL;
      }
      else{
            aux2->prox = novo;
            novo->prox = aux1;
            novo = NULL;
            aux1 = NULL;
            aux2 = NULL;
      }
      }
   }
   return lista;
}

void Imprimir(Usuario *lista){
   Usuario* aux;

   if (lista == NULL){
      printf("A agenda esta vazia!\n");
   }else{
      printf("Nome: %s", lista->nome);
      printf("\nTelefone: %d", lista->telefone);
      printf("\nEndereco: %s\n", lista->endereco);
      aux = lista->prox;
      while(aux != NULL){
         printf("\nNome: %s", aux->nome);
         printf("\nTelefone: %d", aux->telefone);
         printf("\nEndereco: %s\n", aux->endereco);
         aux = aux->prox;
      }
   }
}

int Busca(Usuario* lista){
   Usuario *aux;
   char nome[20];
   aux = lista;

   printf("Digite o nome do usuario a ser encontrado: ");
   gets(nome);

   if(lista == NULL){
      printf("A agenda nao existe!");
   }
   while(aux != NULL){
      if(strcmp(aux->nome,nome) == 0){
         printf("\nNome: %s", aux->nome);
         printf("\nTelefone: %d", aux->telefone);
         printf("\nEndereco: %s\n", aux->endereco);
         return 1;
      }
      aux = aux->prox;
   }
   printf("\nUsuario nao encontrado!\n");
   return 0;
}

int Remover(Usuario* lista){
   Usuario *anterior, *atual;
   char name[20];
   anterior = lista;
   atual = lista;

   printf("Digite o nome do usuario a ser removido: ");
   scanf("%s", &name);

   if(lista == NULL){
      return 0;
   }
   if(lista->prox == NULL && (strcmp(lista->nome,name) == 0)){
      free(lista);
      anterior = NULL;
      atual = NULL;
      lista = NULL;
      return NULL;
   }
   else if(lista->prox != NULL && (strcmp(lista->nome,name) == 0)){
      atual = atual->prox;
      free(anterior);
      anterior = atual;
      lista = atual;
      return anterior;
   }
   else{
      atual = lista;
      while(atual != NULL && (strcmp(atual->nome,name) != 0)){
         anterior = atual;
         atual = atual->prox;
      }
      if(atual == NULL && (strcmp(anterior->nome,name) != 0)){
         printf("\nUsuario nao encontrado!\n");
        }
      else if((strcmp(atual->nome,name) == 0)){
         anterior->prox = atual->prox;
         free(atual);
         atual = NULL;
      }
   }
   return lista;
}

int Apagar(Usuario *lista){
   Usuario *aux = lista;
   if(lista == NULL){
      printf("A agenda ja esta vazia!");
   }
   else{
      while(lista != NULL){
         aux = lista;
         lista = lista->prox;
         free(aux);
      }
   free(lista);
   printf("Agenda liberada!\n");
   return NULL;
   }
}
