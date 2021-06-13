#ifndef OLED_1602A_H
#define OLED_1602A_H

void oled_init();


static void oled_cmd(int cmd);


static void oled_data(int data);


void oled_display1(const char * message);


void oled_display2(const char * message);

#endif // OLED_1602A_H