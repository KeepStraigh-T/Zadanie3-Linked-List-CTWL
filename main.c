#include <stdio.h>
#include <stdlib.h>
#include "ctwl.h"


CTWL* ctwl_cyclic_cover(CTWL* list, unsigned int period)
{
	if(list == NULL || list->cur == NULL)
		return NULL;
	else if(period == 0)
	{
		printf("Program terminates: Period must be a positive number\n");
		return NULL;
	}

	unsigned int list_length = ctwl_length(list);
	if(list_length % period != 0)
	{
		printf("Program terminates: Period does not divide list_length without reminder\n");
		return NULL;
	}

	CTWL* cover_list = ctwl_create_empty();
	if(cover_list == NULL)
		return NULL;

	TWN* init_pos = list->cur;
	// Amount of nodes to be combined to get node in cover list
	unsigned int cover_width = list_length / period;
	
	for(unsigned i = 0; i < period; i++)
	{
		float temp_data = 0;
		
		for(unsigned j = 0; j < cover_width; j++)
		{
			temp_data += list->cur->data;

			for(unsigned step = 0; step < period; step++)
				ctwl_cursor_step_right(list);
		}
		// Add new node to cover list
		TWN* cover_node = ctwl_insert_left(cover_list, temp_data);
		if(cover_node == NULL)
		{
			printf("Program terminates: Failed to create or insert node in cover list\n");
			ctwl_destroy(cover_list);
			list->cur = init_pos;
			return NULL;
		}
		// Moves cursor to next a[i]
		list->cur = list->cur->next;
	}
	// Return cursor to initial position
	list->cur = init_pos; 
		
	return cover_list;
}

int main(void)
{
	CTWL* list = ctwl_create_empty();
	if(list == NULL)
		return CTWL_FAIL;

	for(int i = 0; i < 15; i++)
	{
		ctwl_insert_right(list, (float) i);
		list->cur = list->cur->next;
	}
	
	list->cur = list->cur->next;

	ctwl_print_list(list);
	printf("Length: %d\n", ctwl_length(list));
	printf("Cursor: %0.2f\n\n", list->cur->data);
	
	CTWL* cover = ctwl_cyclic_cover(list, 3);
	if(cover == NULL)
		return CTWL_FAIL;

	ctwl_print_list(cover);
	printf("Length: %d\n", ctwl_length(cover));
	printf("Cursor: %0.2f\n\n", cover->cur->data);

	ctwl_destroy(cover);
	ctwl_destroy(list);

	return 0;
}
