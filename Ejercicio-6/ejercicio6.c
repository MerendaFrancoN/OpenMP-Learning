#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/*                EJERCICIO 6: Multiplicación de matrices (A x B)
    Realice un programa OpenMP que realice la multiplicación de 
    matrices.

*/

/*Matrix Utils*/
int *allocate1D2DMatrix(int rows, int columns);
void fillMatrix(int *matrixToFill, int rows, int columns);
void printMatrix(int *matrixToPrint, int rows, int columns);
int* multiplyParallelMatrix(int* A, int* B, int rowsA, int colsA, int rowsB, int colsB);

int main(int argc, char **argv){
    
    /*
      *rowsA - size of rows in A
      *columnsA - size of columns in A
      *rowsB - size of rows in B
      *columnsB - size of columns in B
      *A - Matrix to Multiply 
      *B - Matrix multiplier   
    */
    int rowsA, rowsB, colsA, colsB;
    int *A, *B, *result;

    //Set the total threads
    omp_set_num_threads(atoi(argv[1]));
    
    //Set the sizes of the matrix A
    rowsA = atoi(argv[2]);
    colsA = atoi(argv[3]);

    //Set the sizes of the matrix A
    rowsB = atoi(argv[4]);
    colsB = atoi(argv[5]);

    //Set the Matrixs
    A = allocate1D2DMatrix(rowsA, colsA);
    B = allocate1D2DMatrix(rowsB, colsB);
    
    
    //Fill Matrixs
    fillMatrix(A, rowsA, colsA);
    fillMatrix(B, rowsB, colsB);

    //Multiply
    result = multiplyParallelMatrix(A, B, rowsA, colsA, rowsB, colsB);

    //Print Results
    //printMatrix(result, rowsA, colsB);
    
}

int* multiplyParallelMatrix(int* A, int* B, int rowsA, int colsA, int rowsB, int colsB){
    
    /*Private Variables
        tid - Thread ID
        offsetA -  Rows Offset in MatrixA
        offsetB -  Rows Jump Offset in Matrix B
        sum - Accumulated sum
        indexMul - index of the current row-col multiplication
        rowIndex - index of Rows in A
        colIndex - index of Cols in B
    */
    int tid, offsetA, offsetB, sum, indexMul, rowIndex, colIndex; 
    double tA, tB;
    //Shared Variable
    int *result = allocate1D2DMatrix(rowsA, colsB); //Result Matrix
    
    //Control of sizes
    if(colsA != rowsB){
        printf("Matrix size error\n");
        return NULL;
    }
    
    //Timing
    tA = omp_get_wtime();

    //Multiply Matrixs
    #pragma omp parallel shared(result) private(tid, rowIndex, colIndex, sum, offsetA, offsetB, indexMul)
    {
      //Get Thread ID
      //tid = omp_get_thread_num();

      #pragma omp for schedule(static)
		for(rowIndex = 0; rowIndex < rowsA; rowIndex++){
			
            offsetA = rowIndex * colsA;
			
            for(colIndex=0; colIndex < colsB; colIndex++){
				sum = 0;
				for(indexMul=0; indexMul < rowsB; indexMul++){
                    offsetB = indexMul * colsB;
					sum += A[offsetA + indexMul] * B[offsetB + colIndex];
				}
                //printf("I'm THREAD N° %d\n", tid);
				result[rowIndex*colsB + colIndex] = sum;
			}
		}
    }

    //Timing
    tB = omp_get_wtime();
    printf("Time: %lf\n", tB-tA);

    return result;
}

int *allocate1D2DMatrix(int rows, int columns){
    int *matrix = (int *)malloc(rows * columns * sizeof(int));
    return matrix;
}

void fillMatrix(int *matrixToFill, int rows, int columns){
    int dataToCharge = 1;

    for (int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < columns; columnIndex++)
        {
            matrixToFill[(rowIndex * columns) + columnIndex] = dataToCharge++;
        }
    }
}

void printMatrix(int *matrixToPrint, int rows, int columns){
    printf("[\n");
    for (int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < columns; columnIndex++)
        {
            printf("%d ", matrixToPrint[rowIndex * columns + columnIndex]);
        }
        printf("\n");
    }
    printf("]");
}