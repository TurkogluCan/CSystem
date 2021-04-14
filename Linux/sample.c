#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main(int argc, char *argv[])
{
	const char *optstring = "ab:c:";
	int result;
	int flag_a, flag_b, flag_c, flag_err = 0;
	char *arg_a, *arg_b, *arg_c;
	flag_a = flag_b = flag_c = 0;

	opterr = 0;

	while ( (result = getopt(argc, argv, optstring)) != -1 )
	{
		switch (result)
		{
			case 'a':
			
				arg_a = optarg;
				flag_a = 1;
				break;
			
			case 'b':
			
				arg_b = optarg;
				flag_b = 1;
				break;
			
			case 'c':

				arg_c = optarg;
				flag_c = 1;
				break;
			
			case '?':	/* Invalid option */
				flag_err = 1;
				fprintf(stderr, "invalid option: -%c\n", optopt);
				break;

			default:
				break;
		}
	} 

	if (flag_err)														/* Hatali secenek girisi varsa programdan cikar */
		exit(EXIT_FAILURE);

	if (flag_a && arg_a != NULL)
		printf("-a option used and have an arguman %s\n", arg_a);
	else if (flag_a)
		printf("-a option used\n");

	if (flag_b && arg_b != NULL)
		printf("-b option used and have an arguman %s\n", arg_b);
	else if (flag_b)
		printf("-b option used\n");

	if (flag_c && arg_c != NULL)
		printf("-c option used and  have an arguman %s\n", arg_c);
	else if (flag_c)
		printf("-c option used\n");


	
	if (optind != argc )												/* Seceneksiz arguman varsa */
	{
		puts("\nSeceneksiz argumanlar");
		for (int i = optind; i < argc; i++)
		{
			printf("%s\n", argv[i]);
		}
	}

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
 *	hata mesaji basar ve -1 degerini dondurur. 	 
 *  
 * 
 *  getopt(...) fonksiyonu, komut satiri argumanlarinin *argv[] icerisindeki
 *  yerlerini degistirerek seçeneksiz argümanlari en sona atar.
 * 
 *  Saf hali:    ./sample -a veli selami -c -b ali
 *  Duzen. hali: ./sample -a -c -b ali veli selami 
 * 
 *  NOT: Burada veli eger -a nın argümanı ise sona alınmaz. 
 *  Sadece seçeneksiz bir argümansa sona alınır.
 *  
 *  "a:b:"
 *  Saf hali:    ./sample -a enes xxx -b can yyy
 *  Duzen. hali: ./sample -a enes -b can xxx yyy 
 
 *  "ab:"
 *  Saf hali:    ./sample -a enes xxx -b can yyy
 *  Duzen. hali: ./sample -a -b can enes xxx yyy 
 * 
 *  optarg : Argümanın *argv[]''deki adresini gösterir.
 *  optind : Seçeneksiz argümanlarin başladığı argc değerini içerir. Eğer hiç
 *           seçeneksiz argüman yoksa argc'ye eşit olur.
 *  opterr : opterr değişkenine sıfırdan başka, NONZERO bir deger girilirse
 *           hatayi rapor eder, ekrana uyari basar. 
 * 			 Eğer 0 girilirse hata raporlama işini size bırakır.
 *           Default değeri NONEZERO'dur, yani hatayi rapor eder. 
 *  optopt : Eger geçersiz argüman girilirse, geçersiz argümanı döndürür.
 * 
 * 

*/
/************************************************ CODE PARTICLES
 * 
 * can girilsin
 * printf("%c\n", argv[0][0]); = printf("%c\n", *argv[0]) = 'c';
 * printf("%s\n", argv[0])                                = can;
 * 
*/