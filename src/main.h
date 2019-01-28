#ifndef _MAIN_H
#define _MAIN_H

typedef struct bridge_t {
  fifo led_data;
  output_processor output_processor;
  cmd_handler_t cmd_state;
  input_t input;
} bridge_t;

void main_loop(bridge_t *bridge);
#endif
