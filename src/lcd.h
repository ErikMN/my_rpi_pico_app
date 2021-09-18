#ifndef LDC_H
#define LDC_H

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"

// Modes for lcd_send_byte
#define LCD_CHARACTER 1
#define LCD_COMMAND 0

#define MAX_LINES 2
#define MAX_CHARS 16

void lcd_clear(void);
void lcd_set_cursor(int line, int position);
void lcd_string(const char *s);
void lcd_init(void);

#endif /* LDC_H */
