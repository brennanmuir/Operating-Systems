/*
Brennan Muir
Operating Systems
A5
4/2/18

REFERENCES:
Course Hero
coursehero.com/file/p7uoes1/c-Pure-paging-Pure-paging-does-not-require-the-operating-system-to-allocate-the/

This document that i found looks like it is taken from a textbook that describes the process of pure paging.
It also shows how to complete the solution.
*/

/*
Write a C program that is passed a virtual address (decimal) on the command
line and have it output the page number and offset for the given address.
*/


#include <stdio.h>

int main(int argc, char *argv[]){
  unsigned long page;
  unsigned long offset;
  unsigned long address;

  address = atoll(argv[1]);
  page = address >>12;
  offset = address & 0xfff;

  printf("The address %lu contains: \n", address);
  printf("page number = %lu\n", page);
  printf("offset = %lu\n", offset);

  return 0;
}
