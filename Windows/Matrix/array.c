#include "stdio.h"
#include "stdlib.h"
#include "array.h"
#include "math.h"



HARRAY CreateArray(size_t size)
{
	ARRAY *pArray;																						/* Pointer struct yaratildigi icin alan tahsis edilmeli */
																										/* Normal struct yaratilsa malloc'a gerek yoktu */
	if ((pArray = malloc(sizeof(ARRAY))) == NULL)
	{
		fprintf(stderr, "malloc error\n");
		exit(EXIT_FAILURE);
	}

	if ( (pArray->pdArray = malloc( sizeof(size_t)*size )) == NULL)
	{
		fprintf(stderr, "malloc error\n");
		exit(EXIT_FAILURE);
	}
	
	pArray->size = size;

	return pArray;
}


HARRAY CreateArrayWithZeros(size_t size)
{
	ARRAY *pArray;																						/* Pointer struct yaratildigi icin alan tahsis edilmeli */
																										/* Normal struct yaratilsa malloc'a gerek yoktu */
	if ((pArray = malloc(sizeof(ARRAY))) == NULL)
	{
		fprintf(stderr, "malloc error\n");
		exit(EXIT_FAILURE);
	}

	if ((pArray->pdArray = malloc(sizeof(double) * size)) == NULL)
	{
		fprintf(stderr, "malloc error\n");
		exit(EXIT_FAILURE);
	}

	pArray->size = size;

	for (size_t i = 0; i < size; i++)
			pArray->pdArray[i] = 0;

	return pArray;
}


HARRAY CreateArrayWithValues(const double *pd, size_t size)
{
	ARRAY *pArray;																						/* Pointer struct yaratildigi icin alan tahsis edilmeli */
																										/* Normal struct yaratilsa malloc'a gerek yoktu */
	if ((pArray = malloc(sizeof(ARRAY))) == NULL)
	{
		fprintf(stderr, "malloc error\n");
		exit(EXIT_FAILURE);
	}

	if ((pArray->pdArray = malloc(sizeof(double) * size)) == NULL)
	{
		fprintf(stderr, "malloc error\n");
		exit(EXIT_FAILURE);
	}

	pArray->size = size;

	for (size_t i = 0; i < size; i++)
		pArray->pdArray[i] = pd[i];

	return pArray;
}


void CloseArray(HARRAY hArray)
{
	ARRAY *pArray = (ARRAY *)hArray;
	
	free(pArray->pdArray);
	free(pArray);
}


HARRAY SinArray(HARRAY hArray)
{
	ARRAY *pArray = (ARRAY *)hArray;

	for (size_t i = 0; i < pArray->size; i++)
	pArray->pdArray[i] = sin(pArray->pdArray[i]);

	return pArray;
}


HARRAY CosArray(HARRAY hArray)
{
	ARRAY *pArray = (ARRAY *)hArray;

	for (size_t i = 0; i < pArray->size; i++)
		pArray->pdArray[i] = cos(pArray->pdArray[i]);

	return pArray;
}


HARRAY TanArray(HARRAY hArray)
{
	ARRAY *pArray = (ARRAY *)hArray;

	for (size_t i = 0; i < pArray->size; i++)
		pArray->pdArray[i] = tan(pArray->pdArray[i]);

	return pArray;
}


HARRAY SqrtArray(HARRAY hArray)
{
	ARRAY *pArray = (ARRAY *)hArray;

	for (size_t i = 0; i < pArray->size; i++)
		pArray->pdArray[i] = sqrt(pArray->pdArray[i]);
		
	return pArray;
}


HARRAY LogArray(HARRAY hArray)
{
	ARRAY *pArray = (ARRAY *)hArray;

	for (size_t i = 0; i < pArray->size; i++)
		pArray->pdArray[i] = log(pArray->pdArray[i]);

	return pArray;
}


HARRAY PowArray(HARRAY hArray, double x)
{
	ARRAY *pArray = (ARRAY *)hArray;

	for (size_t i = 0; i < pArray->size; i++)
		pArray->pdArray[i] = pow(pArray->pdArray[i], x);

	return pArray;
}


HARRAY AddArray(HARRAY hArray1, HARRAY hArray2)
{
	ARRAY *pArray1 = (ARRAY *)hArray1;
	ARRAY *pArray2 = (ARRAY *)hArray2;
	ARRAY *pArrayMin;
	ARRAY *pArrayMax;
	ARRAY *pArrayRes = (ARRAY *)hArray1;


	if (pArray1->size > pArray2->size)
	{
		pArrayMax = pArray1;
		pArrayMin = pArray2;
	}
	else
	{
		pArrayMax = pArray2;
		pArrayMin = pArray1;
	}

	for (size_t i = 0; i < pArrayMin->size; i++)
		pArrayRes->pdArray[i] = pArrayMin->pdArray[i] + pArrayMax->pdArray[i];

	if ((pArrayMax->size - pArrayMin->size) != 0)
	{
		for (size_t i = pArrayMin->size; i < pArrayMax->size; i++)
			pArrayRes->pdArray[i] = pArrayMax->pdArray[i] + pArrayMin->pdArray[ i % pArrayMin->size];
	}

	return pArrayRes;
}


HARRAY SubArray(HARRAY hArray1, HARRAY hArray2)
{
	ARRAY *pArray1 = (ARRAY *)hArray1;
	ARRAY *pArray2 = (ARRAY *)hArray2;
	ARRAY *pArrayMin;
	ARRAY *pArrayMax;
	ARRAY *pArrayRes = (ARRAY *)hArray1;


	if (pArray1->size > pArray2->size)
	{
		pArrayMax = pArray1;
		pArrayMin = pArray2;
	}
	else
	{
		pArrayMax = pArray2;
		pArrayMin = pArray1;
	}

	for (size_t i = 0; i < pArrayMin->size; i++)
		pArrayRes->pdArray[i] = pArrayMin->pdArray[i] - pArrayMax->pdArray[i];

	if ((pArrayMax->size - pArrayMin->size) != 0)
	{
		for (size_t i = pArrayMin->size; i < pArrayMax->size; i++)
			pArrayRes->pdArray[i] = pArrayMax->pdArray[i] - pArrayMin->pdArray[i % pArrayMin->size];
	}

	return pArrayRes;
}


HARRAY MulArray(HARRAY hArray1, HARRAY hArray2)
{
	ARRAY *pArray1 = (ARRAY *)hArray1;
	ARRAY *pArray2 = (ARRAY *)hArray2;
	ARRAY *pArrayMin;
	ARRAY *pArrayMax;
	ARRAY *pArrayRes = (ARRAY *)hArray1;


	if (pArray1->size > pArray2->size)
	{
		pArrayMax = pArray1;
		pArrayMin = pArray2;
	}
	else
	{
		pArrayMax = pArray2;
		pArrayMin = pArray1;
	}

	for (size_t i = 0; i < pArrayMin->size; i++)
		pArrayRes->pdArray[i] = pArrayMin->pdArray[i] * pArrayMax->pdArray[i];

	if ((pArrayMax->size - pArrayMin->size) != 0)
	{
		for (size_t i = pArrayMin->size; i < pArrayMax->size; i++)
			pArrayRes->pdArray[i] = pArrayMax->pdArray[i] * pArrayMin->pdArray[i % pArrayMin->size];
	}

	return pArrayRes;
}


HARRAY DivArray(HARRAY hArray1, HARRAY hArray2)
{
	ARRAY *pArray1 = (ARRAY *)hArray1;
	ARRAY *pArray2 = (ARRAY *)hArray2;
	ARRAY *pArrayMin;
	ARRAY *pArrayMax;
	ARRAY *pArrayRes = (ARRAY *)hArray1;


	if (pArray1->size > pArray2->size)
	{
		pArrayMax = pArray1;
		pArrayMin = pArray2;
	}
	else
	{
		pArrayMax = pArray2;
		pArrayMin = pArray1;
	}

	for (size_t i = 0; i < pArrayMin->size; i++)
		pArrayRes->pdArray[i] = pArrayMin->pdArray[i] / pArrayMax->pdArray[i];

	if ((pArrayMax->size - pArrayMin->size) != 0)
	{
		for (size_t i = pArrayMin->size; i < pArrayMax->size; i++)
			pArrayRes->pdArray[i] = pArrayMax->pdArray[i] / pArrayMin->pdArray[i % pArrayMin->size];
	}

	return pArrayRes;
}







/*
	for (size_t i = 0; i < pArray->size; i++)
	{
		pArray->pdArray[i] = sqrt(pArray->pdArray[i]);
		printf("%f\n", pArray->pdArray[i]);
	}

*/




