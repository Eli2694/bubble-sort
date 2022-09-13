#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#pragma warning(disable:4996)

#define FILE_NAME "bubble.log"

//Beginning of the linked-list and the end;
struct ItemNum* head = NULL;
struct ItemNum* tail = NULL;

//time - log
time_t t;

//struct
struct ItemNum
{
	int num;
	struct ItemNum* prev;
	struct ItemNum* next;
};

//function - specification
struct ItemNum* newItem(int num);
void printNumList();
void replace(struct ItemNum* item);
void sort();
void releaseList();
void Log(char message[100]);
void LogError(char message[100]);
void LogEvent(char message[100]);

//global variables
int numberOfItems = 0;


int main()
{
	printf("1.Add Item\n2.print list'n\n3.sort list\n4.free memory allocation\n0.exit\n");
	int userInput = 1;

	int num;
	while (userInput != 0)
	{

		time_t k = time(NULL);
		srand(k);

		printf("what is you choice?\n");
		scanf("%d", &userInput); // my choice

		switch (userInput)
		{
		case 1:
			printf("Create linkedlist with 50 items\n");
			for (int i = 0; i < 50; i++)
			{
				int randomNumber = rand() % 100000;
				newItem(randomNumber);
				numberOfItems++;
			}
			break;
		case 2:
			printf("print list\n");
			printNumList();
			break;
		case 3:
			printf("sort list\n");
			LogEvent("before sorting");
			sort();
			break;
		case 4:
			printf("release memory allocation\n");
			releaseList();
		}
	}


	return 0;
}

struct ItemNum* newItem(int num)
{

	struct ItemNum* curr = head;
	curr = (struct Item*)malloc(sizeof(struct ItemNum));
	if (!curr)
	{
		LogError("Allocating Memory Error");
		printf("Allocating Memory Error");
		return;
	}
	else // Creating LinkedList
	{
		LogEvent("Creation of new item");
		curr->num = num;

		if (!head)
		{
			head = curr;
			tail = curr;
			head->next = NULL;
			head->prev = NULL;
		}
		else
		{
			curr->prev = tail;
			curr->next = NULL;
			tail->next = curr;
			tail = curr;
		}
		printf("Successful item creation!!\n");
	}

}

void printNumList()
{
	LogEvent("Printing list of items");
	int count = 0;
	struct ItemNum* print = head;
	if (print == NULL)
	{
		LogError("The list does not exist");
		return;
	}
	else
	{
		while (print != NULL)
		{
			printf("Item placement %d, Item number: %d\n", count, print->num);
			print = print->next;
			count++;
		}
	}

}

void replace(struct ItemNum* item)
{
	LogEvent("Item replacement");
	struct ItemNum* temp1 = item;
	struct ItemNum* temp2 = item->next;
	if (item == NULL)
	{
		LogError("No item in the list");
		return;
	}
	else if (temp2 == NULL && temp1 == head) // 1 item
	{
		LogEvent("1 item in the list");
		return;
	}
	else if (temp1->prev == NULL && temp2->next == NULL) // 2 items
	{
		LogEvent("2 item int the list");
		temp2->next = temp1;
		temp2->next->prev = temp2;
		temp2->next->next = NULL;
		temp2->prev = NULL;
		head = temp2;
		tail = temp1;
		printf("After Replace: \n");
		printNumList();
	}
	else if (temp2 == tail && temp1->prev != NULL) // at lest 3 item : 7,8,9
	{
		LogEvent("At least 3 item from the end - tail");
		temp1->prev->next = temp2;
		temp2->prev = temp1->prev;
		temp2->next = temp1;
		temp1->prev = temp2;
		temp1->next = NULL;
		tail = temp1;
		printf("After Replace: \n");
		printNumList();
	}
	else if (temp1 == head && temp2->next != NULL)
	{
		LogEvent("more then 2 item from the start - head");
		temp2->next->prev = temp1;
		temp1->next = temp2->next;
		temp1->prev = temp2;
		temp2->next = temp1;
		temp2->prev = NULL;
		head = temp2;
		printf("After Replace: \n");
		printNumList();
	}
	else // more then 2 items
	{
		LogEvent("Swapping items in the middle of the list");
		temp2->next->prev = temp1;
		temp1->prev->next = temp2;
		temp2->prev = temp1->prev;
		temp1->next = temp2->next;
		temp2->next = temp1;
		temp1->prev = temp2;
		printf("After Replace: \n");
		printNumList();
	}
}

void sort()
{
	
	struct ItemNum* sort = head;
	int temp = numberOfItems;

	while (numberOfItems != 0)
	{
		int forward = 0;
		int backward = 0;

		if (sort->next == NULL)
		{
			return;
		}

		for (int i = 0; i < numberOfItems - 1; i++)
		{
			if (sort->next != NULL && sort->num > sort->next->num)
			{
				replace(sort);
				sort = sort->prev;
				forward++;
			}
			sort = sort->next;
		}

		

		for (int i = 0; i < numberOfItems - 1; i++)
		{
			if (sort->prev != NULL && sort->num < sort->prev->num)
			{

				replace(sort->prev);
				if (sort->next != NULL)
				{
					sort = sort->next;
					backward++;
				}
				
			}
			sort = sort->prev;
		}

		numberOfItems--;

		if (backward == 0 && forward == 0)
		{
			break;
		}
	}	

	numberOfItems = temp;
	LogEvent("after sorting");
}

void releaseList()
{
	LogEvent("release itemlist");
	struct ItemNum* rel = NULL;
	struct ItemNum* curr = head;
	while (curr != NULL)
	{
		rel = curr;
		curr = curr->next;
		free(rel);
	}

	numberOfItems = 0;

}

void Log(char message[100])
{
	FILE* f = fopen(FILE_NAME, "a");
	fputs(message, f);
	fputs("\n", f);
	fclose(f);
}
void LogError(char message[100])
{
	
	time(&t);
	struct tm* timeinfo;
	timeinfo = localtime(&t);
	char str[1000];
	sprintf(str, "%d/%d/%d %d.%d.%d - Error - %s", timeinfo->tm_year, timeinfo->tm_mon, timeinfo->tm_yday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,message);

	Log(str);
}
void LogEvent(char message[100])
{
	
	time(&t);
	struct tm* timeinfo;
	timeinfo = localtime(&t);
	char str[100];
	sprintf(str, "%d/%d/%d %d.%d.%d - Event - %s", timeinfo->tm_mday , timeinfo->tm_mon +1 , timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, message);

	Log(str);
}