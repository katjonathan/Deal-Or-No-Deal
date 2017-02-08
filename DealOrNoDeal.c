#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int* moneylist;		// gives errors unless I put it here


void initarrays();
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


void initarrays()
{
	
	moneylist = (int*)malloc(sizeof(int)*TOTAL_CASES);
	moneylist[0] = 1;
	moneylist[1] = 5;
	moneylist[2] = 10;
	moneylist[3] = 25;
	moneylist[4] = 50;
	moneylist[5] = 75;
	moneylist[6] = 100;
	moneylist[7] = 200;
	moneylist[8] = 300;
	moneylist[9] = 400;
	moneylist[10] = 500;
	moneylist[11] = 750;
	moneylist[12] = 1000;
	int i;
	for(i = 13; i < TOTAL_CASES; i++)
	{
		moneylist[i] = moneylist[i-13] * 1000;
	}
}

void initcases()
{
	// print a welcome screen with the rules
	// .....
	initarrays();
	casesleft = TOTAL_CASES;
	int i;
	
	// generate the cases
	for(i = 0; i < TOTAL_CASES; i++)
	{		
		cases[i].caseno = i;
		// search to see if value was recorded previously
		int flag = 0;
		int rand;
		do 
		{
			rand = moneylist[rand()%TOTAL_CASES];
			int j;
			for(j = 0; j < i; j++)
			{
				if(rand == cases[j].value)
				{
					flag = 1;
					break;
				}
				flag = 0;
			}
			
		} while(flag == 1);
		cases[i].value = rand;
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
			int val = casematch(cases, casesleft, atoi(input));
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

