#include "stdio.h"
#include "stdlib.h"
#include "windows.h"



void ExitSys(LPCSTR lpszMsg);


int main(void)
{
	HANDLE		 hStdOut;
	const char   buf[]     = {"Ali"};
	DWORD		 dwWritten;
	COORD		 coord;
	WORD		 wAttr[3];

	if ((hStdOut = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE)
		ExitSys("GetStdHandle");

	/* StdOutHandle'i ile belirtilen bufferin belirtilen byte kadar ekrana yazdirilmasi */
	if( !(WriteConsole(hStdOut, buf, (DWORD)strlen(buf), &dwWritten, NULL)) )
		ExitSys("WriteConsole");;

	coord.X = 0;
	coord.Y = 0;

	wAttr[0] = BACKGROUND_BLUE | FOREGROUND_RED;
	wAttr[1] = FOREGROUND_RED  | FOREGROUND_BLUE;
	wAttr[2] = BACKGROUND_BLUE | FOREGROUND_GREEN;

	/* StdOutHandle'i ile belirtilen COORdinattan baslanarak belirtilen byte kadar 
		tasarlanan karakter attribute dizisine gore islenir, boyanir vs. */
	WriteConsoleOutputAttribute(hStdOut, wAttr, (DWORD)strlen(buf), coord, &dwWritten);

	coord.X = 10;
	coord.Y = 20;
	/* StdOutHandle'i ile Cursor(Imlec) yeri belirlenen koordinatlara goturulur */
	SetConsoleCursorPosition(hStdOut, coord);

	if (!(WriteConsole(hStdOut, buf, (DWORD)strlen(buf), &dwWritten, NULL)))
		ExitSys("WriteConsole");;

	WriteConsoleOutputAttribute(hStdOut, wAttr, (DWORD)strlen(buf), coord, &dwWritten);

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


	--------- WriteConsole  ---------
	https://docs.microsoft.com/en-us/windows/console/writeconsole

	BOOL WINAPI WriteConsole(
								_In_             HANDLE  hConsoleOutput,
								_In_       const VOID    *lpBuffer,
								_In_             DWORD   nNumberOfCharsToWrite,
								_Out_opt_        LPDWORD lpNumberOfCharsWritten,
								_Reserved_       LPVOID  lpReserved
							);


	Writes a character string to a console screen buffer beginning at the current cursor location.

	Parameters:
	----------	
	hConsoleOutput [in]
	A handle to the console screen buffer. The handle must have the GENERIC_WRITE access right. For more information, see Console Buffer Security and Access Rights.
	
	lpBuffer [in]
	A pointer to a buffer that contains characters to be written to the console screen buffer. This is expected to be an array of either char for WriteConsoleA or wchar_t for WriteConsoleW.
	
	nNumberOfCharsToWrite [in]
	The number of characters to be written. If the total size of the specified number of characters exceeds the available heap, the function fails with ERROR_NOT_ENOUGH_MEMORY.
	
	lpNumberOfCharsWritten [out, optional]
	A pointer to a variable that receives the number of characters actually written.

	lpReserved Reserved; must be NULL.
	
	Return value:
	------------
	If the function succeeds, the return value is nonzero.
	If the function fails, the return value is zero. To get extended error information, call GetLastError.

	
	--------- WriteConsoleOutputAttribute  ---------
	https://docs.microsoft.com/en-us/windows/console/writeconsoleoutputattribute

	BOOL WINAPI WriteConsoleOutputAttribute(
											 _In_        HANDLE  hConsoleOutput,
											 _In_  const WORD    *lpAttribute,
											 _In_        DWORD   nLength,
											 _In_        COORD   dwWriteCoord,
											 _Out_       LPDWORD lpNumberOfAttrsWritten
										   );

	--> StdOutHandle'i ile belirtilen COORdinattan baslanarak belirtilen byte kadar tasarlanan karakter attribute dizisine gore islenir, boyanir vs.
	Onemli nokta, lpAttribute dizisi her bir karakter icin tek tek belirtilmelidir. Karakter bazli calisir.

	Copies a number of character attributes to consecutive cells of a console screen buffer, beginning at a specified location.

	Parameters:
	----------
	hConsoleOutput [in]
	A handle to the console screen buffer. The handle must have the GENERIC_WRITE access right. For more information, see Console Buffer Security and Access Rights.
	
	lpAttribute [in]
	The attributes to be used when writing to the console screen buffer. For more information, see Character Attributes.
	
	nLength [in]
	The number of screen buffer character cells to which the attributes will be copied.
	
	dwWriteCoord [in]
	A COORD structure that specifies the character coordinates of the first cell in the console screen buffer to which the attributes will be written.
	
	lpNumberOfAttrsWritten [out]
	A pointer to a variable that receives the number of attributes actually written to the console screen buffer.

	Return value:
	------------
	If the function succeeds, the return value is nonzero.
	If the function fails, the return value is zero. To get extended error information, call 



 ******************************************************************************************************************************************************

******************************************************************************************************************************************************
*/