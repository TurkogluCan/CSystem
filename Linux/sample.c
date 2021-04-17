#include "stdio.h"
#define MAX   100


int main(int argc, char *argv[])
{
	double result;

	result = MAX;
	
	printf("Test %f\n", result);
	
	return 0;
}





/****************************************************** Others
 *  KOD CALSTIRMA ORNEGI:
 *  gcc -E sample.c
 *  
*/

/************************************************ CODE PARTICLES
 * gcc -E sample.c yapılarak derlemeden ve linklemeden önceki, kodun preprocessor kısmı gözlemlenebilmektedir. Bu kısımda # ile belirtilen yerler
 * uygun değerlerle doldurulup farklı bir temp dosyaya yazılıp bu dosya silinip diğer temp dosyanın ismi değiştirilerek daha sonra derleme ve linkelem 
 * işlemi yapılarak tamamlanır. 
 * Preprocessor işlemi sadece #define için değildir. Örneğin kütüphaneyi #include "stdio.h" include edersek, preprocessor derleme yapmadan önce stdio.h
 * kütüphanesinin tamamını kopyalar ve kodun yukarısını yapıştırır. 
 * Deneme için aşağıdaki kod belirtilen şekilde çalıştırılabilir. Fazla satır olduğu için yapmadım.;

gcc -E sample.c

#include "stdio.h"
#define MAX   100


int main(int argc, char *argv[])
{
	double result;

	result = MAX;
	
	printf("Test %f\n", result);
	
	return 0;
} 

 ******************************************************************************************************************************************************
ÇIKTI - 1

ect@ect-virtual-machine:~/Desktop/sample$ gcc -E sample.c
# 1 "sample.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "sample.c"


int printf(const char *format, ...);

int main(int argc, char *argv[])
{
 double result;

 result = 100;

 printf("Test %f\n", result);

 return 0;
}
******************************************************************************************************************************************************
*/