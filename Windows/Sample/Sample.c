#include "stdio.h"
#include "stdlib.h"
#include "windows.h"

#define	BUFSIZE				4096																								/* 512 isletim sistemlerindeki sector uzunlugudur. 4096 da katidir. */
#define	SuKadarByteKaydir 	15

void ExitSys(LPCSTR lpszMsg);


int main(void)
{
	HANDLE  hFileR;
	DWORD	dwRead, dwSetted;
	char	cBufRead[BUFSIZE+1];
	


	if ((hFileR = CreateFile("Test.txt", GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE)
		ExitSys("CreateFile Read");

	
	if ( (dwSetted=SetFilePointer(hFileR, SuKadarByteKaydir, NULL, FILE_BEGIN)) != SuKadarByteKaydir)
		ExitSys("SetFilePointer");


	for (;;)
	{
		if (!ReadFile(hFileR, cBufRead, BUFSIZE, &dwRead, NULL))
			ExitSys("ReadFile");

		if (dwRead == 0 )																									/* Eger okunacak dosya sonuna gelinmisse donguden cik */
			break;

		cBufRead[dwRead] = '\0';
		printf("%s", cBufRead);
	}
	
																															/* CloseHandle ile Handle'in gosterdigi dosyalar kullanici tarafindan yazilmasa da */
	CloseHandle(hFileR);																									/* Isletim sistemi tarafindan zaten kapatilacaktir. */

	return 0;
}



void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastError = GetLastError();
	PTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (PTSTR)&lpszErr, 0, NULL)) {
		printf("%s: ", lpszMsg);

		for (int i = 0; lpszErr[i] != '\n'; i++)
			printf("%c", lpszErr[i]);
		printf("\n");

		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}








/****************************************************** Others
	-----------------CALISTIRMA ORNEGI
	SetFilePointer fonksiyonu ile okunan "Test.txt" dosyasinda belirlenen deger kadar dosya göstericisi kaydirilmistir ve sonrasinda dosyadan okuma yapilmistir.








	--------- CreateFile Ornegi ---------
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea

	HANDLE WINAPI CreateFile(
  								LPCTSTR lpFileName,									//Dosya yol ifadesi
  								DWORD dwDesiredAccess,								//Okuma veya yazma veya her ikisi de modu
  								DWORD dwShareMode,									//Dosyayı başkası da açabilsin mi veya hangi modal açsın
  								LPSECURITY_ATTRIBUTES lpSecurityAttributes,			//Kernel nesnesinin güvenlik parametresi(Default: NULL)
  								DWORD dwCreationDisposition,						//Dosya yoksa veya varsa ne yapılacak, yaratmak, açmak vs
  								DWORD dwFlagsAndAttributes,							//Dosya yaratiliyorsa dosyanin attributes  özellikleri(Default:0)
  								HANDLE hTemplateFile								//Eger daha önceden acilmiş bir dosyanin handle değeri geçilirse
                                     												//ilgili ozellikleri(girilen parametreleri) onunki gibi alıyor              
																					//(Default: NULL)
								);

	CreateFile("Test.txt", 
				GENERIC_READ | GENERIC_WRITE,
				0,
				NULL,
				OPEN_EXISTING,
				0,
				NULL);


	- Ayni anda ayni dosyaya birden fazla kez create islemi yapilamaz, hata verir. Farkli dosyalar icin yapilabilir.


	--------- ReadFile Ornegi ---------
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-readfile

	BOOL WINAPI ReadFile(
							HANDLE hFile,							//CreateFile’dan alinan Handle
							LPVOID lpBuffer,						//Okunacaklarin yerleştirecegi adresi
							DWORD nNumberOfBytesToRead,				//Okunacak byte sayisi
							LPDWORD lpNumberOfBytesRead,			//Basarili olarak okunabilen byte sayisi
							LPOVERLAPPED lpOverlapped			  	//Overlapped IO işlemi (Default: NULL)
							
							);
	

	If the function succeeds, the return value is nonzero (TRUE).

	If the function fails, or is completing asynchronously, the return value is zero (FALSE). 
	To get extended error information, call the GetLastError function.


	--------- WriteFile Ornegi ---------
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-writefile

	BOOL WINAPI WriteFile(
							HANDLE hFile,								//CreateFile’dan alinan Handle
							LPCVOID lpBuffer,							//Dosyaya yazılacak Buffer
							DWORD nNumberOfBytesToWrite,				//Yazilacak byte sayisi
							LPDWORD lpNumberOfBytesWritten,				//Basarili olarak yazilabilen byte sayisi
							LPOVERLAPPED lpOverlapped					//Overlapped IO işlemi (Default: NULL)
						
							);

	--------- SetFilePointer ---------
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-setfilepointer

	DWORD WINAPI SetFilePointer(
								HANDLE hFile,
								LONG lDistanceToMove,
								PLONG lpDistanceToMoveHigh,
								DWORD dwMoveMethod
								);

				     Windows		   Linux
	Işlemci			32		64		32		64	
	-------------------------------------------
	int				4		4		4		4	BYTE
	short			2		2		2		2	BYTE
	long			4		4		4		8	BYTE
	
	Windowsta tanımlanabilecek maksimum işaretli tamsayı değeri(long) 4byte’dır. Yani bir değişken ile yazılabilecek en büyük işaretli tamsayı 2GB’dır.
	
	Fakat bir dosya 2GB’dan büyük olabilir. Bu durumda “SetFilePointer” ile konumlandırı 2GB’dan ileriye konumlandırılmak istenirse 4Byte’lık tek bir değişkenle konumlandırılamaz. Bu soruna karşılık “lpDistanceToMoveHigh” parametresi bulunmaktadır. Fonksiyon kullanıcıdan 2 ayrı 32 bit istemektedir. Bu parametre “lDistanceToMove” konumlandırılacak yerin low kısmı, “lpDistanceToMoveHigh” parametresi ise konumlandırılacak yerin high kısmıdır.
	Ayrıca Fonksiyon çıkışta da konumlandırılan yeri döneceği için, fonksiyonun return değeri alçak(low) 4 byte’ı, lpDistanceToMoveHigh parametresi ise yüksek(High) Byte’ı gösterir. Eğer 2GB’dan fazla yazılmayacaksa bu paramertre NULL geçilebilir.

	NTFS dosya sistemlerinde, dosya konumlandırıcısı, dosyanın sonundan ileriye konumlandırılabilir. Bu geçerlidir. Aşağıda açıklanıyor.Bu tür durumlarda dosyaya yazma yapıldığında dosya deliği (file hole) oluşur


	--------- CloseHandle ---------

	https://docs.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle
	- BOOL CloseHandle(HANDLE) fonksiyonu, Sadece dosyayi değil, kernel nesnelerini de ortak olarak kapatir.

	---------------


	



 ******************************************************************************************************************************************************

	// Dosya varsa ac, yoksa hata ver 
	if ((hFile = CreateFile("Test.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE)
		ExitSys("CreateFile");

	// Dosya varsa sifirla, yoksa yarat 
	if ((hFile = CreateFile("TASDest.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL)) == INVALID_HANDLE_VALUE)
		ExitSys("CreateFile");

	// Dosya varsa hata ver, yoksa yarat
	if ((hFile = CreateFile("Teasdasdst.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_NEW, 0, NULL)) == INVALID_HANDLE_VALUE)
		ExitSys("CreateFile");
******************************************************************************************************************************************************
*/