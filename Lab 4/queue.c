#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


void push(node_pointer *queue, process process) {
  /*initalize a new node_pointer '*currentNode' and set it equal to queue;
  loop through to the end of the queue
  while currentNode -> next != NULL
    set current node to currentNode -> next
  allocate space with malloc for currentNode -> next to sizeof(node);
  set currentNode -> next -> process to process;
  set currentNode -> next -> next to NULL;*/
	node_pointer currentNode = queue;
	while (currentNode.next != NULL) {
		currentNode = currentNode.next;
	}
	malloc(sizeof(currentNode.next));
	currentNode.next.process = process;
	currentNode.next.next = NULL;
}

process pop(node_pointer *queue) {
  /*check if queue is empty and if it is exit. If not:
  create a struct process (as defined in queue.h) and initialize it to queue -> next -> process;
  create a struct node_pointer (as defined in queue.h) and initalize it to queue -> next
  set queue -> next to queue -> next -> next
  free node_pointer
  return process*/
	if (queue == NULL) {
		printf("queue is empty, exiting.\n");
		exit(0);
	} else {
		struct process newProcess = queue.next.process;
		//why create this new pointer?
		struct node_pointer newPointer = queue.next;
		queue.next = queue.next.next;

	}
	return newProcess;
}