#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include "base.h"
#include "ev.h"
#include "utc.h"

void exit_after_shutdown( char *name, void *data, void *udata ) {
  if ( data == NULL ) {
    exit(0);
  }
  exit((int)data);
}

// Shutdown gracefully
void catchSigint( int sig ) {
  signal(sig, SIG_IGN);
  printf("\nShutting down\n");
  ev_trigger( "shutdown", NULL );
}

int main( int argc, char *argv[] ) {

  // First registered = last executed
  ev_on("shutdown", &exit_after_shutdown, NULL);

  // Catch ^C for a graceful shutdown
  signal( SIGINT, catchSigint );

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
