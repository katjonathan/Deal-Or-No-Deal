#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define TOTAL_CASES 25

typedef struct
{
	int caseno;
	int value;
	int taken;
} casing;

typedef enum {CASE_MODE, MONEY_MODE} mode;

casing cases[TOTAL_CASES];		// all of the cases
int casesleft = TOTAL_CASES;

// FUNCTION DECLARATIONS NEEDS TO BE REDONE
void initarrays(int*);				// helper to initcases()
void initcases(void);				// initializes cases
int listcases(mode);				// lists all available cases
int linsearch(mode, int);			// helper to rem()
int rem(mode, int);				// removes case from the cases list
void sort(mode);				// sorts cases[] using insertion sort
casing* readcase(void);				// read user selection
casing* casematch(int);				// matches an int to any entry in list of cases
int offer(void);				// this is the value of the banker's offer
void grabchar(char*);				// helper to get first character from input
void play(void);				// plays the game


int main()
{
	while(1)
	{
		initcases();
		play();
	}
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
	srand(time(NULL));

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

int linsearch(mode m, int key)
{
	int i;
	for(i = 0; i < casesleft; i++)
	{
		if(m == MONEY_MODE)
		{
			if(key == cases[i].value)
			{
				return i;
			}
		}
		if(m == CASE_MODE)
		{
			if(key == cases[i].caseno)
			{
				return i;
			}
		}
	}
	return -1;
}

int rem(mode m, int key)
{
	//search for the key (using linear search)
	int index = linsearch(m, key);
	if(index != -1)
	{
		int i;
		for(i = index; i < casesleft-1; i++)
		{
			// twirl it around until its at the end of the index
			casing temp = cases[i];
			cases[i] = cases[i+1];
			cases[i+1] = temp;
		}
		casesleft -= 1;
		cases[i].taken = 1;
	}
	return index;
}

void sort(mode m)
{
	// insertion sort
	int i;
	for(i = 0; i < casesleft; i++)
	{
		int j;
		for(j = i+1; j > 0; j--)
		{
			if(m == CASE_MODE)
			{
				if(cases[j].caseno < cases[i].caseno)
				{
					casing temp = cases[j];
					cases[j] = cases[j-1];
					cases[j-1] = temp;
				}
			}
			else if(m == MONEY_MODE)
			{
				if(cases[j].value < cases[i].value)
				{
					casing temp = cases[j];
					cases[j] = cases[j-1];
					cases[j-1] = temp;
				}
			}
		}
	}
}

int listcases(mode m)
{
	sort(m);
	int i;
	for(i = 0; i < casesleft; i++)
	{
		if(m == CASE_MODE)
		{
			if(cases[i].taken == 0)
			{
				printf("%d\n", cases[i].caseno);
			}
		}
		if(m == MONEY_MODE)
		{
			if(cases[i].taken == 0)
			{
				printf("%d\n", cases[i].value);
			}
		}
	}
	return 0;
}

casing* readcase()
{
	char* input = (char*)malloc(sizeof(char)*1000);
	do
	{
		scanf("%s", input);
		if(strcmp(input, "exit") == 0)
		{
			// free input
			free(input);
			input = NULL;

			// exit the program
			return NULL;
		}
		if(strcmp(input, "cases") == 0)
		{
			printf("\n");
			listcases(CASE_MODE);
		}
		if(atoi(input) > 0 && atoi(input) <= casesleft)
		{
			casing* val = casematch(atoi(input));
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

casing* casematch(int key)
{
	// finds the case based on the caseno
	casing* ptr = cases;
	int i;
	for(i = 0; i < casesleft; i++)
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
		// get sum of remaining cases
		avg = avg + cases[i].value;
	}
	return avg/casesleft;
}

void grabchar(char* ret)
{
	char string[1000];		// buffer for string
	scanf("%s", string);
	char* ptr;
	ptr = string;
	while(*ptr != '\0')
	{
		if(*ptr != ' ' || *ptr != '\t' || *ptr != '\n')
		{
			if((int)*ptr >= 97 && (int)*ptr <= 122)
			{
				*ret = toupper(*ptr);
			}
			else
			{
				*ret = *ptr;
			}
			break;
		}
		ptr += 1;
	}
}

void play()
{
	// assume that arrays are already set up properly
	// list all the cases available
	// points to a case in the case array
	casing** chosen = (casing**)malloc(sizeof(casing*));
	char** input = (char**)malloc(sizeof(char*));			// use as input for later
	listcases(CASE_MODE);
	printf("Choose a case to keep!\n  >  ");
	// read whether the selection is valid
	*chosen = readcase();
	rem(CASE_MODE, (*chosen)->caseno);
	// eliminate the cases
	while(casesleft > 1)
	{
		int bfreq = (rand() % (casesleft / 4))+1;		// the number of turns it will take for the banker to call
		while(bfreq > 0)
		{
			printf("Pick a case to eliminate!\n  >  ");
			casing* in = readcase();
			if(in == NULL)
			{
				// free everything; premature exit
				free(input);
				free(chosen);
				return;
			}
			rem(CASE_MODE, in->caseno);
			bfreq -= 1;
		}
		// offer a deal: expected value of remaining cases

		int deal = offer();
		while(1)
		{
			printf("The banker offers you $%d. Will you take it? (y/n)\n", deal);
			printf(">  ");
			grabchar(*input);
			if(**input == 'Y' || **input == 'N')
			{
				if(**input == 'Y')
				{
					printf("Your case contained.......$%d\n", (*chosen)->value);
					if((*chosen)->value > deal)
					{
						printf("YOU WIN!\n");
					}
					else if((*chosen)->value < deal)
					{
						printf("YOU LOSE!\n");
					}
					else
					{
						printf("TIE!\n");
					}
					break;
				}
			}
		}
	}
	while(1)
	{
		printf("There is only one case left. Will you switch cases? (y/n)\n");
		printf(">  ");
		grabchar(*input);
		if(**input == 'Y' || **input == 'N')
		{
			casing** other = (casing**)malloc(sizeof(casing*));
			if(**input == 'Y')
			{
				*other = *chosen;
				*chosen = &cases[0];
			}
			if(**input == 'N')
			{
				*other = &cases[0];
			}
			printf("Your case contained.......$%d\n", (*chosen)->value);
			if((*chosen)->value > (*other)->value)
			{
				printf("YOU WIN!\n");
			}
			else if((*chosen)->value < (*other)->value)
			{
				printf("YOU LOSE!\n");
			}
			free(other);
			other = NULL;
			break;
		}
	}
	free(input);
	free(chosen);
	input = NULL;
	chosen = NULL;
}
