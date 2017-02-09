#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_CASES 25
#define CASE_MODE 0
#define MONEY_MODE 1

typedef struct
{
	int caseno;
	int value;
	int taken;
} casing;


casing cases[TOTAL_CASES];
int casesleft = TOTAL_CASES;


void initarrays(int*);
void initcases();
int listcases(int);
void quicksort(int*, int, int);		// sorts an array of cases
int partition(int*, int, int);		// helper to quicksort
casing* readcase();					// read user selection
casing* casematch(casing*, int, int);		// matches an int to any entry in cases


int main()
{
	initcases();
	// .....
	// play();
	
	return 0;
}


void initarrays(int* mlist)
{
	mlist[0] = 1;
	mlist[1] = 5;
	mlist[2] = 10;
	mlist[3] = 25;
	mlist[4] = 50;
	mlist[5] = 75;
	mlist[6] = 100;
	mlist[7] = 200;
	mlist[8] = 300;
	mlist[9] = 400;
	mlist[10] = 500;
	mlist[11] = 750;
	mlist[12] = 1000;
	int i;
	for(i = 13; i < TOTAL_CASES; i++)
	{
		mlist[i] = mlist[i-13] * 1000;
	}
}

void initcases()
{
	// print a welcome screen with the rules
	// .....
	int* moneylist = (int*)malloc(sizeof(int)*TOTAL_CASES);
	initarrays(moneylist);
	casesleft = TOTAL_CASES;
	int i;
	time_t t;
	srand((unsigned) time(&t));
	
	// generate the cases
	for(i = 0; i < TOTAL_CASES; i++)
	{		
		cases[i].caseno = i;
		// search to see if value was recorded previously
		int flag = 0;
		int random;
		do 
		{
			random = moneylist[rand() % TOTAL_CASES];
			int j;
			for(j = 0; j < i; j++)
			{
				if(random == cases[j].value)
				{
					flag = 1;
					break;
				}
				flag = 0;
			}
			
		} while(flag == 1);
		cases[i].value = random;
		cases[i].taken = 0;	
	}
	free(moneylist);
	moneylist = NULL;
}

void quicksort(int* array, int start, int end)
{
	if(start - end != 0)
	{
		int pivot = partition(array, start, end);
		quicksort(array, start, pivot-1);
		quicksort(array, pivot, end);
	}
}

int partition(int* array, int i, int j)
{
	int pivot = (i + j)/2;
	while(i < j)
	{
		while(array[i] < array[pivot])
		{
			i += 1;
		}
		while(array[j] > array[pivot])
		{
			j -= 1;
		}
		if(array[i] > array[pivot] && array[j] < array[pivot])
		{
			int temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
	}
	return i;
}

int listcases(int mode)
{
	int* available = (int*)malloc(sizeof(int)*casesleft);
	int i;
	for(i = 0; i < TOTAL_CASES; i++)
	{
		if(cases[i].taken == 0)
		{
			if(mode == MONEY_MODE)
			{
				available[i] = cases[i].value;
			}
			if(mode == CASE_MODE)
			{
				available[i] = cases[i].caseno;
			}
			else
			{ 
				return 1;
			}
		}		 
	}
	quicksort(available, 0, casesleft);
	printf("cases avaiable to pick from:\n");
	for(i = 0; i < casesleft; i++)
	{
		printf("%d\n", available[i]);
	}
	free(available);
	available = NULL;
	return 0;
}

casing* readcase()
{
	char* input = (char*)malloc(sizeof(char)*1000);
	do 
	{
		gets(input);
		if(strcmp(input, "exit") == 0)
		{
			// free all arrays
			free(input);
			input = NULL;
			
			// exit the program
			exit(0);
		}
		if(strcmp(input, "cases") == 0)
		{
			printf("\n");			
			listcases(CASE_MODE);
		}
		if(strcmp(input, "help") == 0)
		{
			printf("\n");
			// send to help screen
		}
		if(atoi(input) > 0)
		{
			casing* val = casematch(cases, casesleft, atoi(input));
			if(val != NULL)
			{
				free(input);
				input = NULL;
				return val;
			}
		}
		else
		{
			printf("ERROR: You have inputted an invalid number!\n");
			printf("Type \"cases\" for a list of available cases.\n");
		}
	} while(1);
}

casing* casematch(casing* array, int size, int key)
{
	casing* ptr = array;
	int i;
	for(i = 0; i < size; i++)
	{
		if(ptr->caseno == key && ptr->taken == 0)
		{
			return ptr;		// SUCCESS
		}
		ptr += i;
	}
	return NULL;				// FAILURE
}

void play()
{
	// assume that arrays are already set up properly
	// list all the cases available
	int i;
	// points to a case in the case array
	casing** chosen = (casing**)malloc(sizeof(casing*));
	listcases(CASE_MODE);
	printf("Choose a case to keep!\n  >  ");
	// read whether the selection is valid
	*chosen = readcase();
	do 
	{
		printf("Pick a case to eliminate!\n  >  ");
		
	} while(casesleft > 2);
	
	free(chosen);
	chosen = NULL;
}
