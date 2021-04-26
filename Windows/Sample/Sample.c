#include "stdio.h"


int main(void)
{
	// Ornegin imlec 10,10 pozisyonuna gitsin;
	printf("\x1B[10;10H");

	// Set style to bold, red background.
	printf("\x1B[1;41mHello\n");

	return 0;
}


/****************************************************** Others
	-----------------CALISTIRMA ORNEGI

	---------------------------------------------------- A N S I  E S C A P E  C O D E ----------------------------------------------------
	https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797

	ANSI escape kodlari, ekrana ozel bazi karakterler, renkli yazma, cursor tasima vs. islemlerini printf ile yapmaktadir. Bu kodlar printf'e string
	karakter girisi ile kullanilir.

	ESC = \x1B
	\e windowsta olmadi, Linux'ta oldu


	ESC[{line};{column}H  -->  moves cursor to line #, column #

	Ornegin imlec 10,10 pozisyonuna gitsin;
		printf("\e[10;10H");


	\x1b[1;31m            -->  Set style to bold, red foreground.
		printf("\e[1;31mHello\n");

	\x1b[1;41m            -->  Set style to bold, red background.
		printf("\e[1;41mHello\n");



	



 ******************************************************************************************************************************************************


******************************************************************************************************************************************************
*/