// Name : Samyog Koirala
// Student Id : 2358296

#include <stdio.h>  //To use printf and scanf
#include <pthread.h> // To use multi-threading
#include <stdlib.h> // To use malloc, calloc and realloc for memory dynamically
#include <math.h>  // To use built in math properties 
#include <unistd.h> // To use sleep function

//Global Variables 
double initial_value_of_pi = 0.0;
double final_value_of_pi = 0.0;  // Final value of pi
pthread_mutex_t mutex;  // Using Mutex to prevent race condition

typedef struct { // Creating a user-defined datatype using typedef
    int start;
    int finish;
    double sum;
} NewVar; // Typedefining a structure as NewVar

// Creating the initial value of pi
void *PI_calculations(void *p){
	NewVar *help = (NewVar *)p;
	double sum = 0.0;
	
	// Locking the mutex
	pthread_mutex_lock(&mutex);
	int i=0;
	// For loop used from start to ending point
    // Performing leibniz series
	for (i=help->start;i<help->finish;i++){
		double upperPart = pow(-1,i);
		double lowerPart = ((2*i)+1);
		
		// Updating the initial value of pi
		initial_value_of_pi = initial_value_of_pi + (upperPart/lowerPart);	
	}

	// Unlocking the  mutex
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}

// Main Fuinction to run the code
int main(){
	int Number_of_threads, Number_of_iterations;
	
	// Prompting the number of threads
	printf("Enter the Number of Thread: ");
	scanf("%d",&Number_of_threads);
	
	// Prompting the number of loops
	printf("Enter the Number of iterations: ");
	scanf("%d",&Number_of_iterations);
	
	// Slicing the work for numbers of loops
	int slices[Number_of_threads];
	
	// Creating the array of threads
	pthread_t thread[Number_of_threads];
		
	NewVar arguments[Number_of_threads]; 
	
	int iterations_Per_Threads = Number_of_iterations/Number_of_threads;
	int extra_iterations = Number_of_iterations%Number_of_threads;
	
	// Initializing the mutex 
	pthread_mutex_init(&mutex, NULL);
	
	
	int i=0;
	for (i=0;i<Number_of_threads;i++){
		slices[i] = iterations_Per_Threads;
	}
	for (i=0;i<extra_iterations;i++){
		slices[i] +=1;
	}
	
	// Calculating start and end for each thread
	for (i=0;i<Number_of_threads;i++){
		if(i==0){
			arguments[i].start = 0;
		}else{
			arguments[i].start = arguments[i-1].finish +1;
		}
		arguments[i].finish = arguments[i].start + slices[i]-1;
	}
	
	// Creating threads
	for (i=0;i<Number_of_threads;i++){
		pthread_create(&thread[i],NULL,PI_calculations,&arguments[i]);
	}
	
	// Joining the threads
	for (i=0;i<Number_of_threads;i++){
		pthread_join(thread[i],NULL);
	}
	
	// Destroying the mutex
	pthread_mutex_destroy(&mutex);
	
	// Calculating the final value of PI
	final_value_of_pi = initial_value_of_pi * 4;
	
	// Printing the value of pi
	printf("The value of PI is: %lf",final_value_of_pi);
    // Returning 0 to stop program
	return 0;
}