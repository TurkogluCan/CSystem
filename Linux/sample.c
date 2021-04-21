#include "stdio.h"
#include "stdlib.h"									/* EXIT_FAILURE icin*/
#include "fcntl.h"									/* open icin */
#include "errno.h"									/* errno icin */
#include "string.h"									/* strerror icin */


int main(void)
{

	int result;
	
	if ( (result = open("test.txt", O_RDONLY)) == -1)
	{
		fprintf(stderr, "Open fail: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	puts("OK");

	return 0;
}





/****************************************************** Others
 * KOD CALSTIRMA ORNEGI:
 * gcc -o sample sample.c 
 * ./sample
 * 
 ******************************************************************************************************************************************************
	ornek olarak "open" POSIX fonksiyonu kullanilmistir. Bu fonksiyonda hata olmasi durumunda Normal bir POSIX fonksyionu gibi "-1",
	barasili olmasi durumunda ise "0" degerini dondurur. Fakat bazı adres donen POSIX fonksiyonlari hata durumunda NULL da donebilmektedir.

	Bu durumda "open" fonksiyonu kendi icerisinde "errno" degiskenini doldurur. Doldurulan bu sayısal deger bir hata koduna denk gelmektedir.
	Bu hata kodu ise "strerror(errno)" fonksiyonuyla yapilmaktadir. Bu fonksiyon errno giris parametresini alarak ilgili hata kodunun adresini
	doner, biz de bu adresi string olarak yazdiririz.



******************************************************************************************************************************************************
*/