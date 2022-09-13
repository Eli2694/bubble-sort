/*
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#pragma warning(disable:4996)

#define FILE_LOG "file.log"

//Beginning of the linked-list and the end;
struct ItemNum* head = NULL;
struct ItemNum* tail = NULL;

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


int main()
{
	printf("1.Add Item\n2.print list'n\n3.sort list\n4.free memory allocation\n0.exit\n");
	int userInput = 1;
	
	int num;
	while (userInput != 0)
	{
		printf("what is you choice?\n");
		scanf("%d", &userInput); // my choice

		switch (userInput)
		{
		case 1:
			printf("Enter Number and add new item\n");
			scanf("%d", &num);
			newItem(num);
			break;
		case 2:
			printf("print list\n");
			printNumList();
			break;
		case 3:
			printf("sort list\n");
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
	else if(temp1 == head && temp2->next != NULL)
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
	LogEvent("item sorting");
	struct ItemNum* sort = head;
	while (sort != NULL)
	{
		if (sort->next == NULL)
		{
			return;
		}

		if (sort->num > sort->next->num)
		{
			replace(sort);
		}
		sort = sort->next;
	}
	
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


}

void Log(char message[100])
{
	FILE* f = fopen(FILE_LOG, "a");
	fputs(message, f);
	fputs("\n", f);
	fclose(f);
}
void LogError(char message[100])
{
	time_t t;
	time(&t);
	struct tm* timeinfo;
	timeinfo = localtime(&t);
	char str[100];
	sprintf(str, "%d/%d/%d %d.%d.%d", timeinfo->tm_year, timeinfo->tm_mon, timeinfo->tm_yday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);

	Log("%s - Error - %s", str, message);
}
void LogEvent(char message[100])
{
	time_t t;
	time(&t);
	struct tm* timeinfo;
	timeinfo = localtime(&t);
	char str[100];
	sprintf(str, "%d/%d/%d %d.%d.%d", timeinfo->tm_year, timeinfo->tm_mon, timeinfo->tm_yday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

	Log("%s - Event - %s", str, message);
}
*/