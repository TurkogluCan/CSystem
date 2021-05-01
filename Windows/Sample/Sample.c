#include "stdio.h"
#include "stdlib.h"
#include "windows.h"



void ExitSys(LPCSTR lpszMsg);


int main(void)
{

	
	if (!DeleteFile("x.txt"))
		ExitSys("DeleteFile");

	//if (remove("xsds.txt"))
	//	ExitSys("remove");

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
 
 --------------------------------------------------------------------- D E L E T E  F I L E ---------------------------------------------------------- 

	Deletes an existing file. To perform this operation as a transacted operation, use the DeleteFileTransacted() function. The syntax is:
	
	BOOL DeleteFile( LPCSTR lpFileName );
	
	RETURN:
	------
	If the function succeeds, the return value is nonzero and 
	if the function fails, the return value is zero (0). To get extended error information, call GetLastError().


  --------------------------------------------------------------------- R E M O V E ----------------------------------------------------------
	
	---> Aslinda "remove" fonksiyonu da kendi icerisinde "DeleteFile" Windows API'sini cagirmaktadir. Yani remove ust, DeleteFile alt katman fonksiyonudur.

	In the C Programming Language, the remove function removes a file pointed to by filename.
	
	#include <stdio.h>
	int remove(const char *filename);

	RETURN:
	------
	The remove function returns zero is successful, otherwise nonzero.

******************************************************************************************************************************************************
*/