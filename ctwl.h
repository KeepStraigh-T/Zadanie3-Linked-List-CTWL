#ifndef _CTWL_
#define _CTWL_

#define LIST_ERROR 1


typedef struct TWN
{
	float data;
	struct TWN* prev;
	struct TWN* next;
}TWN;

typedef struct 
{
	TWN* cur;
}CTWL;

CTWL* ctwl_create_empty(void);
TWN* twn_create_node_random(void);
CTWL* ctwl_create_empty(void);
CTWL* ctwl_create_random(unsigned int size);
void ctwl_print_list(CTWL* list);
#endif
