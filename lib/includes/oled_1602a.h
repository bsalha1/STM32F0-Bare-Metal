#ifndef OLED_1602A_H
#define OLED_1602A_H


#define CHARACTERS_PER_LINE 16
#define NUM_LINES 2

enum entry_mode {
	ENTRY_MODE_AUTO_INCREMENT,
	ENTRY_MODE_AUTO_DECREMENT
};

enum display_type {
	DISPLAY_TYPE_CURSOR,
	DISPLAY_TYPE_SCREEN
};

enum direction {
	DIRECTION_LEFT,
	DIRECTION_RIGHT
};

void oled_init();

static void oled_cmd(uint8_t cmd);

static void oled_data(uint16_t data);

void oled_display1(const char * message);

void oled_display2(const char * message);

void oled_clear_display();

void oled_return_home();

void oled_entry_mode_set(enum entry_mode mode, bool shift_display);

void oled_display_control(bool display_on, bool cursor_on, bool blinking_cursor);

void oled_display_shift(enum display_type display_type, enum direction direction);

void oled_set_ddram_address(uint8_t address);

void oled_clear_display1();

void oled_clear_display2();

void oled_putchar_offset(char character, uint8_t offset);

void oled_putchar(char character);

void oled_puts(char* string);

void oled_printf(char* format,...);

#endif // OLED_1602A_H