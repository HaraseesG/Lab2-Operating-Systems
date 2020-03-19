#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"
#include "utility.h"
#include "hostd.h"

//Assign final variables to represent total available resources of system
#define MEMORY 1024
#define PRINTERS 2
#define SCANNERS 1
#define MODEMS 1
#define CDS 2

//Initialize structs
process current_process;
resources resource;

node_pointer * job_queue = NULL;
node_pointer * real_time_queue = NULL;
node_pointer * p1_queue = NULL;
node_pointer * p2_queue = NULL;
node_pointer * p3_queue = NULL;
node_pointer * temp_queue = NULL;

void print_process(process process);

int main(int argc, char *argv[])
{
  //initalize resource parameters
  resource.printers = PRINTERS;
  resource.scanners = SCANNERS;
  resource.modems = MODEMS;
  resource.cds = CDS;

  //Allocate memory space for each queue
  job_queue = malloc(sizeof(node_pointer));
  real_time_queue = malloc(sizeof(node_pointer));
  p1_queue = malloc(sizeof(node_pointer));
  p2_queue = malloc(sizeof(node_pointer));
  p3_queue = malloc(sizeof(node_pointer));
  temp_queue = malloc(sizeof(node_pointer));

  //Since there are no elements in any queue yet, initialize the next struct to be NULL
  job_queue -> next = NULL;
  real_time_queue -> next = NULL;
  p1_queue -> next = NULL;
  p2_queue -> next = NULL;
  p3_queue -> next = NULL;
  temp_queue -> next = NULL;

  //Load dispatchlist into job_queue
  printf("Loading...\n");
  loadJobQueue("dispatchlist", job_queue, current_process);
  printf("Finished loading\n");
  initMem(&resource);
  int global_timer = 0;

  while (job_queue -> next != NULL || real_time_queue -> next != NULL || p1_queue -> next != NULL || p2_queue -> next != NULL || p3_queue -> next != NULL)
  {// while there are any elements in any of the active queues
      while (job_queue -> next != NULL && job_queue -> next -> process.arrivalTime <= global_timer)
      {//while there are any jobs in job queue and that job has an arrival time <= the amount of time that has passed, push job to appropriate queue
        current_process = dequeue(job_queue);
        if (current_process.priority == 3)
        {
          enqueue(p3_queue, current_process);
        }else if (current_process.priority == 2)
        {
          enqueue(p2_queue, current_process);
        }else if (current_process.priority == 1)
        {
          enqueue(p1_queue, current_process);
        }else
        {
          enqueue(real_time_queue, current_process);
        }
      }

      //init memAdd, allocated resources, process struct, bool flag to run process or not, and hold
      int address, allocated;
      process *temp_process;
      bool flag = false;
      int hold = 0;

      if (real_time_queue -> next != NULL)
      {//if the real time queue has an element in it
        while (real_time_queue -> next != NULL)
        {//for every element in the real time queue
          hold++;
          temp_process = &real_time_queue-> next-> process;

          if ((address = allocMem(temp_process-> memBytes, 0, &resource)) != -1)
          {//if memory can be allocated
            temp_process-> memAddress = address;
          }else
          {//if the memory cannot be allocated, run the current process to free resources
            runProcess(real_time_queue, real_time_queue, argv);
          }
          runProcess(real_time_queue, real_time_queue, argv);
        }
        flag = true;
      }

      printf("%d\n", flag);
      clearMem(&resource);

      if (p1_queue-> next != NULL && flag == false)
      {
        printf("priority 1\n");
      }else if (p2_queue-> next != NULL && flag == false)
      {
        printf("priority 2\n");
      }else if (p3_queue-> next != NULL && flag == false)
      {
        printf("priority 3\n");
      }

  }

}

void printCurrentProcess(process process)
{

}

void runProcess(node_pointer * pop_queue, node_pointer * push_queue, char *argv[])
{

}
