// Task 1 of C**Program:
// Name: Samyog Koirala
// UID: 2358296

#include <stdio.h> 
#include <stdlib.h> 

//Creating a function to calculate the linear regression:
void linear_regression(char *filename,int *count, double *sum_of_X, double *sum_of_Y, double *sum_of_X_square, double *sum_of_Y_square, double *sum_of_XY, double *A, double *B){
	
    //now opening the files of datasets to read i.e "r" mode.
	FILE *fptr = fopen(filename, "r");	
	
	//Handling Error if any errors occors while opening file.
	if (fptr == NULL){
		printf("Error on Opening the file: %s.\n",filename);
		return 1;	
	}else{
		printf("File opened Successfully.\n");
	}
		
		
	//Reading data of files and finding sum of the data
	double x,y;
		
	while(fscanf(fptr,"%lf,%lf",&x,&y) != EOF){
		*sum_of_X +=x;
		*sum_of_Y +=y;
		*sum_of_X_square +=x*x;
		*sum_of_Y_square += y*y;
		*sum_of_XY +=x*y;
		(*count)++;
	}
	
	//Closing file
	fclose(fptr);
}

// Main Function to run code!
int main(){
	//Array of files
	char *filename[] = {"datasetLR1.txt","datasetLR2.txt","datasetLR3.txt","datasetLR4.txt"}; 
	int number_of_datasets = 4;  // Because we have 4 datasets
	double sum_of_X = 0.0;
	double sum_of_Y = 0.0;
	double sum_of_X_square = 0.0;
	double sum_of_Y_square = 0.0;
	double sum_of_XY = 0.0; 
	int count = 0; //Intializing the count variable for updating the number of the dataset 
	double A, B;
	double x,y;
	int i = 0;
	//using for loop to access all the datasets in the array
	for (i=0;i<number_of_datasets;i++){
		//calculating linear regression
		linear_regression(filename[i],&count,&sum_of_X, &sum_of_Y,&sum_of_X_square,&sum_of_Y_square,&sum_of_XY,&A,&B);
		
	}
	
	printf("********************************************************************************************************************-\n");
	
    printf("sum_of_X: %.2lf\n", sum_of_X);
    printf("sum_of_Y: %.2lf\n", sum_of_Y);
    printf("sum_of_X_square: %.2lf\n", sum_of_X_square);
    printf("sum_of_Y_square: %.2lf\n", sum_of_Y_square);
    printf("sum_of_XY: %.2lf\n", sum_of_XY);
    
    printf("********************************************************************************************************************-\n");
    //Now calculating coefficents (A and B) to find linear regression 
	B = ((count * sum_of_XY) - (sum_of_X * sum_of_Y)) / ((count * sum_of_X_square )- (sum_of_X * sum_of_X));
	A = ((sum_of_Y * sum_of_X_square) - (sum_of_X * sum_of_XY)) / ((count * sum_of_X_square )- (sum_of_X * sum_of_X));
	
	//Printing A and B
	printf("A: %.2lf\n", A);
    printf("B: %.2lf\n", B);
	
	printf("********************************************************************************************************************-\n\n");
			
	printf("For the all Datasets , the Linear Regression Equation is:  y = (%.2lf)x + (%.2lf)\n",B,A);
			
	// Prompt x to find y
	double new_value_of_x;
	printf("Enter a value of x : ");
	scanf("%lf", &new_value_of_x);
	
	// Printing equation for linear regression
	y = B*new_value_of_x + A;
	printf("The new value of y = %.2lf\n", y);
	
    // Returning 0 to end program
	return 0;
}
