#ifdef __cplusplus
extern "C" {
#endif

#ifndef H_BASE
#define H_BASE

#define INIT void __attribute__ ((constructor))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#endif // H_BASE

#ifdef __cplusplus
} // extern "C"
#endif
