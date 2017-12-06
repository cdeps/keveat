#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "base.h"
#include "ev.h"
#include "utc.h"

void exit_after_shutdown( char *name, void *data, void *udata ) {
  exit(0);
}

int main( int argc, char *argv[] ) {

  // First registered = last executed
  ev_on("shutdown", &exit_after_shutdown, NULL);

  // These should be registered through INIT functions
  ev_trigger("start", NULL);

  // Fire the tick event every 100 ms
  // Don't sleep if we're past due
  long int now,reftime = utcm();
  while(1) {
    ev_trigger("tick", NULL);
    now = utcm();
    usleep( MAX( 0, reftime-now ) * 1000 );
    reftime += 100;
  }

  return 0;
}

#ifdef __cplusplus
} // extern "C"
#endif
