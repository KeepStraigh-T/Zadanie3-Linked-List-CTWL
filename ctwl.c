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
	if(list == NULL)
		return;
	else if(list->cur == NULL)
	{
		free(list);
		return;
	}
	
	TWN* start = list->cur;
	TWN* temp = start->next;
	TWN* next;
		
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
	else if(size == 0)
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
		// Connect nodes
		previous->next = new_node;
		new_node->prev = previous;
		previous = new_node;
	}
	// Connect first and last nodes
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
			return;
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
		if(first_node == NULL)
			return NULL;

		list->cur = first_node;
		return first_node;
	}

	TWN* new_node = twn_create_node(data);
	if(new_node == NULL)
		return NULL;

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
		if(first_node == NULL)
			return NULL;

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
		return CTWL_FAIL;
	
// If only one node in the list
	if(list->cur->next == list->cur && list->cur->prev == list->cur)
	{
		free(list->cur);
		list->cur = NULL;
		return CTWL_OK;
	}

	TWN* to_delete = list->cur;
	TWN* previous = list->cur->prev;
	TWN* next = list->cur->next;

	previous->next = next;
	next->prev = previous;
	list->cur = next;
	
	free(to_delete);

	return CTWL_OK;
}
