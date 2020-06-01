#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define MAX_ITERATION 50

/*
Realice un programa OpenMP el cual disponga de un conjunto de funciones capaces
de calcular el mínimo, máximo, la multiplicación y desviación estándar de un conjunto
de un millón de elementos contenidos en un arreglo.
Cada una de estas funciones deberá recibir por parámetro los datos a procesar y
deberá devolver el valor resultante.
Se pide que realice un programa OpenMP que sea capaz de realizar en paralelo todas
estas operaciones. El programa además deberá informar por pantalla que thread ha
realizado que operación.
Finalmente se pide que calcule el speedup de esta aplicación. Para realizar este
cálculo debe trabajar con los valores promedios obtenidos de 50 ejecuciones tanto
para la solución paralela como para la solución secuencial.

*/


//Array Operations
__uint64_t multiplyArray(__uint64_t* array, int n);
__uint64_t minArray(__uint64_t* array, int n);
__uint64_t maxArray(__uint64_t* array, int n);
double stdDeviation(__uint64_t* array, int n);

double timeIt(__uint64_t* array, int n, int sizeThreads, double* bestTime);

void fillArray(__uint64_t* array, int n);
void printArray(__uint64_t* array, int n);


int main(int argc, char **argv){
    
    //Array with unsigned 128 bits
    __uint64_t *array;
    int n, tid; //Array size -- Thread number
    double bestTimeSeq = 999.0, bestTimePll = 999.0, speedUp;

    n = atoi(argv[2]); // Size of array

    //Allocate Array with n elements
    array = (__uint64_t*)malloc( sizeof(__uint64_t) * n );

    //Fill array with some data
    fillArray(array, n);

    //Sequential Time - Unique Thread
    printf("-- RUNNING SEQUENTIAL... --\n");
    timeIt(array, n, 1, &bestTimeSeq);
    
    //SpeedUp numerator
    speedUp = bestTimeSeq;
    
    //Parallel Time + 1 thread
    printf("-- RUNNING PARALLEL... --\n");
    
    //SpeedUp calculate
    speedUp /= timeIt(array, n, atoi(argv[1]), &bestTimePll);
    

    printf("BEST TIME SEQUENTIAL = %lf\n", bestTimeSeq);
    printf("BEST TIME PARALELL = %lf\n", bestTimePll);

    printf("SPEEDUP = %lf\n", speedUp);

}

/*

*/
double timeIt(__uint64_t* array, int n, int sizeThreads, double* bestTime) {
    /*
        tA, tB - Time from A to point B.
        sequentialBest - Best sequential time
        avgTime - Average time on Parallel execution
    */
    double tA = 0.0, tB = 0.0, avgTime = 0.0;
    int tid;
    //Set the total threads and set size of the array
    omp_set_num_threads(sizeThreads);

    for(int execution = 0; execution < MAX_ITERATION; execution++){
    
        //Start clock
        tA = omp_get_wtime();

        #pragma omp parallel shared(array) private(tid)
        {
            tid = omp_get_thread_num();
            #pragma omp sections
            {    
                #pragma omp section
                {
                    //minArray(array, n);
                    printf("Thread N° %d -- MinValue = %llu\n", tid, minArray(array, n));
                }
                #pragma omp section
                {
                    //maxArray(array, n);
                    printf("Thread N° %d -- MaxValue = %llu\n", tid, maxArray(array, n));
                }
                #pragma omp section
                {
                    //multiplyArray(array, n);
                    printf("Thread N° %d -- Multiply = %llu\n", tid, multiplyArray(array, n));
                }
                    
                #pragma omp section
                {
                    //stdDeviation(array, n);
                    printf("Thread N° %d -- Standard Deviation = %lf\n", tid, stdDeviation(array, n));
                }
            }
        }
        tB = omp_get_wtime(); //Stop clock
        //Timing calculations
        avgTime += (tB-tA);

        if( (tB-tA) < *bestTime)
            *bestTime = (tB-tA);
    }  
    return avgTime / MAX_ITERATION;
}


void fillArray(__uint64_t* array, int n) {
    
    int index = 0;
    #pragma omp parallel for schedule(static) private(index)
    for(index = 0; index < n; index++){
        array[index] = (__uint64_t) rand() % 10 + (__uint64_t)1 ;
    }
}

void printArray(__uint64_t* array, int n) {
    int index;
    printf("[ ");
    for(index = 0; index < n; index++){
        printf("%llu ",array[index]);
    }
    printf("] \n\n");
}

__uint64_t multiplyArray(__uint64_t* array, int n){
    
    __uint64_t index;
    __uint64_t sum = 1;

    #pragma omp parallel for schedule(static) private(index) reduction (*:sum)
    for(index = 0; index < n; index++){
        sum = sum * array[index];
    }
    return sum;
}

__uint64_t minArray(__uint64_t* array, int n) {
    
    __uint64_t index;
    __uint64_t min_value = array[0];

    #pragma omp parallel for schedule(static) private(index) reduction (min : min_value)
    for(index = 0; index < n; index++){
        if(array[index] < min_value){
            min_value = array[index];  
        }
    }
    return min_value;
}

__uint64_t maxArray(__uint64_t* array, int n){
    
    __uint64_t index;
    __uint64_t max_value = array[0];

    #pragma omp parallel for schedule(static) private(index) reduction (min : max_value)
    for(index = 0; index < n; index++){
        if(array[index] > max_value){
            max_value = array[index];  
        }
    }
    return max_value;
}

double stdDeviation(__uint64_t* array, int n) {

    int index;
    double mean = 0, variance = 0;

    #pragma omp parallel for schedule(static)
    for(index = 0; index < n; index++){
        mean += array[index];
    }
    //Calculate mean
    mean /= n;

    // Calculate Variance
    #pragma omp parallel for schedule(static)
    for (index = 0; index < n; index++)
    {
        variance += pow((array[index] - mean), 2.0);
    }
    variance /= (n - 1);

    // Calculates the desviacion estandar
    return sqrt(variance);
}

