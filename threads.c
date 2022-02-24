/*
threads.c
contains functions for each thread
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include "threads.h"
#include "buffers.h"

unsigned int stop_flag = 0;
unsigned int stop_idx = 0;

/* Called within input thread */
char* get_user_input()
{
	char* value = NULL;
	size_t len = 0;
	ssize_t nread;
	if(nread = getline(&value, &len, stdin) != -1)
		return value;
	else
	{		
		perror("getline failed!");
		exit(1);
	}
}

/* Input thread */
void* get_input(void *args)
{
    for(int i = 0; i < BUFFER_NUM_ITEMS; i++)
    {
      // Get the user input
      char* item = get_user_input();
	  if(strcmp(item, "STOP\n") == 0)
	  {
			printf("stop flag set!\n");
			stop_flag = 1; /* Setting the global stop flag */
			return NULL;
	  }
      put_buff_1(item);
    }
	stop_flag = 1;
    return NULL;
}

/* Line-separator thread */
void *line_separator(void *args)
{
    char* item;
	unsigned int max_idx = BUFFER_NUM_ITEMS;
    for (int i = 0; i < max_idx; i++) //for (int i = 0; i < BUFFER_NUM_ITEMS; i++)
    {
      item = get_buff_1();
	  
	  for(int j = 0; j < BUFFER_ITEM_SIZE; j++)
	  {
		  if(item[j] == '\n') /* Converting newline character to space */
			  item[j] == ' ';
	  }
	 
		put_buff_2(item);
    }
    return NULL;
}

/* Plus-sign thread ("++"+ -> "^")*/
void* plusplus_to_carrot(void* args)
{
	char* item;
	for (int i = 0; i < BUFFER_NUM_ITEMS; i++)
    {
      item = get_buff_2();
	  
	  for(int j = 0; j < strlen(item) - 1; j++)
	  {
		if(item[j] == '+' && item[j+1] == '+') /* If current item[j] is a +, and the next one is aswell...*/
		{
			j++; /* We want to double increment, so we don't catch the second '+' twice...*/
			put_buff_3('^'); /* Putting a '^' into the buffer instead */
		}
		else put_buff_3(item[j]);
	  }
    }
	return NULL;
}

/* Output thread */
void *write_output(void *args)
{
	char item[PRINT_LEN] = "";
	int j = 0;
	for(int i = 0; i < BUFFER_NUM_ITEMS * BUFFER_ITEM_SIZE; i++)
	{
		item[j] = get_buff_3();
		j++;
		//printf("fakeOutput: %s, j==%i\n", item,j);
		if(j == PRINT_LEN)
		{
			printf("Output: %.80s\n", item);
			j = 0;
			memset(item, 0, PRINT_LEN);
		}
	}

return NULL;
}