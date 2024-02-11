// Name: Samyog Koirala
// UID: 2358296

#include <stdio.h>  //To use printf and scanf
#include <pthread.h> // To use multi-threading
#include <stdlib.h> // To use malloc, calloc and realloc for memory dynamically
#include <math.h>  // To use built in math properties 
#include <unistd.h> // To use sleep function
#include <stdbool.h> // To use Boolean variables

typedef struct { // Creating a user-defined datatype using typedef
	int *numbers;
    int start;
    int end;
    int primes;
    int *prime_numbers; // Array for to prime numbers
} newVar; // Typedefining a structure as NewVar

// Checking for prime number
int check_primeNum(int num) {
    int i;
    if (num <= 1)
        return 0;
    for (i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

// Count the prime number present in files
void *count_primeNum(void *arg){
	newVar *values = (newVar *)arg;
	int i=0;
	for(i=values->start;i<= values->end; i++){
		if(check_primeNum(values->numbers[i])) {
			values->primes++;
			values->prime_numbers[values->primes - 1] = values->numbers[i];
		}
	}
	pthread_exit(NULL);
}

// Creating main function to run a program
int main(){
	int total_num = 0;
	int *numbers;
	int total_files = 3;
	FILE *files[total_files];
	// Creating the array for given 3 files
	char *filename[3] = {"PrimeData1.txt","PrimeData2.txt","PrimeData3.txt"};
	
	int i=0;
	for (i=0;i<total_files;i++){
		files[i] = fopen(filename[i],"r");
		if(files[i] == NULL){
			printf("File %d : Error in Opening the file.\n", i+1,filename[i]);
			exit(1);
		}else{
			printf("File %d : opened Succesfully.\n",i+1,filename[i]);
		}
		int num;
		//counting all the numbers in files
		while (fscanf(files[i], "%d", &num) != EOF){
			total_num = total_num + 1;
		}
		rewind(files[i]);
	}
	
	// Uisng malloc or dynamically allocating memory and reading number from files
	numbers = (int *) malloc(total_num*sizeof(int));
	int index = 0;
	
	for (i=0;i<total_files;i++){
		int num;
		// Counting all prime from files
		while (fscanf(files[i], "%d", &num) != EOF){
			numbers[index++] = num;
		}
		fclose(files[i]);
	}
	
	
	// Creating threads and dividing work equally
	int number_of_threads;
	
	// Prompting the number of threads
	printf("Enter the number of threads: ");
	scanf("%d",&number_of_threads);
	
	pthread_t threads[number_of_threads];
	newVar thread_data[number_of_threads];
	
	int total_num_per_threads = total_num/number_of_threads;
	int remainder = total_num%number_of_threads;
	int start = 0;
	for (i=0;i<number_of_threads;i++){
		int end = start + total_num_per_threads - 1;
		if(i<remainder){
			end++;
		}
		thread_data[i].numbers = numbers;
		thread_data[i].start = start;
		thread_data[i].end = end;
		thread_data[i].primes = 0;
		thread_data[i].prime_numbers = (int *)malloc(total_num_per_threads * sizeof(int));
		start = end + 1;
		pthread_create(&threads[i],NULL,count_primeNum, (void *)&thread_data[i]); // Creating the threads
	}
	
	// Joining all the threads
	for (i=0;i<number_of_threads;i++){
		pthread_join(threads[i],NULL);
	}
	
	// Storing the prime to new file named OutputPrimeData.txt
    FILE *OutputPrimeDataFile = fopen("OutputPrimeData.txt", "w");
    int totalPrimes = 0;
    for (i = 0; i < number_of_threads; i++) {
        totalPrimes += thread_data[i].primes;
    }
    fprintf(OutputPrimeDataFile, "\nTotal prime numbers are: %d\n", totalPrimes);
    printf("Total prime numbers are: %d\n", totalPrimes);
    for (i = 0; i < number_of_threads; i++) {
        fprintf(OutputPrimeDataFile, "\nThread %d found %d prime numbers.\n", i + 1, thread_data[i].primes);
        printf("Thread %d found %d prime numbers.\n", i + 1, thread_data[i].primes);
        int j=0;
        for ( j = 0; j < thread_data[i].primes; j++) {
            fprintf(OutputPrimeDataFile, "%d ", thread_data[i].prime_numbers[j]);
        }
        fprintf(OutputPrimeDataFile, "\n");
    }
    
    printf("\n------------------------------------------------------------------------------------------------\n\n");
    printf("The Prime Numbers are saved in a new file named: OutputPrimeData.txt \n\n");
	
	
	//closing new primenumber the file
	fclose(OutputPrimeDataFile);
	
	
	// Freeing allocated memory 
	free(numbers);
	free(thread_data);
	free(threads);
    // Returning 0 to stop program
	return 0;
}
