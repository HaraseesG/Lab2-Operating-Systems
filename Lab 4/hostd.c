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

          if ((address = allocateMem(temp_process-> memBytes, 0, &resource)) != -1)
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

      //check
      printf("%d\n", flag);
      clearMem(&resource);

      if (p1_queue-> next != NULL && flag == false)
      {//just testing
        printf("priority 1\n");
      }else if (p2_queue-> next != NULL && flag == false)
      {
        printf("priority 2\n");
      }else if (p3_queue-> next != NULL && flag == false)
      {
        printf("priority 3\n");
      }

      if (p1_queue -> next != NULL && flag == false)
      {
        while (p1_queue->next != NULL)
        {
          //set temp_process to next process in p1_queue
          temp_process = &p1_queue -> next -> process;

          //Set memAddress and allocate appropriate resources
          address = allocateMem(temp_process->memBytes, 64, &resource);
          allocated = allocateResources(&resource, *temp_process);

          if (address != -1)
          {//if memory can be allocated
            temp_process -> memAddress = address;

            if (allocated != 0)
            {//if resources can be allocated
              temp_process -> allocated = allocated;
              enqueue(temp_queue, *temp_process);
              dequeue(p1_queue);
            }else
            {//if resources cannot be allocated
              while ((allocated = allocateResources(&resource, *temp_process)) == 0)
              {//while they cannot be allocated run the process that is queued to free those resources
                runProcess(temp_queue, p2_queue, argv);
              }
              temp_process -> allocated = allocated;
              enqueue(temp_queue, *temp_process);
              dequeue(p1_queue);

              if (temp_queue -> next -> next == NULL && p1_queue -> next == NULL)
              {
                runProcess(temp_queue, p2_queue, argv);
              }
            }
          }else
          {//if mem can't be allocated
            if (temp_queue -> next -> next != NULL)
            {//if there are multiple processes in temp, run the fooker
              runProcess(temp_queue, p2_queue, argv);
            }else
            {
              enqueue(p1_queue, pop(p1_queue));
              clearMem(&resource);
            }
          }
        }
        flag = true;
      }else if (p2_queue -> next != NULL && flag == false)
      {
        while (p2_queue->next != NULL)
        {
          //set temp_process to next process in p2_queue
          temp_process = &p2_queue -> next -> process;

          //Set memAddress and allocate appropriate resources
          address = allocateMem(temp_process->memBytes, 64, &resource);
          allocated = allocateResources(&resource, *temp_process);

          if (address != -1)
          {//if memory can be allocated
            temp_process -> memAddress = address;

            if (allocated != 0)
            {//if resources can be allocated
              temp_process -> allocated = allocated;
              enqueue(temp_queue, *temp_process);
              dequeue(p2_queue);
            }else
            {//if resources cannot be allocated
              while ((allocated = allocateResources(&resource, *temp_process)) == 0)
              {//while they cannot be allocated run the process that is queued to free those resources
                runProcess(temp_queue, p3_queue, argv);
              }
              temp_process -> allocated = allocated;
              enqueue(temp_queue, *temp_process);
              dequeue(p2_queue);
            }
            if (temp_queue -> next -> next == NULL && p2_queue -> next == NULL)
            {
              runProcess(temp_queue, p3_queue, argv);
            }
          }else
          {//if mem can't be allocated
            if (temp_queue -> next -> next != NULL)
            {//if there are multiple processes in temp, run the fooker
              runProcess(temp_queue, p2_queue, argv);
            }else
            {
              enqueue(p1_queue, pop(p1_queue));
              clearMem(&resource);
            }
          }
        }
        flag = true;
      }else if (p3_queue -> next != NULL && flag == false)
      {
        while (p3_queue->next != NULL)
        {//set temp_process to next process in p2_queue
          temp_process = &p3_queue -> next -> process;

          //Set memAddress and allocate appropriate resources
          address = allocateMem(temp_process->memBytes, 64, &resource);
          allocated = allocateResources(&resource, *temp_process);

          if (address != -1)
          {//if memory can be allocated
            temp_process -> memAddress = address;

            if (allocated != 0)
            {//if resources can be allocated
              temp_process -> allocated = allocated;
              enqueue(temp_queue, *temp_process);
              dequeue(p3_queue);
            }else
            {//if resources cannot be allocated
              while ((allocated = allocateResources(&resource, *temp_process)) == 0)
              {//while they cannot be allocated run the process that is queued to free those resources
                runProcess(temp_queue, p3_queue, argv);
              }
              if (allocated == 0)
              {
                clearResources(&resource);
                allocated = allocateResources(&resource, *temp_process);
              }

              temp_process -> allocated = allocated;
              enqueue(temp_queue, *temp_process);
              dequeue(p3_queue);
            }

            if (temp_queue -> next -> next == NULL && p3_queue -> next == NULL)
            {
              runProcess(temp_queue, p3_queue, argv);
            }
          }else
          {//if mem can't be allocated
            if (temp_queue -> next -> next != NULL)
            {//if there are multiple processes in temp, run the fooker
              runProcess(temp_queue, p3_queue, argv);
            }else
            {
              enqueue(p3_queue, pop(p3_queue));
              clearMem(&resource);
            }
          }
        }
      }

      printf("%d\n", flag);
      clearMem(&resource);

      if (hold > 0)
      {
        timer += hold;
      }else
      {
        timer ++;
      }
      flag = false;
  }
  //outside of the original while loop and within main

  int address, allocated;
  process temp_process;

  while (real_time_queue -> next != NULL)
  {//same as above outside of the loop
    temp_process = &real_time_queue -> next -> process;

    if ((address = allocateMem(temp_process-> memBytes, 0, &resource)) != -1)
    {//if memory is available
      temp_process -> memAddress = address;
    }else
    {
      runProcess(real_time_queue, real_time_queue, argv);
    }
    runProcess(real_time_queue, real_time_queue, argv);
  }

  clearMem(&resource);
  while(p1_queue -> next != NULL)
  {
    temp_process = &p1_queue -> next -> process;

    address = allocateMem(temp_process -> memBytes, 64, &resource);
    allocated = allocateResources(&resource, *temp_process);

    if (address != -1)
    {
      temp_process -> memAddress = address;
      if (allocated != 0)
      {
        temp_process -> allocated = allocated;

        enqueue(temp_queue, *temp_process);
        dequeue(p1_queue);
      }else
      {
        while ((allocated = allocateResources(&resource, *temp_process)) == 0)
        {
          runProcess(temp_queue, p2_queue, argv);
        }
        temp_process -> allocated = allocated;

        enqueue(temp_queue, *temp_process);
        dequeue(p1_queue);

        if (temp_queue -> next -> next == NULL && p1_queue -> next == NULL)
        {
          runProcess(temp_queue, p2_queue, argv);
        }
      }
    }else
    {
      runProcess(temp_queue, p2_queue, argv);
    }
  }

  clearMem(&resource);
  while(p2_queue -> next != NULL)
  {
    temp_process = &p2_queue -> next -> process;

    address = allocateMem(temp_process -> memBytes, 64, &resource);
    allocated = allocateResources(&resource, *temp_process);

    if (address != -1)
    {
      temp_process -> memAddress = address;
      if (allocated != 0)
      {
        temp_process -> allocated = allocated;

        enqueue(temp_queue, *temp_process);
        dequeue(p2_queue);
      }else
      {
        while ((allocated = allocateResources(&resource, *temp_process)) == 0)
        {
          runProcess(temp_queue, p3_queue, argv);
        }
        temp_process -> allocated = allocated;

        enqueue(temp_queue, *temp_process);
        dequeue(p2_queue);
      }

      if (temp_queue -> next -> next == NULL && p2_queue -> next == NULL)
      {
        runProcess(temp_queue, p3_queue, argv);
      }
    }else
    {
      if (temp_queue -> next -> next != NULL)
      {
        runProcess(temp_queue, p3_queue, argv);
      }else
      {
        enqueue(p2_queue, pop(p2_queue));
        clearMem(&resource);
      }
    }
  }

  clearMem(&resource);
  while(p3_queue -> next != NULL)
  {
    temp_process = &p3_queue -> next -> process;

    address = allocateMem(temp_process -> memBytes, 64, &resource);
    allocated = allocateResources(&resource, *temp_process);

    if (address != -1)
    {
      temp_process -> memAddress = address;
      if (allocated != 0)
      {
        temp_process -> allocated = allocated;

        enqueue(temp_queue, *temp_process);
        dequeue(p3_queue);
      }else
      {
        while ((allocated = allocateResources(&resource, *temp_process)) == 0)
        {
          runProcess(temp_queue, p3_queue, argv);
        }

        if (allocated == 0)
        {
          clearResources(&resource);
          allocated = allocateResources(&resource, *temp_process);
        }
        temp_process -> allocated = allocated;

        enqueue(temp_queue, *temp_process);
        dequeue(p3_queue);
      }

      if (temp_queue -> next -> next == NULL && p3_queue -> next == NULL)
      {
        runProcess(temp_queue, p3_queue, argv);
      }
    }else
    {
      if (temp_queue -> next -> next != NULL)
      {
        runProcess(temp_queue, p3_queue, argv);
      }else
      {
        enqueue(p3_queue, pop(p3_queue));
        clearMem(&resource);
      }
    }
  }

  return EXIT_SUCCESS;
}

void printCurrentProcess(process process)
{//print process struct info
  printf("Arrival Time: %d | Priority: %d | Time Left: %d | Size: %dbytes | Printers: %d | Scanners: %d | Modems: %d, CDs: %d\n", process.arrivalTime, process.priority, process.memBytes, process.printers, process.scanners, process.modems, process.cds);
}

void runProcess(node_pointer * dequeue_queue, node_pointer * enqueue_queue, char *argv[])
{
  int waiter, status;
  pid_t pid;

  process *process;
  process dequeue_job;
  dequeue_job = dequeue(dequeue_queue);
  process = & dequeue_job;

  pid = fork();
  if (process -> pid == 0)
  {
    process -> pid = (int) pid;
  }

  if (pid < (pid_t) 0)
  {
    exit(1);
  }

  if (pid == 0)
  {//child process
    execv("./process", argv);
  }else
  {//parent
    printCurrentProcess(*process);

    if (process -> priority == 0)
    {
      sleep(process -> processTime);
      kill(process -> pid, SIGINT);

      for (int i = 0; i < 15; i++)
      {
        waiter = waitpid(pid, &status, WNOHANG|WUNTRACED);

        if (waiter == -1)
        {
          printf("Process Failure\n");
          exit(-1);
        }else if (waiter == pid)
        {
          break;
        }else if (waiter == 0)
        {
          sleep(1);
        }
      }

      freeMem(&resource, process -> memAddress, process -> memBytes);
    }else
    {
      if (process -> paused == 0)
      {
        sleep(1);
        process -> processTime--;

        kill(process -> pid, SIGTSTP);
        process -> paused = 1;
        sleep(1);
      }

      freeMem(&resource, process -> memAddress, process -> memBytes);
      freeResources(&resource, *process);

      if (process -> priority == 1 || process -> priority == 2)
      {
        proc -> priority++;
      }else if (process -> priority == 3)
      {
        proc -> priority = 3;
      }

      if (process -> processTime == 0)
      {
        sleep(1);
        process -> processTime--;
        kill(process -> pid, SIGINT);

        for (int i = 0; i < 15; i++)
        {
          waiter = waitpid(pid, &status, WNOHANG|WUNTRACED);

          if (waiter == -1)
          {
            printf("Process Failed to terminate");
            exit(-1);
          }else if (waiter == pid)
          {
            break;
          }else if (waiter == 0)
          {
            sleep(1);
          }
        }
      }else
      {
        enqueue(enqueue_queue, *process);
      }
    }
  }
}