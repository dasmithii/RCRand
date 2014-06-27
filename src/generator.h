#ifndef _RCRAND_GENERATOR_H_
#define _RCRAND_GENERATOR_H_
#define BUFFER_SIZE 234
#define SEGMENT_SIZE 100
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>


// Race Condition Random Generator
typedef struct {
	pthread_mutex_t mutex;
	pthread_t *threads;
	size_t num_threads;
	char buffer[BUFFER_SIZE];
	char prev;
} rcr;

int rcr_init(rcr *gen, size_t num_workers);
void rcr_kill(rcr *gen);
unsigned char rcr_byte(rcr *gen);
void rcr_output(rcr *gen, bool formatted);


// Global Generator 
int grcr_init(size_t num_workers);
void grcr_kill();
unsigned char grcr_byte();
void grcr_output(bool formatted);

#endif