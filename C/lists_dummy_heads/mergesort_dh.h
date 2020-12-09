// Fichier  : mergesort_dh.h
// Format   : C header file
// Auteur   : Florent Hivert
// A propos : CFA L3 Algo
// Date     : mar. oct. 18 23:38:28 CEST 2011
/******************************************************/

#ifndef _MERGE_SORT_DH_H
#define _MERGE_SORT_DH_H

#include "lists_dh.h"

int is_sorted_ldh(list lst);
void insert_cell_sorted_ldh(list lst, cell *cel);
void insert_sort_ldh(list lst);

cell *cut_half_ldh(list lst);
void merge_ldh(list l1, cell *l2);
void merge_sort_ldh(list lst);
void merge_sort_len_rec(list lst, long int length);
void merge_sort_len_ldh(list lst);
void merge_sort_ins_rec(list lst, long int length);
void merge_sort_ins_ldh(list lst);

#endif
