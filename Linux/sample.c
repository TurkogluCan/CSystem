#include <stdio.h>
#include <stdlib.h>

#define LINE_LENGTH     1024

int main(int argc, char *argv[])
{
	FILE *pFT, *pFS;
	char *pFNameS, *pFNameT;				//** Name of Source file, Name of Temp file 
	char buf[LINE_LENGTH];


	pFNameS =  argv[1];						//** Kaynak, okunacak dosyanin ismi
	pFNameT =  argv[2];						//** Kaynak dosyanin icindekilerin yazdirilacagi dosyanin ismi

	if ( (pFT = fopen(pFNameT, "w")) == NULL)
	{
		printf("fopen pFT error");
		exit(EXIT_FAILURE);
	}

	if ( (pFS = fopen(pFNameS, "r")) == NULL)
	{
		printf("fopen pFS error");
		exit(EXIT_FAILURE);
	}

	while ( fgets(buf, LINE_LENGTH, pFS) != NULL)
	{
		fprintf(pFT, "%s", buf);
		printf("%s\n", buf);
	}

	fclose(pFS);
	fclose(pFT);
    
    return 0;
}
/* Others

	CMD:	./sample test.txt hedef.txt
	FILE:	hedef.txt, test.txt
*/