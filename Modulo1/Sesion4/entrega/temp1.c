#include <time.h>
#include <stdio.h>

int main() {

  clockid_t clocks[] = {
    CLOCK_REALTIME,
    CLOCK_MONOTONIC,
    CLOCK_PROCESS_CPUTIME_ID,
    CLOCK_THREAD_CPUTIME_ID,
    CLOCK_MONOTONIC_RAW,
    CLOCK_REALTIME_COARSE,
    (clockid_t) - 1 
  };

  int i;
  struct timespec res, res2;

  printf ("\n-Con clock_getres: \n");
  for (i = 0; clocks[i] != (clockid_t) - 1; i++) {
    int ret;

    ret = clock_getres (clocks[i], &res);
    //nanos = clock_gettime(clocks[i], &res2);
    
    if (ret){
      perror ("clock_getres");
    }else{
      //printf ("con clock_getres: ");
      printf ("clock=%d sec=%ld nsec=%ld\n",
      clocks[i], res.tv_sec, res.tv_nsec);
    }
  }
  
  printf ("\n-Con clock_gettime: \n");
  for (i = 0; clocks[i] != (clockid_t) - 1; i++) {
    int nanos;
    //int ret;

    nanos = clock_gettime(clocks[i], &res2);
    
    if (nanos){
      perror ("clock_gettime");
    }else{
      //printf ("con clock_gettime: ");
      printf ("clock=%d sec=%ld nsec=%ld\n",
      clocks[i], res2.tv_sec, res2.tv_nsec);
    }
  }

}
