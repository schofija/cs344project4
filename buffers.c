/*
buffers.c
contains put/get functions for each buffer
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include "threads.h"
#include "buffers.h"

/* Global variables for Buffer 1 */
/* NOTE: These global variables were taken from the example code on the assignment page, and slightly modified */
char buffer_1[BUFFER_NUM_ITEMS + 1][BUFFER_ITEM_SIZE]; /* Buffer 1, shared resource between input thread line-separator thread */
int count_1 = 0; /* Number of items in the buffer */
int prod_idx_1 = 0; /* Index where the input threaaad will put the next item */
int con_idx_1 = 0; /* Index where line-separator thread will pick up the next item */
pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER; /* Init mutex for buffer 1 */
pthread_cond_t full_1 = PTHREAD_COND_INITIALIZER; /* Init condition variable for buffer 1 */

/* Global variables for Buffer 2 */
/* NOTE: These global variables were taken from the example code on the assignment page, and slightly modified */
char buffer_2[BUFFER_NUM_ITEMS + 1][BUFFER_ITEM_SIZE]; /* Buffer 2, shared resource between square root thread and output thread */
int count_2 = 0; /* Number of items in the buffer */
int prod_idx_2 = 0; /* Index where the square-root thread will put the next item */
int con_idx_2 = 0; /* Index where the output thread will pick up the next item */
pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER; /* Initialize the mutex for buffer 2 */
pthread_cond_t full_2 = PTHREAD_COND_INITIALIZER; /* Initialize the condition variable for buffer 2 */

/* Global variables for Buffer 3 */
/* NOTE: These global variables were taken from the example code on the assignment page, and slightly modified */
char buffer_3[BUFFER_NUM_ITEMS * BUFFER_ITEM_SIZE + 1]; /* Buffer 3*/
int count_3 = 0; /* Number of items in the buffer */
int prod_idx_3 = 0; /* Index where the square-root thread will put the next item */
int con_idx_3 = 0; /* Index where the output thread will pick up the next item */
pthread_mutex_t mutex_3 = PTHREAD_MUTEX_INITIALIZER; /* Initialize the mutex for buffer 2 */
pthread_cond_t full_3 = PTHREAD_COND_INITIALIZER; /* Initialize the condition variable for buffer 2 */

/* Put an item in buff_1 */
void put_buff_1(char* item)
{
	pthread_mutex_lock(&mutex_1); /* Locking mutex... */
  
	strcpy(buffer_1[prod_idx_1], item); /* Putting item in buffer */
	//buffer_1[prod_idx_1] = item;
	prod_idx_1 += 1;
	count_1 ++;
	pthread_cond_signal(&full_1); /* Signal to the consumer that the buffer is no longer empty */
	
	pthread_mutex_unlock(&mutex_1); /* Unlocking mutex */
}

/* Get the next item from buffer 1 */
char* get_buff_1()
{
	pthread_mutex_lock(&mutex_1); /* Lock the mutex before checking if the buffer has data */
	
	while (count_1 == 0) /* Wait for the producer to signal that the buffer has data */
		pthread_cond_wait(&full_1, &mutex_1);
		
	char* item = (char *) malloc(BUFFER_ITEM_SIZE);
	strcpy(item, buffer_1[con_idx_1]); /* Copy buffer_1 into item*/
  
  con_idx_1 += 1; /* Increment the index from which the item will be picked up */
  count_1--; 
  
  pthread_mutex_unlock(&mutex_1); /* Unlocking mutex */
  
  return item;
}

/* Put an item in buff_2 */
void put_buff_2(char* item)
{
  pthread_mutex_lock(&mutex_2); // Lock the mutex before putting the item in the buffer
  
	strcpy(buffer_2[prod_idx_2], item); // Put the item in the buffer

  prod_idx_2 += 1; // Increment the index where the next item will be put.
  count_2++;
  pthread_cond_signal(&full_2); // Signal to the consumer that the buffer is no longer empty
  
  pthread_mutex_unlock(&mutex_2);   // Unlock the mutex
}

/* Get the next item from buffer 2 */
char* get_buff_2()
{
	pthread_mutex_lock(&mutex_2); // Lock the mutex before checking if the buffer has data
	
	while (count_2 == 0) // Buffer is empty. Wait for the producer to signal that the buffer has data
		pthread_cond_wait(&full_2, &mutex_2);
	
	char* item = (char *) malloc(BUFFER_ITEM_SIZE);
	strcpy(item, buffer_2[con_idx_2]); /* Copy buffer_2 into item*/
	con_idx_2 = con_idx_2 + 1; // Increment the index from which the item will be picked up
	count_2--;
	
	pthread_mutex_unlock(&mutex_2); // Unlock the mutex
  return item;
}

void put_buff_3(char item)
{
	pthread_mutex_lock(&mutex_3); /* Locking mutex */
	
	buffer_3[prod_idx_3] = item; // Put the item in the buffer
	prod_idx_3 += 1; // Increment the index where the next item will be put.
	count_3++;
	pthread_cond_signal(&full_3); // Signal to the consumer that the buffer is no longer empty
	
	pthread_mutex_unlock(&mutex_3); /* Unlocking mutex */
}
char get_buff_3()
{
	pthread_mutex_lock(&mutex_3);
	
	while (count_3 == 0) // Buffer is empty. Wait for the producer to signal that the buffer has data
		pthread_cond_wait(&full_3, &mutex_3);
	
	char item =  buffer_3[con_idx_3]; /* Copy buffer_3 into item*/
	con_idx_3 = con_idx_3 + 1; // Increment the index from which the item will be picked up
	count_3--;
	
	pthread_mutex_unlock(&mutex_3);
  return item;
}
