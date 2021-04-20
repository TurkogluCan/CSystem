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
	LPTSTR lpszErr;
 
	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}






/****************************************************** Others

	Windows sistemlerinde bir API fonksiyonu başarısız olmuşsa neden başarısız olduğu GetLastError isimli fonksiyonla tespit edilir.
	Bu fonksiyonun prototipi şöyledir:

	DWORD GetLastError(void);

	Fonksiyon her farklı error gerekçesi için değişk bir değer vermektedir. Bu değerler aynı zamanda <windows.h> içerisinde
	ERROR_XXXX biçiminde sembolik sabitlerle define edilmiştir. Hatanın nedenini yazı biçiminde oluştuyrmak için FormatMessage isimli
	yardımcı bir API fonksiyonu da vardır. Ancak bu fonksiyonun kullanımı biraz karmaşıktır. Bunun yerine biz ExitSys isimli bir sarma (wrapper)
	fonksiyon yazacağız. Sarma (wrapper) fonksiyonlar, asıl işi yapan fonksiyonu çağaran fonksiyonlardır. Burada da ExitSys(...) asıl fonksiyon olan 
	FormatMessage(...) fonksiyonunu çağırır ve exit yapılır. Bu fonksiyon önce bizim verdiğimiz yazıyı, sonra ':' karakterini sonra da hata kodunu stderr dosyasına yazdırıp
	programı EXIT_FAILURE exit kodu ile sonlandırmaktadır.

 ******************************************************************************************************************************************************


******************************************************************************************************************************************************
*/