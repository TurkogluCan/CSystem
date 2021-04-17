#include "stdio.h"


int main(void)
{
	int x =
	
	#include "test.h"
	;
	
	printf("Test %d\n", x);
	
	return 0;
}





/****************************************************** Others
 * KOD CALSTIRMA ORNEGI:
 * gcc -o sample sample.c 
 * ./sample
 *  
*/

/************************************************ CODE PARTICLES
 * Bu örnekle birlikte; include edilen #include "test.h" dosyanin, preprocessor tarafından olduğu gibi
 * koda yazıldığı açıkça görülmektedir.
 * 
 * test.h içerisinde 10 yazmaktadır.

 ******************************************************************************************************************************************************
 * Kod bu şekilde çalıştırılarak preprocessorun ne yazdığı gösterilebilir.
 * gcc -E sample.c 
 * ./sample
 * 
 * ÇIKTI : 
 ***************************
 ...
 int main(void)
{
 int x =

# 1 "test.h" 1
10
# 9 "sample.c" 2
 ;

 printf("Test %d\n", x);

 return 0;
}


******************************************************************************************************************************************************
*/