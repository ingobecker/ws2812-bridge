#ifndef _INPUT_H
#define _INPUT_H
typedef struct {
  uint8_t (*data_available)();
  uint8_t (*read_byte)();
  void (*write_byte)(uint8_t);
} input_t;

typedef enum {
  INPUT_DRIVER_MOC,
  INPUT_DRIVER_SERIAL,
} input_driver_type_t;

input_t input_driver(input_driver_type_t driver_id);

#endif // _INPUT_H
