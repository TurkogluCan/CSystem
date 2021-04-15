#include "stdio.h"
#include "stdlib.h"
#include "getopt.h"

#define MAX_LINE    1024

int main(int argc, char *argv[])
{

	int result;
	int flag_bytes= 0, flag_line= 0, flag_help= 0, flag_verbose= 0, flag_version= 0, flag_err = 0;
	char *arg_bytes, *arg_line;

	int index;

	struct option options[] = 
	{
		{"bytes",   required_argument, NULL, 'c'},
		{"lines",   required_argument, NULL, 'n'},
		{"verbose", no_argument,       NULL, 'v'},
		{"help",    no_argument,       NULL, 'h'},
		{"version", no_argument,       NULL, 'i'},
		{0,0,0,0}
	};
	
	opterr = 0;

	while ( (result = getopt_long(argc, argv, "c:n:v", options, &index)) != -1 )				/* c: argumanli yapildigi secenek oldugu icin ve */
	{																							/* options'taki count val donusu 'c' oldugu icin -c veya --count girilse de ayni seydir. */
		switch (result)
		{
			case 'c':													/* --bytes */
			
				arg_bytes  = optarg;
				flag_bytes = 1;
				break;

			case 'n':													/* --line */
			
				arg_line  = optarg;
				flag_line = 1;
				break;

			case 'v':													/* --verbose */
			
				flag_verbose = 1;
				break;
		    
			case 'h':													/* --help */
			
				flag_help = 1;
				break;

			case 'i':													/* --version */
			
				flag_version = 1;
				break;
			
			case '?':	/* Invalid option */
				if (optopt == 'c')
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

	if (flag_help)
		printf("YARDIM YOK KARDESIM ALLAH VERSIN\n");

	if (flag_version)
		printf("VERSION v1.0\n");


	if ((flag_verbose != 0) && (optind!= argc) )
	{
		printf("==> %s <==\n", argv[optind]);
	}
	else if (flag_verbose == 1 && optind== argc)
	{
		fprintf(stderr, "DOSYA ISMINI GIRMEDINIZ\n");
		exit(EXIT_FAILURE);
	}
/********************************************************  FILE OPERATION *********************************************************/

	FILE *pFile;
	char pLine[MAX_LINE];
	int pBytes;
	int cntArg = optind;
	
	/************************* BYTE by BYTE READ *************************/
	if (flag_bytes)																				/* --byte veya -c secenegi girilmisse */
	{
		if (cntArg < argc)																		/* Seceneksiz arguman yoksa, dosya ismi girilmemisse hata ver kapa */																		
		{
			for (cntArg = optind; cntArg < argc; cntArg++)										/* Seceneksiz arguman sayisi kadar dondurur, birden fazla dosya okumak icin */
			{
				printf("BYTE MODE = DOSYA ISMI = %s\n",argv[cntArg]);
				if ( (pFile = fopen(argv[cntArg], "r")) == NULL )
				{
					fprintf(stderr, "Fail on fopen BYTE\n");
					exit(EXIT_FAILURE);
				}			

				fseek(pFile, 0, SEEK_SET);

				for(int i = 0; i < strtod(arg_bytes, NULL); i++)								/* Dosyayi, girilen byte sayisi kadar byte byte oku ve yazdir */
				{
					if ( fread(&pBytes, sizeof(char), 1, pFile) != 1 )							/* Dosyayi byte byte oku */
					{
						fprintf(stderr, "\nOUT OF BYTES or fgets error\n");
						exit(EXIT_FAILURE);
					}	
					printf("%c", pBytes);
				}
				puts("\n");
				fclose(pFile);
			}
		}
	}
	
	cntArg = optind;
	/************************* LINE by LINE READ *************************/
    if ( flag_line)																				/* --lines veya -n secenegi girilmisse */
	{
		if (cntArg < argc)																		/* Seceneksiz arguman yoksa, dosya ismi girilmemisse hata ver kapa */																		
		{
			for (cntArg = optind; cntArg < argc; cntArg++)										/* Seceneksiz arguman sayisi kadar dondurur, birden fazla dosya okumak icin */
			{
				printf("LINE MODE = DOSYA ISMI = %s\n",argv[cntArg]);
				if ( (pFile = fopen(argv[cntArg], "r")) == NULL )
				{

					fprintf(stderr, "Fail on fopen LINE\n");
					exit(EXIT_FAILURE);
				}

				for(int i = 0; i < strtod(arg_line, NULL); i++)									/* Dosyayi, girilen line sayisi kadar line line oku ve yazdir */
				{
					if ( (fgets(pLine, MAX_LINE, pFile)) == NULL )								/* Dosyayi line line oku */
					{
						fprintf(stderr, "\nOUT OF LINE or fgets error\n");
						exit(EXIT_FAILURE);
					}

					fprintf(stdout, "%s", pLine);
				}
				puts("\n");
				fclose(pFile);
			}
		}
		else
		{
			fprintf(stderr, "Dosya gir\n");
			exit(EXIT_FAILURE);
		}

	
	}

	return 0;
}





/****************************************************** Others
 *  KOD CALSTIRMA ORNEGI:
 *  
 *  ./sample --lines 10 test.txt
 *  ./sample --lines 100 test.txt mest.txt test.txt
 * 	./sample --bytes 10 test.txt
 *  ./sample --bytes 100 test.txt mest.txt test.txt
 *  ./sample --help
 *  ./sample --version
 *  ./sample --verbose test.txt
 * 
 * --verbose veya -v : Dosyanin ismini verir.
 * --bytes   veya -c : Dosyadan okunacak olan byte sayisini verir.
 * --lines   veya -n : Dosyadan okunacak olan line sayisini verir.
 * --help            : Help.
 * --version         : Yazilim versiyonu.

*/

/************************************************ CODE PARTICLES
 	SEÇENEKSIZ ARGUMANLARI YAZDIRIR
	if (optind != argc )												
	{
		puts("\nSeceneksiz argumanlar");
		for (int i = optind; i < argc; i++)
		{
			printf("%s\n\n", argv[i]);
		}
	}


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