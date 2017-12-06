#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "base.h"
#include "utc.h"

int main( int argc, char *argv[] ) {
  printf("%lld\n",utcm());
  return 42;
}

#ifdef __cplusplus
} // extern "C"
#endif
