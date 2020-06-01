#include <stdio.h>
#include <omp.h>

int main(){
    //tid es una variable privada a cada thread
    int nthreads, tid;
    
    //Para variar el numero de threads o utilizo ésta funcion, o
    //Seteo una variable de entorno --> $ export OMP_NUM_THREADS=4
    omp_set_num_threads(4);
    
    //Sección paralela
    #pragma omp parallel private(tid) 
    {
        //Obtengo el id de cada thread
        tid = omp_get_thread_num();
        
        printf("Hola mundo desde el thread %d\n",tid);
        //Solo el thread maestro
        if(tid == 0){
            nthreads = omp_get_num_threads();
            printf("Numero total de threads = %d\n",nthreads);
        }
    }
}