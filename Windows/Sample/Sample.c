#include "stdio.h"
#include "stdlib.h"
#include "windows.h"



void ExitSys(LPCSTR lpszMsg);


int main(void)
{
	
	/* Olmayan bir dizin yaratilir. */
	if (!CreateDirectory("dirTest", NULL))
		ExitSys("CreateDirectory");

	/* Yukaridaki PathName'in uzun hali
	if (!CreateDirectory("C:\\Users\\enesc\\Masaüstü\\GitKrakenRepo\\CSystem_Sample\\CSystem\\Windows\\Sample\\dirTest", NULL))
		ExitSys("CreateDirectory");
	*/


	/* Bos olan bir dizin silinir. */
	if (!RemoveDirectory("dirTest"))
		ExitSys("RemoveDirectory");

	printf("Dizin yaratildi ve silindi. \n");
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

	Verilen PathName'e sahip bir directory(Dosya) varsa hata verir. Verilen PathName'in kullanilmamis olmasi lazim.

 --------------------------------------------------------------------- C r e a t e  D i r e c t o r y ---------------------------------------------------------- 

	Verilen Path Name'de yeni bir dizin yaratir.
	
	BOOL CreateDirectory(
						  LPCTSTR lpPathName,
						  LPSECURITY_ATTRIBUTES lpSecurityAttributes
						);

	
	PARAM:
	-----
	lpPathName               --> The path of the directory to be created.
	lpSecurityAttributes     --> A pointer to a SECURITY_ATTRIBUTES structure. The lpSecurityDescriptor member of the structure specifies a security descriptor for the new directory. 
	                             If lpSecurityAttributes is NULL, the directory gets a default security descriptor.

	RETURN:
	------
	If the function succeeds, the return value is nonzero.
	If the function fails, the return value is zero. To get extended error information, call GetLastError. 

	 --------------------------------------------------------------------- R e m o v e  D i r e c t o r y ----------------------------------------------------------

	Dizinin ici bossa dizini siler.
	Deletes an existing empty directory.

	BOOL RemoveDirectory(
						  LPCSTR lpPathName
						);

	PARAM:
	-----
	lpPathName               --> The path of the directory to be removed. This path must specify an empty directory, and the calling process must have delete access to the directory.

	RETURN:
	------
	If the function succeeds, the return value is nonzero.
	If the function fails, the return value is zero. To get extended error information, call GetLastError.

******************************************************************************************************************************************************
*/