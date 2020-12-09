#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include "mergesort_dh.h"


static __inline__ unsigned long long GetTick()
{
     register unsigned long long ticks;
     __asm__ __volatile__ ( "rdtsc\nshl $0x20, %%rdx\nor  %%rax,%%rdx"
                : "=d" (ticks) :: "%rax");
     return ticks;
}
struct timespec before_time, after_time, diff_time;
long before, after;


long int timespec_subtract (struct timespec *result,
		       struct timespec * x,
		       struct timespec * y)
{
  /* Perform the carry for the later subtraction by updating y. */
  if (x->tv_nsec < y->tv_nsec) {
    long int nsec = (y->tv_nsec - x->tv_nsec) / 1000000000 + 1;
    y->tv_nsec -= 1000000000 * nsec;
    y->tv_sec += nsec;
  }
  if (x->tv_nsec - y->tv_nsec > 1000000000) {
    long int nsec = (x->tv_nsec - y->tv_nsec) / 1000000000;
    y->tv_nsec += 1000000000 * nsec;
    y->tv_sec -= nsec;
  }

  /* Compute the time remaining to wait.
     tv_nsec is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_nsec = x->tv_nsec - y->tv_nsec;

  /* Return 1 if result is negative. */
  return x->tv_sec < y->tv_sec;
}


void start_clock()
{
  clock_gettime(CLOCK_MONOTONIC, &before_time);
  before = GetTick();
}


#define CLOCK_FREQ (2.0e+9)

void end_clock(int l)
{
  long diff;
  after = GetTick();
  clock_gettime(CLOCK_MONOTONIC, &after_time);
  diff = after - before;

  timespec_subtract(&diff_time, &after_time, &before_time);

  printf("Real Time: %2.9fs, CPU tick %11li, %2.9f ratio=%f\n",
	 diff_time.tv_sec + diff_time.tv_nsec/1.0e+9,
	 diff, diff/CLOCK_FREQ, diff/CLOCK_FREQ*1000.0/l);
}


void time_and_check_sort_cache_problem(void sort(), int l)
{
  long int i;

  cell fake_head = { 0, NULL};
  list lst = &fake_head, tmpl = NULL;
  for (i=0; i<l; i++)
    {
      tmpl = create_cell(random());
      tmpl->next = lst->next;
      lst->next = tmpl;
    }

  start_clock();
  sort(lst);
  end_clock(l);
  if (!is_sorted_ldh(lst))
    {
      fprintf(stderr, "BUG: The list is not sorted !\n");
      exit(EXIT_FAILURE);
    }
  if (length_ldh(lst) != l)
    {
      fprintf(stderr, "BUG: some elements were lost !\n");
      exit(EXIT_FAILURE);
    }
  delete_ldh(lst);
  lst->next=NULL;
}


void time_and_check_sort(void sort(), int l)
{
  long int i;
  list lst = (list) malloc((l+1)*sizeof(cell));
  for (i=0; i<l; i++)
    {
      lst[i].next = lst+i+1;
      lst[i+1].val = random();
    }
  lst[l].next = NULL;

  start_clock();
  sort(lst);
  end_clock(l);
  if (!is_sorted_ldh(lst))
    {
      fprintf(stderr, "BUG: The list is not sorted !\n");
      exit(EXIT_FAILURE);
    }
  if (length_ldh(lst) != l)
    {
      fprintf(stderr, "BUG: some elements were lost !\n");
      exit(EXIT_FAILURE);
    }
  free(lst);
}


int main(void)
{
  long int l, seed;
  seed = GetTick();
  srandom(seed);
  printf("Init clock:        ");
  start_clock(); end_clock(1);
  //  for (l=1; l<200; l+=2)
  for (l=1; l<10000000; l=l<<1)
    {
      printf("len = %10li\n", l);
      if (l < 50000)
	{
	  printf("Insert:    "); time_and_check_sort(insert_sort_ldh, l);
	}
      printf("Merge:     "); time_and_check_sort(merge_sort_ldh, l);
      printf("Merge len: "); time_and_check_sort(merge_sort_len_ldh, l);
      printf("Merge ins: "); time_and_check_sort(merge_sort_ins_ldh, l);
    }
  return EXIT_SUCCESS;
}
