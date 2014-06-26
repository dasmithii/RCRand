#include <stdbool.h>
#include "generator.h"

bool has_flag(char *flag, int argc, char *argv[])
{
	for(int i = 0; i < argc; ++i){
		if(strlen(argv[i]) > 1 &&
		   argv[i][0] == '-'   &&
		   argv[i][1] != '-'   &&
		   strcmp(flag, argv[i] + 1) == 0)
			return true;
	}
	return false;
}

char *get_option(char *name, int argc, char *argv[])
{
	for(int i = 0; i < argc - 1; ++i){
		if(strlen(argv[i]) > 1 &&
		   argv[i][0] == '-'   &&
		   argv[i][1] == '-'   &&
		   strcmp(name, argv[i] + 2) == 0)
			return argv[i + 1];
	}
	return NULL;
}


int main(int argc, char *argv[]){
	grcr_init(5);

	const bool formatted = has_flag("format", argc, argv);
	if(formatted)
		printf("FORMATED\n");
	const char *num_spec = get_option("bytes", argc, argv);
	const size_t bytes   = num_spec? atoi(num_spec):0;

	if(bytes == 0) {
		for(;;)
			grcr_output(formatted);
	} else {
		for(int i = 0; i < bytes; ++i)
			grcr_output(formatted);
	}

	grcr_kill();
}