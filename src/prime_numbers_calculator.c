/*
 ============================================================================
 A simple prime number calculator
 Once it reaches the limit that is entered, they are saved in a .csv file
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"

int* newInt();
int listNumbers(LinkedList* primeNumbers);
int saveToText(char* path, LinkedList* primeNumbers);
int getText(char buffer[], char* message);
int getInt(int* pResult, char* message, char* errorMessage, int min);

int main(void) {
	setbuf(stdout, NULL);

	int number = 1;
	int notPrime;
	int to;
	int counter = 0;

	int* primeNumber;
	LinkedList* primeNumbers = ll_newLinkedList();

	getInt(&to, "\nUp to what number do you want to search?\n >> ", "ERROR\n", 1);

	do{
		notPrime = 0;
		counter++;
		number++;

		for(int i = 2; i < number; i++){
			if(number % i == 0){
				notPrime = 1;
				break;
			}
		}

		if(notPrime == 0){
			primeNumber = newInt();

			if(primeNumber != NULL){
				*primeNumber = number;
				ll_add(primeNumbers, primeNumber);
			}
			else{
				printf("\n[ERROR] full memory");
				break;
			}
		}

		if(counter == 100000 || number == to-1){
			if(saveToText("prime_numbers.csv", primeNumbers) == 1){
				printf("\nsaved...");
				ll_clear(primeNumbers);
				counter = 0;
			}
		}
	}
	while(number < to);

	return EXIT_SUCCESS;
}


int* newInt(){
	int* pAux;

	pAux = (int*) malloc(sizeof(int));

	return pAux;
}


static int isNumeric(char* string){
    int rtn = 1;
    int i = 0;

    if(string[0] == '-'){
        i = 1;
    }

    for( ; string[i] != '\0'; i++){
        if(string[i] == '.')
        {
            if((string[i] > '9' || string[i] < '0') && (string[i] != '.')){
                rtn = 0;
                break;
            }
        } else
            {
                if((string[i] > '9' || string[i] < '0') && (string[i] != '.')){
                    rtn = 0;
                    break;
             }
        }

    }

    return rtn;
}


int getText(char buffer[], char* message){
	int rtn = -1;

	if(buffer != NULL && message != NULL){
		fflush(stdin);
		printf("%s", message);
		fgets(buffer, 4096, stdin);

		if(buffer[strlen(buffer) - 1] == '\n'){
			buffer[strlen(buffer) - 1] = '\0';
		}

		rtn = 0;
	}

	return rtn;
}


int getInt(int* pResult, char* message, char* errorMessage, int min){
	int rtn = -1;
	int number;
	char buffer[4096];

	if(pResult != NULL && message != NULL && errorMessage != NULL){
		do{
			getText(buffer, message);

			if(isNumeric(buffer)){
				number = atoi(buffer);

				if(number >= min){
					*pResult = number;
					rtn = 1;
				}
				else{
					printf("%s", errorMessage);
				}
			}
			else{
				printf("%s", errorMessage);
			}

		}while(rtn == -1);
	}

	return rtn;
}


int listNumbers(LinkedList* primeNumbers){
	int rtn = -1;
	int size;
	int* primeNumber;

	size = ll_len(primeNumbers);

	for(int i = 0; i < size; i++){
		primeNumber = ll_get(primeNumbers, i);
		printf("\n%-d", *primeNumber);
	}

	return rtn;
}


int saveToText(char* path, LinkedList* primeNumbers){
	int rtn = -1;
	int size;
	int* primeNumber;
	FILE* pFile;

	pFile = fopen(path, "a");

	if(pFile != NULL){
		size = ll_len(primeNumbers);

		for(int i = 0; i < size; i++){
			primeNumber = ll_get(primeNumbers, i);

			fprintf(pFile, "%d\n", *primeNumber);
		}

		fclose(pFile);

		rtn = 1;
	}

	return rtn;
}



