#include "stdio.h"
#include "stdlib.h"
#include "windows.h"


void ExitSys(LPCSTR lpszMsg);



int main(void)
{
	HANDLE hFile;

	/* Dosya varsa ac, yoksa hata ver */
	if ((hFile = CreateFile("Test.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE)
		ExitSys("CreateFile");


	printf("Ok\n");

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
	
	--- CreateFile Ornegi ---

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