#ifndef KEYBOARD_H
#define KEYBOARD_H

void handle_keyboard(unsigned char, int, int);
void handle_movement_keys(int, int, int);
void handle_menu_keyboard(unsigned char, int, int);
void handle_menu_special_keyboard(int, int, int);

#endif