#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>

#include "keveat.h"
#include "memory-adapter.h"

int main() {
  printf("MAIN START\n");

  keveat_ctx *kv = keveat_init(memory_adapter());
  if (!kv) {
    printf("Something went wrong...\n");
    return 1;
  }
  printf("%du\n", kv->recsize);

  return 42;
}

#ifdef __cplusplus
} // extern "C"
#endif
