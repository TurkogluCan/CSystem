#define MAX   100

int printf(const char *format, ...);

int main(int argc, char *argv[])
{
	double result;

	result = MAX;
	
	printf("Test %f\n", result);
	
	return 0;
}





/****************************************************** Others
 *  KOD CALSTIRMA ORNEGI:
 *  ./sample
*/

/************************************************ CODE PARTICLES
 * Eger dosya aşağıdaki gibi çalıştırılırsa sqrt fonksiyonun prototipi 
 * gösterilmediği için otomatik olarak
 * int geri dönüş değerine sahip, default olarak c'de belirtilen bir prototip 
 * yaratilir ve program çalıştırıldığında saçma bir sonuç verir.
 * 
 * Eğer sqrt prototipi düzgün bir şekilde verilirse;
 * double sqrt(double a);
 * fonksiyon düzgün bir şekilde çıktı verecektir. 
 * 
 * #include "math.h" dosyasi çağırılarak ise double sqrt(double xxx) fonksiyonunun prototipi yazılmış olur. 
 * El ile yazmaktan hiçbir farkı yoktur. 
 * sqrt'nin kodları derlenmiş bir şekilde zaten kütüphanelerde bulunmaktadır. 
 * 
 * 
 * Benzer durum printf icin de yapilmistir.
 * 
 ******************************************************************************************************************************************************
**** YANLIS ******
#include "stdio.h"

int main(int argc, char *argv[])
{
	double result;

	result = sqrt(100);
	printf("Test %f\n", result);
	
	return 0;
}

**** DOGRU ******
#include "stdio.h"

double sqrt(double a);
int main(int argc, char *argv[])
{
	double result;

	result = sqrt(100);
	printf("Test %f\n", result);
	
	return 0;
}

**** DOGRU ******
#include "stdio.h"
#include "math.h"

int main(int argc, char *argv[])
{
	double result;

	result = sqrt(100);
	printf("Test %f\n", result);
	
	return 0;
}


************************************* PRINTF

#define MAX   100

int printf(const char *format, ...);

int main(int argc, char *argv[])
{
	double result;

	result = MAX;
	
	printf("Test %f\n", result);
	
	return 0;
}
*/