#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main(int argc, char *argv[])
{
	const char *optstring = "msad";
	int result;
	int flag_m, flag_s, flag_d, flag_a, flag_err = 0;
	char *arg_m, *arg_s, *arg_d, *arg_a;
	double arg1, arg2, calculated;
	flag_m = flag_s = flag_d = flag_a = 0;
	


	opterr = 0;															/* getopt(...) fonksiyonu hata raporu vermesin. */

	while ( (result = getopt(argc, argv, optstring)) != -1 )
	{
		switch (result)
		{
			case 'm':
			
				arg_m = optarg;
				flag_m = 1;
				break;
			
			case 's':
			
				arg_s = optarg;
				flag_s = 1;
				break;
			
			case 'd':

				arg_d = optarg;
				flag_d = 1;
				break;
			
			case 'a':

				arg_a = optarg;
				flag_a = 1;
				break;

			case '?':	/* Invalid option or no arguman for option with arguments */
				flag_err = 1;
				fprintf(stderr, "invalid option: -%c\n", optopt);
				break;

			default:
				break;
		}
	} 

	if (flag_err)														/* Hatali secenek girisi varsa programdan cikar */
		exit(EXIT_FAILURE);

	if (flag_a + flag_s + flag_m + flag_d != 1)
	{
		puts("Bir seyler gir");
		exit(EXIT_FAILURE);
	}
	else if (argc - optind != 2)
	{
		puts("Wrong number of argumants");
		exit(EXIT_FAILURE);
	}	


	arg1 = strtod(argv[optind], NULL);
	arg2 = strtod(argv[optind + 1], NULL);
	
	if (flag_a)
		calculated = arg1 + arg2;
	if (flag_m)
		calculated = arg1 - arg2;
	if (flag_d)
		calculated = arg1 / arg2;
	if (flag_s)
		calculated = arg1 * arg2;

	printf("Calculated = %.2f\n", calculated);

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
 * 
 * 
 *   elde edilen sayi = strtod(argümanlar, fonksiyon sayinin bittiği yerin adresini döner)
*/
/************************************************ CODE PARTICLES
 * 
 * can girilsin
 * printf("%c\n", argv[0][0]); = printf("%c\n", *argv[0]) = 'c';
 * printf("%s\n", argv[0])                                = can;
 * 
*/