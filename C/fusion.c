#include<stdlib.h>
#include<stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>


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

  printf("Real Time: %2.9fs, CPU tick %11li\n",
	 diff_time.tv_sec + diff_time.tv_nsec/1.0e+9,
	 diff, diff/CLOCK_FREQ);
}



typedef int elem;




void bubble_sort(elem T[], int taille)
{
  int i, max, nmax;
  elem tmp;

  max = taille - 2;
  do
    {
      // Les elements d'indices max+1...taille-1 sont les plus grands
      // et sont triees.
      nmax = -1;
      for (i=0; i <= max; i++)
        if (T[i] > T[i+1])
          {
            tmp = T[i]; T[i] = T[i+1]; T[i+1] = tmp;
            nmax = i;
          }
      max = nmax - 1;
    } while (max >= 0);
}

void insert_sort_min_max(elem T[], int min, int max)
{
  elem Tmp;
  int i,j;
  for (i=min+1; i<=max; i++)
    {
      Tmp = T[i];
      j=i;
      while ((j>min) && (T[j-1] > Tmp))
	{
	  T[j] = T[j-1];
	  j--;
	}
      T[j] = Tmp;
    }
}

void insert_sort(elem T[], int taille)
{
  insert_sort_min_max(T, 0, taille-1);
}

void merge(elem T1[], int min1, int max1,
	   elem T2[], int min2, int max2,
	   elem T[])
/* T est alloué de taille (max1 - min1 + 1) + (max2 - min2 + 1) */
{
  int i1, i2, i;
  i1 = min1; i2 = min2; i = 0;
  while ((i1 <= max1) && (i2 <= max2))
    {
      if (T1[i1] < T2[i2])
	{
	  T[i] = T1[i1]; i++; i1++;
	}
      else
	{
	  T[i] = T2[i2]; i++; i2++;
	}
    }
  if (i1 <= max1)
    do
      {
        T[i] = T1[i1]; i++; i1++;
      }
    while (i1 <= max1);
  else
    do
      {
	T[i] = T2[i2]; i++; i2++;
      }
    while (i2 <= max2);
}


void merge_sort_rec(elem T[], int min, int max, elem Tmp[])
{
  int mid, i, itmp;
  if (min < max)
    {
      mid = (min + max)/2;
      merge_sort_rec(T, min, mid, Tmp);
      merge_sort_rec(T, mid+1, max, Tmp);
      merge(T, min, mid, T, mid+1, max, Tmp);
      for(i=min, itmp=0;
	  i <= max;
	  i++,   itmp++)
	T[i] = Tmp[itmp];
    }
}

void merge_sort(elem T[], int taille)
{
  elem *Tmp = (elem *) malloc(taille*sizeof(elem));
  merge_sort_rec(T, 0, taille-1, Tmp);
  free(Tmp);
}

#define SEUIL 200

void merge_insert_sort_rec(elem T[], int min, int max, elem Tmp[])
{
  int mid, i, itmp;
  if (max - min < SEUIL)
    insert_sort_min_max(T, min, max);
  else
    {
      mid = (min + max)/2;
      merge_insert_sort_rec(T, min, mid, Tmp);
      merge_insert_sort_rec(T, mid+1, max, Tmp);
      merge(T, min, mid, T, mid+1, max, Tmp);
      for(i=min, itmp=0;
	  i <= max;
	  i++,   itmp++)
	T[i] = Tmp[itmp];
    }
}

void merge_insert_sort(elem T[], int taille)
{
  elem *Tmp = (elem *) malloc(taille*sizeof(elem));
  merge_insert_sort_rec(T, 0, taille-1, Tmp);
  free(Tmp);
}

void time_and_check_sort(char* name, void sort(), int l)
{
  long int i;
  int *tab = (int*) malloc(l*sizeof(int));
  printf(name);
  for (i=0; i<l; i++)
    {
      tab[i+1] = random();
    }

  start_clock();
  sort(tab, l);
  end_clock(l);
  for (i=0; i<l-1; i++)
    if (tab[i] > tab[i+1])
      {
	fprintf(stderr, "BUG: The list is not sorted !\n");
	exit(EXIT_FAILURE);
      }
  free(tab);
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
	time_and_check_sort("Insert:    ", insert_sort, l);
	time_and_check_sort("Bubble:    ", bubble_sort, l);
	}
      time_and_check_sort(  "Merge:     ", merge_sort, l);
      time_and_check_sort(  "MergeIns:  ", merge_insert_sort, l);
    }
  return EXIT_SUCCESS;
}
