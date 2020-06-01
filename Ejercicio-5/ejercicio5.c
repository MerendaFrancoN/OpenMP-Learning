#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define SIZE 11 

/*                  EJERCICIO 5: Suma de arreglos
    Realice un programa OpenMP que realice la suma de dos arreglos 
    componente a componente y deje el resultado en un nuevo arreglo.
    Ejecute el programa variando el número de threads.
*/

int main(int argc, char **argv){
    
    /*Shared Variables*/
    int A[11] = {1,2,3,4,5,6,7,8,9,10,11};
    int B[11] = {1,2,3,4,5,6,7,8,9,10,11};
    int RESULT[11];
    int index; //Index
    
    /*Private Variable*/
    int tid; //ThreadID

    /*Para variar el numero de threads o utilizo ésta funcion, o
      Seteo una variable de entorno --> $ export OMP_NUM_THREADS=4 */
    omp_set_num_threads(atoi(argv[1]));
    
    //Sección paralela
    #pragma omp parallel shared(A,B,RESULT,index) private(tid)
    {
      tid = omp_get_thread_num();//Solo para mostrar
      #pragma omp for //Reparto suma entre los threads
        for(index=0;index < SIZE;index++){
          RESULT[index] = A[index] + B[index];
          
          //Check who is doing the sum
          printf("Thread N°%d - Calculated = %d\n",tid, RESULT[index]);
        }
    }

    /*Print RESULT*/
    for(int i=0; i<SIZE; i++)
      printf("%d ",RESULT[i]);
}