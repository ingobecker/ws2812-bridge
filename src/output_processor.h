#ifndef _OUTPUT_PROCESSOR_H
#define _OUTPUT_PROCESSOR_H

#define OUTPUT_PROCESSOR_PAGE_SIZE    LED_COUNT * 24
#define OUTPUT_PROCESSOR_BUFFER_SIZE  OUTPUT_PROCESSOR_PAGE_SIZE * 2

typedef struct {
  int page_size;
  int read_page;
  int write_page;
  int write_fin;
  int write_count;
  uint8_t *write_p;
  int buffer_underruns;
  uint8_t buffer[OUTPUT_PROCESSOR_BUFFER_SIZE];
} output_processor;

void output_processor_init(output_processor *op);
int output_processor_buffer_writable(output_processor *op);
int output_processor_generate_timer_values(const uint8_t input_byte, uint8_t *timer_values);
void output_processor_write_byte(output_processor *op, uint8_t byte);
void output_processor_flip_page(output_processor *op);

#endif // _OUTPUT_PROCESSOR_H
