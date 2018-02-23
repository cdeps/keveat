#ifdef __cplusplius
extern "C" {
#endif

#include "base.h"

int main() {

  var test  = { .type=VAR_INT };
  test.vint = 42;

  return test.vint;
}

#ifdef __cplusplius
} // extern "C"
#endif
