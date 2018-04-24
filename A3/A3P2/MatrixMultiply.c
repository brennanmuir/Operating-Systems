// Brennan Muir
// CS4540 Spring 2018
// A3


// References
// The Single UNIX Specification, Version 2
// pubs.opengroup.org/onlinepubs/7908799/xsh/pthread.h.html

// Linux Programmer's Manual PTHREAD_CREATE(3)
// man7.org/linux/man-pages/man3/pthread_create.3.html

// The Pthreads Library
// www.cs.nmsu.edu/~jcook/Tools/pthreads/library.html

// How to multiply Matrices - Used this to find the math of how to mutliply 2 matrices. Used in the math method
// geeksforgeeks.orc/c-program-multiply-two-matrices/


// Assignment Details

// Given 2 matrices A and B
// A contains M rows and K columns, B contains K rows and N columns
// A[M,K].....B[K,N]
// The matrix product, C, contains M rowns and N columns
// C[M,N]
// Calculate each element C_i,j_ in a separate worker thread.
// Create MxN worker Threads
// The main/parent thread will initialize the matrices A and B. Decalre as global data so each woker thread has access to A,B,C


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h> // POSIX Threads

// Taken from the assignment sheet
// Matrices A and B can be initialized statically, as shown below:
# define M 3
# define K 2
# define N 3

int A[M][K] = {
  {1,4},
  {2,5},
  {3,6}};

int B[K][N] = {
  {8,7,6},
  {5,4,3}};

int C[M][N];

// Passing parameters to each thread
// Parent thread will create MxN worker threads, passing each worker tha values of row i and col j
// Requires passing 2 parameters to each thread.
// Create a data structure using a struct.

// The members of this structure are i and j, and the struct appears as follows:
// Taken from the assignment sheet
struct v
{
  int i; // row
  int j; // col
};

void *math(void *arg){

  struct v* matrix = (struct v*)arg;

  int i, j, k;

  i = matrix->i;

  j = matrix->j;

  C[i][j] = 0;

  for(k=0; k< N; k++){
    C[i][j]+=A[i][k]*B[k][j];
  }

  return 0;
}

int main(int argc, char *argv[]) {
  // Pthreads programs will create the worker threads using the strategy shown below
  // Create M * N worker Threads
  int i;
  int j;
  pthread_t workers[M*N]; // Dimensions of C

// Taken from the assignment sheet
// For the height and width of C
  for(i=0; i<M; i++){
    for(j=0; j<N; j++){
      struct v *data = (struct v *) malloc(sizeof(struct v)); // Allocate memory the size of our struct
      data->i=i;
      data->j=j;
      // Now, create the thread passing it data as a parameter
      int wThread=pthread_create(&workers[i*N + j], NULL, math, (void *)data);
    }
  }

// Taken from the assignment sheet
// Wait for threads to complete. Once all worker threads have completed, the main thread will output the product containined in Matrix C.
// Wait on several threads. enclose the join operation with a simple loop.
  for(i=0; i<M*N; i++){
    pthread_join(workers[i],NULL);
  }

// Print out the matrix result
  printf("Given the hard-coded dimensions of Matrix A and Matrix B, here is the result for Matrix C:\n\n");
  // Matrix C has the dimensions C[M][N]
  for(i=0;i<M;i++){
    for(j=0;j<N;j++){
      if(j!=N-1){
        printf("|%d|", C[i][j]);
      }
      else{
        printf("|%d|", C[i][j]);
      }
    }
    printf("\n------------\n");
  }
  printf("\n");
return 0;
}
