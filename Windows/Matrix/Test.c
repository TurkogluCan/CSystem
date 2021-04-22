#include "stdio.h"
#include "stdlib.h"
#include "array.h"
#include "math.h"

int main(void)
{
	HARRAY hArray1, hArray2;

	const double a[7] = {1, 2, 3, 4, 5, 6 ,7};
	const double b[3] = {10, 20, 30};

	hArray1 = CreateArrayWithValues((double *)a, sizeof(a) / sizeof(double));
	hArray2 = CreateArrayWithValues((double *)b, sizeof(b) / sizeof(double));





	CloseArray(hArray1);
	CloseArray(hArray2);

	return 0;
}


/*
printf("size = %d", sizeof(a) / sizeof(double));
*/


