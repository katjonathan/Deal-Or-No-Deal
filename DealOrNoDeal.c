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
casing* untaken[TOTAL_CASES];
int casesleft = TOTAL_CASES;


void initarrays(int*);
void initcases();
int listcases(int);
void quicksort(casing*, int, int, int);		// sorts an array of cases
int partition(casing*, int, int, int);		// helper to quicksort
casing* readcase();					// read user selection
casing* casematch(casing*, int, int);		// matches an int to any entry in cases
void remove(casing*, casing);
int offer();		// this is the value of the banker's offer


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
	
	for(i = 0; i < TOTAL_CASES; i++)
	{
		untaken[i] = &cases[i];
	}
	free(moneylist);
	moneylist = NULL;
}

remove(casing* array, casing key)
{
	
}

void quicksort(casing* array, int mode, int start, int end)
{
	if(start - end != 0)
	{
		int pivot = partition(array, mode, start, end);
		quicksort(array, mode, start, pivot-1);
		quicksort(array, mode, pivot, end);
	}
}

int partition(casing* array, int mode, int i, int j)
{
	int pivot = (i + j)/2;
	if(mode == CASE_MODE)
	{
		while(i < j)
		{
			while(array[i].caseno < array[pivot].caseno)
			{
				i += 1;
			}
			while(array[j].caseno > array[pivot].caseno)
			{
				j -= 1;
			}
			if(array[i].caseno > array[pivot].caseno && array[j].caseno < array[pivot].caseno)
			{
				casing temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
	if(mode == MONEY_MODE)
	{
		
		while(i < j)
		{
			while(array[i].value < array[pivot].value)
			{
				i += 1;
			}
			while(array[j].value > array[pivot].value)
			{
				j -= 1;
			}
			if(array[i].value > array[pivot].value && array[j].value < array[pivot].value)
			{
				casing temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
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
				return 1;		// ERROR
			}
		}		 
	}
	quicksort(available, mode, 0, casesleft);
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

int offer(void)
{
	int avg = 0;
	int i;
	for(i = 0; i < casesleft; i++)
	{
		
	}
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
	chosen->taken = 1;
	casesleft -= 1;
	untaken[TOTAL_CASES - casesleft] = *chosen;
	// eliminate the cases
	while(casesleft > 2)
	{
		int bfreq = rand() % (casesleft / 4);		// the number of turns it will take for the banker to call
		if(bfreq == 0)
		{
			bfreq = 1;
		}
		while(bfreq > 0)
		{
			printf("Pick a case to eliminate!\n  >  ");
			casing* in = readcase();
			in->taken = 1;
			casesleft -= 1;
			untaken[TOTAL_CASES - casesleft] = NULL;
			remove(untaken, in);
			bfreq -= 1;
		}
		/* offer a deal: expected value of remaining cases */
		
		int deal 
	}

	free(chosen);
	chosen = NULL;
}
