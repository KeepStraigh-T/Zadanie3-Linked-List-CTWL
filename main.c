#include <stdio.h>
#include <stdlib.h>
#include "ctwl.h"


int main(void)
{
	CTWL* list = ctwl_create_empty();
	
	for(int i = 1; i < 6; i++)
	{
		ctwl_insert_right(list, (float) i);
		list->cur = list->cur->next;
	}
	
	list->cur = list->cur->next;

	ctwl_print_list(list);

	printf("Length: %d\n", ctwl_length(list));
	printf("Cursor: %0.2f\n", list->cur->data);
	
	ctwl_destroy(list);

	return 0;
}
