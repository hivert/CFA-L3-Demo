#include<stdlib.h>
#include<stdio.h>

typedef int elem;
void bubble_sort(elem T[], int taille)
{
  int min = 0, max = taille-1, i, nborne;
  elem tmp;
  while (min < max)
    {
      // Invariant les éléments d'indice < min ou > max sont à leurs places
      // Phase montante
      nborne = min;
      for (i=min; i<max; i++)
	if (T[i] > T[i+1])
	  {
	    tmp = T[i]; T[i] = T[i+1]; T[i+1] = tmp;
	    nborne = i;
	  }
      max = nborne;
      // Phase descendante
      nborne = max;
      for (i=max-1; i>=min; i--)
	if (T[i] > T[i+1])
	  {
	    tmp = T[i]; T[i] = T[i+1]; T[i+1] = tmp;
	    nborne = i;
	  }
      min = nborne+1;
    }
}

#define SIZE 20
elem T[SIZE];

static __inline__ unsigned long long GetTick()
{
     register unsigned long long ticks;
     __asm__ __volatile__ ( "rdtsc\nshl $0x20, %%rdx\nor  %%rax,%%rdx"
                : "=d" (ticks) :: "%rax");
     return ticks;
}

void main(void)
{
  int i;
  srandom(GetTick());
  for (i=0; i<SIZE; i++)
    T[i] = random() % 100;
  for (i=0; i<SIZE; i++)
    printf("%i ", T[i]);
  printf("\n");
  printf("Debut \n");
  bubble_sort(T, SIZE);
  printf("Fin \n");
  for (i=0; i<SIZE; i++)
    printf("%i ", T[i]);
  printf("\n");
}
