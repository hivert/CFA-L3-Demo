// Fichier  : lists_dh.c
// Format   : C file
// Auteur   : Florent Hivert
// A propos : CFA L3 Algo
// Date     : mar. oct. 18 23:38:28 CEST 2011
/******************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "lists_dh.h"

cell *alloc_cell(void)
{
  cell *pCl;

  if ((pCl=(cell*)malloc(sizeof(cell))) == NULL)
    {
      fprintf(stderr,"memory full !");
      exit(1);
    }
  return pCl;
}

cell *create_cell(val_t d)
{
  cell *pCl = alloc_cell();
  pCl->val = d;
  pCl->next = NULL;

  return pCl;
}

void print_ldh(list lst)
{
  while (lst != NULL)
    {
      printf("[%i]->",lst->val);
      lst=lst->next;
    }
  printf("NULL\n");
}

void delete_ldh(list lst)
{
  list tmp;
  tmp = lst;
  lst = lst->next; // skip the dummy head
  tmp->next = NULL;
  while (lst != NULL)
    {
      tmp = lst;
      lst = lst->next;
      free(tmp);
    }
}

long int length_ldh(list lst)
{
   long int  k = 0;
   while (lst->next != NULL)
     {
       lst = lst->next;
       k++;
     }
   return k;
}

inline cell *ith_cell_ldh(list lst, long int i)
{
  while (lst != NULL && i>0)
    {
      lst = lst->next;
      i--;
    }
  return lst;
}

void insert_after(cell *lst, cell* cel)
{
  cel->next = lst->next;
  lst->next = cel;
}

cell *remove_after(cell *lst)
{
  cell *res = lst->next;
  if (lst->next != NULL)
    lst->next = lst->next->next;
  return res;
}

cell *cut_after(cell *lst)
{
  cell *res = lst->next;
  lst->next = NULL;
  return res;
}
