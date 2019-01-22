#include <stdlib.h>
#include <stdint.h>
#include "fifo.h"

int fifo_init(fifo *f, int size) {
  f->read = 0;
  f->write = 0;
  f->size = size;
  f->level = 0;
  f->buffer = malloc(size * sizeof(uint8_t));
  return 0;
}

int fifo_advance(int size, int v) {
  v++;
  if(v == size)
    return 0;
  else
    return v;
}

void fifo_write(fifo *f, uint8_t v) {
  if(f->level < f->size) {
    f->buffer[f->write] = v;
    f->write = fifo_advance(f->size, f->write);
    f->level++;
  }
}

uint8_t fifo_read(fifo *f){
  uint8_t r;
  if(f->level){
    r = f->buffer[f->read];
    f->read = fifo_advance(f->size, f->read);
    f->level--;
  }
  return r;
}

uint8_t fifo_peek(fifo *f){
  return f->buffer[f->read];
}

uint8_t fifo_full(fifo *f) {
  return f->level == f->size;
}
