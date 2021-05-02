#include "stdio.h"
#include "stdlib.h"
#include "windows.h"



void ExitSys(LPCSTR lpszMsg);


int main(void)
{
	HANDLE hFile;
	DWORD  dwFileSize;

	/* Dosya Read ve Open Existing modda acilir, handle degeri elde edilir. */
	if( (hFile = CreateFile("Test.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE )
		ExitSys("CreateFile");

	/* handle degeri alinan dosya, GetFileSize fonksiyonuna girlir. 
		 Eger okunacak dosyanin uzunlugu biliniyorsa ve LPDWORD degilse 2.parametre NULL gecilebilir. Return degeri size degeri olacaktir.
	     Eger 2.parametre NULL gecilmezse, return degerine alcak 4 byte, 2. parametreye yuksek 4 byte'lik degeri yazilir.  */
	if( (dwFileSize=GetFileSize(hFile, NULL)) == INVALID_FILE_SIZE)
		ExitSys("GetFileSize");
		
	/* Dosya uzunlugu yazdirilir. */
	printf("File size: %lu\n", dwFileSize);

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
*   Test.txt dosyasinin Karakter encodingi = Codepage 1252
*   Eger karakter encodingi değiştirilirse, örn UTF-8 vs yapilirsa
*   karakter boyutu değişeceğinden dosya boyutu da değişir.

	Test.txt içeriği = 123456789 
	GetFileSize ile dosyanın okunup ekrana bastırılan uzunluğu ise 9 Byte.


	!!!
	GetFileSize fonksiyonu açılmış bir dosyanın uzunluğunu elde etmek için kullanılmaktadır. Bu fonksiyonun birinci parametresi açılmış dosyanın handle değerini, 
	ikinci parametresi ise dosya uzunluğunun yüksek anlamlı 4 byte'lık kısmının yerleştirileceği DWORD nesnenin adresini almaktadır. 
	İkinci parametre NULL geçilebilir. GetFileSize fonksiyonu başarısızlık durumunda INVALID_FILE_SIZE özel değerine geri döner. 
	Ancak bu INVALID_FILE_SIZE sembolik sabiti 0xFFFFFFFF değerine sahip olduğu için ve bu değer de geçerli bir dosya uzunluğu olabildiği için programcının 
	ayrıca fonksiyonun başarısını GetLastError fonksiyonuyla belirlemesi gerekmektedir. 
		Yani eğer fonksiyon INVALID_FILE_SIZE değerine geri dönmüşse programcının GetLastError fonksiyonunu çağırması gerekir. GetLastError eğer NO_ERROR değerini verirse fonksiyon başarısız olmamıştır. 
		Dosya gerçekten 0xFFFFFFFF uzunluğundadır
	!!!

 --------------------------------------------------------------------- G e t  F i l e  S i z e ---------------------------------------------------------- 

	Retrieves the size of the specified file, in bytes.
	
	DWORD GetFileSize(
					  HANDLE  hFile,
					  LPDWORD lpFileSizeHigh
					);
	
	PARAM:
	-----
	hFile               --> A handle to the file.
	lpFileSizeHigh      --> A pointer to the variable where the high-order doubleword of the file size is returned. 
							This parameter can be NULL if the application does not require the high-order doubleword.

	RETURN:
	------
	If the function succeeds, the return value is the low-order doubleword of the file size, and, if lpFileSizeHigh is non-NULL, 
	the function puts the high-order doubleword of the file size into the variable pointed to by that parameter.

	If the function fails and lpFileSizeHigh is NULL, the return value is INVALID_FILE_SIZE. To get extended error information, 
	call GetLastError. When lpFileSizeHigh is NULL, the results returned for large files are ambiguous, and you will not be able to determine the actual size of the file. 
	It is recommended that you use GetFileSizeEx instead.

	If the function fails and lpFileSizeHigh is non-NULL, the return value is INVALID_FILE_SIZE and GetLastError will return a value other than NO_ERROR.

******************************************************************************************************************************************************
*/