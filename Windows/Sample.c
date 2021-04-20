#include "stdio.h"
#include "windows.h"


void ExitSys(LPCSTR lpszMsg);



int main(void)
{
	if (CreateSemaphore(NULL, -10, 1, "") == NULL)
		ExitSys("CreateSemaphore");

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
	
	v0.1.13 versiyonunda hocanin yazdigi, bulunan hatanin stringe donusturme ve exit'leme fonksiyonu bulunmaktadir. Bu fonksiyon bende calistirildiginda
	hata kodunun sadece ilk karakterinin basildigi gorulmustur. Garip bir olay anlayamadim. Bu yuzden kod revize edilmistir. Sorunsuz calismaktadir.
	

 ******************************************************************************************************************************************************


******************************************************************************************************************************************************
*/