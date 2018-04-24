// Brennan Muir
// CS4540 Spring 2018
// A3


// References
// 6.2.2 Creating Pipes in C
// tldp.org/LDP/lpg/node11.html

// The Single UNIX Specification, Version 2
// pubs.opengroup.org/onlinepubs/7908799/xsh/open.html

// The Open Group Base Specifications Issue 6
// pubs.opengroup.org/onlinepubs/000095399/basedefs/fcntl.h.html

// Code Wiki
// codewiki.wikidot.com/c:system-calls:open



// 1. Design a file copying program using ordinary pipes
// 2. Pass in 2 parameters: name of file to be copied and name of the new, copied file
// 3. Create an ordinary pipe and write the contesnts of the file to be copied to the pipe.
// 4. Child process will read file from the pipe and write it to the destination file.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // Access to POSIX OS API
#include <fcntl.h> // File Control Options - pubs.opengroup.org/onlinepubs/000095399/basedefs/fcntl.h.html

int main(int argc, char *argv[]) {
  // Initialize file descriptor array
  int fd[2]; // fd[0] is for reading, fd[1] is for writing

  char readBuffer[50];
  char writeBuffer[50];

  char* inputFile = argv[1];
  char* outputFile = argv[2];

  // Create pipe
  pipe(fd);

  // Check that 3 parameters are passed
  if(argc < 3){
    printf("Need 3 parameters (./FileCopy file1.txt file2.txt)\n");
    exit(1);
  }

  // Create Child Process
  if(fork()==0){
    close(fd[1]);

    int file = open(outputFile, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); //Set Permissions
    ssize_t size1 = read(fd[0], writeBuffer, sizeof(writeBuffer));

    close(fd[0]);

    write(file, writeBuffer, size1);
  }
  // Parent Process
  else{
    close(fd[0]);

    int inFile = open(inputFile, O_RDONLY);  //Read Only, readBuffer.
    ssize_t size2 = read(inFile, readBuffer, sizeof(readBuffer));

    write(fd[1], readBuffer, size2);

    close(fd[1]);
  }
  return 0;
}
