#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <sched.h>

void print_usage() {
  printf("\n"
	 "\nusage: configurator <command>"
	 "\n"
	 "\n  <command> can be one of the following symbols:"
	 "\n"
	 "\n    char-bit_num"
	 "\n    short-bit_num"
	 "\n    int-bit_num"
	 "\n    long-bit_num"
	 "\n    long_long-bit_num"
	 "\n    pointer-bit_num"
	 "\n    float-bit_num"
	 "\n    double-bit_num"
	 "\n    processor_num"
	 "\n"
	 );
}

int main(int argc, char** argv) {
  if (argc != 2) {
    print_usage();
    return 1;
  }
  char* command = argv[1];
  if (strcmp(command, "char-bit_num") == 0) {
    printf("%u\n", (unsigned int)sizeof(char) * 8);
  } else if (strcmp(command, "short-bit_num") == 0) {
    printf("%u\n", (unsigned int)sizeof(short) * 8);
  } else if (strcmp(command, "int-bit_num") == 0) {
    printf("%u\n", (unsigned int)sizeof(int) * 8);
  } else if (strcmp(command, "long-bit_num") == 0) {
    printf("%u\n", (unsigned int)sizeof(long) * 8);
  } else if (strcmp(command, "long_long-bit_num") == 0) {
    printf("%u\n", (unsigned int)sizeof(long long) * 8);
  } else if (strcmp(command, "pointer-bit_num") == 0) {
    printf("%u\n", (unsigned int)sizeof(void*) * 8);
  } else if (strcmp(command, "float-bit_num") == 0) {
    printf("%u\n", (unsigned int)sizeof(float) * 8);
  } else if (strcmp(command, "double-bit_num") == 0) {
    printf("%u\n", (unsigned int)sizeof(double) * 8);
  } else if (strcmp(command, "processor_num") == 0) {
    unsigned int processor_num = 0;
    {
      cpu_set_t cpu_set;
      CPU_ZERO(&cpu_set);
      sched_getaffinity(0, sizeof(cpu_set_t), &cpu_set);
      {
	unsigned int i;
	for (i = 0; i < CPU_SETSIZE; i ++) {
	  if (CPU_ISSET(i, &cpu_set)) {
	    processor_num ++;
	  }
	}
      }
    }
    if (processor_num == 0) {
      processor_num = 1;
    }
    printf("%u\n", processor_num);
  } else {
    printf("\n"
	   "\nunknown configurator command, \"%s\"!"
	   "\n", command);
    print_usage();
    return 2;
  }
  return 0;
}

