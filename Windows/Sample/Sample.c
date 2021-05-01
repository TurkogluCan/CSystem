#include "stdio.h"
#include "stdlib.h"
#include "windows.h"



void ExitSys(LPCSTR lpszMsg);


int main(void)
{

	/* mest.txt dosyasinin dizin bilgileri movedMest.txt olarak degistirilir. */
	if ( !MoveFile("mest.txt", "movedMest.Txt") )
		ExitSys("MoveFile");

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
 
	!!!
	Taşıma demek, dataları kopyalamak değil, dizin girişini silerek başka bir dizin içerisinde burayı referans eden bir dizin yaratmak demek.
	Dosyanın erişmek için gereken path’i değiştirilir, dosya içeriği değiştirilmez. Aslında dosyanin isim değişikliği de dosya taşımayla yapılmaktadır. 
	!!!

 --------------------------------------------------------------------- M O V E  F I L E ---------------------------------------------------------- 

	Bir dosyayı yeni bir konuma taşır.
	
	BOOL MoveFile(
				  LPCTSTR lpExistingFileName,
				  LPCTSTR lpNewFileName
				);
	
	PARAM:
	-----
	lpExistingFileName      --> The current name of the file or directory on the local computer. Must be exist.
	lpNewFileName           --> The new name for the file or directory. The new name must not already exist. 
								A new file may be on a different file system or drive.
								A new directory must be on the same drive.
								Yani dosya başka bir drive(disk)'e taşınabilir fakat bir dizin başka bir drive'a taşınamaz.

	RETURN:
	------
	If the function succeeds, the return value is nonzero.
	If the function fails, the return value is zero. To get extended error information, call "GetLastError".

******************************************************************************************************************************************************
*/