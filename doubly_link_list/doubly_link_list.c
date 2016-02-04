  /**
   * The follwing C code roughly translates to below descriptions
   *  Create new doubly linked list
   *  Create new enqueuable item
   *  Create a new data item
   *  Test wheather an item is enqueued
   *  Test wheather a list is empty
   *  Add an item to head of list
   *  Add an item to tail of list
   *  Dequeue an item from the list
   *  Dequeue an item at the head of a list
   *  Author : Hardik Balar
   *
  **/

  #include <stdio.h>
  #include "dbg.h"
  #include "double_ll.h"

   List list_init()
   {
   	  //intialize the list head 'Anchor' with no data node attached 
      Basic_Node *Anchor = malloc(sizeof *Anchor);
      check_mem(Anchor);

      Anchor->flink = (struct Basic_Node_tag *)Anchor;
      check(Anchor->flink , "flink is NULL");
      Anchor->blink = (struct Basic_Node_tag *) Anchor;
      check(Anchor->blink , "blink is NULL");
      Anchor->data = NULL;

      struct List_tag *list_t = malloc(sizeof *list_t);
      check_mem(list_t);

      list_t->point = Anchor;
      
      return list_t;

      error:
        free(Anchor);
      	return NULL;
   }

  Data_Item create_data_node(char *name, char *address, char *country)
  {
      struct Data_Item_tag *data_node = malloc(sizeof *data_node);
      check_mem(data_node);
      data_node->name = name;
      data_node->address = address;
      data_node->country = country;

     return data_node;

     error:
     return NULL;
  }

  Node create_enqueuble_node(Data_Item data)
  { 
      struct Basic_Node_tag *node = malloc(sizeof *node);
      check_mem(node);
      node->data = data;
      node->blink = NULL;
      node->flink = NULL;

      return node;

      error:  
      return NULL;
  }

  List enqueue_item_at_head(Node node, List list)
  {
   	check(list->point != NULL, "NULL List passed");
    check(node->flink == NULL, "Not a valid node");
    check(node->data != NULL ,"Not a valid node-data");
      
      Node anchor = list->point;
      if(anchor->flink != anchor && anchor->blink != anchor)
      {  
      	anchor->flink->blink = node;
      	node->blink = anchor;
      	node->flink = anchor->flink;
      	anchor->flink = node;
      }
      else
      {
   
    	node->flink = list->point;
    	node->blink = list->point;
   	  anchor->flink = node;
   	  anchor->blink = node;
   	  }

   	return list;

   	error:
   	 return NULL;	
   }

  List enqueue_item_at_tail(Node node, List list)
  {
      check(list->point != NULL, "NULL List passed");
      check(node->flink == NULL, "Not a valid node");
      check(node->data != NULL ,"Not a valid node-data");
      
      Node anchor = list->point;

      if(anchor->blink != anchor && anchor->flink != anchor)
      {  
        anchor->blink->flink = node;
        node->blink = anchor->blink;
        anchor->blink =node;
        node->flink = list->point;
      }
      else
      {
   
        node->flink = list->point;
        node->blink = list->point;
        anchor->flink = node;
        anchor->blink = node;
      }

    return list;
    error:
    return NULL; 
  }

  int is_node_enqueued(Node node)
  {

    check(node != NULL, "NULL item passed");

    if((node->flink != NULL && node->blink != NULL) && node->data != NULL)
    return 0;
    else 
    return -1;

    error:
    return -1;
  }

  Node dequeue_item(Node node)
  {
    check(node->flink != NULL, "flink is null");
    check(node->blink != NULL, "blink is null");

    node->blink->flink = node->flink;
    node->flink->blink = node->blink;
    node->flink = NULL;
    node->blink =NULL;

    return node;
    error:
    return NULL;
  }

  int is_list_empty(List list)
  {
    check(list->point != NULL, "NULL List passed");
     
  	if(list->point->flink->data != NULL)
    {
      return 1;
    }
   
  	else 
    {
  		return 0;
    }
  	error:
  		return 0;
  }

  Node dequeue_item_from_head(List list)
  {
     check(list->point != NULL, "List is not valid");

     Node anchor = list->point;

     if(anchor->blink != anchor && anchor ->flink != anchor)
     {
     	Node node = anchor->flink;
     	node->flink->blink =anchor;
     	anchor->flink = node->flink;
     	node->flink = NULL;
     	node->blink = NULL;

     	return node;
     }
     else
     {
     	return NULL;
     }

     error:
     return NULL;
  }

  void print_list(List list)
  {

  	check(list !=NULL, "list is null");
  	Node anchor = list->point;
  	int node_count = 1;
  	Node flink_i = NULL; 
    Data_Item data = NULL;
    
  	for(flink_i = anchor->flink; flink_i->flink !=anchor; flink_i= flink_i->flink)
  	{
  		data = flink_i->data;
  		printf("Node %d => { Name: %s, Address: %s, Country: %s } \n",node_count, data->name, data->address, data->country);
  		node_count++;
  	}
  	  data = flink_i->data;
  		printf("Node %d => { Name: %s, Address: %s, Country: %s } \n",node_count, data->name, data->address, data->country);
  	
  	error:
  	return;
  }

  List do_stuff_over_list()
  {
      //the follwing part is testing of create doubly linked list
      // feel free to change it and see how the entire program works 
      struct List_tag *list = NULL;
      list = list_init();
      char *name ="Hardik";
      char *address="Dr. Grosz str";
      char *country = "Germany";

      Data_Item data_node = create_data_node(name,address,country);
      Node node = create_enqueuble_node(data_node);
     
      list = enqueue_item_at_head(node, list); //enq node at head
      int rc = is_node_enqueued(node);
      check(rc==0, "node is not enqueued");

      Data_Item data_node_2 = create_data_node("Dada","Simada Gam","India");
      Node node_2 = create_enqueuble_node(data_node_2);

      list =enqueue_item_at_tail(node_2, list); //enq node_2 at tail
      rc= is_node_enqueued(node_2);
      check(rc==0, "node_2 is not enqueued");

      node = dequeue_item(node); //deq node

      list = enqueue_item_at_tail(node, list); //end node at tail, so node_2 is at head
      rc = is_node_enqueued(node);
      check(rc==0, "node is not enqueued");


      rc = is_list_empty(list);
      if(rc != 0)
      printf("List is not empty\n");
   
      print_list(list);


      Node dequed_node = dequeue_item_from_head(list);
      rc = is_node_enqueued(dequed_node);
      check(rc !=0, "dequed_node is not dequeued");

      dequed_node = dequeue_item_from_head(list);
      rc = is_node_enqueued(dequed_node);
      check(rc !=0, "dequed_node is not dequeued");
      rc = is_list_empty(list);
      if(rc == 0)
        printf("List is now empty\n");

      Data_Item data_node_3 = create_data_node("Iron Man","La Cindrella","Spain");
      Node node_3 = create_enqueuble_node(data_node_3);

      list =enqueue_item_at_tail(node_3, list); //enq node_2 at tail
      rc= is_node_enqueued(node_3);
      check(rc==0, "node_3 is not enqueued");

      Data_Item data_node_4 = create_data_node("Jastin Tredaeu","Vancouver East","Canada");
      Node node_4 = create_enqueuble_node(data_node_4);

      list =enqueue_item_at_tail(node_4, list); //enq node_2 at tail
      rc= is_node_enqueued(node_4);
      check(rc==0, "node_4 is not enqueued");

      Data_Item data_node_5 = create_data_node("Barak Obama","White House","United States");
      Node node_5 = create_enqueuble_node(data_node_5);

      list =enqueue_item_at_tail(node_5, list); //enq node_2 at tail
      rc= is_node_enqueued(node_5);
      check(rc==0, "node_5 is not enqueued");

      Data_Item data_node_6 = create_data_node("Angela Merkel","Fredrich str.","Germany");
      Node node_6 = create_enqueuble_node(data_node_6);

      list =enqueue_item_at_tail(node_6, list); //enq node_2 at tail
      rc= is_node_enqueued(node_6);
      check(rc==0, "node_6 is not enqueued");

      Data_Item data_node_7 = create_data_node("David Cameroon","Sir David str","United Kingdom");
      Node node_7 = create_enqueuble_node(data_node_7);

      list =enqueue_item_at_tail(node_7, list); //enq node_2 at tail
      rc= is_node_enqueued(node_7);
      check(rc==0, "node_7 is not enqueued");

      Data_Item data_node_8 = create_data_node("Maek Zuckerburg","Beverly Hills","United States");
      Node node_8 = create_enqueuble_node(data_node_8);

      list =enqueue_item_at_tail(node_8, list); //enq node_2 at tail
      rc= is_node_enqueued(node_8);
      check(rc==0, "node_8 is not enqueued");

      return list; 
      error:
      return NULL;
  }

  int main(int argc, char **argv)
  {
       print_list(do_stuff_over_list());
   	   return 0;
  }
