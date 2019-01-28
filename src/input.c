#include <stdint.h>
#include "input.h"
#include "input/moc.h"

input_t input_driver(input_driver_type_t driver_id){

  static input_t input_drivers[] = {
    {.data_available = moc_data_available,
    .read_byte = moc_read_byte,
    .write_byte = moc_write_byte},
  };

  return input_drivers[driver_id];

}
