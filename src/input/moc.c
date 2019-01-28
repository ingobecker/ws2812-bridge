#include <stdint.h>
#include "fifo.h"
#include "moc.h"

struct input_moc_data{
  uint8_t *data;
  uint8_t cnt;
  uint8_t read_idx;
};

struct input_moc_data imd;

void input_moc_init(uint8_t *data, uint8_t cnt){
  imd.data = data;
  imd.cnt = cnt;
  imd.read_idx = 0;
}

uint8_t moc_data_available(){
  return imd.read_idx < imd.cnt;
}

uint8_t moc_read_byte(){
  return imd.data[imd.read_idx++];
}

void moc_write_byte(uint8_t byte){
}
