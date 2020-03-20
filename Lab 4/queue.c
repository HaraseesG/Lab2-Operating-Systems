#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


void enqueue(node_pointer *queue, process process) {
  /*initalize a new node_pointer '*currentNode' and set it equal to queue;
  loop through to the end of the queue
  while currentNode -> next != NULL
    set current node to currentNode -> next
  allocate space with malloc for currentNode -> next to sizeof(node);
  set currentNode -> next -> process to process;
  set currentNode -> next -> next to NULL;*/
	node_pointer *currentNode = queue;
	while (currentNode->next != NULL) {
		currentNode = currentNode->next;
	}

	currentNode-> next = (*node_pointer)malloc(sizeof(node_pointer));
	currentNode->next->process = process;
	currentNode->next->next = NULL;
}

process dequeue(node_pointer *queue) {
  /*check if queue has relevant elements and if it is exit. If not:
  create a struct process (as defined in queue.h) and initialize it to queue -> next -> process;
  set queue -> next to queue -> next -> next
  return process*/
	if (queue->next == NULL) {
		printf("queue is empty, exiting.\n");
		exit(0);
	}
	process newProcess = queue->next->process;

	queue->next = queue->next->next;
	return newProcess;
}