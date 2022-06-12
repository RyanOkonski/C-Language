#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ABB_.c"

int main()
{
  ARVORE *arv;
  arv = criar_arvore();
  menu(arv);
  return 0;
}