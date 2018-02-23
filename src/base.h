#ifdef __cplusplus
extern "C" {
#endif

#ifndef _KEVEAT_BASE_H_
#define _KEVEAT_BASE_H_

#include "var.h"

#define INIT void __attribute__ ((constructor))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define SHUTDOWN_SUCCESS ((void*)EXIT_SUCCESS)
#define SHUTDOWN_FAILURE ((void*)EXIT_FAILURE)

#endif // _KEVEAT_BASE_H_

#ifdef __cplusplus
} // extern "C"
#endif
