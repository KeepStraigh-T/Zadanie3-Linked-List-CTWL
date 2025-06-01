#include <stdio.h>
#include <stdlib.h>
#include "ctwl.h"


int main(void)
{
	CTWL* list = ctwl_create_random(5);

	if(list == NULL)
	{
		printf("list is NULL\n");
	}
	ctwl_print_list(list);

	return 0;
}
