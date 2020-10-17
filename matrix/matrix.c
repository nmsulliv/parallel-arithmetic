#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX 4 

// Used this as a reference: https://www.geeksforgeeks.org/multiplication-of-matrix-using-threads/

int matA[MAX][MAX]; 
int matB[MAX][MAX]; 

int matSumResult[MAX][MAX];
int matDiffResult[MAX][MAX]; 
int matProductResult[MAX][MAX]; 
int turn0 = 0, turn1 = 0, turn2 = 0; 

// int MAX = 0;

void fillMatrix(int matrix[MAX][MAX]) {
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            matrix[i][j] = rand()%10+1;
        }
    }
}

void printMatrix(int matrix[MAX][MAX]) {
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Fetches the appropriate coordinates from the argument, and sets
// the cell of matSumResult at the coordinates to the sum of the
// values at the coordinates of matA and matB.
void* computeSum(void* args) {
	int i, j;
	int k = turn0++;
	for (i = k ; i < (k + 1); i++) {
		for (j = 0; j < MAX; j++) { 
				matSumResult[i][j] = matA[i][j] + matB[i][j]; 
		}
	}
}

// Fetches the appropriate coordinates from the argument, and sets
// the cell of matSumResult at the coordinates to the difference of the
// values at the coordinates of matA and matB.
void* computeDiff(void* args) {
	int i, j;
	int k = turn1++;
	for (i = k; i < (k + 1); i++) {
		for (j = 0; j < MAX; j++) { 
				matDiffResult[i][j] = matA[i][j] - matB[i][j]; 
		}
	}
}

// Fetches the appropriate coordinates from the argument, and sets
// the cell of matSumResult at the coordinates to the inner product
// of matA and matB.
void* computeProduct(void* args) {
		int i, j, m;
		int k = turn2++;
		for (i = k; i < (k + 1); i++) {
			for (j = 0; j < MAX; j++) { 
				for (m = 0; m < MAX; m++) {
					matProductResult[i][j] += matA[i][m] * matB[m][j]; 
				}
			}
		}
}

// Spawn a thread to fill each cell in each result matrix.
// How many threads will you spawn?
int main() {
    srand(time(0));  // Do Not Remove. Just ignore and continue below.
    
    // 0. Get the matrix size from the command line and assign it to MAX
    // Using #define MAX 4 for now...
// 		printf("How large should the NxN matrices be? Enter an integer: ");
// 		scanf("%d", &MAX);

    // 1. Fill the matrices (matA and matB) with random values.
    fillMatrix(matA);
    fillMatrix(matB);

    // 2. Print the initial matrices.
    printf("Matrix A:\n");
    printMatrix(matA);
    printf("Matrix B:\n");
    printMatrix(matB);
    
    // 3. Create pthread_t objects for our threads.
    pthread_t threads[MAX];

    // 4. Create a thread for each cell of each matrix operation.
		int i;
    for(i = 0; i < MAX; i++) {
			  int* arg;
        pthread_create(&threads[i], NULL, computeSum, (void*)(arg));
			  pthread_create(&threads[i], NULL, computeDiff, (void*)(arg)); 
        pthread_create(&threads[i], NULL, computeProduct, (void*)(arg));

		}
    // You'll need to pass in the coordinates of the cell you want the thread
    // to compute.
    // 
    // One way to do this is to malloc memory for the thread number i, populate the coordinates
    // into that space, and pass that address to the thread. The thread will use that number to calcuate 
    // its portion of the matrix. The thread will then have to free that space when it's done with what's in that memory.
    
    // 5. Wait for all threads to finish.
		for (i = 0; i < MAX; i++) {
			pthread_join(threads[i], NULL);  
		}

    // 6. Print the results.
    printf("Results:\n");
    printf("Sum:\n");
    printMatrix(matSumResult);
    printf("Difference:\n");
    printMatrix(matDiffResult);
    printf("Product:\n");
    printMatrix(matProductResult);
    return 0;
  
}