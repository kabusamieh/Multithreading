//Khalid Abusamieh
//Linux

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define handle_error_en(en, msg) \
	do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

volatile int running_threads = 0;

pthread_t thread[3];

int numOfElements;

struct Results{
	int sum;
	int product;
}Results;

void *findSum(void *array_ptr){

	int i;

	int *elements = (int*)array_ptr;

	for(i = 0; i < numOfElements; i++){
		
		Results.sum += elements[i];
	}

	running_threads -= 1;

return NULL;
}


void *findProduct(void *array_ptr){

	int i;

	int *elements = (int*)array_ptr;

	Results.product = 1;

	for(i = 0; i < numOfElements; i++){
		
		Results.product *= elements[i];
	}

	running_threads -= 1;

return NULL;
}

int getArrayInput(int n, int *array_ptr){

		int input;

		int numberOfElements = 0;

	printf("Creating Array...\n-\n");

		for(;;){
		
		printf("Enter a positive value (Negative to close):\n");

			if (scanf("%d",&input) != 1){

				printf("\nThat wasn't an Integer\nTry Again\n");

				exit(EXIT_FAILURE);
			}

		if (input >= 0){

			if (numberOfElements == n){

				n += 1;

				array_ptr = realloc(array_ptr, n * sizeof(int));
			}

			array_ptr[numberOfElements++] = input;
		}

		
		else{
	
			printf("\nNumber of Integers: %d\n", numberOfElements);

			break;

			}

		}

	return numberOfElements;

		}

void joinThreads(int numberOfThreads){
	
	int i;

	int s;

	while(numberOfThreads >= 0){

		s = pthread_join(thread[numberOfThreads], NULL);

		if (s != 0){

			handle_error_en(s, "pthread_create");

		}

		numberOfThreads--;

	}

}

void createThreads(int *array_ptr){
	
	int s;

	s = pthread_create(&thread[0], NULL, findSum, (void *)array_ptr);

	if (s != 0){
	
		handle_error_en(s, "pthread_create");
	}
	
	running_threads +=1;



	s = pthread_create(&thread[1], NULL, findProduct, (void *)array_ptr);

	if (s != 0){
	
		handle_error_en(s, "pthread_create");
	}
	
	running_threads +=1;
}

int main(){

	int n = 1;

	int *array_ptr = malloc(n * sizeof(int));

		numOfElements = getArrayInput(n, array_ptr);

		createThreads(array_ptr);

		while(running_threads > 0){

			sleep(1);

		}

		joinThreads(1);

		printf("\nThe Sum is %d\nThe Product is %d\n",Results.sum, Results.product);

	return(0);

}
