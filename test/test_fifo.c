#include <stdint.h>
#include "unity.h"
#include "fifo.h"

fifo f;

void setUp(void)
{
  fifo_init(&f);
}

void tearDown(void)
{
}

void test_fifo_init() {

  TEST_ASSERT_EQUAL_INT(0, f.level);
  TEST_ASSERT_EQUAL_INT(2, f.size);
}

void test_fifo_write() {
  fifo_write(&f, 23);

  TEST_ASSERT_EQUAL_INT(1, f.level);
  TEST_ASSERT_EQUAL_INT(23, f.buffer[0]);
}

void test_fifo_peek() {
  fifo_write(&f, 23);
  fifo_write(&f, 42);

  TEST_ASSERT_EQUAL_INT(2, f.level);
  TEST_ASSERT_EQUAL_INT(23, fifo_peek(&f));
  TEST_ASSERT_EQUAL_INT(2, f.level);
  TEST_ASSERT_EQUAL_INT(23, fifo_peek(&f));
}

void test_fifo_read() {
  fifo_write(&f, 23);
  fifo_write(&f, 42);

  TEST_ASSERT_EQUAL_INT(2, f.level);
  TEST_ASSERT_EQUAL_INT(23, fifo_read(&f));
  TEST_ASSERT_EQUAL_INT(42, fifo_read(&f));
  TEST_ASSERT_EQUAL_INT(0, f.level);
}

void test_fifo_wrap() {
  uint8_t b[] = {5, 42};
  fifo_write(&f, 23);
  fifo_write(&f, 42);
  
  TEST_ASSERT_EQUAL_INT(f.size, f.level);
  TEST_ASSERT_EQUAL_INT(23, fifo_read(&f));
  TEST_ASSERT_EQUAL_INT(1, f.level);

  fifo_write(&f, 5);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(b, f.buffer, 2);
  TEST_ASSERT_EQUAL_INT(2, f.level);
  TEST_ASSERT_EQUAL_INT(42, fifo_read(&f));
  TEST_ASSERT_EQUAL_INT(5, fifo_read(&f));
  TEST_ASSERT_EQUAL_INT(0, f.level);
}

void test_fifo_full() {
  fifo_write(&f, 42);

  TEST_ASSERT_EQUAL_INT(0, fifo_full(&f));
  fifo_write(&f, 42);
  TEST_ASSERT_EQUAL_INT(1, fifo_full(&f));
}
