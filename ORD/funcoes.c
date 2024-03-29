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
int buscaReg(char *busca, FILE *entrada);
int buscaRemocao(char *busca, FILE *entrada);
int insercaoReg(char *novoReg, FILE *entrada);
int atualizaLed(int enderecoReg);
int topoLed();
void impressaoLed();

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
   int byte_offset = 4;
   char buffer[TAM_MAX_REG], busca[3], op, *ind;

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
         fseek(dados, byte_offset, SEEK_SET);
      }
      if (op == 'r')
      {
         fgetc(operacao);
         fgets(busca, 4, operacao);
         printf("\nRemocao do registro de chave: %s \n", busca);
         buscaRemocao(busca, dados);
         fseek(dados, byte_offset, SEEK_SET);
      }
      if (op == 'i')
      {
         fgetc(operacao);
         fgets(buffer, sizeof(buffer), operacao);
         printf("\nInsercao do registro!\n");
         insercaoReg(buffer, dados);
         fseek(dados, byte_offset, SEEK_SET);
      }
   }
   fclose(dados);
   fclose(operacao);
   return 0;
}

int buscaReg(char *busca, FILE *entrada)
{
   char *ind, *campo;
   char buffer[TAM_MAX_REG];
   short tamreg, achou = FALSE;

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
   if(!achou){printf("Erro: registro nao encontrado!\n");}
   return 0;
}

int buscaRemocao(char *busca, FILE *entrada)
{
   char *ind;
   char buffer[TAM_MAX_REG];
   short tamreg;
   int jump, topo;

   topo = topoLed();
   while (fread(&tamreg, sizeof(tamreg), 1, entrada) > 0)
   {
      fread(buffer, sizeof(char), tamreg, entrada);
      ind = strtok(buffer, "|");
      if (strcmp(ind, busca) == 0)
      {
         jump = tamreg;
         fseek(entrada, -jump, SEEK_CUR);
         printf("Registro removido! (%d bytes)\n", tamreg);
         printf("Local: offset = %ld bytes", ftell(entrada));
         atualizaLed(ftell(entrada));
         fputc('*', entrada);
         fwrite(&topo, sizeof(int), 1, entrada);
      }
      fseek(entrada, 1, SEEK_CUR);
   }
   printf("Erro: registro nao encontrado!\n");
   return 0;
}

int insercaoReg(char *novoReg, FILE *entrada)
{
   entrada = fopen("dados.dat", "rb+");
   short tamReg, compReg;
   int enderecoReg, calcLed;

   tamReg = strlen(novoReg);
   fread(&enderecoReg, sizeof(int), 1, entrada);
   if (enderecoReg == -1)
   {
      fseek(entrada, 0, SEEK_END);
      fwrite(&tamReg, sizeof(tamReg), 1, entrada);
      fputs(novoReg, entrada);
      printf("Local: fim do arquivo\n");
   }
   else if (enderecoReg != -1)
   {
      calcLed = enderecoReg - sizeof(short);
      fseek(entrada, calcLed, SEEK_SET);
      fread(&compReg, sizeof(short), 1, entrada);
      if (tamReg > compReg)
      {
         fseek(entrada, 0, SEEK_END);
         fwrite(&tamReg, sizeof(tamReg), 1, entrada);
         fputs(novoReg, entrada);
         printf("Local: fim do arquivo\n");
      }
      else if (tamReg <= compReg)
      {
         printf("Tamanho do espaco reutilizado: %d bytes\n", compReg);
         printf("Local: offset = %ld bytes\n", ftell(entrada));
         fseek(entrada, -sizeof(short), SEEK_CUR);
         fwrite(&tamReg, sizeof(tamReg), 1, entrada);
         fputs(novoReg, entrada);
      }
   }

   fclose(entrada);
   return 0;
}

int atualizaLed(int enderecoReg)
{
   FILE *arquivoCopia;
   int cabeca;

   arquivoCopia = fopen("dados.dat", "rb+");
   fread(&cabeca, sizeof(int), 1, arquivoCopia);

   if (cabeca != enderecoReg)
   {
      cabeca = enderecoReg;
      fseek(arquivoCopia, 0, SEEK_SET);
      fwrite(&cabeca, sizeof(int), 1, arquivoCopia);
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

void impressaoLed()
{
   FILE *arquivoCopia;
   int sizeVetor = 1;
   int offset;

   if ((arquivoCopia = fopen("dados.dat", "rb+")) == NULL)
   {
      printf("Erro na abertura do arquivo --- programa abortado\n");
      exit(EXIT_FAILURE);
   }

   fread(&offset, sizeof(int), 1, arquivoCopia);
   while (offset != -1)
   {
      sizeVetor++;
      fseek(arquivoCopia, (offset + 1), SEEK_SET);
      fread(&offset, sizeof(int), 1, arquivoCopia);
   }
   rewind(arquivoCopia);

   int vetorOffset[sizeVetor], indexV = 0;
   fread(&offset, sizeof(int), 1, arquivoCopia);
   vetorOffset[0] = offset;

   while (offset != -1)
   {
      indexV++;
      fseek(arquivoCopia, (offset + 1), SEEK_SET);
      fread(&offset, sizeof(int), 1, arquivoCopia);
      vetorOffset[indexV] = offset;
   }
   vetorOffset[sizeVetor] = -1;

   for (int i = 0; i < sizeVetor; i++)
   {
      printf("Offsets[%d] = %d bytes\n", i, vetorOffset[i]);
   }

   fclose(arquivoCopia);
}