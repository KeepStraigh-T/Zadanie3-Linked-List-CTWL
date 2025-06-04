#include <stdio.h>
#include <stdlib.h>
#include "ctwl.h"


TWN* twn_create_node(float new_data)
{
	TWN* new_node = (TWN*) malloc(sizeof(TWN));

	if(new_node == NULL)
		return NULL;

	new_node->data = new_data;
	new_node->next = new_node;
	new_node->prev = new_node;

	return new_node;	
}

TWN* twn_create_node_random(void)
{
	TWN* new_node = (TWN*) malloc(sizeof(TWN));

	if(new_node == NULL)
		return NULL;

	new_node->next = new_node;
	new_node->prev = new_node;

	return new_node;
}

CTWL* ctwl_create_empty(void)
{
	CTWL* list = (CTWL*) malloc(sizeof(CTWL));

	if(list == NULL)
		return NULL;

	list->cur = NULL;

	return list;
}

void ctwl_destroy(CTWL* list)
{
	if(list == NULL || list->cur == NULL)
		return;
	
	TWN* next;
	TWN* start = list->cur;
	TWN* temp = start->next;
		
	while (temp != start)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}

	free(start);

	free(list);
}

CTWL* ctwl_create_random(unsigned int size)
{
	CTWL* list = ctwl_create_empty();
	TWN* head;
	TWN* new_node;

	if(list == NULL)
		return NULL;

	if(size == 0)
		return list;

	head = twn_create_node_random(); // First node in the list

	if(head == NULL)
	{
		free(list);
		return NULL;
	}

	list->cur = head; // Sets cursor on the first node
	TWN* previous = head;

	for(unsigned int i = 1; i < size; i++)
	{
		new_node = twn_create_node_random();
		
		if(new_node == NULL)
		{
			ctwl_destroy(list);
			printf("List creation failed");
			return NULL;
		}
		
		previous->next = new_node;
		new_node->prev = previous;
		previous = new_node;
	}

	head->prev = previous;
	previous->next = head;

	return list;
}

void ctwl_print_list(CTWL* list)
{
	if(list == NULL || list->cur == NULL)
		return;

	TWN* temp = list->cur;
	
	do
	{
		if(temp == NULL)
		{
			printf("One of the nodes has pointer to NULL\n");
			break;
		}

		printf("%0.2f\n", temp->data);
		temp = temp->next;
	}
	while(temp != list->cur);
	
	printf("\n");
}

unsigned int ctwl_length(CTWL* list)
{
	if(list == NULL || list->cur == NULL)
		return 0;

	TWN* start = list->cur;
	TWN* temp = list->cur;
	
	unsigned int counter = 0;

	do
	{
		temp = temp->next;
		counter++;
	} while (temp != start);
	
	return counter;
}

void ctwl_cursor_step_right(CTWL* list)
{
	if(list == NULL || list->cur == NULL)
		return;

	list->cur = list->cur->next;
}

void ctwl_cursor_step_left(CTWL* list)
{
	if(list == NULL || list->cur == NULL)
		return;

	list->cur = list->cur->prev;
}

TWN* ctwl_insert_right(CTWL* list, float data)
{
	if(list == NULL)
		return NULL;

	if(list->cur == NULL) // If the list has no nodes
	{
		TWN* first_node = twn_create_node(data);
		list->cur = first_node;
		return first_node;
	}

	TWN* new_node = twn_create_node(data);
	TWN* temp = list->cur->next;
	
	list->cur->next = new_node;
	new_node->prev = list->cur;
	new_node->next = temp;
	temp->prev = new_node;

	return new_node;
}

TWN* ctwl_insert_left(CTWL* list, float data)
{
	if(list == NULL)
		return NULL;
	
	if(list->cur == NULL) // If the list has no nodes
	{
		TWN* first_node = twn_create_node(data);
		list->cur = first_node;
		return first_node;
	}

	TWN* new_node = twn_create_node(data);

	if(new_node == NULL)
		return NULL;

	TWN* temp = list->cur->prev;

	list->cur->prev = new_node;
	new_node->next = list->cur;
	new_node->prev = temp;
	temp->next = new_node;

	return new_node;
}

char ctwl_delete(CTWL* list)
{
	if(list == NULL)
		return LIST_ERROR;

	if(list->cur == NULL)
		return CWTL_FAIL;
	
// If only one node in the list
	if(list->cur->next == list->cur && list->cur->prev == list->cur)
	{
		free(list->cur);
		list->cur = NULL;
		return CWTL_OK;
	}

	TWN* to_delete = list->cur;
	TWN* previous = list->cur->prev;
	TWN* next = list->cur->next;

	previous->next = next;
	next->prev = previous;
	list->cur = next;
	
	free(to_delete);

	return CWTL_OK;
}

CTWL* ctwl_cyclic_cover(CTWL* list, unsigned int period)
{
	if(list == NULL || list->cur == NULL)
		return NULL;

	if(period == 0)
		return NULL;

	unsigned int list_length = ctwl_length(list);

	if(list_length % period != 0)
	{ 
		printf("Period does not divide list_length without reminder\n");
		return NULL;
	}

	// List that covers initial list has equal size
	else if(period == list_length)
	{
		CTWL* cover_list = list;
		return cover_list;
	}

	// Cover list has only one node
	else if(period == 1)
	{
		TWN* temp = list->cur;
		float value = 0;

		// Sum of values of all nodes of initial list
		do
		{
			value += list->cur->data;
			list->cur = list->cur->next;
		} while(list->cur != temp);

		CTWL* cover_list = ctwl_create_random(1);

		if(cover_list == NULL)
			return NULL;

		cover_list->cur->data = value;

		return cover_list;
	}

	else if(list_length % period == 0)
	{
		CTWL* cover_list = ctwl_create_empty();

		if(cover_list == NULL)
			return NULL;

		TWN* init_pos = list->cur;
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

			TWN* cover_node = ctwl_insert_left(cover_list, temp_data);
			
			if(cover_node == NULL)
			{
				printf("Failed to create or insert node in cover list\n");
				ctwl_destroy(cover_list);
				return NULL;
			}

			list->cur = list->cur->next;
		}

		list->cur = init_pos;
		
		return cover_list;
	}

	else
	{
		printf("Undefined error\n");
		return NULL;
	}
	
	

}