#ifdef __cplusplus
extern "C" {
#endif

#ifndef _KEVEAT_TEST_MEMORY_ADAPTER_H_
#define _KEVEAT_TEST_MEMORY_ADAPTER_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#include "keveat.h"

char *kv_memory_data    = 0;
keveat_adapter *adapter = 0;
uint64_t size           = 512*1024*1024; // 512 MiB

int64_t kv_memory_read( int64_t position, int64_t length, void *buffer, void *udata ) {
  printf("READ:\n  POS: %d\n  LEN: %d\n\n", position, length);
  if ( position+length >= size ) { length = size - position; }
  memcpy( buffer, kv_memory_data + position, length );
  return length;
}

int64_t kv_memory_write( int64_t position, int64_t length, void *buffer, void *udata ) {
  printf("WRITE:\n  POS: %d\n  LEN: %d\n\n", position, length);
  if ( position+length >= size ) { length = size - position; }
  memcpy( kv_memory_data + position, buffer, length );
  return length;
}

keveat_stat * kv_memory_stat( void *udata ) {
  keveat_stat *stat = calloc(1,sizeof(keveat_stat));
  stat->size  = size;
  stat->flags = KEVEAT_FLAG_STAT_FREE | KEVEAT_FLAG_ADAPTER_FREE; // Instructions for keveat on how to free us
  return stat;
}

void kv_memory_close( void *udata ) {

}

keveat_adapter * memory_adapter() {
  if ( !kv_memory_data ) {
    kv_memory_data = calloc( 1, size );
    *(kv_memory_data+0) = 0;   // Intentionally left blank, allows jmps when used on a drive
    *(kv_memory_data+1) = 0;
    *(kv_memory_data+2) = 'K'; // Signature
    *(kv_memory_data+3) = 'E'; //   Indicates the medium is keveat-compatible
    *(kv_memory_data+4) = 'V'; //   null-terminated to allow strcmp check
    *(kv_memory_data+5) = 'E';
    *(kv_memory_data+6) = 'A';
    *(kv_memory_data+7) = 'T';
    *(kv_memory_data+8) = 0;
    *(kv_memory_data+9) = 5; // 512 << 5 = 16 KiB per record
  }
  if ( !adapter ) {
    adapter           = calloc(1,sizeof(keveat_adapter));
    adapter->read     = &kv_memory_read;
    adapter->write    = &kv_memory_write;
    adapter->stat     = &kv_memory_stat;
  }
  return adapter;
}

#endif // _KEVEAT_TEST_MEMORY_ADAPTER_H_

#ifdef __cplusplus
} // extern "C"
#endif
