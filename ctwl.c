#include <stdio.h>
#include <stdlib.h>
#include "ctwl.h"


CTWL* ctwl_create_empty(void)
{
	CTWL* list = (CTWL*) malloc(sizeof(CTWL));

	if(list == NULL)
		return NULL;

	list->cur = NULL;

	return list;
}

CTWL* ctwl_create_random(unsigned int size)
{
	CTWL* list = ctwl_create_empty();

	if(list == NULL)
		return NULL;

	
}


