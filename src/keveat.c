#ifdef __cplusplus
extern "C" {
#endif

#include "keveat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

keveat_ctx * keveat_open( int fd ) {

  // Prepare output & check memory
  keveat_ctx *output = calloc( 1, sizeof(keveat_ctx) );
  char *check = malloc( 9 );

  // Fetch first 9 bytes for header check
  fseek( fd, 0, SEEK_SET );
  read( fd, check, 9 );

  // Allow newline after start with "KEVEAT"
  if ( *(check+6) == '\n' ) {
    *(check+6) = '\0';
  }

  // We may skip the first 2 bytes for hard drives (MBR)
  // Make sure the buffer ends in \0 to prevent segfault
  *(check+8) = '\0';

  // Run the actual check
  // Fail = stop right now
  if ( strcmp("KEVEAT", check   ) != 0 &&
       strcmp("KEVEAT", check+2 ) != 0 ) {
    free(check);
    free(output);
    return NULL;
  }

  // We're here so we're good

  // TODO
  // Read metadata
  //   - Header-size   : optional, may be indicated through double line feed '\n'
  //   - Pending       : not given = read-only collection
  //   - Copy-on-write : not given = read-only collection

  output->fd = fd;
  return output;
}



// /**
// * Gracefully shutdown the collection after finishing all requests
// *
// * Enqueues a shutdown to execute & prevents new tasks to be given
// *
// * @param {keveat_ctx*}               ctx       The collection context to work upon
// * @param {function(keveat_event*)*}  callback  The function that will be called once this has completed
// * @param {*}                         udata     Data to pass to the callback
// */
// void keveat_shutdown( keveat_ctx *ctx, void (*callback)(struct keveat_event *), void *udata );

// /**
// * Shutdown the collection NOW
// *
// * Instantly stops the collection without running any tasks. You will lose all
// * data that is in the queue and has not been written yet.
// *
// * @param {keveat_ctx*}  ctx  The collection to shut down
// */
// void keveat_destroy( keveat_ctx *ctx );

#ifdef __cplusplus
} // extern "C"
#endif
