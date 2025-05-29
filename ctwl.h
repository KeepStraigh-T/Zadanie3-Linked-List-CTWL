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

CTWL* ctwl_create_emty(void);

#endif
