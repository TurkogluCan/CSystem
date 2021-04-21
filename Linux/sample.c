#include "stdio.h"									/* perror da bunun icerisindedir */
#include "stdlib.h"									/* EXIT_FAILURE icin*/
#include "fcntl.h"									/* open icin */
#include "errno.h"									/* errno icin */

void exit_sys(const char *msg);						


int main(void)
{

	int result;
	
	if ( (result = open("test.txt", O_RDONLY)) == -1)
	{
		exit_sys("open fail");
	}

	puts("OK");

	return 0;
}

void exit_sys(const char *msg)						/* Hatali durumlar icin girilen uyari mesaji ve error mesaji yazdirilarak exit yapilir */
{
	perror(msg);
	exit(EXIT_FAILURE);
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

	Bir adimd daha ileri gidilmis olan "perror" yani acilimiyla printerror fonksiyonu, aldigi parametreyi ekrana yazdirir. Sonrasina ":" koyar ve sonrasinda ise 
	hatayi yazdirir. Bu fonksiyon "stdio.h" icerisindedir. Yani Standart C fonksiyonudur.

	Hata yazdirma ve exit yapma islemi tek fonksiyonda toplanmistir.



******************************************************************************************************************************************************
*/