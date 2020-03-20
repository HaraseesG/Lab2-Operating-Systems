#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include "queue.h"

#define PRINTERS 2
#define SCANNERS 1
#define MODEMS 1
#define CDS 2

void initMem(resources * resources) {
    // initalize memory for the res_struct (resources) to 0. Memory is given as a variable MEMORY and is 1024 initially
    // Resources has an attribute called availableMem[MEMORY]
    // for every element i between 0 and MEMORY, set the availableMem[i] of the resource struct to 0
    for (int i = 0; i < MEMORY; i++) {
        resources -> availableMem[i] = 0;
    }
}

int allocateMem(int size, int reserve, resources * resources) {
    // size is the amount of memory needed, reserve is always 64 (needed in case a real time process is queued), and *resources is the current job resource
    int reserved, address;
    int available = 0;

    reserved = reserve;

    // check for available memory
    // for every i in range of reserved + 1 (65 onwards to keep first 64 clear), and while i < MEMORY and available < size, increment i
    // if the availableMem of resources at i-1 is 0 and the availableMem at i is 0,
    // increment available by 1
    for (int i = reserved + 1; i < MEMORY && available < size; i++) {
    if (resources -> availableMem[i - 1] == 0 && resources -> availableMem[i] == 0) {
      available++;
    }
    }

    // if the size is less than or equal to available
    // for i in range of reserved and while i < MEMORY and available > 0; increment i
    // if the availableMem at position i is 0
    // if the available is greater than 0
    // set the availableMem at i of that resource to 1
    // decrement available by 1
    // and if the size isn't less than or equal to available
    // address = -1;
    if (size <= available) {
      for (int i = reserved; i < MEMORY && available > 0; i++) {
        if (resources -> availableMem[i] == 0) {
          if (available > 0) {
            resources -> availableMem[i] = 1;
            available--;
            address = (i - size) + 1;
          }
        }
      }
    }
    else {
      address = -1;
    }

    // return the address
    return address;
}

int allocateResources(resources *resource, process processes) {
  // check to see if there are enough resources available
  // if resource -> printers - process.printers < 0 OR resource -> scanners - process.scanners <0 OR resource -> modems - process.modems <0 OR resource -> cds - process.cds < 0 {return 0}
  // if the printers/scanners/modems/cds held by resources - the printers/scanners/modems/cds held by process is less than 0
    // return 0
  // else
    // set the printers/scanners/modems/cds in resources to itself minus the printers/scanners/modems/cds held by the process
    // return 1
  if (resource -> printers > 0 && resource -> scanners > 0 && resource -> modems > 0 && resource -> cds > 0){
    if ((resource -> printers - processes.printers) < 0){
      return 0;
    }else{
      resource -> printers = resource -> printers - processes.printers;
    }

    if ((resource -> scanners - processes.scanners) < 0){
      return 0;
    }else{
      resource -> scanners = resource -> scanners - processes.scanners;
    }

    if ((resource -> modems - processes.modems) < 0){
      return 0;
    }else{
      resource -> modems = resource -> modems - processes.modems;
    }

    if ((resource -> cds - processes.cds) < 0){
      return 0;
    }else{
      resource -> cds = resource -> cds - processes.cds;
    }

    return 1;
  }else{
    return 0;
  }
}

void clearMem(resources *resources) {
  // for i in range 0 to MEMORY increment i
    // set the resource availableMem[i] to 0
  for (int i = 0; i < MEMORY; i++) {
    resources -> availableMem[i] = 0;
  }
}

void freeMem(resources *resources, int index, int size) {
  // for i in range of index to size, increment i
    // set the resource availableMem[i] to 0
  for (int i = index; i < size; i++) {
    resources -> availableMem[i] = 0;
  }
}

void clearResources(resources *resources) {
  // reset all resources to their original full values
  resources -> printers = 2;
  resources -> scanners = 1;
  resources -> modems = 1;
  resources -> cds = 2;
}

void freeResources(resources *resources, process processes) {
  // set all resources to themselves plus the process held resources
  resources -> printers += processes.printers;
  resources -> scanners += processes.scanners;
  resources -> modems += processes.modems;
  resources -> cds += processes.cds;
}

void loadJobQueue(char *dispatchlist, node_pointer *queue, process tempProcess) {
  // create a FILE and open dispatchlist as a readable
  // create a buffer of 256 or 512 (512 is playing super safe)
  FILE *fp = fopen(dispatchlist,"r");
  char buffer[256];

  while(fgets(buffer, 256, fp) != NULL) {
    // create a char pointer
    // set the contents of that pointer to a tokenized version of the buffer content seperated at " , "
    // initially a counter to 0
    char *token;
    token = strtok(buffer, " , ");
    int counter = 0;
    while (token != NULL) {
      // if the counter is 0, set the tempProcess.arrivalTime to atoi(pointer);
      // if the counter is 1, set the tempProcess.priority to atoi(pt);
      // and keep going until a counter of 7. Base this on the process struct in queue.h
      // Keep in mind that these are not else if statements. They are all individual if statements
      if (counter == 0) {
        tempProcess.arrivalTime = atoi(token);
      }
      if (counter == 1) {
        tempProcess.priority = atoi(token);
      }
      if (counter == 2) {
        tempProcess.processTime = atoi(token);
      }
      if (counter == 3) {
        tempProcess.memBytes = atoi(token);
      }
      if (counter == 4) {
        tempProcess.printers = atoi(token);
      }
      if (counter == 5) {
        tempProcess.scanners = atoi(token);
      }
      if (counter == 6) {
        tempProcess.modems = atoi(token);
      }
      if (counter == 7) {
        tempProcess.cds = atoi(token);
      }
      token = strtok(NULL, ", ");
      counter++;
    }
    tempProcess.pid = 0;
    tempProcess.memAddress = -1;
    tempProcess.allocated = 0;
    tempProcess.paused = 0;
    enqueue(queue, tempProcess);
  }
  fclose(fp);
}
