#include <stdint.h>
#include "fifo.h"
#include "output_processor.h"

void output_processor_init(output_processor *op) {
  op->read_page = 1;
  op->write_page = 0;
  op->write_count = 0;
  op->write_fin = 0;
  op->write_p = op->buffer;
  op->page_size = OUTPUT_PROCESSOR_PAGE_SIZE;
  op->buffer_underruns = 0;
}

int output_processor_generate_timer_values(const uint8_t input_byte, uint8_t *timer_values) {
  int bit_mask = 1;
  for(int i=0; i<8; i++){
    if(input_byte & bit_mask)
      timer_values[i] = OUTPUT_PROCESSOR_LED_1;
    else
      timer_values[i] = OUTPUT_PROCESSOR_LED_0;
    bit_mask <<= 1;
  }
}

int output_processor_buffer_writable(output_processor *op){
  if(op->write_fin){
    if(op->write_page == op->read_page){
      op->write_fin = 0;
      op->write_count = 0;
      op->write_page = ~op->write_page & 1;
      op->write_p = op->buffer + (op->page_size * op->write_page);
      return 1;
    }
    else
      return 0;
  }
  return 1;
}

void output_processor_write_byte(output_processor *op, uint8_t byte){
  output_processor_generate_timer_values(byte, op->write_p + op->write_count);
  op->write_count += 8;

  if(op->write_count == op->page_size)
    op->write_fin = 1;
}

void output_processor_flip_page(output_processor *op){
  if(op->write_fin && op->write_page != op->read_page){
    op->read_page = ~op->read_page & 1;
  }
  else
    op->buffer_underruns++;
}
