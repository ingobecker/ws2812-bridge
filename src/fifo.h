#ifndef _FIFO_H
#define _FIFO_H

typedef struct {
  int read;
  int write;
  int size;
  int level;
  uint8_t buffer[FIFO_SIZE * sizeof(uint8_t)];
} fifo;

int fifo_init(fifo *f);
int fifo_advance(int size, int v);
void fifo_write(fifo *f, uint8_t v);
uint8_t fifo_read(fifo *f);
uint8_t fifo_peek(fifo *f);
uint8_t fifo_full(fifo *f);

#endif // _FIFO_H
