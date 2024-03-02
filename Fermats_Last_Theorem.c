#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "gmp.h"
/*
	Author: Simone Remoli
	Programming: Fermat's_Last_Theorem  -> A^n + B^n = C^n
*/

union uny
{
	struct fermat
	{
		mpz_t n;
		mpz_t a;
		mpz_t b;
		mpz_t c;
	}fermat_theorem;
};

void setting(mpz_t, mpz_t, mpz_t, mpz_t*,mpz_t*,mpz_t*);
void teorema_di_fermat(mpz_t,mpz_t,mpz_t,mpz_t,void(*)(mpz_t, mpz_t, mpz_t, mpz_t*,mpz_t*,mpz_t*));
int main(int argc, char **argv)
{
	union uny unyy;
	mpz_t due; mpz_init_set_str(due, "2", 10);
	void(*ptr)(mpz_t, mpz_t, mpz_t, mpz_t*,mpz_t*,mpz_t*)  = setting;//pointer to function
	fputs(" \t A^n + B^n = C^n.  | n > 2 \n",stdout);
	mpz_init_set_str(unyy.fermat_theorem.a, "0", 10);
	mpz_init_set_str(unyy.fermat_theorem.b, "0", 10);
	mpz_init_set_str(unyy.fermat_theorem.c, "0", 10);
	printf("\n");
	do{
		puts(" ");
		fprintf(stdout,"\t Insert n > 2 !\n");
		gmp_printf("Insert the exponent n to prove Fermat's_Last_Theorem: ");
		gmp_scanf("%Zd", unyy.fermat_theorem.n);
	}while(mpz_cmp(unyy.fermat_theorem.n,due)<=0);
	gmp_printf("A: ");
	gmp_scanf("%Zd", unyy.fermat_theorem.a);
	gmp_printf("B: ");
	gmp_scanf("%Zd", unyy.fermat_theorem.b);
	gmp_printf("C: ");
	gmp_scanf("%Zd", unyy.fermat_theorem.c);
	teorema_di_fermat(unyy.fermat_theorem.n,unyy.fermat_theorem.a,unyy.fermat_theorem.b,unyy.fermat_theorem.c,ptr);
	return 0;
}
void teorema_di_fermat(mpz_t n, mpz_t a, mpz_t b, mpz_t c, void(*ptrf)(mpz_t, mpz_t, mpz_t, mpz_t*,mpz_t*,mpz_t*))
{
	union uny uny1;
	mpz_t i,uno; mpz_init_set_str(uno, "1", 10);
	mpz_t** array_pointer =(mpz_t**)malloc(sizeof(mpz_t*)*3);
	array_pointer[0] = &uny1.fermat_theorem.a;
	array_pointer[1] = &uny1.fermat_theorem.b;
	array_pointer[2] = &uny1.fermat_theorem.c;

	(*ptrf)(a,b,c,array_pointer[0],array_pointer[1],array_pointer[2]);

	for(mpz_init_set_str(i, "1", 10);  mpz_cmp(i,n)!=0;  mpz_add(i,i,uno))
	{
		mpz_mul(a, a, *array_pointer[0]);
		mpz_mul(b, b, *array_pointer[1]);
		mpz_mul(c, c, *array_pointer[2]);

	}
	gmp_printf("Valore %Zd ^ %Zd = %Zd \n", *array_pointer[0],n,a);
	gmp_printf("Valore %Zd ^ %Zd = %Zd \n", *array_pointer[1],n,b);
	gmp_printf("Valore %Zd ^ %Zd = %Zd \n", *array_pointer[2],n,c);

	if(mpz_cmp(a,b)==0)
	{
		if(mpz_cmp(b,c)==0)
		{
			gmp_printf("Dimostrato per n = %Zd con a = %Zd, b = %Zd, c = %Zd\n", n,a,b,c);
		}
	}
}
void setting(mpz_t a, mpz_t b, mpz_t c, mpz_t* ar0,mpz_t* ar1,mpz_t* ar2)
{
	mpz_init_set_str(*ar0, "0", 10);
	mpz_init_set_str(*ar1, "0", 10);
	mpz_init_set_str(*ar2, "0", 10);
	mpz_set(*ar0,a);
	mpz_set(*ar1,b);
	mpz_set(*ar2,c);
}