#include <stdio.h>
#include <stdlib.h>
#include "ctwl.h"


TWN* twn_create_node(float new_data)
{
	TWN* new_node = (TWN*) malloc(sizeof(TWN));

	if(new_node == NULL)
		return NULL;

	new_node->data = new_data;
	new_node->next = NULL;
	new_node->prev = NULL;

	return new_node;	
}

TWN* twn_create_node_random(void)
{
	TWN* new_node = (TWN*) malloc(sizeof(TWN));

	if(new_node == NULL)
		return NULL;

	new_node->next = NULL;
	new_node->prev = NULL;

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

CTWL* ctwl_create_random(unsigned int size)
{
	CTWL* list = ctwl_create_empty();
	TWN* head;
	TWN* new_node;

	if(list == NULL)
		return NULL;

	if(size == 0)
		return list;

	head = twn_create_node(66); // First node in the list

	if(head == NULL)
	{
		free(list);
		return NULL;
	}

	list->cur = head; // Sets cursor on the first node
	TWN* previous = head;

	for(unsigned int i = 1; i < size; i++)
	{
		new_node = twn_create_node(66);
		
		if(new_node == NULL)
			continue;
		
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
	if(list == NULL)
		return;

	TWN* temp = list->cur;

	do
	{
		printf("%0.2f\n", list->cur->data);
		list->cur = list->cur->next;
	}
	while(list->cur->next != temp->next);
	
	printf("\n");
}




