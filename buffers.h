#ifndef BUFFERS_H__
#define BUFFERS_H__

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

/*
NOTE: 
Large portions of these functions use code taken from the example on the assignment page.
*/

//Buffer 1:
	void put_buff_1(char*);
	char* get_buff_1();	
	
//Buffer 2:
	void put_buff_2(char*);
	char* get_buff_2();
	
//Buffer 3:
	void put_buff_3(char);
	char get_buff_3();

#endif