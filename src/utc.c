#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <time.h>

#include "utc.h"

long long utc() {
  return utcm() / 1000;
}

long long utcm() {
  long long result;
  struct timespec spec;
  clock_gettime(CLOCK_REALTIME, &spec);
  result = spec.tv_sec * 1000;
  result += round(spec.tv_nsec / 1.0e6);
  return result;
}

#ifdef __cplusplus
} // extern "C"
#endif
