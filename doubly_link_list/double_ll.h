/**
 * This header file defines the basic data structure for holding \
 * doubly linked list
 * Basic_Node is a node without data node attached.
 * Data_item is skeleton of Basic_Node combined with data.
 * This doubly linked list is assumed to be circular in nature.
 * Author: Hardik Balar
 * 
**/

#ifndef _double_ll_h_
#define _double_ll_h_
#include <stdio.h>
#include <stdlib.h>

typedef struct Data_Item_tag{
	char *name;
	char *address;
	char *country;
	int *contact_no;
}*Data_Item;

typedef struct Basic_Node_tag{
	struct Basic_Node_tag *flink;
	struct Basic_Node_tag *blink;
	Data_Item data;
}Basic_Node, *Node;

typedef struct List_tag{
	Basic_Node *point;
}*List;

#endif
