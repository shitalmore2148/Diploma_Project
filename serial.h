#ifndef SERIAL_H
#define SERIAL_H 1

serial_init();
void transmit(unsigned char value);
void transmit_str (unsigned char *senpoint);
unsigned char rx();
#endif