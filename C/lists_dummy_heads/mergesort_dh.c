#include <stdio.h>
#include <stdlib.h>
#include "mergesort_dh.h"

int is_sorted_ldh(list lst)
{
  lst = lst->next; // skip the dummy head
  while (lst->next != NULL)
    {
      if (lst->val > lst->next->val)
	return 0;
      lst = lst->next;
    }
  return 1;
}

void insert_cell_sorted_ldh(list lst, cell *cel)
// Isert the cell cel at the proper place in the sorted list lst
// The list lst has a dummy head
{
  while ((lst->next != NULL) && (lst->next->val < cel->val))
    lst = lst->next;
  cel->next = lst->next;
  lst->next = cel;
}

void insert_sort_ldh(list lst)
{
  list res = lst, tmp;
  lst = lst->next;
  res->next = NULL;
  while (lst != NULL)
    {
      tmp = lst->next;
      insert_cell_sorted_ldh(res, lst);
      lst = tmp;
    }
}

cell *cut_half_ldh(list lst)
// Cut the list lst in the middle
// The list lst has a dummy head
// the returned list is a bunch of cells without a dummy head
{
  list cur2 = lst; // advance cur2 twice as fast a lst
  while (cur2->next != NULL)
    {
      cur2=cur2->next;
      if (cur2->next != NULL)
	{
	  cur2=cur2->next;
	  lst=lst->next;
	}
    }
  // reuse cur2 as result
  cur2 = lst->next;
  lst->next = NULL;
  return cur2;
}

cell *cut_after_ith_cell_ldh(list lst, long int i)
{
  cell *res;
  while (lst != NULL && i>0)
    {
      lst = lst->next;
      i--;
    }
  res  = lst->next;
  lst->next = NULL;
  return res;
}

void merge_ldh(list l1, cell *l2)
// Merge the sorted list l2 into the sorted list l1
// The list l1 has a dummy head
// l2 is a bunch of cells without a dummy head
{
  list endres = l1; // the last cell of the constructed list
  l1 = l1->next;    // skip the the fake head from l1
  while ((l1 != NULL) && (l2 != NULL))
    {
      if (l1->val <= l2->val)
	{
	  endres->next = l1;
	  l1 = l1->next;
	}
      else
	{
	  endres->next = l2;
	  l2 = l2->next;
	}
      endres = endres->next;
    }
  if (l1 == NULL) endres->next = l2;
  else            endres->next = l1;
}

void merge_sort_ldh(list lst)
// Sort the list lst
// The list lst has a dummy head
// The tricky part is to avoid allocating more dummy head
{
  cell *pcells, *ptmp;

  // Nothing to do on empty or one cell list
  if ((lst->next == NULL) || (lst->next->next == NULL)) return;
  pcells = cut_half_ldh(lst);
  merge_sort_ldh(lst);
  ptmp = lst->next; // switch the dummy head
  lst->next = pcells;
  merge_sort_ldh(lst);
  merge_ldh(lst, ptmp);
}

void merge_sort_len_rec(list lst, long int length)
// Sort the list lst
// The list lst has a dummy head
// lenght must be the length of the list lst (not counting the dh)
// The tricky part is to avoid allocating more dummy head
{
  long int l2;
  cell *pcells, *ptmp;

  // Nothing to do on empty or one cell list
  if (length < 2) return;
  l2 = length >> 1;
  pcells = cut_after_ith_cell_ldh(lst, l2);
  merge_sort_len_rec(lst, l2);
  ptmp = lst->next; // switch the dummy head
  lst->next = pcells;
  merge_sort_len_rec(lst, length - l2);
  merge_ldh(lst, ptmp);
}

void merge_sort_len_ldh(list lst)
// Sort the list lst
// The list lst has a dummy head
{
  merge_sort_len_rec(lst, length_ldh(lst));
}

void merge_sort_ins_rec(list lst, long int length)
// Sort the list lst
// The list lst has a dummy head
// lenght must be the length of the list lst (not counting the dh)
// The tricky part is to avoid allocating more dummy head
{
  long int l2;
  cell *pcells, *ptmp;

  // on short lists simply call insertion sort
  if (length < 100)
    {
      insert_sort_ldh(lst);
      return;
    }
  l2 = length >> 1;
  pcells = cut_after_ith_cell_ldh(lst, l2);
  merge_sort_ins_rec(lst, l2);
  ptmp = lst->next; // switch the dummy head
  lst->next = pcells;
  merge_sort_ins_rec(lst, length - l2);
  merge_ldh(lst, ptmp);
}

void merge_sort_ins_ldh(list lst)
// Sort the list lst
// The list lst has a dummy head
{
  merge_sort_ins_rec(lst, length_ldh(lst));
}
