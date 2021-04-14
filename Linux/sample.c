#include "stdio.h"
#include "stdlib.h"
#include "getopt.h"

int main(int argc, char *argv[])
{

	int result;
	int flag_a= 0, flag_b= 0, flag_help= 0, flag_count= 0, flag_line= 0, flag_err = 0;
	char *arg_a, *arg_b, *arg_count, *arg_line;

	int index;

	struct option options[] = 
	{
		{"help",  no_argument,       &flag_help, 1  },
		{"count", required_argument, NULL,       'c'},				
		{"line",  optional_argument, NULL,       3  },
		{0,0,0,0}
	};
	

	opterr = 0;

	while ( (result = getopt_long(argc, argv, "ab:c:", options, &index)) != -1 )				/* c: argumanli yapildigi secenek oldugu icin ve */
	{																							/* options'taki count val donusu 'c' oldugu icin -c veya --count girilse de ayni seydir. */
		switch (result)
		{
			case 'a':											
			
				arg_a  = optarg;
				flag_a = 1;
				break;

			case 'b':							
			
				arg_b  = optarg;
				flag_b = 1;
				break;

			case 'c':													/* --count */
			
				arg_count  = optarg;
				flag_count = 1;
				break;
			
			case 3:														/* --line */

				arg_line  = optarg;
				flag_line = 1;
				break;
			
			case '?':	/* Invalid option */
				if (optopt == 'b')
					fprintf(stderr, "Short option must be have an argument.\n");
				else if (optopt != 0)
					fprintf(stderr, "Invalid option.\n");
				else
					fprintf(stderr, "Invalid long option.\n");
				flag_err = 1;
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

	if (flag_help)
		printf("--help option used\n");

	if (flag_count)
		printf("--count option used and  have an arguman \"%s\"\n", arg_count);
	else if (flag_count)
		printf("--count option used\n");

	if (flag_line && arg_line != NULL)
		printf("--line option used and  have an arguman \"%s\"\n", arg_line);
	else if (flag_line)
		printf("--line option used\n");


	
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
 * 	Calistirma orneği:
 *  ./sample --line=ali
 *  ./sample --line
 *  ./sample --count=veli
 *  ./sample --count=veli -ab deniz
 * ---
 *  int getopt_long(int argc, char * const argv[],
                  const char *optstring,
                  const struct option *longopts, int *longindex);
 * 	---------------------------------------------------------------
 * 
 *  Yaratılacak olan option structının son elemanı {0,0,0,0} ile bitmelidir.
 * 
 *  struct option 
 * 	{
     const char *name;
     int         has_arg;
     int        *flag;
     int         val;
    };

	name   is the name of the long option.

    has_arg
            is:  
			no_argument (or 0) if the option does not take an argument;
            required_argument (or 1) if the option requires an argument;  or
            optional_argument  (or  2) if the option takes an optional argu‐
            ment.

	no argument       = argümansız
	required_argument = argümanlı, --line=ali
						Eğer argüman verilmeden yazılırsa seçeneği de görmez.
	optional_argument = argümanlı veya argümansız


    flag    specifies how results are returned for a long option.   
			If  flag is  NULL,  then  getopt_long()  returns  val.  
			(For example, the calling program may set val to the equivalent short option char‐
            acter.)   Otherwise, getopt_long() returns 0, and flag points to
            a variable which is set to val if the option is found, but  left
            unchanged if the option is not found.

	Eğer NULL girilirse geri döneceği değeri val'e set eder.
	Eğer int değişkenin adresini girersen seçenek geldiğinde val değeri flage atanir. 

    val     is  the value to return, or to load into the variable pointed to
            by flag.

	RETURN
	------
	
	Eğer flag == NULL ise, getopt_long un geri donduruleceği değer val değeridir. 
	Eğer flag != NULL ise, 0 değerini döndürür.
	Eğer bütün seçenekler parse edilmişse -1 değerini döndürür. 
	Eğer girilen arg uyuşmazsa ? döndürür.
	Kısa seçeneği de döner.

	getopt fonksiyonunda char döndürülüp anlaşılıyordu fakat
	burada structta long optiona özgü tanımlanan val değerini döndürür.



*/
/************************************************ CODE PARTICLES
 * 
 * can girilsin
 * printf("%c\n", argv[0][0]); = printf("%c\n", *argv[0]) = 'c';
 * printf("%s\n", argv[0])                                = can;
 * 
 * 
 * gcc -Wall -o sample sample.c
 * ----------------------------
 * Koddaki butun uyarilari verir, degiskeni yaratip kullanmasan bile soyler.
 * 
*/