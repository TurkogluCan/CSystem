#include "stdio.h"
#include "stdlib.h"
#include "windows.h"



void ExitSys(LPCSTR lpszMsg);


int main(void)
{

	/* Windows case sensitive degildir. Bu yuzden dosya isimlerindeki buyuk kucuk harfler
	   sorun yasatmaz. Unix Linux case sensitivedir.

	   Eger bFailIfExists = TRUE ise;
		Kaynak uzantidaki dosyayi, hedefteki dosyayi yaratir ve dosyaya kopyalar.
		Eger hedef dosya varsa hata verir.

	   Eger bFailIfExists = FALSE ise;
		Kaynak uzantidaki dosyayi, hedefteki dosya var ise siler kopyalar, yoksa yaratir kopyalar.
	    
	   */
	if ( !CopyFile("mest.txt", "TesT.Txt", FALSE) )
		ExitSys("CopyFile");

	printf("OK\n");

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


 ******************************************************************************************************************************************************
 
 --------------------------------------------------------------------- C O P Y  F I L E ---------------------------------------------------------- 

	Copies an existing file to a new file.
	
	BOOL CopyFile(
					LPCTSTR lpExistingFileName,
					LPCTSTR lpNewFileName,
					BOOL    bFailIfExists
				 );
	
	PARAM:
	-----
	lpExistingFileName    --> The name of an existing file. 
	lpNewFileName         --> The name of the new file.
	bFailIfExists         --> If this parameter is TRUE  and the new file specified by lpNewFileName already exists, the function fails. 
							  If this parameter is FALSE and the new file already exists, the function overwrites the existing file and succeeds.

	RETURN:
	------
	If the function succeeds, the return value is nonzero.
	If the function fails, the return value is zero. To get extended error information, call "GetLastError".

******************************************************************************************************************************************************
*/