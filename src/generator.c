#include "generator.h"

// ----------------------------------------------------------- //
static void work_once(void *addr)
{
	char *buffer = addr;
	for(int b = 0; b < BUFFER_SIZE; ++b){
		const char byte = buffer[b];
		int offset = (b + byte) % BUFFER_SIZE;
		buffer[b] ^= buffer[offset];
	}
}

// ----------------------------------------------------------- //
static void *work(void *addr)
{
	for(;;)
		work_once(addr);
	return NULL;
}

// ----------------------------------------------------------- //
int rcr_init(rcr *gen, size_t num_workers)
{
	// Setup worker threads. Fuck error handling.
	pthread_mutex_init(&gen->mutex, NULL);
	gen->threads = calloc(num_workers, sizeof(pthread_t));
	gen->num_threads = num_workers;
	for(int i = 0; i < num_workers; ++i)
		pthread_create(gen->threads + i, NULL, work, gen->buffer);

	// Randomize initial bytes.
	srand(time(0));
	for(int i = 0; i < BUFFER_SIZE; ++i)
		gen->buffer[i] = (char) rand();
	return 0;
}

// ----------------------------------------------------------- //
void rcr_kill(rcr *gen)
{
	for(int i = 0; i < gen->num_threads; ++i)
		pthread_cancel(gen->threads[i]);
	free(gen->threads);
	gen->num_threads = 0;
}

// ----------------------------------------------------------- //
static unsigned char rcr_current_byte(rcr *gen)
{
	unsigned char byte = gen->buffer[0];
	for(int i = 1; i < BUFFER_SIZE; ++i)
		byte ^= gen->buffer[i];
	return byte;
}

// ----------------------------------------------------------- //
unsigned char rcr_byte(rcr *gen)
{
	pthread_mutex_lock(&gen->mutex);
	unsigned char byte;
	do {
		byte = rcr_current_byte(gen);
	} while(byte == gen->prev);
	gen->prev = byte;
	pthread_mutex_unlock(&gen->mutex);
	return byte;
}

// ----------------------------------------------------------- //
void rcr_output(rcr *gen, bool formatted)
{
	unsigned char byte = rcr_byte(gen);
	if(formatted)
		printf("%d\n", (unsigned int) byte);
	else
		printf("%c", (char) byte);
}

// ----------------------------------------------------------- //
static rcr *rcr_g = NULL;

// ----------------------------------------------------------- //
int grcr_init(size_t num_workers)
{
	rcr_g = malloc(sizeof(rcr));
	if(!rcr_g)
		return 1;
	return rcr_init(rcr_g, num_workers);
}

// ----------------------------------------------------------- //
void grcr_kill()
{
	rcr_kill(rcr_g);
}

// ----------------------------------------------------------- //
unsigned char grcr_byte()
{
	return rcr_byte(rcr_g);
}

// ----------------------------------------------------------- //
void grcr_output(bool formatted)
{
	rcr_output(rcr_g, formatted);
}