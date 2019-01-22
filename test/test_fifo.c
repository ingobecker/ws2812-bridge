#include <stdint.h>
#include "unity.h"
#include "fifo.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_fifo_init() {
  fifo f;
  fifo_init(&f, 2);

  TEST_ASSERT_EQUAL_INT(f.level, 0);
  TEST_ASSERT_EQUAL_INT(f.size, 2);
}

void test_fifo_write() {
  fifo f;
  fifo_init(&f, 2);
  fifo_write(&f, 23);

  TEST_ASSERT_EQUAL_INT(1, f.level);
  TEST_ASSERT_EQUAL_INT(23, f.buffer[0]);
}

void test_fifo_peek() {
  fifo f;
  fifo_init(&f, 2);
  fifo_write(&f, 23);
  fifo_write(&f, 42);

  TEST_ASSERT_EQUAL_INT(2, f.level);
  TEST_ASSERT_EQUAL_INT(23, fifo_peek(&f));
  TEST_ASSERT_EQUAL_INT(2, f.level);
  TEST_ASSERT_EQUAL_INT(23, fifo_peek(&f));
}

void test_fifo_read() {
  fifo f;
  fifo_init(&f, 2);
  fifo_write(&f, 23);
  fifo_write(&f, 42);

  TEST_ASSERT_EQUAL_INT(2, f.level);
  TEST_ASSERT_EQUAL_INT(23, fifo_read(&f));
  TEST_ASSERT_EQUAL_INT(42, fifo_read(&f));
  TEST_ASSERT_EQUAL_INT(0, f.level);
}

void test_fifo_wrap() {
  uint8_t b[] = {5, 42};
  fifo f;
  fifo_init(&f, 2);
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
  fifo f;
  fifo_init(&f, 2);
  fifo_write(&f, 42);

  TEST_ASSERT_EQUAL_INT(0, fifo_full(&f));
  fifo_write(&f, 42);
  TEST_ASSERT_EQUAL_INT(1, fifo_full(&f));
}
