#include "stdio.h"
#include "unistd.h"

int main(int argc, char *argv[])
{
	const char *optstring = "abc";
	int result;
	int flag_a, flag_b, flag_c;

	flag_a = flag_b = flag_c = 0;

	/* Geri donulen deger, okudugu karakterin ascii degeridir. 
	Karakterler fonksyion tarafından tek tek okunur. Eger 
	girilen arguman, parametrede belirtilenle uyusmazsa ekrana
	hata mesaji basar ve -1 degerini dondurur. */	 
	while ( (result = getopt(argc, argv, optstring)) != -1 )
	{
		puts("Secenek girildi");
		switch (result)
		{
			case 'a':
				
				flag_a = 1;
				break;
			
			case 'b':

				flag_b = 1;
				break;
			
			case 'c':

				flag_c = 1;
				break;
			
			default:
				break;
		}
	} 

	if (flag_a)
		printf("-a option used\n");
	if (flag_b)
		printf("-b option used\n");
	if (flag_c)
		printf("-c option used\n");


	return 0;
}




/****************************************************** Others
 *
 *  argv[] dizisinin son elemanının NULL karakter olacağı standartlarda garanti edilmiştir.
 * 
 * ---
 *  int getopt(int argc, char *const argv[], const char *optstring)
 * 	---------------------------------------------------------------
 *  optstring = Seçeneklerin bulunduğu yazı. 
 *  Örn; 
 *  "abc", bunlar da -a-b-c,
 *  "ab:c", burada ise b'nin argümanlı olacağı anlamına gelmektedir.
 * 
 *  getopt her çağırıldığında farklı bir seçeneği vermektedir. O yüzden iş bitene kadar 
 *  çağırılmalıdır.
 * 
 *  Return: 
 *    If an option was successfully found, then getopt() returns the
 *    option character.  If all command-line options have been parsed,
 *    then getopt() returns -1.  If getopt() encounters an option
 *    character that was not in optstring, then '?' is returned. 
 *  
 *   Geri donulen deger, okudugu karakterin ascii degeridir. 
 *	Karakterler fonksyion tarafından tek tek okunur. Eger 
 *	girilen arguman, parametrede belirtilenle uyusmazsa ekrana
 *	hata mesaji basar ve -1 degerini dondurur. */	 
 *  

/************************************************ CODE PARTICLES
 * 
 * 
 * 
*/