#ifndef _CTWL_
#define _CTWL_

#define CTWL_OK 1
#define CTWL_FAIL -1
#define PRINT_OK 2
#define PRINT_FAIL -2
#define LIST_ERROR -10


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
void ctwl_destroy(CTWL* list);
unsigned int ctwl_length(CTWL* list);
void ctwl_cursor_step_right(CTWL* list);
void ctwl_cursor_step_left(CTWL* list);
TWN* ctwl_insert_right(CTWL* list, float data);
TWN* ctwl_insert_left(CTWL* list, float data);
char ctwl_delete(CTWL* list);
CTWL* ctwl_cyclic_cover(CTWL* list, unsigned int period);
#endif
