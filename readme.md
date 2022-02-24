gcc -std=gnu99 -lpthread main.c buffers.c threads.c -o line_processor

Note: this program has undefined behavior once past the defined # of inputs the buffer can take(default 50)
