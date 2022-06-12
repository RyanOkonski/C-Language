/*Nome: Ryan Guilherme Okonski dos Santos RA: 124117
  Nome: Lucas Garcia dos Santos           RA: 123851
*/

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