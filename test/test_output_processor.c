#include <stdint.h>
#include "unity.h"
#include "fifo.h"
#include "output_processor.h"

output_processor op;
uint8_t byte;
uint8_t byte_timer_values[] = {
  OUTPUT_PROCESSOR_LED_0, OUTPUT_PROCESSOR_LED_1,
  OUTPUT_PROCESSOR_LED_0, OUTPUT_PROCESSOR_LED_0,
  OUTPUT_PROCESSOR_LED_0, OUTPUT_PROCESSOR_LED_0,
  OUTPUT_PROCESSOR_LED_0, OUTPUT_PROCESSOR_LED_1,
};

void setUp(void)
{
  output_processor_init(&op);
  byte = 0b10000010;
}

void tearDown(void)
{
}

void test_output_processor_generate_timer_values(){
  uint8_t generated_values[8] = { 0 };

  output_processor_generate_timer_values(byte, generated_values);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(byte_timer_values, generated_values, 8);
}

void test_output_processor_write_byte(){
  output_processor_write_byte(&op, byte);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(byte_timer_values, op.buffer, 8);
  TEST_ASSERT_EQUAL_INT(8, op.write_count);

  output_processor_write_byte(&op, byte);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(byte_timer_values, op.buffer + 8, 8);
  TEST_ASSERT_EQUAL_INT(16, op.write_count);
}


void test_output_processor_write_byte_finishes(){
  for(int i=0; i<LED_COUNT * 3; i++){
    TEST_ASSERT_EQUAL_INT(0, op.write_fin);
    output_processor_write_byte(&op, byte);
  }

  TEST_ASSERT_EQUAL_INT(1, op.write_fin);
}

void test_output_processor_buffer_writable_no_write_page_flip(){

  for(int i=0; i<LED_COUNT * 3; i++){
    TEST_ASSERT_EQUAL_INT(1, output_processor_buffer_writable(&op));
    output_processor_write_byte(&op, byte);
  }

  TEST_ASSERT_EQUAL_INT(0, output_processor_buffer_writable(&op));
}

void test_output_processor_buffer_writable_write_page_flip(){
  test_output_processor_buffer_writable_no_write_page_flip();

  TEST_ASSERT_EQUAL_INT(1, op.read_page);

  output_processor_flip_page(&op);
  TEST_ASSERT_EQUAL_INT(0, op.read_page);
  TEST_ASSERT_EQUAL_INT(0, op.write_page);
  TEST_ASSERT_EQUAL_INT(0, op.buffer_underruns);
  TEST_ASSERT_EQUAL_INT(48, op.write_count);

  TEST_ASSERT_EQUAL_INT(1, output_processor_buffer_writable(&op));
  TEST_ASSERT_EQUAL_INT(1, op.write_page);
  TEST_ASSERT_EQUAL_INT(0, op.write_count);
}

void test_output_processor_buffer_underrun(){
  op.read_page = 1;
  output_processor_write_byte(&op, byte);

  output_processor_flip_page(&op);
  TEST_ASSERT_EQUAL_INT(1, op.buffer_underruns);
  TEST_ASSERT_EQUAL_INT(1, op.read_page);
  TEST_ASSERT_EQUAL_INT(0, op.write_page);

  TEST_ASSERT_EQUAL_INT(1, output_processor_buffer_writable(&op));
  TEST_ASSERT_EQUAL_INT(0, op.write_page);
}

void test_output_processor_buffer_underrun_no_writes(){
  test_output_processor_buffer_writable_no_write_page_flip();

  output_processor_flip_page(&op);
  output_processor_flip_page(&op);
  TEST_ASSERT_EQUAL_INT(1, op.buffer_underruns);
}
