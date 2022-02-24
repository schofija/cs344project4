#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include "threads.h"
#include "buffers.h"

#ifndef BUFFER_NUM_ITEMS
	#define BUFFER_NUM_ITEMS 50
#endif

#ifndef BUFFER_ITEM_SIZE /* An input line will never be longer than 1000 characters (including the line separator).*/
	#define BUFFER_ITEM_SIZE 1000
#endif

#ifndef PRINT_LEN /* Length to print */
	#define PRINT_LEN 80
#endif

/* 	main()
	Creates/joins threads
*/
int main()
{
	pthread_t input_t, line_separator_t, plus_sign_t, output_t;
	// Create the threads
    pthread_create(&input_t, NULL, get_input, NULL);
	pthread_create(&line_separator_t, NULL, line_separator, NULL);
	pthread_create(&plus_sign_t, NULL, plusplus_to_carrot, NULL);
	pthread_create(&output_t, NULL, write_output, NULL);
	// Wait for the threads to terminate
    pthread_join(input_t, NULL);
	pthread_join(line_separator_t, NULL);
	pthread_join(plus_sign_t, NULL);
	pthread_join(output_t, NULL);
	
	return EXIT_SUCCESS;
}

