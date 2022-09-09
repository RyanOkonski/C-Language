#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_MAX_REG 82
#define DELIM_STR "|"
#define DELIM_LINE "\n"
#define TAM_STR 30
#define TRUE 1
#define FALSE 0

void importar(char *argv);
int executar_operacoes(char *argv, int argc);
void concatena_campo(char *buffer, char *campo);
void le_reg_e_mostra(FILE *entrada, int *rrn);
short leia_reg(char *buffer, int tam, FILE *arq);
int input(char *str, int size);

void importar(char *argv)
{
   FILE *saida, *entrada;
   char buffer[TAM_MAX_REG];
   int LED = -1;
   short comprimento;

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

   fwrite(&LED, sizeof(LED), 1, saida);
   while (fgets(buffer, TAM_MAX_REG, entrada) != NULL)
   {
      comprimento = strlen(buffer) - 1;
      fwrite(&comprimento, sizeof(comprimento), 1, saida);
      fputs(buffer, saida);
   }

   fclose(entrada);
   fclose(saida);
}

int executar_operacoes(char *argv, int argc)
{
   FILE *entrada;
   int rrn = 0, byte_offset = 4;
   short comp_reg, achou, compr = 2;
   char buffer[TAM_MAX_REG];
   char *campo;

   entrada = fopen(argv, "rb");
   if ((entrada = fopen(argv, "rb")) == NULL)
   {
      printf("Erro na abertura do arquivo --- programa abortado\n");
      exit(EXIT_FAILURE);
   }

   fseek(entrada, byte_offset, SEEK_SET);
   achou = FALSE;
   comp_reg = leia_reg(buffer, TAM_MAX_REG, entrada);
   while (!achou && comp_reg > 0)
   {
      campo = strtok(buffer, DELIM_STR);
      rrn = atoi(campo);
      if (argc == rrn)
      {
         printf("\nSEEK = %d\n", ftell(entrada));
         achou = TRUE;
      }
      else
      {
         printf("\nSEEK = %d\n", ftell(entrada));
         comp_reg = leia_reg(buffer, TAM_MAX_REG, entrada);
      }
      if (achou)
      {
         //le_reg_e_mostra(entrada, &rrn);
      }
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

short leia_reg(char *buffer, int tam, FILE *arq)
{
   short comp_reg;

   if (fread(&comp_reg, sizeof(comp_reg), 1, arq) == 0)
   {
      return 0;
   }

   printf("Cpm = %d", comp_reg);
   if (comp_reg < tam)
   {
      comp_reg = fread(buffer, sizeof(char), comp_reg, arq);
      buffer[comp_reg] = '\0';
      return comp_reg;
   }
   else
   {
      printf("Buffer overflow\n");
      return 0;
   }
}

int input(char *str, int size)
{
   int i = 0;
   char c = getchar();
   while (c != '\n')
   {
      if (i < size - 1)
      {
         str[i] = c;
         i++;
      }
      c = getchar();
   }
   str[i] = '\0';
   return i;
}