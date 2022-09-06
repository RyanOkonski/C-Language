#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_MAX_REG 64
#define DELIM_STR "|"

void importar(char *argv);
void le_reg_e_mostra(FILE *entrada, int *rrn);
int input(char *str, int size);
int executar_operacoes(char *argv);
void concatena_campo(char *buffer, char *campo);

void importar(char *argv)
{
   FILE *saida, *entrada;
   char buffer[TAM_MAX_REG];
   int comprimento;

   entrada = fopen(argv, "r");
   saida = fopen("dados.dat", "wb");

   if ((entrada = fopen(argv, "r")) == NULL)
   {
      printf("Erro na abertura do arquivo --- programa abortado\n");
      exit(EXIT_FAILURE);
   }

   if ((saida = fopen("dados.dat", "wb")) == NULL)
   {
      printf("Erro na criacao do arquivo --- programa abortado\n");
      exit(EXIT_FAILURE);
   }
   while (fgets(buffer, TAM_MAX_REG, entrada) != NULL)
   {
      comprimento = strlen(buffer);
      buffer[comprimento] = '\0';
      fprintf(saida, "%s", buffer);
   }

   fclose(entrada);
   fclose(saida);
}

int executar_operacoes(char *argv)
{
   FILE *entrada;
   int rrn = 0, byte_offset, num;
   char buffer[TAM_MAX_REG + 1];
   char op;

   printf("Digite: ");
   gets(&op);

   printf("Digite o registro que busca: ");
   scanf("%d", &num);

   entrada = fopen(argv, "rb");

   if ((entrada = fopen(argv, "rb")) == NULL)
   {
      printf("Erro na abertura do arquivo --- programa abortado\n");
      exit(EXIT_FAILURE);
   }

   switch (op)
   {
   case 'b':
      rrn = num;
      byte_offset = (rrn - 1) * TAM_MAX_REG;
      fseek(entrada, byte_offset, SEEK_SET);
      le_reg_e_mostra(entrada, &rrn);
      rewind(entrada);
      break;

   default:
      break;
   }

   fclose(entrada);
   return 0;
}

void concatena_campo(char *buffer, char *campo)
{
   strcat(buffer, campo);
   strcat(buffer, DELIM_STR);
}

void le_reg_e_mostra(FILE *entrada, int *rrn)
{
   char buffer[TAM_MAX_REG + 1];
   char *campo;

   fread(buffer, sizeof(char), TAM_MAX_REG, entrada);
   buffer[TAM_MAX_REG] = '\0';

   printf("\nBusca pelo registro de chave [%d]\n", *rrn);
   campo = strtok(buffer, DELIM_STR);
   while (campo != NULL)
   {
      printf("%s|", campo);
      campo = strtok(NULL, DELIM_STR);
   }
}