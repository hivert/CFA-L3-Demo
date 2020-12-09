// Fichier  : list_dh.h
// Format   : C header file
// Auteur   : Florent Hivert
// A propos : CFA L3 Algo
// Date     : mar. oct. 18 23:38:28 CEST 2011
/******************************************************/


#ifndef _LIST_DH_H
#define _LIST_DH_H

typedef int val_t;

struct s_cell
{
  val_t   val;
  struct s_cell * next;
};
typedef struct s_cell cell;
typedef struct s_cell *list;
// Convention:
//   a variable declared as a list has a dummy head
//   a variable declared as a cell * has no dummy head


cell *alloc_cell(void);
cell *create_cell(val_t d);
void print_ldh(list lst);
void delete_ldh(list lst);
long int length_ldh(list p);
cell *ith_cell_ldh(list lst, long int i);
void insert_after(cell *lst, cell* cel);
cell *remove_after(cell *lst);
cell *cut_after(cell *lst);

#endif


