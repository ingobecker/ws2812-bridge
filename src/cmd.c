#include <stdint.h>
#include "fifo.h"
#include "input.h"
#include "output_processor.h"
#include "cmd.h"
#include "main.h"

cmd_handler_t cmd_buffer_underruns(bridge_t *b, int *locals, uint8_t input_data){
  return_cmd_handler(cmd_main);
}

cmd_handler_t cmd_buffer_available_space(bridge_t *b, int *locals, uint8_t input_data){
  //fifo_free(f); fifo.size - fifo.level
  return_cmd_handler(cmd_main);
}

cmd_handler_t cmd_buffer_write_data_in(bridge_t *b, int *locals, uint8_t input_data){

  fifo_write(&b->led_data, input_data);
  (*locals)--;
  if(*locals == 0){
    // HACK: curly braces needed, due to crappy macro definition
    return_cmd_handler(cmd_main);
  }
  return_cmd_handler(cmd_buffer_write_data_in);
}


cmd_handler_t cmd_buffer_write_main(bridge_t *b, int *locals, uint8_t input_data){

  *locals = input_data;
  return_cmd_handler(cmd_buffer_write_data_in);
}

cmd_handler_t cmd_main(bridge_t *b, int *locals, uint8_t handler_id){
  static cmd_handler_t ha[] = {
    {.handler = cmd_main},
    {.handler = cmd_buffer_available_space},
    {.handler = cmd_buffer_underruns},
    {.handler = cmd_buffer_write_main},
  };

  if(handler_id <= sizeof(ha)/sizeof(cmd_handler_t))
    return ha[handler_id];
  else
    return ha[0];
}
