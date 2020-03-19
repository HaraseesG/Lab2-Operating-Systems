#ifndef QUEUE_H_
#define QUEUE_H_

#define MEMORY 1024

typedef struct
{
  int printers;
  int scanners;
  int modems;
  int cds;
  int *availableMem[MEMORY];
} resources;

typedef struct
{
  int arrivalTime;
  int priority;
  int processTime;
  int memBytes;
  int printers;
  int scanners;
  int modems;
  int cds;
  int pid;
  int memAddress;
  int allocated;
  int paused;
} process;

typedef struct node
{
  process process;
  struct node *next;
} node_pointer;

extern void enqueue(node_pointer *queue, process process);
extern process dequeue(node_pointer *queue);
#endif
