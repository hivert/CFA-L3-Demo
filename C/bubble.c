#include<stdlib.h>
#include<stdio.h>

typedef int elem;
void bubble_sort(elem T[], int taille)
{
  int i, sorted;
  elem tmp;

  do
    {
      sorted = 1;
      for (i=0; i < taille-1; i++)
	if (T[i] > T[i+1])
	  {
	    tmp = T[i]; T[i] = T[i+1]; T[i+1] = tmp;
	    sorted = 0;
	  }
    } while (!sorted);
}


void bubble_sort_2(elem T[], int taille)
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


#define SIZE 20
elem T[SIZE], T0[SIZE];

static __inline__ unsigned long long GetTick()
{
     register unsigned long long ticks;
     __asm__ __volatile__ ( "rdtsc\nshl $0x20, %%rdx\nor  %%rax,%%rdx"
                : "=d" (ticks) :: "%rax");
     return ticks;
}

int main(void)
{
  unsigned long long deb, fin;
  int i, rep;
  srandom(GetTick());
  for (i=0; i<SIZE; i++)
    T0[i] = random() % 100;
  for (i=0; i<SIZE; i++)
    printf("%i ", T0[i]);
  printf("\n");
  for (rep=0; rep<20; rep++) {
    for (i=0; i<SIZE; i++) T[i] = T0[i];
    deb = GetTick();
    bubble_sort_2(T, SIZE);
    fin = GetTick();
    for (i=0; i<SIZE; i++)
      printf("%i ", T[i]);
    printf("Time = %llu \n", fin-deb);
  }
  return EXIT_SUCCESS;
}
