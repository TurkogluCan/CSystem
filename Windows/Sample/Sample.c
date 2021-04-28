#include "stdio.h"
#include "windows.h"



void ExitSys(LPCSTR lpszMsg);


int main(void)
{
	/* Ekrana bir yazi yazidirlmadan once veya bir yazi okunmadan once Console ve
	   Editor karakter encodinglerinin ayni almasi gerekmektedir. 
	   Bu ornekle beraber PC karakter kodu UTF8-65001 olarak yapilmistir. 
	   
	   Calisilan osyanin editordeki karakter kodu da Save as->Save/Secenekler->Save with encoding diyerek
	   degistirilebilir. Editorun komple degistirildigi bir senecek de mevcuttur buyuk ihtimalle.
	   
	   Ama onemli olan sey, editor ile consolun aynı karakter encoding degerine sahip olmasi gerekmektedir.

	   SetConsoleOutputCP(...) ile de konsol karakter encoing degeri gecici olarak değiştirilebilmektedir.

	   Karakter tabloları;

	   1Byte'lık ve 2Byte'lık olmak uzere 2'ye ayrılır.

		1Byte'lık tablolarda karakterler 1Bytedır ve birçok farklı region vs. için çeşitlidir.
		2Byte'lık tablolarda karakterler 2Bytedır. Unicode olarak da denmektedir. Bütün dünyada aynıdır.
		Unicode tabloda dünyanın bütün karakterleri vardır.

		UTF8 Tablosu ise sıkıştırılmış Unicode tablo anlamındadır. Bu tabloda ASCII karakterler 1 byte ile kodlanir. 
		Eger deger ASCII dışına geliyorsa bu karakter 2byte, 3byte vs kodlarınır. Bu kodlama biçimine "Multibyte kodlama" denmektedir.
			Ornegin; 
		
		char text[] = "ağ";
		printf("%u", strlen(text));
		----> 3Byte

		C Standartlarına gore ''(Orn 'x') icerisinde bir karakter alınırsa 1Byte yer kaplaması zorunlu değildir ve bu int türündendir. 
		Fakat cpp'da ''(Orn 'x') icerisinde bir karakter alınırsa 1Byte yer kaplar ve türü char'dır. 
	   */

	printf("%c", 'Ğ');

	return 0;
}







/****************************************************** Others
	-----------------CALISTIRMA ORNEGI

	CMD CODPAGE DEGISTIRME ORNEGI
	https://stackoverflow.com/questions/7432545/change-codepage-in-cmd-permanently/30100565

	CMD CODPAGE DEGISTIRME UTF8 - 65001 yapilmistir.

 ******************************************************************************************************************************************************

******************************************************************************************************************************************************
*/