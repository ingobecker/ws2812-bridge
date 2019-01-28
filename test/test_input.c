#include <stdint.h>
#include "unity.h"
#include "input.h"
#include "input/moc.h"

void test_input_driver_select(void)
{
  // TODO: mock input function calls
  input_t moc = input_driver(INPUT_DRIVER_MOC);
  TEST_ASSERT_EQUAL_UINT8(0, moc.data_available());
}
