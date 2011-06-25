#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <sched.h>
#include <time.h>
#include <pthread.h>

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
	 "\n    deep_sleep_nanoseconds"
	 "\n"
	 );
}

typedef unsigned long long u64;
typedef   signed long long s64;

#define nanoseconds_per_second ((u64)1000000000ull)

void raw__nanosleep(u64 nanoseconds) {
  struct timespec sleepTime;
  struct timespec remainingSleepTime;
  sleepTime.tv_sec  = nanoseconds / nanoseconds_per_second;
  sleepTime.tv_nsec = nanoseconds - ((nanoseconds / nanoseconds_per_second) * nanoseconds_per_second);
  nanosleep(&sleepTime, &remainingSleepTime);
}

u64 raw__nanoseconds_since_1970() {
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  return (((u64)ts.tv_sec) * nanoseconds_per_second) + ((u64)ts.tv_nsec);
}

u64 raw__processor_thread__execution_nanoseconds() {
  struct timespec ts;
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
  return (((u64)ts.tv_sec) * nanoseconds_per_second) + ((u64)ts.tv_nsec);
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
  } else if (strcmp(command, "deep_sleep_nanoseconds") == 0) {
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_lock(&mutex);
    {
      u64    sleep_nanoseconds = 1;
      double processor_usage   = 100.0;
      double target_usage      = (1.0 / 1000.0);
      while (processor_usage > target_usage) {
	s64 total_spins = 100;
	{
	  s64 i = total_spins;
	  u64 begin__nanoseconds_since_1970 = raw__nanoseconds_since_1970();
	  u64 begin__execution_nanoseconds  = raw__processor_thread__execution_nanoseconds();
	  while (pthread_mutex_trylock(&mutex)) {
	    if (i <= 0) {
	      break;
	    }
	    i --;
	    raw__nanosleep(sleep_nanoseconds);
	  }
	  u64 end__nanoseconds_since_1970 = raw__nanoseconds_since_1970();
	  u64 end__execution_nanoseconds  = raw__processor_thread__execution_nanoseconds();
	  processor_usage = ((double)(end__execution_nanoseconds - begin__execution_nanoseconds)) / ((double)(end__nanoseconds_since_1970 - begin__nanoseconds_since_1970));
	  //printf("(%f at %lu)\n", processor_usage, sleep_nanoseconds);
	  if (processor_usage > target_usage) {
	    sleep_nanoseconds <<= 1;
	  }
	}
      }
      printf("%lu\n", sleep_nanoseconds);
    }
    pthread_mutex_destroy(&mutex);
  } else {
    printf("\n"
	   "\nunknown configurator command, \"%s\"!"
	   "\n", command);
    print_usage();
    return 2;
  }
  return 0;
}

