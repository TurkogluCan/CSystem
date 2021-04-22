#ifndef ARRAY_H_
#define ARRAY_H_

#include "stddef.h"

/* SYMBOLIC CONSTANTS */
#define TRUE	1
#define FALSE	0

/* TYPE DECLARATIONS */

typedef struct tagARRAY
{
	double *pdArray;			/* Dizinin baslangic adresi */
	size_t	size;				/* Dizinin uzunlugu */
} ARRAY;

typedef void *HARRAY;

/* FUNCTION PROTOTYPES */

HARRAY	CreateArray(size_t size);
HARRAY	CreateArrayWithZeros(size_t size);
HARRAY	CreateArrayWithValues(const double *pd, size_t size);
void	CloseArray(HARRAY hArray);

HARRAY	SinArray(HARRAY hArray);
HARRAY	CosArray(HARRAY hArray);
HARRAY	TanArray(HARRAY hArray);
HARRAY	SqrtArray(HARRAY hArray);
HARRAY	LogArray(HARRAY hArray);
HARRAY	PowArray(HARRAY hArray, double x);

HARRAY	AddArray(HARRAY hArray1, HARRAY hArray2);
HARRAY	SubArray(HARRAY hArray1, HARRAY hArray2);
HARRAY	MulArray(HARRAY hArray1, HARRAY hArray2);
HARRAY	DivArray(HARRAY hArray1, HARRAY hArray2);




#endif // ARRAY_H_
