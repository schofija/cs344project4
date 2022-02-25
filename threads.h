#ifndef THREADS_H__
#define THREADS_H__

#include <stddef.h>
#include <unistd.h>

#ifndef BUFFER_NUM_ITEMS
	#define BUFFER_NUM_ITEMS 50
#endif

#ifndef BUFFER_ITEM_SIZE /* An input line will never be longer than 1000 characters (including the line separator).*/
	#define BUFFER_ITEM_SIZE 1000
#endif

#ifndef PRINT_LEN /* Length to print */
	#define PRINT_LEN 80
#endif

extern char buffer_1[BUFFER_NUM_ITEMS + 1][BUFFER_ITEM_SIZE];
extern int count_1;
extern int prod_idx_1;
extern int con_idx_1;
extern pthread_mutex_t mutex_1;
extern pthread_cond_t full_1;

extern char buffer_2[BUFFER_NUM_ITEMS + 1][BUFFER_ITEM_SIZE];
extern int count_2;
extern int prod_idx_2;
extern int con_idx_2;
extern pthread_mutex_t mutex_2;
extern pthread_cond_t full_2;

extern char buffer_3[BUFFER_NUM_ITEMS * BUFFER_ITEM_SIZE + 1];
extern int count_3;
extern int prod_idx_3;
extern int con_idx_3;
extern pthread_mutex_t mutex_3;
extern pthread_cond_t full_3;

/* This header file contains the function declarations for each thread*/

//Input thread
char* get_user_input(); /* Contains code from example on assignment page */
void* get_input(void*); /* Contains code from example on assignment page */

//Line-separator thread:
void* line_separator(void*);

//Plus-sign thread:
void* plusplus_to_carrot(void*);

//Output thread:
void *write_output(void*);

#endif