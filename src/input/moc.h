#ifndef _MOC_H
#define _MOC_H

uint8_t moc_data_available();
uint8_t moc_read_byte();
void moc_write_byte(uint8_t byte);
void input_moc_init(uint8_t *data, uint8_t cnt);

#endif // _MOC_H
