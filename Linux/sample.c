#include "stdio.h"									/* perror da bunun icerisindedir */
#include "stdlib.h"									/* EXIT_FAILURE icin*/
#include "fcntl.h"									/* open icin, File Control */
#include "errno.h"									/* errno icin */
#include "sys/stat.h"								/* S_I... parametreleri icin */
#include "unistd.h"									/* read ve write icin */ 


//********************************** Define
#define ByteSizeRead		4096

//********************************** Function Prototypes
void exit_sys(const char *msg);						



int main(int argc, const char *argv[])
{
	int     fd;
	char    bufR[ByteSizeRead+1];
	ssize_t resR;

	if ( (fd=open(argv[1], O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1 )
		exit_sys("open");
		
	
	for (;;)
	{
		if ( (resR = read(fd, bufR, 1)) == -1 )
		exit_sys("read");

		if (resR == 0)
		break;

		bufR[resR] = '\0';
		printf("%s", bufR);
	}
	

	puts("Success");

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
	---------------------------------------------------- R E A D ----------------------------------------------------
	#include <unistd.h>     // standard symbolic constants and types 

    ssize_t read(int fd, void *buf, size_t count);

	Param:
	------	
	int fd      	---> File descriptor
	void *buf   	---> Dosyadan okunup doldurulacak olan buffer
	size_t count	---> Okunacak olan byte sayisi

	Dosya gostericisinin bulundugu yerden itibaren verilen byte sayisi kadar belirtilen dosyadan okuma yapar ve buf'i doldurur.
	read() attempts to read up to count bytes from file descriptor fd into the buffer starting at buf.

	Return:
	-------
	Okyabildigi byte sayisina geri doner. Ornegin verilen byte sayisi kadar okunmus, dosya sonlanmis ve hala okunacak byte sayisina ulasilamamissa bu bir hata 
	degildir. 	
	Eger ornegin bir dosya 100byte olsun ve dosya gostericisi de 50.byte'da yer alsın. Eger dosyadan 100Byte okunmak istenirse fonksiyonun donus degeri okuyabildigi
	byte sayisi olan 50 olacaktir. Cunku EOF ile karsilasmis, dosyanin sonuna gelmistir.

	   On success, the number of bytes read is returned (zero indicates
       end of file), and the file position is advanced by this number.
	   On error, -1 is returned, and errno is set to indicate the error.
       In this case, it is left unspecified whether the file position
       (if any) changes.

       It is not an error if this number is smaller than the number of
       bytes requested; this may happen for example because fewer bytes
       are actually available right now (maybe because we were close to
       end-of-file, or because we are reading from a pipe, or from a
       terminal), or because read() was interrupted by a signal.  See
       also NOTES.


	---------------------------------------------------- W R I T E ----------------------------------------------------
	#include <unistd.h>     // standard symbolic constants and types 

    ssize_t write(int fd, const void *buf, size_t count);

	Param:
	------	
	int fd      	---> File descriptor
	void *buf   	---> Dosyadan okunup doldurulacak olan buffer
	size_t count	---> Okunacak olan byte sayisi

	Dosya gostericisinin bulundugu yerden itibaren verilen byte sayisi kadar belirtilen dosyaya belirtilen buf'i yazar.
	write() writes up to count bytes from the buffer starting at bufto the file referred to by the file descriptor fd.

	Return:
	-------
	Yazabildigi byte sayisina geri doner. 

		On success, the number of bytes written is returned.  On error,
       -1 is returned, and errno is set to indicate the error.

	---------------------------------------------------- O P E N ----------------------------------------------------
	#include <fcntl.h>				//File Control
	 
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


	open fonksiyonun 3.parametresi, dosyanin erisim haklarini belirlemektedir. 
	O_ parametreleri #include <fcntl.h> kutuphanesinde bulunmasina ragmen S_I parametreleri asagidaki kutuphanede bulunmaktadir;
	#include <sys/stat.h>

	!!!!!! Eger dosya zaten yaratilmişsa erişim haklarına girilmesi anlamsız olur. Bu sabitlerin kullanilmasinin anlamli olabilmesi icin
	yeni bir dosya yaratilmasi gerekmektedir. Yeni dosya yaratilirken verilen sembolik sabitlerdeki erisim haklarina sahip dosya yaratilmaktadir. Olan bir
	dosyanin erisim haklarini degistirmez !!!!!! Bu yuzden 3.parametre kullanilacaksa 2.paremetrede "O_CREAT" kullanilmasi anlamli olur. 
	
	Erisim haklarini belirlemede kullanilan sembolik sabitler;

	S_IRUSR
	S_IWUSR
	S_IXUSR

	S_IRGRP
	S_IWGRP
	S_IXGRP

	S_IROTH
	S_IWOTH
	S_IXOTH

	Ayrıca bu sembolik sabitlerin dışında aşağıdaki üç sembolik sabit de bulunmaktadır:

  	S_IRWXU
	S_IRWXG
	S_IRWXO

	Bu sembolik sabitler aslında aşağıdakilerle eşdeğerdir:

	#define S_IRWXU (S_IRUSR|S_IWUSR|S_IXUSR)
	#define S_IRWXG (S_IRGRP|S_IWGRP|S_IXGRP)
	#define S_IRWXO (S_IROTH|S_IWOTH|S_IXOTH)



	Bu sembolik sabitlerin hepsinin başının S_I ile başladığına dikkat ediniz. Bunu R, W ve X harfleri, bunu da USR, GRP ya da OTH karakterleri izlemektedir. 

	Ornek olarak;
					S_I R USR
						W GRP
						X OTH

	Bu sembolik sabitler OR'lanarak kullanilabilmektedir. Ornegin;

	S_IRUSR | S_IWUSR   ---> Sadece User icin Read ve Write hakki verilmis, Group ve Other icin erisim hakkı verilmemis.
	Bu durumda erisim haklari -r-------- seklinde olacaktir. 

	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH   ---> User icin okuma ve yazma, group ve other icin sadece okuma hakkı verilmistir.
	Bu durumda erisim haklari -rw-r--r-- seklinde olacaktir. 


******************************************************************************************************************************************************
*/