#include "stdio.h"
#include "stdlib.h"
#include "windows.h"

#define	BUFSIZE		4096																									/* 512 isletim sistemlerindeki sector uzunlugudur. 4096 da katidir. */
#define	END_FILE	0

void ExitSys(LPCSTR lpszMsg);


int main(int argc, char *argv[])
{
	HANDLE	hFileW, hFileR;
	DWORD	dwRead, dwWritten;
	char	cBufRead[BUFSIZE];
	
	if (argc != 3)																											/* errno donmedigi icin ExitSys yapilamaz */
	{
		fprintf(stderr, "Yanlis arguman sayisi\n");
		exit(EXIT_FAILURE);
	}


	if ((hFileW = CreateFile(argv[1], GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL)) == INVALID_HANDLE_VALUE)
		ExitSys("CreateFile Write");
	if ((hFileR = CreateFile(argv[2], GENERIC_READ,  0, NULL, OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE)
		ExitSys("CreateFile Read");

	
	for (;;)
	{
		if (!ReadFile(hFileR, cBufRead, BUFSIZE, &dwRead, NULL))
			ExitSys("ReadFile");

			if (!WriteFile(hFileW, cBufRead, dwRead, &dwWritten, NULL) )													/* Eger dosyaya yazilirken hata olusmussa */
				ExitSys("WriteFile");

		if (dwRead == 0 )																									/* Eger okunacak dosya sonuna gelinmisse donguden cik */
			break;

		if (dwWritten != dwRead)																							/* Eger okunan kadar yazilamamissa exit yap. errno donmedigi icin ExitSys yapilamaz */
		{
			fprintf(stderr, "Yanlis arguman sayisi\n");	
			exit(EXIT_FAILURE);
		}
	}


	puts("Okunan dosyanin yazilmasi gerceklesmistir.");

	CloseHandle(hFileW);																									/* CloseHandle ile Handle'in gosterdigi dosyalar kullanici tarafindan yazilmasa da */
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
	----------CALISTIRMA ORNEGI
	!!!!! Program arguman alarak calismaktadir. Alinan ilk arguman yazilacak dosya, ikinci arguman ise okunacak dosya olarak girilmelidir. !!!!!



	--- CreateFile Ornegi ---
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


	--- ReadFile Ornegi ---
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


	--- WriteFile Ornegi ---
	https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-writefile

	BOOL WINAPI WriteFile(
							HANDLE hFile,								//CreateFile’dan alinan Handle
							LPCVOID lpBuffer,							//Dosyaya yazılacak Buffer
							DWORD nNumberOfBytesToWrite,				//Yazilacak byte sayisi
							LPDWORD lpNumberOfBytesWritten,				//Basarili olarak yazilabilen byte sayisi
							LPOVERLAPPED lpOverlapped					//Overlapped IO işlemi (Default: NULL)
						
							);



	--- CloseHandle ---

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