#include <stdint.h>
#include "unity.h"
#include "fifo.h"
#include "input/moc.h"
#include "input.h"
#include "output_processor.h"
#include "cmd.h"
#include "main.h"

bridge_t br;

void setUp(void)
{
  fifo_init(&br.led_data);
  output_processor_init(&br.output_processor);
  br.cmd_state.handler = cmd_main;
  br.input = input_driver(0);
}

void test_main(){

  uint8_t cmd_data[] = {
    0,
    0,
    0,
    0,
  };

  input_moc_init(cmd_data, 4);

  TEST_ASSERT(br.cmd_state.handler == cmd_main);
  main_loop(&br);
  TEST_ASSERT(br.cmd_state.handler == cmd_main);
}

void test_main_loop_data_from_input_to_output(){

  uint8_t byte = 0b10000010;
  uint8_t byte_timer_values[] = {
    OUTPUT_PROCESSOR_LED_0, OUTPUT_PROCESSOR_LED_1,
    OUTPUT_PROCESSOR_LED_0, OUTPUT_PROCESSOR_LED_0,
    OUTPUT_PROCESSOR_LED_0, OUTPUT_PROCESSOR_LED_0,
    OUTPUT_PROCESSOR_LED_0, OUTPUT_PROCESSOR_LED_1,
  };
  
  uint8_t cmd_data[] = {
    3, // write into buffer
    1, // write one byte
    byte
  };
  input_moc_init(cmd_data, 3);

  TEST_ASSERT_EQUAL_UINT8(0, br.led_data.level);
  TEST_ASSERT(br.cmd_state.handler == cmd_main);
  main_loop(&br);
  TEST_ASSERT(br.cmd_state.handler == cmd_buffer_write_main);
  main_loop(&br);
  TEST_ASSERT(br.cmd_state.handler == cmd_buffer_write_data_in);
  main_loop(&br);
  TEST_ASSERT(br.cmd_state.handler == cmd_main);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(byte_timer_values, br.output_processor.buffer, 8);
}
