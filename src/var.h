#ifdef __cplusplus
extern "C" {
#endif

#ifndef _KEVEAT_VAR_H_
#define _KEVEAT_VAR_H_

#include <stdint.h>

#define VAR_UNDEFINED   0
#define VAR_UNDEF       0
#define VAR_NULL        1
#define VAR_BOOLEAN     2
#define VAR_BOOL        2
#define VAR_INT         4
#define VAR_INTEGER     4
#define VAR_FLOAT       8
#define VAR_DOUBLE      8
#define VAR_NUMBER     12
#define VAR_STRING     16
#define VAR_BUFFER     32
#define VAR_VAR        64
#define VAR_FUNCTION  128

typedef struct {
  void *next;
  char *name;
  uint8_t type;
  uint32_t length;
  union {
    uint8_t vbool;      // bool, boolean
    int64_t vint;       // int, integer
    double vfloat;      // float, double
    void *vpoint;       // string, buffer, var
    void (*vfunc)(var*) // function(args)
  };
} var;

#endif // _KEVEAT_VAR_H_

#ifdef __cplusplus
} // extern "C"
#endif
