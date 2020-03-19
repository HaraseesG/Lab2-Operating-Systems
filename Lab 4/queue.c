// #include <stdio.h>
// #include <stdlib.h>
// #include "queue.h"

/*
void push (node_pointer *queue, process process)
{
  initalize a new node_pointer '*currentNode' and set it equal to queue;
  loop through to the end of the queue
  while currentNode -> next != NULL
    set current node to currentNode -> next

  allocate space with malloc for currentNode -> next to sizeof(node);
  set currentNode -> next -> process to process;
  set currentNode -> next -> next to NULL;
}

process pop(node_pointer *queue)
{
  check if queue is empty and if it is exit. If not:
  create a struct process (as defined in queue.h) and initialize it to queue -> next -> process;
  create a struct node_pointer (as defined in queue.h) and initalize it to queue -> next

  set queue -> next to queue -> next -> next

  free node_pointer
  return process
}
*/
