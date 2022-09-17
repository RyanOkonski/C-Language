#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_MAX_REG 120
#define DELIM_STR "|"
#define DELIM_LINE "\n"
#define TAM_STR 30
#define TRUE 1
#define FALSE 0

void importar(char *argv);
int executar_operacoes(char *argv);
void concatena_campo(char *buffer, char *campo);
void le_reg_e_mostra(FILE *entrada, int *rrn);
short leia_reg(char *buffer, int tam, FILE *arq);
int input(char *str, int size);
int buscaReg(char *busca, FILE *entrada);
int buscaRemocao(char *busca, FILE *entrada);
int atualizaLed(int posicao);
int topoLed();

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

int executar_operacoes(char *argv)
{
   FILE *dados, *operacao;
   int rrn = 0, byte_offset = 4;
   short comp_reg, achou, compr = 2;
   char buffer[TAM_MAX_REG], *campo, busca[3], op;

   if ((operacao = fopen(argv, "r")) == NULL)
   {
      printf("Erro na abertura do arquivo --- programa abortado\n");
      exit(EXIT_FAILURE);
   }

   if ((dados = fopen("dados.dat", "rb+")) == NULL)
   {
      printf("Erro na abertura do arquivo --- programa abortado\n");
      exit(EXIT_FAILURE);
   }

   fseek(dados, byte_offset, SEEK_SET);
   while (!feof(operacao))
   {
      op = fgetc(operacao);
      if (op == 'b')
      {
         fgetc(operacao);
         fgets(busca, 4, operacao);
         printf("\nBusca pelo registro de chave [%s]: \n", busca);
         buscaReg(busca, dados);
         rewind(dados);
      }
      if (op == 'r')
      {
         fgetc(operacao);
         fgets(busca, 4, operacao);
         printf("\nRemocao do registro de chave: %s \n", busca);
         buscaRemocao(busca, dados);
         rewind(dados);
      }
   }
   fclose(dados);
   fclose(operacao);
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

int buscaReg(char *busca, FILE *entrada)
{
   char *ind, *campo;
   char buffer[TAM_MAX_REG];
   short tamreg;
   int achou = FALSE;

   while (fread(&tamreg, sizeof(tamreg), 1, entrada) > 0)
   {
      fread(buffer, sizeof(char), tamreg, entrada);
      ind = strtok(buffer, "|");
      if (strcmp(ind, busca) == 0)
      {
         achou = TRUE;
         fseek(entrada, -tamreg, SEEK_CUR);
         fgets(buffer, tamreg, entrada);
         campo = strtok(buffer, DELIM_STR);
         while (campo != NULL)
         {
            printf("%s|", campo);
            campo = strtok(NULL, DELIM_STR);
         }
         printf(" (%d bytes)\n", tamreg);
      }
      fseek(entrada, 1, SEEK_CUR);
   }
   if(!achou){
      printf("Erro: registro nao encontrado!\n");
   }
}

int buscaRemocao(char *busca, FILE *entrada)
{
   char *ind, *campo;
   char buffer[TAM_MAX_REG];
   short tamreg;
   int achou = FALSE, jump, topo;
   topo = topoLed();

   while (fread(&tamreg, sizeof(tamreg), 1, entrada) > 0)
   {
      fread(buffer, sizeof(char), tamreg, entrada);
      ind = strtok(buffer, "|");
      if (strcmp(ind, busca) == 0)
      {
         printf("Registro removido! (%d bytes)\n", tamreg);
         printf("Local: offset = %d bytes (%x)\n", ftell(entrada), ftell(entrada));
         jump = tamreg;
         fseek(entrada, -jump, SEEK_CUR);
         fputc('*', entrada);
         fwrite(&topo, sizeof(int), 1, entrada);
         atualizaLed(tamreg);
      }
      fseek(entrada, 1, SEEK_CUR);
   }
   if(!achou){
      printf("Erro: registro nao encontrado!\n");
   }
}

int atualizaLed(int comprimentoReg)
{
   FILE *arquivoCopia;
   int cabeca;

   arquivoCopia = fopen("dados.dat", "rb+");
   fread(&cabeca, sizeof(int), 1, arquivoCopia);

   if (cabeca != comprimentoReg)
   {
      cabeca = comprimentoReg;
      fseek(arquivoCopia, 0, SEEK_SET);
      fwrite(&cabeca, sizeof(int), 1 ,arquivoCopia);  
   }

   fclose(arquivoCopia);
   return cabeca;
}

int topoLed()
{
   FILE *arquivoCopia;
   int topoLed;

   arquivoCopia = fopen("dados.dat", "rb+");
   fread(&topoLed, sizeof(int), 1, arquivoCopia);

   fclose(arquivoCopia);
   return topoLed;
}