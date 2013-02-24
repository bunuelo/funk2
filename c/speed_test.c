#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef unsigned long long u64;
typedef   signed long long s64;

#define nanoseconds_per_second ((u64)1000000000ull)

typedef struct global_state_s {
  u64             total_pthread_count;
  pthread_mutex_t start_mutex;
  pthread_cond_t  start_cond;
  int             start;
} global_state_t;

global_state_t global_state;

typedef struct my_pthread_s {
  int id;
} my_pthread_t;

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

#define max_loop_count ((u64)2500000000ull)

void* pthread_start_function(void* user_ptr) {
  //my_pthread_t* my_pthread = user_ptr;
  pthread_mutex_lock(&(global_state.start_mutex));
  while (global_state.start == 0) {
    pthread_cond_wait(&(global_state.start_cond), &(global_state.start_mutex));
  }
  pthread_mutex_unlock(&(global_state.start_mutex));
  u64 j = 0;
  {
    u64 i;
    for (i = 0; i < max_loop_count; i++) {
      j += i;
    }
  }
  return (void*)(j);
}

u64 run_test_helper(void) {
  pthread_t*    pthread    = (pthread_t*)   malloc(sizeof(pthread_t)    * global_state.total_pthread_count);
  my_pthread_t* my_pthread = (my_pthread_t*)malloc(sizeof(my_pthread_t) * global_state.total_pthread_count);
  pthread_mutex_init(&(global_state.start_mutex), NULL);
  pthread_cond_init(&(global_state.start_cond), NULL);
  global_state.start = 0;
  {
    int i;
    for (i = 0; i < global_state.total_pthread_count; i ++) {
      my_pthread[i].id = i;
      pthread_create(&(pthread[i]), NULL, pthread_start_function, &(my_pthread[i]));
    }
  }
  sleep(1);
  pthread_mutex_lock(&(global_state.start_mutex));
  global_state.start = 1;
  pthread_cond_broadcast(&(global_state.start_cond));
  u64 start_time = raw__nanoseconds_since_1970();
  pthread_mutex_unlock(&(global_state.start_mutex));
  {
    int i;
    for (i = 0; i < global_state.total_pthread_count; i ++) {
      pthread_join(pthread[i], NULL);
    }
  }
  u64 end_time = raw__nanoseconds_since_1970();
  u64 loops_per_second = (u64)((double)global_state.total_pthread_count * (double)max_loop_count * 1000000000.0 / (double)(end_time - start_time));
  printf("\n        total_loops = %llu", global_state.total_pthread_count * max_loop_count);
  printf("\n        elapsed_time = %g", (end_time - start_time) / 1000000000.0);
  printf("\n        [%llu]: %llu\n", global_state.total_pthread_count, loops_per_second);
  pthread_mutex_destroy(&(global_state.start_mutex));
  pthread_cond_destroy(&(global_state.start_cond));
  free(pthread);
  free(my_pthread);
  return loops_per_second;
}

int main(int argc, char** argv) {
  u64 minimum_pthread_count;
  u64 maximum_pthread_count;
  u64 total_loop_count;
  if (argc == 4) {
    minimum_pthread_count = atoi(argv[1]);
    maximum_pthread_count = atoi(argv[2]);
    total_loop_count      = atoi(argv[3]);
    if (minimum_pthread_count > maximum_pthread_count) {
      printf("\nspeed_test fatal: minimum_pthread_count must not be greater than maximum_pthread_count.\n");
      return -1;
    }
  } else {
    printf("\nspeed_test <minimum-pthread-count> <maximum-pthread-count> <total-loop-count>\n");
    return -1;
  }
  {
    u64 i;
    for (i = minimum_pthread_count; i <= maximum_pthread_count; i ++) {
      global_state.total_pthread_count = i;
      u64 sum = 0;
      u64 j;
      for (j = 0; j < total_loop_count; j ++) {
	sum += run_test_helper();
      }
      printf("\nAVG [%llu]: %llu\n", global_state.total_pthread_count, sum / total_loop_count);
    }
  }
  return 0;
}
