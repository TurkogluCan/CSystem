#include "stdio.h"									/* perror da bunun icerisindedir */
#include "stdlib.h"									/* EXIT_FAILURE icin*/
#include "fcntl.h"									/* open icin, File Control */
#include "errno.h"									/* errno icin */
#include "sys/stat.h"								/* S_I... parametreleri icin */
#include "unistd.h"									/* read ve write icin */ 
#include "getopt.h"

//********************************** Define
#define ByteSizeRead		4096

//********************************** Function Prototypes
void exit_sys(const char *msg);						



int main(int argc, char *argv[])
{
	int result, resAcc;
	int flag_n= 0, flag_i= 0, flag_err = 0;

	int index;
	int fdr, fdw; 
	size_t  cntReaded;
	size_t  cntWrited;
	char 	buf[ByteSizeRead+1];
	
	struct option options[] = 
	{
		{"interactive",  no_argument,  NULL,  'i' },
		{"no-clobber", 	 no_argument,  NULL,  'n' },
		{0,0,0,0}
	};
	

	opterr = 0;

	while ( (result = getopt_long(argc, argv, "in", options, &index)) != -1 )				    
	{											
		switch (result)
		{
			case 'i':											

				flag_i = 1;
				break;

			case 'n':							

				flag_n = 1;
				break;
			
			case '?':	/* Invalid option */

				if (optopt != 0)
					fprintf(stderr, "Invalid option.\n");
				else
					fprintf(stderr, "Invalid long option.\n");
				flag_err = 1;
				break;

			default:
				break;
		}
	} 

	if (flag_err)														/* Hatali secenek girisi varsa programdan cikar */
		exit_sys("Hatali secenek girisi");

	
	resAcc = access(argv[optind + 1], F_OK); 

	if ( ((flag_n && flag_i) || flag_n) )
	{
		if (resAcc!=-1)
		{
			fprintf(stderr,"Bu modda var olan dosya uzerine yazilamaz.\n");
			exit(EXIT_FAILURE);
		}
		else
		{
				if( (fdr=open(argv[optind], O_RDONLY)) == -1)
					exit_sys("open -n");

				if( (fdw=open(argv[optind+1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP| S_IROTH)) == -1)
					exit_sys("open -n");

				for (;;)
				{
					if ( (cntReaded = read(fdr, buf, 1)) == -1 )
						exit_sys("read -n");

					if (cntReaded == 0)
					break;
					
					if ( (cntWrited=write(fdw, buf, cntReaded)) == -1 )
						exit_sys("write -n");
				}
		}
	}
	else
	{
		if (resAcc != -1)												/* Dosya varsa */
		{
			char scaned;
			puts("Var olan bir dosya uzerine kopyalamaya devam etmek istiyor musunuz? (y/n)");
			scanf("%c", &scaned);

			if (scaned != 'y' )
				exit_sys("y girmedin");
			else
			{
				if( (fdr=open(argv[optind], O_RDONLY)) == -1)
					exit_sys("open -i");

				if( (fdw=open(argv[optind+1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU)) == -1)
					exit_sys("open -i");

				for (;;)
				{
					if ( (cntReaded = read(fdr, buf, 1)) == -1 )
						exit_sys("read -i");

					if (cntReaded == 0)
					break;
					
					if ( (cntWrited=write(fdw, buf, cntReaded)) == -1 )
						exit_sys("write -i");
				}
			}
		}
	}

	close(fdr);
	close(fdw);

	return 0;
}

void exit_sys(const char *msg)						/* Hatali durumlar icin girilen uyari mesaji ve error mesaji yazdirilarak exit yapilir */
{
	perror(msg);
	exit(EXIT_FAILURE);
}




/****************************************************** Others
 * KOD CALSTIRMA ORNEGI:
 * gcc -Wall -o mycp mycp.c 
 * ./mycp <arguman> <kaynak dosya ismi> <hedef dosya ismi>
 * 
 * ./mycp test.txt mest.txt -n -i
	Bu modda var olan dosya uzerine yazilamaz.

	./mycp test.txt xxxest.txt -n

	./mycp  test.txt mest.txt -i
	Var olan bir dosya uzerine kopyalamaya devam etmek istiyor musunuz? (y/n)
	y


	Kendi dosya kopyalama fonksiyonumu yaptik. Girilecek olan -i(--interactive) ve -n(no-clobber) argumanlari ile kaynak dosyanin okunup hedef dosyaya
	yazdirilma islemi gerceklestirilmistir. 
	close fonksiyonu kullanilarak dosya kapatilmistir.
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


	---------------------------------------------------- L S E E K ----------------------------------------------------
	#include <unistd.h>     // standard symbolic constants and types 

	off_t lseek(int fildes, off_t offset, int whence);

	Param:
	------	
	int fildes      ---> File descriptor
	off_t offset    ---> Konumlandirma ofseti (<0 ise bulunulan yerden geriye >=0 ise ileriye dogru gidilir.)
	int fildes      ---> Konumlandirma orjini

	Konumlandirma orjinine kadar belirtilen offset degeri kadar fildes'in gosterdigi dosya uzerinde imlec konumlandirilir.

	lseek - move the read/write file offset. 
	
	The lseek() function shall set the file offset for the open file description associated with the file descriptor fildes, as follows:
		If whence is SEEK_SET, the file offset shall be set to offset bytes and offset must be positive number. 
		If whence is SEEK_CUR, the file offset shall be set to its current location plus offset.
		If whence is SEEK_END, the file offset shall be set to the size of the file plus offset.
	The symbolic constants SEEK_SET, SEEK_CUR, and SEEK_END are defined in <unistd.h>.

	Return:
	-------
	Upon successful completion, the resulting offset, as measured in bytes from the beginning of the file, shall be returned. 
	Otherwise, (off_t)-1 shall be returned, errno shall be set to indicate the error, and the file offset shall remain unchanged.


	---------------------------------------------------- C L O S E ----------------------------------------------------
	#include <unistd.h>     // standard symbolic constants and types 

	int close(int fildes);

	Param:
	------	
	int fildes      ---> File descriptor

	Eger girilen file descriptor parametresi duzgunse cok yuksek ihtimalle dosya hatasiz bir sekilde kapatilacaktir. Eger
	dosya kapatilamazsa isletim sisteminde hata vardir. Bu durumda bir sey yapilamayacagi icin hata kontrolune gerek yoktur.

	Return:
	-------
	Upon successful completion, 0 shall be returned; otherwise, -1 shall be returned and errno set to indicate the error.


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