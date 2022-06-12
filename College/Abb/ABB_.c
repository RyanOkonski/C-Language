/*Nome: Ryan Guilherme Okonski dos Santos RA: 124117
  Nome: Lucas Garcia dos Santos           RA: 123851
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ABB_.h"
#define Filho_esq 0
#define Filho_dir 1

int menu(ARVORE *arvore)
{
   int opcoes, item;

   while (opcoes != 9)
   {

      printf("                           NAVEGUE ESCOLHENDO UM DOS NUMEROS                            \n");
      printf("========================================================================================\n");
      printf("| 1 -> Cadastrar Titulo     ||  2 -> Descadastrar Titulo  ||  3 -> Buscar Titulo       |\n");
      printf("| 4 -> Mostra Cadastrados   ||  5 -> Votar                ||  6 -> Retirar Voto        |\n");
      printf("| 7 -> Mostra Votos         ||  8 -> Resultado Parcial    ||  9 -> Finalizar Programa  |\n");
      printf("========================================================================================\n");
      printf("                                     OPCAO = ");
      scanf("%d", &opcoes);
      system("cls");

      if (opcoes == 1)
      {
         printf("==================CADASTRAMENTO DE TITULO==================\n");
         cadastrar(arvore);
         printf("-----------------------------------------------------------\n");
         printf("\n");
         system("pause");
         system("cls");
      }
      else if (opcoes == 2)
      {
         if (arvore == NULL)
            printf("Ninguem cadastrou titulo ate o momomento...\n");
         else
         {
            printf("==================REMOCAO DE TITULO==================\n");
            printf("Insira o titulo que deseja remover: ");
            scanf("%d", &item);
            arvore->raiz = remover(arvore->raiz, item);
            printf("-----------------------------------------------------\n");
         }
         printf("\n");
         system("pause");
         system("cls");
      }
      else if (opcoes == 3)
      {
         if (arvore == NULL)
            printf("Ninguem cadastrou titulo ate o momomento...\n");
         else
         {
            printf("==================MENU DE BUSCA==================\n");
            printf("Qual titulo voce deseja buscar: ");
            scanf("%d", &item);
            fflush(stdin);
            if (busca(arvore, item) != 0)
            {
               printf("Titulo encontrado: %d\n", busca(arvore, item));
            }
            printf("-------------------------------------------------\n");
         }
         printf("\n");
         system("pause");
         system("cls");
      }
      else if (opcoes == 4)
      {
         if (arvore == NULL)
            printf("Ninguem cadastrou titulo ate o momomento...\n");
         else
         {
            printf("==================ELEITORES CADASTRADOS==================\n");
            emordem(arvore);
            printf("---------------------------------------------------------\n");
         }
         printf("\n");
         system("pause");
         system("cls");
      }
      else if (opcoes == 5)
      {
         printf("==================MENU DE VOTACAO==================\n");
         validar(arvore);
         printf("---------------------------------------------------\n");
         printf("\n");
         system("pause");
         system("cls");
      }
      else if (opcoes == 6)
      {
         if (arvore == NULL)
            printf("Ninguem votou ate o momomento...\n");
         else
         {
            printf("==================REMOCAO DE VOTO==================\n");
            printf("Digite seu titulo para remover o voto: ");
            scanf("%d", &item);
            fflush(stdin);
            arvore->rz = removerV(arvore->rz, item);
            printf("---------------------------------------------------\n");
         }
         printf("\n");
         system("pause");
         system("cls");
      }
      else if (opcoes == 7)
      {
         if (arvore == NULL)
            printf("Ninguem votou ate o momomento...\n");
         else
         {
            printf("==================PESSOAS QUE JA VOTARRAM==================\n");
            emordemVotar(arvore);
            printf("-----------------------------------------------------------\n");
         }
         printf("\n");
         system("pause");
         system("cls");
      }
      else if (opcoes == 8)
      {
         if (arvore == NULL)
            printf("Ninguem votou ate o momomento...\n");
         else
         {
            printf("===================RESULTADO PARCIAL===================\n");
            printf("Qual candidato voce deseja saber a quantidade de votos?\n");
            scanf("%d", &item);
            printf("Candidato [%d] recebeu: %d votos\n", item, contador(arvore->rz, item));
            printf("\n");
            printf("Menor titulo que ja votou: %d\n", menorNo(arvore->rz));
            printf("Maior titulo que ja votou: %d\n", maiorNo(arvore->rz));
            printf("-------------------------------------------------------\n");
         }
         printf("\n");
         system("pause");
         system("cls");
      }
      else if (opcoes == 9)
      {
         encerrar(arvore);
         printf("Programa encerrado!");
         return 0;
      }
   }
   return 0;
}

ARVORE *criar_arvore()
{
   ARVORE *arv;
   arv = (ARVORE *)malloc(sizeof(ARVORE));

   if (arv != NULL)
   {
      arv->raiz = NULL;
      arv->rz = NULL;
   }
   return arv;
}

ELEITOR *criar_raiz(ARVORE *arvore, int item)
{
   arvore->raiz = (ELEITOR *)malloc(sizeof(ELEITOR));

   if (arvore->raiz != NULL)
   {
      arvore->raiz->fdir = NULL;
      arvore->raiz->fesq = NULL;
      arvore->raiz->titulo = item;
   }
   return arvore->raiz;
}

VOTAR *criar_raizVotar(ARVORE *arvore, int titulo, int candidato)
{
   arvore->rz = (VOTAR *)malloc(sizeof(VOTAR));

   if (arvore->rz != NULL)
   {
      arvore->rz->fdir = NULL;
      arvore->rz->fesq = NULL;
      arvore->rz->titulo = titulo;
      arvore->rz->candidato = candidato;
   }
   return arvore->rz;
}

ELEITOR *inserir_filho(int filho, ELEITOR *eleitor, int item)
{
   ELEITOR *pnovo = (ELEITOR *)malloc(sizeof(ELEITOR));
   if (pnovo != NULL)
   {
      pnovo->fdir = NULL;
      pnovo->fesq = NULL;
      pnovo->titulo = item;
   }
   if (filho == Filho_esq)
   {
      eleitor->fesq = pnovo;
   }
   else
   {
      eleitor->fdir = pnovo;
   }
   return pnovo;
}

VOTAR *inserir_filhoVotar(int filho, VOTAR *eleitor, int titulo, int candidato)
{
   VOTAR *pnovo = (VOTAR *)malloc(sizeof(VOTAR));
   if (pnovo != NULL)
   {
      pnovo->fdir = NULL;
      pnovo->fesq = NULL;
      pnovo->titulo = titulo;
      pnovo->candidato = candidato;
   }
   if (filho == Filho_esq)
   {
      eleitor->fesq = pnovo;
   }
   else
   {
      eleitor->fdir = pnovo;
   }
   return pnovo;
}

int inserir_aux(ELEITOR *raiz, int ItemNovo)
{
   if (raiz->titulo > ItemNovo)
   {
      if (raiz->fesq != NULL)
      {
         return inserir_aux(raiz->fesq, ItemNovo);
      }
      else
      {
         return (inserir_filho(Filho_esq, raiz, ItemNovo) != NULL);
      }
   }
   else if (raiz->titulo < ItemNovo)
   {
      if (raiz->fdir != NULL)
      {
         return inserir_aux(raiz->fdir, ItemNovo);
      }
      else
      {
         return (inserir_filho(Filho_dir, raiz, ItemNovo) != NULL);
      }
   }
   else
   {
      return 0;
   }
}

int inserir_auxVotar(VOTAR *raiz, int titulo, int candidato)
{
   if (raiz->titulo > titulo)
   {
      if (raiz->fesq != NULL)
      {
         return inserir_auxVotar(raiz->fesq, titulo, candidato);
      }
      else
      {
         return (inserir_filhoVotar(Filho_esq, raiz, titulo, candidato) != NULL);
      }
   }
   else if (raiz->titulo < titulo)
   {
      if (raiz->fdir != NULL)
      {
         return inserir_auxVotar(raiz->fdir, titulo, candidato);
      }
      else
      {
         return (inserir_filhoVotar(Filho_dir, raiz, titulo, candidato) != NULL);
      }
   }
   else
   {
      return 0;
   }
}

int inserir(ARVORE *arvore, int item)
{
   return inserir_aux(arvore->raiz, item);
}

int inserirVotar(ARVORE *arvore, int titulo, int candidato)
{
   return inserir_auxVotar(arvore->rz, titulo, candidato);
}

ARVORE *cadastrar(ARVORE *arvore)
{
   int item;

   if (arvore->raiz == NULL)
   {
      printf("Digite o primeiro titulo: ");
      scanf("%d", &item);
      fflush(stdin);
      criar_raiz(arvore, item);
   }
   else
   {
      printf("Digite o proximo titulo: ");
      scanf("%d", &item);
      fflush(stdin);

      if (busca(arvore, item) == item)
      {
         printf("Esse titulo ja foi cadastrado!");
      }
      else
      {
         inserir(arvore, item);
      }
   }
   return arvore;
}

void emordem_aux(ELEITOR *raiz)
{
   if (raiz != NULL)
   {
      emordem_aux(raiz->fesq);
      printf("Titulo de eleitor: %d\n", raiz->titulo);
      emordem_aux(raiz->fdir);
   }
}

void emordem(ARVORE *arvore)
{
   emordem_aux(arvore->raiz);
}

void emordem_auxVotar(VOTAR *raiz)
{
   if (raiz != NULL)
   {
      emordem_auxVotar(raiz->fesq);
      printf("Titulo: %d, Votou no Candidato: %d\n", raiz->titulo, raiz->candidato);
      emordem_auxVotar(raiz->fdir);
   }
}

void emordemVotar(ARVORE *arvore)
{
   emordem_auxVotar(arvore->rz);
}

ELEITOR *remover(ELEITOR *eleitor, int valor)
{
   if (eleitor != NULL)
   {
      if (eleitor->titulo > valor)
      {
         eleitor->fesq = remover(eleitor->fesq, valor);
      }
      else if (eleitor->titulo < valor)
      {
         eleitor->fdir = remover(eleitor->fdir, valor);
      }
      else
      {
         ELEITOR *aux;
         if (eleitor->fesq == NULL)
         {
            aux = eleitor;
            eleitor = eleitor->fdir;
            free(aux);
            printf("Titulo de eleitor removido com sucesso!\n");
         }
         else if (eleitor->fdir == NULL)
         {
            aux = eleitor;
            eleitor = eleitor->fesq;
            free(aux);
            printf("Titulo de eleitor removido com sucesso!\n");
         }
         else
         {
            aux = eleitor->fesq;
            while (aux->fdir != NULL)
            {
               aux = aux->fdir;
            }
            eleitor->titulo = aux->titulo;
            aux->titulo = valor;
            eleitor->fesq = remover(eleitor->fesq, valor);
         }
      }
   }
   return eleitor;
}

VOTAR *removerV(VOTAR *eleitor, int valor)
{
   if (eleitor != NULL)
   {
      if (eleitor->titulo > valor)
      {
         eleitor->fesq = removerV(eleitor->fesq, valor);
      }
      else if (eleitor->titulo < valor)
      {
         eleitor->fdir = removerV(eleitor->fdir, valor);
      }
      else
      {
         VOTAR *aux;
         if (eleitor->fesq == NULL)
         {
            aux = eleitor;
            eleitor = eleitor->fdir;
            free(aux);
            printf("Voto removido com sucesso!\n");
         }
         else if (eleitor->fdir == NULL)
         {
            aux = eleitor;
            eleitor = eleitor->fesq;
            free(aux);
            printf("Voto removido com sucesso!\n");
         }
         else
         {
            aux = eleitor->fesq;
            while (aux->fdir != NULL)
            {
               aux = aux->fdir;
            }
            eleitor->titulo = aux->titulo;
            aux->titulo = valor;
            eleitor->fesq = removerV(eleitor->fesq, valor);
         }
      }
   }
   return eleitor;
}

int busca(ARVORE *arvore, int chave)
{
   return busca_aux(arvore->raiz, chave);
}

int busca_aux(ELEITOR *raiz, int chave)
{
   if (raiz == NULL)
   {
      return 0;
   }
   else if (raiz->titulo > chave)
   {
      return busca_aux(raiz->fesq, chave);
   }
   else if (raiz->titulo < chave)
   {
      return busca_aux(raiz->fdir, chave);
   }
   return raiz->titulo;
}

int votou_aux(VOTAR *raiz, int chave)
{
   if (raiz == NULL)
   {
      return 0;
   }
   else if (raiz->titulo > chave)
   {
      return votou_aux(raiz->fesq, chave);
   }
   else if (raiz->titulo < chave)
   {
      return votou_aux(raiz->fdir, chave);
   }
   else
   {
      return raiz->titulo;
   }
}

int votou(ARVORE *arvore, int chave)
{
   return votou_aux(arvore->rz, chave);
}

int validar(ARVORE *arvore)
{
   ELEITOR *aux = (ELEITOR *)malloc(sizeof(ELEITOR));
   int titulo;

   printf("Insira o titulo de quem esta votando: ");
   scanf("%d", &titulo);
   fflush(stdin);

   aux->titulo = busca(arvore, titulo);

   if (aux->titulo == titulo)
   {
      printf("Titulo liberado para votar!");
      printf("\n");
      CadastrarVoto(arvore, titulo);
      return 1;
   }
   else
   {
      printf("Titulo nao liberado para voto!");
      printf("\n");
      return 0;
   }
}

ARVORE *CadastrarVoto(ARVORE *arvore, int titulo)
{
   int aux, candidato;
   printf("Digite seu voto: ");
   scanf("%d", &candidato);
   fflush(stdin);

   aux = busca(arvore, candidato);

   if (arvore->rz == NULL && aux == candidato)
   {
      criar_raizVotar(arvore, titulo, candidato);
   }
   else if (aux == candidato)
   {
      inserirVotar(arvore, titulo, candidato);
   }
   else
   {
      printf("Candidato nao pode ser votado!");
      printf("\n");
   }
   return arvore;
}

int menorNo(VOTAR *raiz)
{
   int menor = 0;

   if (raiz->titulo > menor)
   {
      if (raiz->fesq != NULL)
      {
         return menorNo(raiz->fesq);
      }
      else
      {
         menor = raiz->titulo;
         return menor;
      }
   }
   return 0;
}

int maiorNo(VOTAR *raiz)
{
   int maior = 0;

   if (raiz->titulo > maior)
   {
      if (raiz->fdir != NULL)
      {
         return maiorNo(raiz->fdir);
      }
      else
      {
         maior = raiz->titulo;
         return maior;
      }
   }
   return 0;
}

void apagar_aux(ELEITOR *raiz)
{
   if (raiz != NULL)
   {
      apagar_aux(raiz->fesq);
      apagar_aux(raiz->fdir);
      remover(raiz,raiz->titulo);
      free(raiz);
   }
}

void apagar_voto(VOTAR *raiz)
{
   if (raiz != NULL)
   {
      apagar_voto(raiz->fesq);
      apagar_voto(raiz->fdir);
      removerV(raiz,raiz->titulo);
      free(raiz);
   }
}

void encerrar(ARVORE *arvore)
{
   apagar_aux(arvore->raiz);
   apagar_voto(arvore->rz);
   free(arvore);
   arvore = NULL;
}

int contador(VOTAR *raiz, int candidato)
{
   int cont;

   if (raiz == NULL)
   {
      return 0;
   }
   if (raiz->candidato == candidato)
   {
      cont = 1;
   }
   else
   {
      cont = 0;
   }
   cont = cont + contador(raiz->fesq, candidato) + contador(raiz->fdir, candidato);
   return cont;
}