#include "stdio.h"									/* perror da bunun icerisindedir */
#include "stdlib.h"									/* EXIT_FAILURE icin*/
#include "fcntl.h"									/* open icin */
#include "errno.h"									/* errno icin */

void exit_sys(const char *msg);						


int main(int argc, const char *argv[])
{
	int fd;

	if ( (fd=open(argv[1], O_RDWR | O_CREAT )) == -1 )
		exit_sys("open");
		


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
 * gcc -Wall -o sample sample.c 
 * ./sample <dosya ismi>
 * 
 ******************************************************************************************************************************************************
	#include <fcntl.h>

	int open(const char *pathname, int flags);
    int open(const char *pathname, int flags, mode_t mode);

	Aslinda fonksiyonun gercek prototipi;
		int open(const char *pathname, int flags, ...); 
	seklindedir. Buradaki "..." isareti, koyuldugu yerden sonra fonksiyonun birden cok parametre alabilecegi anlamina gelmektedir. "printf(, ...)" de buna ornektir.

	Return:
		On success, open() return the new file descriptor (a nonnegative integer).  On error, -1 is returned and
    errno is set to indicate the error.

	ornek olarak "open" POSIX fonksiyonu kullanilmistir. Bu fonksiyonda hata olmasi durumunda Normal bir POSIX fonksyionu gibi "-1",
	basarili olmasi durumunda ise "0" degerini dondurur. Fakat bazı adres donen POSIX fonksiyonlari hata durumunda NULL da donebilmektedir.

	Bu durumda "open" fonksiyonu kendi icerisinde "errno" degiskenini doldurur. 

	
	open fonksiyonun 2.parametresi için;

	Aşağıdakilerden yalnızca birisi muhakkak kullanılmalıdır.
	O_RDONLY		:Yalnızca okuma
	O_WRONLY		:Yalnızca yazma
	O_RDWR			:Yazma + Okuma

	Aşağıdaki flagler ile yukarıda belirtilen flagler OR'lanarak dosya üzerinde aşağı belirtilenler yapılabilir. Aşağıdaki flagler kendi içinde de OR'lanabilir;
	O_CREAT			:Yoksa yarat, varsa aç 
	O_TRUNC 		:Dosya açılırken silinsin.
	O_EXCL			:Dosya varsa basarisiz ol. O_EXCL tek başına kullanılamaz ancak O_CREAT ile birlikte kullanılabilmektedir.
	O_APPEND		:Dosyadan okuma veya yazma yapilabilir ancak her yazma sonrasi dosya gostericisi dosyanin sonuna konumlanir. 
					 Yani her write islemi dosya sonuna yazilir.



******************************************************************************************************************************************************
*/