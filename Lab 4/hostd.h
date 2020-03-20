#ifndef HOSTD_H_
#define HOSTD_H_

#include "queue.h"

extern void printCurrentProcess(process processes);
extern void runProcess(node_pointer * dequeue_queue, node_pointer * enqueue_queue, char *argv[]);

#endif
