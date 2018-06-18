#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "keveat.h"
#include "memory-adapter.h"

int main() {
  keveat_ctx *kv = keveat_init(memory_adapter());
  char *tmpbuf   = malloc( 12 );
  strcpy(tmpbuf,"Hello World");

  if (!kv) {
    printf("Something went wrong...\n");
    return 1;
  }

  // Write test values
  if ( keveat_write( kv, "000", tmpbuf, strlen(tmpbuf)+1) != strlen(tmpbuf)+1 ) {
    printf("Writing did not return the correct written bytes\n");
  }
  if ( keveat_write( kv, "001", tmpbuf, strlen(tmpbuf)+1) != strlen(tmpbuf)+1 ) {
    printf("Writing did not return the correct written bytes\n");
  }
  if ( keveat_write( kv, "002", tmpbuf, strlen(tmpbuf)+1) != strlen(tmpbuf)+1 ) {
    printf("Writing did not return the correct written bytes\n");
  }

  // Read a test key


  keveat_free( kv );
  return 42;
}

#ifdef __cplusplus
} // extern "C"
#endif
