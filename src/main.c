#include <stdint.h>
#include "fifo.h"
#include "input.h"
#include "output_processor.h"
#include "cmd.h"
#include "main.h"

void main_loop(bridge_t *bridge){

  // TODO handle input
  if(bridge->input.data_available()){
    uint8_t input_byte = bridge->input.read_byte();
    int locals;
    bridge->cmd_state = bridge->cmd_state.handler(bridge, &locals, input_byte);
  }

  // process frames
  if(output_processor_buffer_writable(&bridge->output_processor) &&
      bridge->led_data.level){
    output_processor_write_byte(&bridge->output_processor,
        fifo_read(&bridge->led_data));
  }
}

#ifndef TEST
int main(){

  bridge_t br;

  fifo_init(&br.led_data);
  output_processor_init(&br.output_processor);
  br.cmd_state.handler = cmd_main;

  while(1){
    main_loop(&br);
  }

  return 0;
}
#endif
