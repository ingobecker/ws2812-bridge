#ifndef _CMD_H
#define _CMD_H

#define return_cmd_handler(cmd_name)   cmd_handler_t r = {.handler = cmd_name}; return r

// TODO: is there a better approach for cyclic deps?
//       are there side effects?
typedef struct bridge_t bridge_t;

typedef struct cmd_handler {
  struct cmd_handler (*handler)(bridge_t *, int *, uint8_t);
} cmd_handler_t;

cmd_handler_t cmd_main(bridge_t *b, int *, uint8_t);
cmd_handler_t cmd_buffer_underruns(bridge_t *b, int *, uint8_t);
cmd_handler_t cmd_buffer_underruns(bridge_t *b, int *, uint8_t);
cmd_handler_t cmd_buffer_write_main(bridge_t *b, int *, uint8_t);
cmd_handler_t cmd_buffer_write_data_in(bridge_t *b, int *, uint8_t);

#endif // _CMD_H
