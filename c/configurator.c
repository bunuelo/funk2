#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sched.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#include "f2_os.h"

typedef unsigned long long u64;
typedef   signed long long s64;

/*
#ifdef F2__APPLE
#  include <mach/clock.h>
#  include <mach/mach.h>
#  include <mach/mach_init.h>
#  include <mach/thread_info.h>
#  include <mach/thread_policy.h>
#  define cpu_set_t               thread_affinity_policy_data_t
#  define CPU_SETSIZE             sysconf(_SC_NPROCESSORS_ONLN)
#  define CPU_ZERO(new_mask)      *new_mask.affinity_tag = THREAD_AFFINITY_TAG_NULL
#  define CLOCK_THREAD_CPUTIME_ID NULL
#endif

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
#ifdef F2__APPLE // OS X does not have clock_gettime, use clock_get_time
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
  clock_get_time(cclock, &mts);
  mach_port_deallocate(mach_task_self(), cclock);
  ts.tv_sec = mts.tv_sec;
  ts.tv_nsec = mts.tv_nsec;
#else
  clock_gettime(CLOCK_REALTIME, &ts);
#endif
  return (((u64)ts.tv_sec) * nanoseconds_per_second) + ((u64)ts.tv_nsec);
}

u64 raw__processor_thread__execution_nanoseconds() {
#ifdef F2__APPLE // OS X does not have clock_gettime, use clock_get_time
  thread_t                 my_mach_thread    = mach_thread_self();
  int                      flavor            = THREAD_BASIC_INFO;
  struct thread_basic_info thread_basic_info;
  mach_msg_type_number_t   thread_infoCnt    = THREAD_BASIC_INFO_COUNT;
  kern_return_t            mach_return_value = thread_info(my_mach_thread, flavor, (thread_info_t)&thread_basic_info, &thread_infoCnt);
  if (mach_return_value != KERN_SUCCESS) {
    fprintf(stderr, "\nfunk2 error: raw__processor_thread__execution_nanoseconds had error executing thread_info.\n");
    exit(-1);
  }
  u64 nanoseconds = (((u64)(thread_basic_info.system_time->seconds + thread_basic_info.user_time->seconds)) * nanoseconds_per_second) + (((u64)(thread_bassic_info.system_time->microseconds + thread_basic_info.user_time->microseconds)) * nanoseconds_per_microsecond);
  return nanoseconds;
#else
  struct timespec ts;
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
  return (((u64)ts.tv_sec) * nanoseconds_per_second) + ((u64)ts.tv_nsec);
#endif
}
*/

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
  } else {
    printf("\n"
	   "\nunknown configurator command, \"%s\"!"
	   "\n", command);
    print_usage();
    return 2;
  }
  return 0;
}

