#include "stdio.h"									/* perror da bunun icerisindedir */
#include "stdlib.h"									/* EXIT_FAILURE icin*/
#include "errno.h"									/* errno icin */
#include "sys/stat.h"								/* S_I... parametreleri ve chmod icin */
#include "fcntl.h"									/* open fcn */
#include "unistd.h"									/* close fcn */
//********************************** Define


//********************************** Function Prototypes
void exit_sys(const char *msg);						





int main(void)
{
	int fd, res;

	if ( (fd = open("deneme.txt", O_RDONLY | O_CREAT, S_IRUSR|S_IWUSR)) == -1 )
		exit_sys("open");
	
	/* open ile acilmis veya yaratilmis olan dosyanin erisim haklarini degistirir. */
	if ( (res=fchmod(fd,  S_IRUSR|S_IWUSR | S_IRGRP|S_IROTH)) == -1 )
		exit_sys("fchmod");



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
   	Var olan bir dosyanin erisim haklarini belirtilen gibi yapar. 
   		Eger dosyanin etkin kullanici id'si, programi calistiran processle 
	ayni degilse erisim haklari degistirilemez.
	
		Ya etkin kullanici id'leri ayni olmali, 
		Ya da processin etkin kullanici id'si root(0) olmalidir.
 
 Ornegin;

 >> sudo touch deneme.txt 
 komutu ile programin calistirilma dizininde, daha onceden olmayan bir "deneme.txt" dosyasi yaratin.
 
 >> ls -l deneme.txt 
 komutu ile deneme.txt dosyasinin etkin user id'sinin "root" olduğunu görün.

 sample.c programindaki chmod fcn ornek olarak "chmod("deneme.txt", S_IRUSR|S_IWUSR)" olsun ve programi
 >>./sample 
 olarak calistirn.

 	Eger sudo(root) olarak yaratilan bir dosyanin erisim haklari farklı ve sıradan bir kullanıcı tarafından 
 degistirilmek istenirse bu mümkün değildir, program hata verecektir.
 
 >>sudo ./sample 
 olarak calistir.

	Eger sudo ile calistirilirsa artik processin etkin user id'si 0 olacagi icin program calisip erisim haklari
	degistirilecektir.

Fakat bu olay tam ters şekilde yapılsaydı, yani sıradan bir process dosyayi yaratsa ve root değiştirmek isteseydi,
sikintş yaşanmayacakti. Cunku root her seyi yapabilir.
 ******************************************************************************************************************************************************
	
	---------------------------------------------------- f c h m o d ----------------------------------------------------
	
	-> fchmod isimli POSIX fonksiyonu open ile acilmis veya yaratilmis olan bir dosyanın erişim haklarını değiştirmek için kullanılır. 
	   Change the file modes. 

	-> fchmod fonksiyonu tamamen chmod fonksiyonu gibidir. Ancak açılmış dosyanın dosya betimleyicisindne hareketle dosyanın erişim haklarını değiştirir. 
	 Yani birisi dosyanın yolunu alır, diğeri ise file descriptor’ı alır. 
	 Yani elimizde zaten open fonksiyonuyla açmış olduğumuz bir dosya varsa biz fchmod fonksiyonuyla bu dosyanın erişim haklarını hemen değiştirebiliriz.
	 Bu fonksiyonun chmod fonksiyonundan daha hızlı çalışacağı varsayılabilir
	
	Prototype:
	----------
	#include <sys/stat.h>
	int fchmod(int fd, mode_t mode);


	Param:
	------	
	fd      	---> File Descriptor
	mode     	---> Dosyaya verilecek olan yeni erisim haklari, S_I...

	Return:
	-------
	Yazabildigi byte sayisina geri doner. 

		On success, the number of bytes written is returned.  
		On error, -1 is returned, and errno is set to indicate the error.



******************************************************************************************************************************************************
*/