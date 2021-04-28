#include "stdio.h"									/* perror da bunun icerisindedir */
#include "stdlib.h"									/* EXIT_FAILURE icin*/
#include "fcntl.h"									/* open icin, File Control */
#include "errno.h"									/* errno icin */
#include "sys/stat.h"								/* S_I... parametreleri icin */
#include "unistd.h"									/* read ve write icin */ 
//********************************** Define


//********************************** Function Prototypes
void exit_sys(const char *msg);						






int main(void)
{

	int fd;

	/* umask(S_IWUSR|S_IWOTH);		default umask, kabuk maskesi. Belki degisebilir de. Farkli konsol umask degerleri icin dosya erisim haklarini
									gozlemle. Dosya erisim haklarinin degismesi icin dosyanin yaratilmasi gerekmekte. */

	umask(0);

	if ((fd = open("umask_test.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) == -1)
		exit_sys("open");

	close(fd);

	printf("OK\n");

	return 0;
}

void exit_sys(const char *msg)						
{
	perror(msg);
	exit(EXIT_FAILURE);
}












/****************************************************** Others
 * KOD CALSTIRMA ORNEGI:
 * gcc -Wall -o sample sample.c 
 * ./sample 
 * 
 ******************************************************************************************************************************************************
	
	---------------------------------------------------- U M A S K ----------------------------------------------------
	
		!!! UMASK SADECE ERİŞİM HAKLARINI MASKELEMEKTEDİR. UMASK İLE ERİŞİM HAKLARI DEĞİŞTİRİLMEZ, MASKELENİR !!!
	
	UNIX/Linux sistemlerinde open fonksiyonun üçüncü parameresinde verilen erişim hakları nihai durumu belirtmemektedir. Nihai durum üçüncü
	parametrede belirtilen erişim haklarının prosesin umask değeri ile işleme sokulmasıyla belirlenir. umask değerindeki set edilen bayraklar 
	open fonksiyınunda belirtilse bile dikkate alınmayacak hakları belirtir. open dışında bazı diğer yaratıcı POSIX fonksiyonları da umask değerini
	dikkate almaktadır. umask değeri üst prosesten alt prosese aktarılmaktadır. Shell prosesinin default umask değeri 022'dir. (Yani S_IWUSR|S_IWGRP)
	Proses kendi umask değerini umask isimli POSIX fonksiyonuyla değiştirebilemketdri 

		#incude <sys/stat.h>
		
		mode_t umask(mode_t mask);

	Aşağıdaki programda prosesin umask değeri 0 yapılarak maske ortadan kaldırılmıştır. 

	Shell prosesinin umask değeri umask shell komutuyla alınıp değiştirilebilmektedir.


	EGER ISTENIRSE DOSYA ERISIM HAKLARI "chmod" ile degistirilebilmektedir.
******************************************************************************************************************************************************
*/