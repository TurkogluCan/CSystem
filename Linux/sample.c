#include "stdio.h"									/* perror da bunun icerisindedir */
#include "stdlib.h"									/* EXIT_FAILURE icin*/
#include "fcntl.h"									/* open icin, File Control */
#include "errno.h"									/* errno icin */
#include "sys/stat.h"								/* S_I... parametreleri icin */
#include "unistd.h"									/* read ve write icin */ 
#include "getopt.h"

//********************************** Define


//********************************** Function Prototypes
void exit_sys(const char *msg);						






int main(void)
{
	// Ornegin imlec 10,10 pozisyonuna gitsin;
	printf("\e[10;10H"); 
	
	// Set style to bold, red background.
	printf("\x1B[1;41mHello\n");

	return 0;
}

void exit_sys(const char *msg)						
{
	perror(msg);
	exit(EXIT_FAILURE);
}












/****************************************************** Others
 * KOD CALSTIRMA ORNEGI:
 * gcc -Wall -o sample sample.c 
 * ./sample 
 * 
 ******************************************************************************************************************************************************
	
	---------------------------------------------------- A N S I  E S C A P E  C O D E ----------------------------------------------------
	https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797

	ANSI escape kodlari, ekrana ozel bazi karakterler, renkli yazma, cursor tasima vs. islemlerini printf ile yapmaktadir. Bu kodlar printf'e string
	karakter girisi ile kullanilir. 

	ESC = \e = \x1B
		

	ESC[{line};{column}H  -->  moves cursor to line #, column # 
	
	Ornegin imlec 10,10 pozisyonuna gitsin;
		printf("\e[10;10H"); 


	\x1b[1;31m            -->  Set style to bold, red foreground.
		printf("\e[1;31mHello\n");

	\x1b[1;41m            -->  Set style to bold, red background.
		printf("\e[1;41mHello\n");
******************************************************************************************************************************************************
*/