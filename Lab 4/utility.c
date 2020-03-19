// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "utility.h"
// #include "queue.h"
//
// #define PRINTERS 2
// #define SCANNERS 1
// #define MODEMS 1
// #define CDS 2

/*
void initMem(resources *resources)
{
  //initalize memory for the res_struct (resources) to 0. Memory is given as a variable MEMORY and is 1024 initially
  //Resources has an attribute called availableMem[MEMORY]
  //for every element i between 0 and MEMORY, set the availableMem[i] of the resource struct to 0
}

int allocateMem(int size, int reserve, resources *resources)
{ size is the amount of memory needed, reserve is always 64 (needed in case a real time process is queued), and *resources is the current job resource
  int reserved, address;
  int available= 0;

  reserved = reserve

  check for available memory
  for every i in range of reserved + 1 (65 onwards to keep first 64 clear), and while i < MEMORY and available < size, increment i
    if the availableMem of resources at i-1 is 0 and the availableMem at i is 0,
      increment available by 1.

  if the size is less than or equal to available
    for i in range of reserved and while i < MEMORY and available > 0; increment i
      if the availableMem at position i is 0
        if the available is greater than 0
          set the availableMem at i of that resource to 1
          decrement available by 1

          address = (i - size) + 1;
  and if the size isn't less than or equal to available
    address = -1;

  return the address
}

int allocateResources(resources *resources, process process)
{
  check to see if there are enough resources available

  if the printers/scanners/modems/cds held by resources - the printers/scanners/modems/cds held by process is less than 0
    return 0
  else
    set the printers/scanners/modems/cds in resources to itself minus the printers/scanners/modems/cds held by the process
    return 1
}

void clearMem(resources *resources)
{
  for i in range 0 to MEMORY increment i
    set the resource availableMem[i] to 0
}

void freeMem(resources *resources, int index, int size)
{
  for i in range of index to size, increment i
    set the resource availableMem[i] to 0
}

void clearResources(resources *resources)
{
  reset all resources to their original full values
  resources -> printers = 2;
  resources -> scanners = 1;
  resources -> modems = 1;
  resources -> cds = 2;
}

void freeResources(resources *resources, process process)
{
  set all resources to themselves plus the process held resources
  resources -> printers += process.printers
  resources -> scanners += process.scanners
  resources -> modems += process.modems
  resources -> cds += process.cds
}

void loadJobQueue(char *dispatchlist, node_pointer *queue, process tempProcess)
{
  create a FILE and open dispatchlist as a readable
  create a buffer of 256 or 512 (512 is playing super safe)

  while(fgets(buffer, 256/512 (depends on the choice above), FILE) != NULL)
  {
    create a char pointer
    set the contents of that pointer to a tokenized version of the buffer content seperated at " , "
    initially a counter to 0

    while the pointer is not null{
      if the counter is 0, set the tempProcess.arrivalTime to atoi(pointer);
      if the counter is 1, set the tempProcess.priority to atoi(pt);
      and keep going until a counter of 7. Base this on the process struct in queue.h
      Keep in mind that these are not else if statements. They are all individual if statements

      set the pointer to strtok (NULL, ", ");
      increment the counter by 1
    }

    close the file
  }

  tempProcess.pid = 0;
  tempProcess.memAddress = -1;
  tempProcess.allocated = 0;
  tempProcess.paused = 0;
  push the tempProcess into the given job queue
}
*/
